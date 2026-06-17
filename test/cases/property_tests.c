#include "../harness/test_harness.h"
#include "parsing/parse_expressions.h"
#include "parsing/parse_declarations.h"
#include "sema/type.h"
#include "sema/type_coerce.h"
#include "sema/type_utils.h"
#include "lexing/lexer.h"
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

// --- Helper Functions ---

static const char* get_token_repr(TokenKind kind) {
    switch (kind) {
        case TOK_FN: return "fn";
        case TOK_IF: return "if";
        case TOK_ELSE: return "else";
        case TOK_WHILE: return "while";
        case TOK_FOR: return "for";
        case TOK_RETURN: return "return";
        case TOK_BREAK: return "break";
        case TOK_CONTINUE: return "continue";
        case TOK_CONST: return "const";
        case TOK_PUB: return "pub";
        case TOK_IMPORT: return "import";
        case TOK_ALIAS: return "alias";
        case TOK_DEFER: return "defer";
        case TOK_I32: return "i32";
        case TOK_I64: return "i64";
        case TOK_F32: return "f32";
        case TOK_F64: return "f64";
        case TOK_BOOL: return "bool";
        case TOK_STRING: return "str";
        case TOK_VOID: return "void";
        case TOK_PLUS: return "+";
        case TOK_MINUS: return "-";
        case TOK_STAR: return "*";
        case TOK_SLASH: return "/";
        case TOK_PERCENT: return "%";
        case TOK_EQ_EQ: return "==";
        case TOK_BANG_EQ: return "!=";
        case TOK_LT_EQ: return "<=";
        case TOK_GT_EQ: return ">=";
        case TOK_AND_AND: return "&&";
        case TOK_OR_OR: return "||";
        case TOK_ASSIGN: return "=";
        case TOK_LT: return "<";
        case TOK_GT: return ">";
        case TOK_LPAREN: return "(";
        case TOK_RPAREN: return ")";
        case TOK_LBRACE: return "{";
        case TOK_RBRACE: return "}";
        case TOK_LBRACKET: return "[";
        case TOK_RBRACKET: return "]";
        case TOK_COMMA: return ",";
        case TOK_SEMICOLON: return ";";
        case TOK_COLON: return ":";
        case TOK_DOT: return ".";
        case TOK_STRUCT: return "struct";
        case TOK_AS: return "as";
        case TOK_TRUE: return "true";
        case TOK_FALSE: return "false";
        case TOK_NULL: return "null";
        case TOK_IDENTIFIER: return "my_var_123";
        case TOK_INT_LIT: return "12345";
        case TOK_FLOAT_LIT: return "12.34";
        case TOK_STRING_LIT: return "\"hello world\"";
        default: return NULL;
    }
}

// Generates a random primitive, biased towards integers to test widening
static Type* get_random_primitive(TypeStore *ts) {
    Type* primitives[] = {
        ts->t_i8, ts->t_i16, ts->t_i32, ts->t_i64,
        ts->t_u8, ts->t_u16, ts->t_u32, ts->t_u64,
        ts->t_f32, ts->t_f64,
        ts->t_bool, ts->t_char
    };
    return primitives[rand() % 12];
}

// Given an integer primitive, returns a valid implicit wider type (or the same type)
static Type* get_wider_primitive(TypeStore *ts, Type* base) {
    if (base == ts->t_i8)  return (rand() % 2) ? ts->t_i16 : ts->t_i32;
    if (base == ts->t_i16) return (rand() % 2) ? ts->t_i32 : ts->t_i64;
    if (base == ts->t_i32) return ts->t_i64;
    
    if (base == ts->t_u8)  return (rand() % 2) ? ts->t_u16 : ts->t_u32;
    if (base == ts->t_u16) return (rand() % 2) ? ts->t_u32 : ts->t_u64;
    if (base == ts->t_u32) return ts->t_u64;

    if (base == ts->t_f32) return ts->t_f64;

    return base; // Fallback
}

