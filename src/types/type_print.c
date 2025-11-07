#include <stdio.h>
#include <string.h>
#include "type_print.h"
#include "utils.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

void print_type_signature(Type *type, int depth) {
    if (!type) { printf("NULL"); return; }
    switch (type->kind) {
        case TY_NAMED:
            if (type->u.named.name_rec && type->u.named.name_rec->key) {
                const char *name = (const char*)((Slice*)type->u.named.name_rec->key)->ptr;
                printf("%s", name);
            } else {
                printf("unnamed");
            }
            break;
        case TY_PTR:
            print_type_signature(type->u.ptr.target, depth + 1);
            printf("*");
            break;
        case TY_ARRAY:
            print_type_signature(type->u.array.elem, depth + 1);
            if (type->u.array.size_known) printf("[%lld]", (long long)type->u.array.size);
            else printf("[]");
            break;
        case TY_FUNC:
            printf("(");
            for (size_t i = 0; i < type->u.func.param_count; i++) {
                if (i > 0) printf(", ");
                print_type_signature(type->u.func.params[i], depth + 1);
            }
            printf(") -> ");
            print_type_signature(type->u.func.ret, depth + 1);
            break;
        default:
            printf("unknown(%d)", type->kind);
            break;
    }
}

void print_type_category_colored(Type *type) {
    if (!type) { printf(RED "(null)" RESET); return; }
    switch (type->kind) {
        case TY_NAMED: {
            if (type->u.named.name_rec && type->u.named.name_rec->key) {
                Slice *name_slice = (Slice*)type->u.named.name_rec->key;
                if (name_slice->ptr && name_slice->len > 0) {
                    if ((name_slice->len == 3 && strncmp((char*)name_slice->ptr, "i32", 3) == 0) ||
                        (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "i64", 3) == 0) ||
                        (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "f32", 3) == 0) ||
                        (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "f64", 3) == 0) ||
                        (name_slice->len == 4 && strncmp((char*)name_slice->ptr, "bool", 4) == 0) ||
                        (name_slice->len == 4 && strncmp((char*)name_slice->ptr, "char", 4) == 0) ||
                        (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "str", 3) == 0)) {
                        printf(BLUE "(primitive)" RESET);
                    } else {
                        printf(YELLOW "(named)" RESET);
                    }
                } else {
                    printf(YELLOW "(named)" RESET);
                }
            } else {
                printf(YELLOW "(named)" RESET);
            }
            break;
        }
        case TY_PTR:    printf(GREEN "(pointer)" RESET); break;
        case TY_ARRAY:  printf(MAGENTA "(array)" RESET); break;
        case TY_FUNC:   printf(CYAN "(function)" RESET); break;
        default:        printf(RED "(unknown)" RESET); break;
    }
}