static Type* get_random_type(TypeStore *ts, int depth) {
    if (depth > 2 || (rand() % 5 == 0)) return get_random_primitive(ts);

    int kind = rand() % 3;
    if (kind == 0) {
        Type *base = get_random_type(ts, depth + 1);
        Type proto = { .kind = TYPE_POINTER, .as.ptr.base = base };
        return (Type*)((Slice*)intern_type(ts, &proto)->key)->ptr;
    } else if (kind == 1) {
        Type *base = get_random_type(ts, depth + 1);
        Type proto = { .kind = TYPE_ARRAY, .as.array.base = base, .as.array.size = rand() % 100 + 1 };
        return (Type*)((Slice*)intern_type(ts, &proto)->key)->ptr;
    } else {
        Type *base = get_random_type(ts, depth + 1);
        Type proto = { .kind = TYPE_SLICE, .as.slice.base = base };
        return (Type*)((Slice*)intern_type(ts, &proto)->key)->ptr;
    }
}

// Safer underscore generation: never consecutive, never leading/trailing digits
static void int_to_string_with_underscores(unsigned long long uval, int base, char *buf) {
    char tmp[128];
    int i = 0;
    
    if (uval == 0) {
        strcpy(buf, "0");
        return;
    }

    bool last_was_underscore = false;
    while (uval > 0) {
        // Insert underscore randomly, but ensure it's not consecutive and not the very first character added
        if (i > 0 && !last_was_underscore && (rand() % 4 == 0) && (uval / base > 0)) {
            tmp[i++] = '_';
            last_was_underscore = true;
        } else {
            int digit = uval % base;
            if (digit < 10) tmp[i++] = '0' + digit;
            else tmp[i++] = 'a' + (digit - 10);
            uval /= base;
            last_was_underscore = false;
        }
    }

    int j = 0;
    if (base == 16) { buf[j++] = '0'; buf[j++] = 'x'; }
    else if (base == 2) { buf[j++] = '0'; buf[j++] = 'b'; }

    for (int k = i - 1; k >= 0; k--) {
        buf[j++] = tmp[k];
    }
    buf[j] = '\0';
}

// --- Lexer Tests ---

PROPERTY_CASE_PRIO("Lexer/Property: Token Round-trip", 1000, 10) {
    Arena *arena = arena_create(1024 * 1024);
    char source[8192] = {0}; // Increased size
    TokenKind expected_kinds[200];
    int token_count = 10 + (rand() % 80); // Test slightly larger chunks
    
    int pos = 0;
    int actual_token_count = 0;
    for (int i = 0; i < token_count; i++) {
        TokenKind k;
        const char *repr = NULL;
        while (!repr) {
            k = (TokenKind)(rand() % TOK_UNKNOWN);
            if (k == TOK_EOF || k == TOK_COMMENT || k == TOK_UNKNOWN) continue;
            repr = get_token_repr(k);
        }
        
        int len = snprintf(source + pos, sizeof(source) - pos, "%s ", repr);
        if (len < 0 || (size_t)len >= sizeof(source) - pos) break; 
        
        expected_kinds[actual_token_count++] = k;
        pos += len;
    }
    token_count = actual_token_count;

    Lexer *l = lexer_create(source, pos, arena);
    if (!lexer_lex_all(l)) {
        test_log("      Lexing failed for: %s\n", source);
        arena_destroy(arena);
        return 0;
    }

    size_t count;
    Token *tokens = lexer_get_tokens(l, &count);
    
    if (count != (size_t)(token_count + 1)) {
        test_log("      Token count mismatch: expected %d, got %zu\n", token_count + 1, count);
        test_log("      Source: %s\n", source);

        // --- DEBUG LOOP ---
        test_log("      Lexed Token Kinds: ");
        for(size_t j = 0; j < count; j++) {
            test_log("%d ", tokens[j].type);
        }
        test_log("\n");
        // ------------------

        arena_destroy(arena);
        return 0;
    }

    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type != expected_kinds[i]) {
            test_log("      Token mismatch at %d: expected %d, got %d\n", i, expected_kinds[i], tokens[i].type);
            arena_destroy(arena);
            return 0;
        }
    }

    arena_destroy(arena);
    return 1;
}

// --- Sema Tests ---

PROPERTY_CASE_PRIO("Sema/Property: Type Coercion Transitivity", 1000, 30) {
    Arena *arena = arena_create(1024 * 1024);
    TypeStore *ts = typestore_create(arena, NULL, NULL);

    Type *a, *b, *c;
    
    if (rand() % 2 == 0) {
        a = get_random_primitive(ts);
        b = get_wider_primitive(ts, a);
        c = get_wider_primitive(ts, b);
    } else {
        a = get_random_type(ts, 0);
        b = get_random_type(ts, 0);
        c = get_random_type(ts, 0);
    }

    if (type_can_implicit_cast(b, a) && type_can_implicit_cast(c, b)) {
        if (!type_can_implicit_cast(c, a)) {
            test_log("      Transitivity failure: A -> B and B -> C, but NOT A -> C\n");
            arena_destroy(arena);
            return 0;
        }
    }

    arena_destroy(arena);
    return 1;
}

PROPERTY_CASE_PRIO("Sema/Property: Explicit Cast is Superset of Implicit", 1000, 30) {
    Arena *arena = arena_create(1024 * 1024);
    TypeStore *ts = typestore_create(arena, NULL, NULL);

    Type *src, *dst;
    
    // Bias generator to ensure we frequently test valid implicit casts
    if (rand() % 2 == 0) {
        src = get_random_primitive(ts);
        dst = get_wider_primitive(ts, src);
    } else {
        src = get_random_type(ts, 0);
        dst = get_random_type(ts, 0);
    }

    if (type_can_implicit_cast(dst, src)) {
        if (!type_can_explicit_cast(dst, src)) {
            test_log("      Inconsistency: Implicit cast allowed, but explicit forbidden.\n");
            arena_destroy(arena);
            return 0;
        }
    }

    arena_destroy(arena);
    return 1;
}

PROPERTY_CASE_PRIO("Sema/Property: Array to Slice Decay", 1000, 30) {
    Arena *arena = arena_create(1024 * 1024);
    TypeStore *ts = typestore_create(arena, NULL, NULL);

    Type *base = get_random_type(ts, 0);
    
    Type arr_proto = { .kind = TYPE_ARRAY, .as.array.base = base, .as.array.size = rand() % 100 + 1 };
    Type *arr_type = (Type*)((Slice*)intern_type(ts, &arr_proto)->key)->ptr;

    Type slice_proto = { .kind = TYPE_SLICE, .as.slice.base = base };
    Type *slice_type = (Type*)((Slice*)intern_type(ts, &slice_proto)->key)->ptr;

    if (!type_can_implicit_cast(slice_type, arr_type)) {
        test_log("      Failure: Array T[N] failed to decay to slice T[]\n");
        arena_destroy(arena);
        return 0;
    }

    arena_destroy(arena);
    return 1;
}

// --- Parser Tests ---

PROPERTY_CASE_PRIO("Parser/Property: Integer Literal Round-trip", 1000, 20) {
    unsigned long long original;
    
    // Inject boundary values frequently to catch overflow/underflow bugs
    int mode = rand() % 10;
    if (mode == 0) original = 0;
    else if (mode == 1) original = 0xFFFFFFFFFFFFFFFFULL; 
    else if (mode == 2) original = 0x7FFFFFFFFFFFFFFFULL; // INT64_MAX
    else {
        // Random 64-bit unsigned
        original = ((unsigned long long)rand() << 32) | rand();
    }

    int bases[] = {2, 10, 16};
    int base = bases[rand() % 3];

    char buf[256];
    int_to_string_with_underscores(original, base, buf);

    unsigned long long parsed;
    bool success = parse_int_lit(buf, strlen(buf), &parsed);

    if (!success) {
        test_log("      Failed to parse: %s (base %d)\n", buf, base);
        return 0;
    }

    if (parsed != original) {
        test_log("      Mismatch for %s: expected %llu, got %llu (base %d)\n", buf, original, parsed, base);
        return 0;
    }

    return 1;
}