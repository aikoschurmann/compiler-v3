

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;
typedef long __darwin_intptr_t;
typedef unsigned int __darwin_natural_t;
typedef int __darwin_ct_rune_t;
typedef union {
 char __mbstate8[128];
 long long _mbstateL;
} __mbstate_t;
typedef __mbstate_t __darwin_mbstate_t;
typedef long int __darwin_ptrdiff_t;
typedef long unsigned int __darwin_size_t;
typedef __builtin_va_list __darwin_va_list;
typedef int __darwin_wchar_t;
typedef __darwin_wchar_t __darwin_rune_t;
typedef int __darwin_wint_t;
typedef unsigned long __darwin_clock_t;
typedef __uint32_t __darwin_socklen_t;
typedef long __darwin_ssize_t;
typedef long __darwin_time_t;
typedef __int64_t __darwin_blkcnt_t;
typedef __int32_t __darwin_blksize_t;
typedef __int32_t __darwin_dev_t;
typedef unsigned int __darwin_fsblkcnt_t;
typedef unsigned int __darwin_fsfilcnt_t;
typedef __uint32_t __darwin_gid_t;
typedef __uint32_t __darwin_id_t;
typedef __uint64_t __darwin_ino64_t;
typedef __darwin_ino64_t __darwin_ino_t;
typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t __darwin_mode_t;
typedef __int64_t __darwin_off_t;
typedef __int32_t __darwin_pid_t;
typedef __uint32_t __darwin_sigset_t;
typedef __int32_t __darwin_suseconds_t;
typedef __uint32_t __darwin_uid_t;
typedef __uint32_t __darwin_useconds_t;
typedef unsigned char __darwin_uuid_t[16];
typedef char __darwin_uuid_string_t[37];
struct __darwin_pthread_handler_rec {
 void (*__routine)(void *);
 void *__arg;
 struct __darwin_pthread_handler_rec *__next;
};
struct _opaque_pthread_attr_t {
 long __sig;
 char __opaque[56];
};
struct _opaque_pthread_cond_t {
 long __sig;
 char __opaque[40];
};
struct _opaque_pthread_condattr_t {
 long __sig;
 char __opaque[8];
};
struct _opaque_pthread_mutex_t {
 long __sig;
 char __opaque[56];
};
struct _opaque_pthread_mutexattr_t {
 long __sig;
 char __opaque[8];
};
struct _opaque_pthread_once_t {
 long __sig;
 char __opaque[8];
};
struct _opaque_pthread_rwlock_t {
 long __sig;
 char __opaque[192];
};
struct _opaque_pthread_rwlockattr_t {
 long __sig;
 char __opaque[16];
};
struct _opaque_pthread_t {
 long __sig;
 struct __darwin_pthread_handler_rec *__cleanup_stack;
 char __opaque[8176];
};
typedef struct _opaque_pthread_attr_t __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t *__darwin_pthread_t;
typedef int __darwin_nl_item;
typedef int __darwin_wctrans_t;
typedef __uint32_t __darwin_wctype_t;
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;
typedef int64_t register_t;
typedef __darwin_intptr_t intptr_t;
typedef unsigned long uintptr_t;
typedef u_int64_t user_addr_t;
typedef u_int64_t user_size_t;
typedef int64_t user_ssize_t;
typedef int64_t user_long_t;
typedef u_int64_t user_ulong_t;
typedef int64_t user_time_t;
typedef int64_t user_off_t;
typedef u_int64_t syscall_arg_t;
typedef __darwin_va_list va_list;
typedef __darwin_size_t size_t;

int renameat(int, const char *, int, const char *) __attribute__((availability(macosx,introduced=10.10)));
int renamex_np(const char *, const char *, unsigned int) __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0)));
int renameatx_np(int, const char *, int, const char *, unsigned int) __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0)));
int printf(const char * restrict, ...) __attribute__((__format__ (__printf__, 1, 2)));
typedef __darwin_off_t fpos_t;
struct __sbuf {
 unsigned char * _base;
 int _size;
};
struct __sFILEX;
typedef struct __sFILE {
 unsigned char * _p;
 int _r;
 int _w;
 short _flags;
 short _file;
 struct __sbuf _bf;
 int _lbfsize;
 void *_cookie;
 int (* _Nullable _close)(void *);
 int (* _Nullable _read) (void *, char *, int __n);
 fpos_t (* _Nullable _seek) (void *, fpos_t, int);
 int (* _Nullable _write)(void *, const char *, int __n);
 struct __sbuf _ub;
 struct __sFILEX *_extra;
 int _ur;
 unsigned char _ubuf[3];
 unsigned char _nbuf[1];
 struct __sbuf _lb;
 int _blksize;
 fpos_t _offset;
} FILE;
extern FILE *__stdinp __attribute__((__swift_attr__("nonisolated(unsafe)")));
extern FILE *__stdoutp __attribute__((__swift_attr__("nonisolated(unsafe)")));
extern FILE *__stderrp __attribute__((__swift_attr__("nonisolated(unsafe)")));
void clearerr(FILE *);
int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);
int fgetpos(FILE * restrict, fpos_t *);
char * fgets(char * restrict , int __size, FILE *);
FILE *fopen(const char * restrict __filename, const char * restrict __mode) __asm("_" "fopen" );
int fprintf(FILE * restrict, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3)));
int fputc(int, FILE *);
int fputs(const char * restrict, FILE * restrict) __asm("_" "fputs" );
size_t fread(void * restrict __ptr, size_t __size, size_t __nitems, FILE * restrict __stream);
FILE *freopen(const char * restrict, const char * restrict,
     FILE * restrict) __asm("_" "freopen" );
int fscanf(FILE * restrict, const char * restrict, ...) __attribute__((__format__ (__scanf__, 2, 3)));
int fseek(FILE *, long, int);
int fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
size_t fwrite(const void * restrict __ptr, size_t __size, size_t __nitems, FILE * restrict __stream) __asm("_" "fwrite" );
int getc(FILE *);
int getchar(void);
__attribute__((__deprecated__("This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of gets(3), it is highly recommended that you use fgets(3) instead.")))
char * gets(char *) ;
void perror(const char *) __attribute__((__cold__));
int putc(int, FILE *);
int putchar(int);
int puts(const char *);
int remove(const char *);
int rename (const char *__old, const char *__new);
void rewind(FILE *);
int scanf(const char * restrict, ...) __attribute__((__format__ (__scanf__, 1, 2)));
void setbuf(FILE * restrict, char * restrict );
int setvbuf(FILE * restrict, char * restrict , int, size_t __size);
__attribute__((__availability__(swift, unavailable, message="Use snprintf instead.")))
__attribute__((__deprecated__("This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of sprintf(3), it is highly recommended that you use snprintf(3) instead.")))
int sprintf(char * restrict , const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3))) ;
int sscanf(const char * restrict, const char * restrict, ...) __attribute__((__format__ (__scanf__, 2, 3)));
FILE *tmpfile(void);
__attribute__((__availability__(swift, unavailable, message="Use mkstemp(3) instead.")))
__attribute__((__deprecated__("This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of tmpnam(3), it is highly recommended that you use mkstemp(3) instead.")))
char * tmpnam(char *);
int ungetc(int, FILE *);
int vfprintf(FILE * restrict, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0)));
int vprintf(const char * restrict, va_list) __attribute__((__format__ (__printf__, 1, 0)));
__attribute__((__availability__(swift, unavailable, message="Use vsnprintf instead.")))
__attribute__((__deprecated__("This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of sprintf(3), it is highly recommended that you use vsnprintf(3) instead.")))
int vsprintf(char * restrict , const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0))) ;
char * ctermid(char *);
FILE *fdopen(int, const char *) __asm("_" "fdopen" );
int fileno(FILE *);
int pclose(FILE *) __attribute__((__availability__(swift, unavailable, message="Use posix_spawn APIs or NSTask instead. (On iOS, process spawning is unavailable.)")));
FILE *popen(const char *, const char *) __asm("_" "popen" ) __attribute__((__availability__(swift, unavailable, message="Use posix_spawn APIs or NSTask instead. (On iOS, process spawning is unavailable.)")));
int __srget(FILE *);
int __svfscanf(FILE *, const char *, va_list) __attribute__((__format__ (__scanf__, 2, 0)));
int __swbuf(int, FILE *);
inline __attribute__ ((__always_inline__)) int __sputc(int _c, FILE *_p) {
 if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
  return (*_p->_p++ = _c);
 else
  return (__swbuf(_c, _p));
}
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
int getw(FILE *);
int putw(int, FILE *);
__attribute__((__availability__(swift, unavailable, message="Use mkstemp(3) instead.")))
__attribute__((__deprecated__("This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of tempnam(3), it is highly recommended that you use mkstemp(3) instead.")))
char * tempnam(const char *__dir, const char *__prefix) __asm("_" "tempnam" );
typedef __darwin_off_t off_t;
int fseeko(FILE * __stream, off_t __offset, int __whence);
off_t ftello(FILE * __stream);
int snprintf(char * restrict __str, size_t __size, const char * restrict __format, ...) __attribute__((__format__ (__printf__, 3, 4)));
int vfscanf(FILE * restrict __stream, const char * restrict __format, va_list) __attribute__((__format__ (__scanf__, 2, 0)));
int vscanf(const char * restrict __format, va_list) __attribute__((__format__ (__scanf__, 1, 0)));
int vsnprintf(char * restrict __str, size_t __size, const char * restrict __format, va_list) __attribute__((__format__ (__printf__, 3, 0)));
int vsscanf(const char * restrict __str, const char * restrict __format, va_list) __attribute__((__format__ (__scanf__, 2, 0)));
typedef __darwin_ssize_t ssize_t;
int dprintf(int, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3))) __attribute__((availability(macosx,introduced=10.7)));
int vdprintf(int, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0))) __attribute__((availability(macosx,introduced=10.7)));
ssize_t getdelim(char * *restrict __linep, size_t * restrict __linecapp, int __delimiter, FILE * restrict __stream) __attribute__((availability(macosx,introduced=10.7)));
ssize_t getline(char * *restrict __linep, size_t * restrict __linecapp, FILE * restrict __stream) __attribute__((availability(macosx,introduced=10.7)));
FILE *fmemopen(void * restrict __buf , size_t __size, const char * restrict __mode) __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0)));
FILE *open_memstream(char * *__bufp, size_t *__sizep) __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0)));
extern const int sys_nerr;
extern const char *const sys_errlist[];
int asprintf(char * *restrict, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3)));
char * ctermid_r(char *);
char * fgetln(FILE *, size_t *__len);
const char *fmtcheck(const char *, const char *) __attribute__((format_arg(2)));
int fpurge(FILE *);
void setbuffer(FILE *, char *, int __size);
int setlinebuf(FILE *);
int vasprintf(char * *restrict, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0)));
FILE *funopen(const void *,
     int (* _Nullable)(void *, char *, int __n),
     int (* _Nullable)(void *, const char *, int __n),
     fpos_t (* _Nullable)(void *, fpos_t, int),
     int (* _Nullable)(void *));
extern int __snprintf_chk (char * restrict , size_t __maxlen, int, size_t,
     const char * restrict, ...);
extern int __vsnprintf_chk (char * restrict , size_t __maxlen, int, size_t,
     const char * restrict, va_list);
extern int __sprintf_chk (char * restrict , int, size_t,
     const char * restrict, ...);
extern int __vsprintf_chk (char * restrict , int, size_t,
     const char * restrict, va_list);
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;
typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;
typedef long int intmax_t;
typedef long unsigned int uintmax_t;

void print_i32(int32_t val);
void print_i64(int64_t val);
void print_f32(float val);
void print_f64(double val);
void print_bool(int val);
void print_str(const char *s);
void print_char(char c);
void print_ptr(void *p);
void print_newline(void);
void print_i32(int32_t val) {
    printf("%d", val);
}
void print_i64(int64_t val) {
    printf("%lld", (long long)val);
}
void print_f32(float val) {
    printf("%g", (double)val);
}
void print_f64(double val) {
    printf("%g", val);
}
void print_bool(int val) {
    printf("%s", val ? "true" : "false");
}
void print_str(const char *s) {
    if (s) printf("%s", s);
    else printf("(null)");
}
void print_char(char c) {
    printf("%c", c);
}
void print_ptr(void *p) {
    if (p) printf("%p", p);
    else printf("null");
}
void print_newline(void) {
    printf("\n");
}
typedef long int ptrdiff_t;
typedef long unsigned int rsize_t;
typedef int wchar_t;
typedef long double max_align_t;
void *
  memchr(const void * __s, int __c, size_t __n);
int memcmp(const void * __s1, const void * __s2,
  size_t __n);
void *
  memcpy(void * __dst, const void * __src,
  size_t __n);
void *
  memmove(void * __dst,
  const void * __src, size_t __len);
void *
  memset(void * __b, int __c, size_t __len);
char *
  strcat(char * __s1, const char *__s2)
                                  ;
char * strchr(const char *__s, int __c);
int strcmp(const char *__s1, const char *__s2);
int strcoll(const char *__s1, const char *__s2);
char *
  strcpy(char * __dst, const char *__src)
                                  ;
size_t strcspn(const char *__s, const char *__charset);
char * strerror(int __errnum) __asm("_" "strerror" );
size_t strlen(const char *__s);
char *
  strncat(char * __s1,
  const char * __s2, size_t __n)
                                  ;
int strncmp(const char * __s1,
  const char * __s2, size_t __n);
char *
  strncpy(char * __dst,
        const char * __src, size_t __n)
                                        ;
char * strpbrk(const char *__s, const char *__charset);
char * strrchr(const char *__s, int __c);
size_t strspn(const char *__s, const char *__charset);
char * strstr(const char *__big, const char *__little);
char * strtok(char * __str, const char *__sep);
size_t strxfrm(char * __s1, const char *__s2, size_t __n);
char *
        strtok_r(char * __str, const char *__sep,
        char * *__lasts);
int strerror_r(int __errnum, char * __strerrbuf,
        size_t __buflen);
char * strdup(const char *__s1);
void *
        memccpy(void * __dst, const void * __src,
        int __c, size_t __n);
char *
        stpcpy(char * __dst, const char *__src) ;
char *
        stpncpy(char * __dst,
        const char * __src, size_t __n)
        __attribute__((availability(macosx,introduced=10.7)))
                                        ;
char * strndup(const char * __s1, size_t __n) __attribute__((availability(macosx,introduced=10.7)));
size_t strnlen(const char * __s1, size_t __n) __attribute__((availability(macosx,introduced=10.7)));
char * strsignal(int __sig);
typedef int errno_t;
errno_t memset_s(void * __s, rsize_t __smax, int __c, rsize_t __n) __attribute__((availability(macosx,introduced=10.9)));
void *
        memmem(const void * __big, size_t __big_len,
        const void * __little, size_t __little_len) __attribute__((availability(macosx,introduced=10.7)));
void memset_pattern4(void * __b, const void * __pattern4, size_t __len) __attribute__((availability(macosx,introduced=10.5)));
void memset_pattern8(void * __b, const void * __pattern8, size_t __len) __attribute__((availability(macosx,introduced=10.5)));
void memset_pattern16(void * __b, const void * __pattern16, size_t __len) __attribute__((availability(macosx,introduced=10.5)));
char *
        strcasestr(const char *__big, const char *__little);
__attribute__((availability(macosx,introduced=15.4))) __attribute__((availability(ios,introduced=18.4)))
__attribute__((availability(tvos,introduced=18.4))) __attribute__((availability(watchos,introduced=11.4)))
char *
        strchrnul(const char *__s, int __c);
char *
        strnstr(const char * __big, const char *__little, size_t __len);
size_t strlcat(char * __dst, const char *__source, size_t __size);
size_t strlcpy(char * __dst, const char *__source, size_t __size);
void strmode(int __mode, char * __bp);
char *
        strsep(char * *__stringp, const char *__delim);
void swab(const void * restrict, void * restrict, ssize_t __len);
__attribute__((availability(macosx,introduced=10.12.1))) __attribute__((availability(ios,introduced=10.1)))
__attribute__((availability(tvos,introduced=10.0.1))) __attribute__((availability(watchos,introduced=3.1)))
int timingsafe_bcmp(const void * __b1, const void * __b2, size_t __len);
__attribute__((availability(macosx,introduced=11.0))) __attribute__((availability(ios,introduced=14.0)))
__attribute__((availability(tvos,introduced=14.0))) __attribute__((availability(watchos,introduced=7.0)))
int strsignal_r(int __sig, char * __strsignalbuf, size_t __buflen);
int bcmp(const void *, const void *, size_t __n) ;
void bcopy(const void *, void *, size_t __n) ;
void bzero(void *, size_t __n) ;
char * index(const char *, int) ;
char * rindex(const char *, int) ;
int ffs(int);
int strcasecmp(const char *, const char *);
int strncasecmp(const char *, const char *, size_t);
int ffsl(long) __attribute__((availability(macosx,introduced=10.5)));
int ffsll(long long) __attribute__((availability(macosx,introduced=10.9)));
int fls(int) __attribute__((availability(macosx,introduced=10.5)));
int flsl(long) __attribute__((availability(macosx,introduced=10.5)));
int flsll(long long) __attribute__((availability(macosx,introduced=10.9)));
typedef struct {
    size_t start_line;
    size_t start_col;
    size_t end_line;
    size_t end_col;
} Span;
typedef struct {
    const char* ptr;
    uint32_t len;
} Slice;
static inline size_t slice_hash(void *p) {
    Slice *s = (Slice*)p;
    size_t h = (size_t)1469598103934665603ULL;
    for (size_t i = 0; i < s->len; ++i) {
        h ^= (unsigned char)s->ptr[i];
        h *= (size_t)1099511628211ULL;
    }
    return h;
}
static inline int slice_cmp(void *a, void *b) {
    Slice *sa = (Slice*)a;
    Slice *sb = (Slice*)b;
    if (sa->len != sb->len) return (sa->len < sb->len) ? -1 : 1;
    return memcmp(sa->ptr, sb->ptr, sa->len);
}
static inline Span span_join(const Span *a, const Span *b) {
    if (!a || !b) return (Span){0,0,0,0};
    return (Span){a->start_line, a->start_col, b->end_line, b->end_col};
}
static inline size_t ptr_hash(void *key) {
    size_t k = (size_t)key;
    return (k >> 4) ^ (k >> 9);
}
static inline int ptr_cmp(void *a, void *b) {
    return (a > b) - (a < b);
}
static inline size_t str_hash(void *key) {
    const char *s = (const char *)key;
    size_t h = (size_t)1469598103934665603ULL;
    while (*s) {
        h ^= (unsigned char)*s++;
        h *= (size_t)1099511628211ULL;
    }
    return h;
}
static inline int str_cmp(void *a, void *b) {
    return strcmp((const char *)a, (const char *)b);
}
double now_seconds(void);
size_t get_peak_rss_kb(void);
void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
char *xstrdup(const char *s);

typedef struct ArenaBlock {
    struct ArenaBlock *next;
    size_t capacity;
    size_t used;
    char data[];
} ArenaBlock;
typedef struct Arena {
    ArenaBlock *blocks;
    size_t block_size;
} Arena;
Arena *arena_create(size_t initial_capacity);
void arena_destroy(Arena *arena);
void arena_reset(Arena *arena);
void *arena_alloc(Arena *arena, size_t size);
void *arena_calloc(Arena *arena, size_t size);
size_t arena_bytes_used(const Arena *arena);
size_t arena_bytes_capacity(const Arena *arena);
size_t arena_block_count(const Arena *arena);
size_t arena_total_allocated(const Arena *arena);

typedef struct {
    void *data;
    size_t elem_size;
    size_t count;
    size_t capacity;
    Arena *arena;
} DynArray;
void dynarray_init(DynArray *da, size_t elem_size);
void dynarray_free(DynArray *da);
int dynarray_reserve(DynArray *da, size_t min_capacity);
int dynarray_push_value(DynArray *da, const void *value);
void *dynarray_push_uninit(DynArray *da);
void dynarray_pop(DynArray *da);
void dynarray_remove(DynArray *da, size_t index);
void *dynarray_get(DynArray *da, size_t index);
int dynarray_set(DynArray *da, size_t index, const void *value);
void dynarray_init_in_arena(DynArray *da, Arena *arena, size_t elem_size, size_t initial_capacity);
int dynarray_reserve_in_arena(DynArray *da, size_t min_capacity);
static inline void dynarray_push_ptr(DynArray *da, void *p) {
    dynarray_push_value(da, &p);
}
typedef struct {
    void *key;
    void *value;
} KeyValue;
typedef struct {
    DynArray *buckets;
    size_t bucket_count;
    size_t size;
} HashMap;
HashMap* hashmap_create(size_t bucket_count);
void hashmap_destroy(
    HashMap* map,
    void (*free_key)(void*),
    void (*free_value)(void*)
);
_Bool hashmap_put(
    HashMap* map,
    void* key,
    void* value,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
);
void* hashmap_get(
    HashMap* map,
    void* key,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
);
_Bool hashmap_remove(
    HashMap* map,
    void* key,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*),
    void (*free_key)(void*),
    void (*free_value)(void*)
);
_Bool hashmap_rehash(
    HashMap* map,
    size_t new_bucket_count,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
);
size_t hashmap_size(HashMap* map);
void hashmap_foreach(
    HashMap* map,
    void (*func)(void* key, void* value)
);
typedef struct {
    Arena *arena;
    HashMap *hashmap;
    DynArray *dense_array;
    int dense_index_count;
    void* (*copy_func)(Arena *arena, const void *data, size_t len);
    size_t (*hash_func)(void *key);
    int (*cmp_func)(void *a, void *b);
} DenseArenaInterner;
typedef struct {
    void* meta;
    int dense_index;
} Entry;
typedef struct {
    void *key;
    Entry *entry;
} InternResult;
typedef void* (*CopyFunc)(Arena *arena, const void *data, size_t len);
void* string_copy_func(Arena *arena, const void *data, size_t len);
void* binary_copy_func(Arena *arena, const void *data, size_t len);
DenseArenaInterner* intern_table_create(HashMap *hashmap, Arena *arena, CopyFunc copy_func,
                                       size_t (*hash_func)(void*), int (*cmp_func)(void*, void*));
void intern_table_destroy(DenseArenaInterner *interner, void (*free_key)(void*), void (*free_value)(void*));
InternResult *intern(DenseArenaInterner *interner, Slice *slice, void* meta);
void *intern_ptr(DenseArenaInterner *interner, Slice *slice, void* meta);
int intern_idx(DenseArenaInterner *interner, Slice *slice, void* meta);
InternResult* intern_peek(DenseArenaInterner *interner, Slice *slice);
const char *interner_get_cstr(DenseArenaInterner *interner, int idx);
InternResult *interner_get_result(DenseArenaInterner *interner, int idx);
typedef void (*InternerIterFn)(int idx, const Slice *key, void *meta, void *user);
void interner_foreach(const DenseArenaInterner *interner,
                      InternerIterFn cb,
                      void *user);
typedef enum {
    TOK_FN,
    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,
    TOK_FOR,
    TOK_RETURN,
    TOK_BREAK,
    TOK_CONTINUE,
    TOK_CONST,
    TOK_PUB,
    TOK_IMPORT,
    TOK_ALIAS,
    TOK_DEFER,
    TOK_I32,
    TOK_I64,
    TOK_BOOL,
    TOK_F32,
    TOK_F64,
    TOK_STRING,
    TOK_CHAR,
    TOK_VOID,
    TOK_PLUSPLUS,
    TOK_MINUSMINUS,
    TOK_PLUS_EQ,
    TOK_MINUS_EQ,
    TOK_STAR_EQ,
    TOK_SLASH_EQ,
    TOK_PERCENT_EQ,
    TOK_EQ_EQ,
    TOK_BANG_EQ,
    TOK_LT_EQ,
    TOK_GT_EQ,
    TOK_AND_AND,
    TOK_OR_OR,
    TOK_ARROW,
    TOK_ASSIGN,
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_PERCENT,
    TOK_BANG,
    TOK_AMP,
    TOK_LT,
    TOK_GT,
    TOK_DOT,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACE,
    TOK_RBRACE,
    TOK_LBRACKET,
    TOK_RBRACKET,
    TOK_COMMA,
    TOK_SEMICOLON,
    TOK_COLON,
    TOK_PIPE,
    TOK_AT,
    TOK_FLOAT_LIT,
    TOK_INT_LIT,
    TOK_STRING_LIT,
    TOK_CHAR_LIT,
    TOK_TRUE,
    TOK_FALSE,
    TOK_IDENTIFIER,
    TOK_COMMENT,
    TOK_EOF,
    TOK_STRUCT,
    TOK_AS,
    TOK_UNKNOWN
} TokenType;
typedef struct {
    TokenType type;
    Slice slice;
    Span span;
    InternResult *record;
} Token;

typedef enum {
    INTRINSIC_NONE = 0,
    INTRINSIC_PRINT,
    INTRINSIC_PRINT_NEWLINE,
    INTRINSIC_ALLOC,
    INTRINSIC_FREE,
    INTRINSIC_UNKNOWN
} IntrinsicKind;
typedef struct AstNode AstNode;
typedef struct Type Type;
typedef struct Symbol Symbol;
typedef enum {
    AST_PROGRAM,
    AST_VARIABLE_DECLARATION,
    AST_FUNCTION_DECLARATION,
    AST_PARAM,
    AST_STRUCT_DECLARATION,
    AST_IMPORT_DECLARATION,
    AST_ALIAS_DECLARATION,
    AST_INTRINSIC,
    AST_BLOCK,
    AST_IF_STATEMENT,
    AST_WHILE_STATEMENT,
    AST_FOR_STATEMENT,
    AST_RETURN_STATEMENT,
    AST_BREAK_STATEMENT,
    AST_CONTINUE_STATEMENT,
    AST_DEFER_STATEMENT,
    AST_EXPR_STATEMENT,
    AST_LITERAL,
    AST_IDENTIFIER,
    AST_BINARY_EXPR,
    AST_UNARY_EXPR,
    AST_POSTFIX_EXPR,
    AST_ASSIGNMENT_EXPR,
    AST_CALL_EXPR,
    AST_SUBSCRIPT_EXPR,
    AST_MEMBER_EXPR,
    AST_STRUCT_LITERAL,
    AST_CAST,
    AST_TYPE,
    AST_INITIALIZER_LIST
} AstNodeType;
typedef enum {
    OP_NULL,
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_EQ, OP_NEQ, OP_LT, OP_GT, OP_LE, OP_GE,
    OP_AND, OP_OR, OP_NOT,
    OP_ASSIGN, OP_PLUS_EQ, OP_MINUS_EQ, OP_MUL_EQ, OP_DIV_EQ, OP_MOD_EQ,
    OP_DEREF, OP_ADRESS,
    OP_POST_INC, OP_POST_DEC, OP_PRE_INC, OP_PRE_DEC
} OpKind;
typedef enum {
    INT_LITERAL,
    FLOAT_LITERAL,
    BOOL_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,
    NULL_LITERAL,
    LIT_UNKNOWN
} LiteralType;
typedef struct {
    LiteralType type;
    union {
        long long int_val;
        double float_val;
        int bool_val;
        char char_val;
        InternResult *string_val;
    } value;
} ConstValue;
typedef struct {
    DynArray *decls;
} AstProgram;
typedef struct {
    AstNode *type;
    InternResult *intern_result;
    int is_const;
    int is_pub;
    AstNode *initializer;
} AstVariableDeclaration;
typedef struct {
    AstNode *return_type;
    InternResult *intern_result;
    DynArray *params;
    AstNode *body;
    InternResult *link_name;
    int is_pub;
} AstFunctionDeclaration;
typedef struct {
    int name_idx;
    AstNode *type;
} AstParam;
typedef struct {
    InternResult *name;
    AstNode *type;
} AstFieldDecl;
typedef struct {
    InternResult *original_name;
    InternResult *alias_name;
} ImportSymbol;
typedef struct {
    DynArray *module_path;
    InternResult *module_alias;
    DynArray *specific_symbols;
    int leading_dots;
    _Bool is_root_relative;
    _Bool is_star;
    _Bool is_pub;
    char *resolved_logical_path;
} AstImportDeclaration;
typedef struct {
    InternResult *alias_name;
    AstNode *target;
} AstAliasDeclaration;
typedef struct {
    InternResult *intern_result;
    DynArray *fields;
    int is_pub;
} AstStructDeclaration;
typedef struct {
    DynArray *statements;
} AstBlock;
typedef struct {
    AstNode *condition;
    AstNode *then_branch;
    AstNode *else_branch;
} AstIfStatement;
typedef struct {
    AstNode *condition;
    AstNode *body;
} AstWhileStatement;
typedef struct {
    AstNode *init;
    AstNode *condition;
    AstNode *post;
    AstNode *body;
} AstForStatement;
typedef struct {
    AstNode *expression;
} AstReturnStatement;
typedef struct {
    AstNode *body;
} AstDeferStatement;
typedef struct { } AstBreakStatement;
typedef struct { } AstContinueStatement;
typedef struct {
    AstNode *expression;
} AstExprStatement;
typedef ConstValue AstLiteral;
typedef struct {
    InternResult *intern_result;
    Symbol *symbol;
} AstIdentifier;
typedef struct { AstNode *left; AstNode *right; OpKind op; } AstBinaryExpr;
typedef struct { OpKind op; AstNode *expr; } AstUnaryExpr;
typedef struct { AstNode *expr; OpKind op; } AstPostfixExpr;
typedef struct { AstNode *lvalue; AstNode *rvalue; OpKind op; } AstAssignmentExpr;
typedef struct { AstNode *callee; DynArray *args; } AstCallExpr;
typedef struct { AstNode *target; AstNode *index; } AstSubscriptExpr;
typedef struct { AstNode *target; InternResult *member; Symbol *symbol; } AstMemberExpr;
typedef struct {
    InternResult *name;
    AstNode *expr;
} AstFieldInit;
typedef struct {
    AstNode *type_node;
    DynArray *fields;
} AstStructLiteral;
typedef struct {
    AstNode *expr;
    Type *target_type;
    AstNode *target_type_node;
} AstCastExpr;
typedef enum {
    AST_TYPE_PRIMITIVE,
    AST_TYPE_PTR,
    AST_TYPE_ARRAY,
    AST_TYPE_FUNC
} AstTypeKind;
typedef struct AstType {
    AstTypeKind kind;
    Span span;
    union {
        struct {
            InternResult *intern_result;
            AstNode *path;
        } base;
        struct { AstNode *target; } ptr;
        struct { AstNode *elem; AstNode *size_expr; } array;
        struct { DynArray *param_types; AstNode *return_type; } func;
    } u;
} AstType;
typedef struct {
    DynArray *elements;
} AstInitializeList;
typedef enum {
    AST_FLAG_NONE = 0,
    AST_FLAG_CHECKED = 1 << 0
} AstFlags;
struct AstNode {
    AstNodeType node_type;
    Span span;
    const char *filename;
    Type *type;
    int flags;
    int last_checked_pass;
    uint8_t is_foldable_const;
    uint8_t is_llvm_const_safe;
    ConstValue const_value;
    union {
        AstProgram program;
        AstVariableDeclaration variable_declaration;
        AstFunctionDeclaration function_declaration;
        AstParam param;
        AstStructDeclaration struct_declaration;
        AstImportDeclaration import_declaration;
        AstAliasDeclaration alias_declaration;
        struct {
            IntrinsicKind kind;
            DynArray *args;
        } intrinsic;
        AstBlock block;
        AstIfStatement if_statement;
        AstWhileStatement while_statement;
        AstForStatement for_statement;
        AstReturnStatement return_statement;
        AstDeferStatement defer_statement;
        AstBreakStatement break_statement;
        AstContinueStatement continue_statement;
        AstExprStatement expr_statement;
        AstLiteral literal;
        AstIdentifier identifier;
        AstBinaryExpr binary_expr;
        AstUnaryExpr unary_expr;
        AstPostfixExpr postfix_expr;
        AstAssignmentExpr assignment_expr;
        AstCallExpr call_expr;
        AstSubscriptExpr subscript_expr;
        AstMemberExpr member_expr;
        AstStructLiteral struct_literal;
        AstCastExpr cast_expr;
        AstType ast_type;
        AstInitializeList initializer_list;
    } data;
};
AstNode *ast_create_node(AstNodeType type, Arena *arena, const char *filename);
void print_ast(AstNode *node, int depth, DenseArenaInterner *keywords, DenseArenaInterner *identifiers, DenseArenaInterner *strings);
void print_ast_with_prefix(AstNode *node, int depth, int is_last, DenseArenaInterner *keywords, DenseArenaInterner *identifiers, DenseArenaInterner *strings);
int is_lvalue_node(AstNode *node);
int is_assignment_op(TokenType type);


typedef struct {
    _Bool print_tokens;
    _Bool print_ast;
    _Bool print_ir;
    _Bool print_time;
    _Bool print_types;
    _Bool verbose;
    _Bool run_executable;
    _Bool quiet;
    int opt_level;
    const char *output_name;
    const char *stdlib_path;
} Options;
int parse_options(int argc, char **argv, Options *opts, const char **in_path);
void print_usage(const char *prog);
void print_version(void);

typedef struct Scope Scope;
typedef struct Symbol Symbol;
typedef struct AstNode AstNode;
typedef struct CompilationUnit CompilationUnit;
typedef enum {
    SYMBOL_VALUE_INT,
    SYMBOL_VALUE_FLOAT,
    SYMBOL_VALUE_BOOL,
    SYMBOL_VALUE_FUNCTION,
    SYMBOL_VALUE_TYPE,
    SYMBOL_VALUE_INTRINSIC,
    SYMBOL_VARIABLE,
    SYMBOL_VALUE_MODULE,
    SYMBOL_VALUE_NAMESPACE,
    SYMBOL_VALUE_ALIAS
} SymbolValue;
typedef struct Type Type;
typedef enum {
    SYMBOL_FLAG_NONE = 0,
    SYMBOL_FLAG_CONST = 1 << 0,
    SYMBOL_FLAG_COMPUTED_VALUE = 1 << 1,
    SYMBOL_FLAG_USED = 1 << 2,
    SYMBOL_FLAG_INITIALIZED = 1 << 3,
    SYMBOL_FLAG_COMPUTING = 1 << 4
} SymbolFlags;
typedef struct Symbol {
    InternResult *name_rec;
    Type *type;
    Span span;
    const char *filename;
    _Bool is_pub;
    AstNode *decl_node;
    Scope *module_scope;
    struct Symbol *target_symbol;
    SymbolValue kind;
    SymbolFlags flags;
    int intrinsic_kind;
    union {
        int64_t int_val;
        double float_val;
        _Bool bool_val;
    } value;
} Symbol;
typedef struct Scope {
    Symbol **symbols;
    size_t symbol_count;
    size_t capacity;
    DynArray symbols_list;
    Scope *parent;
    Arena *arena;
    size_t depth;
    int kind;
    CompilationUnit *unit;
} Scope;
typedef enum {
    SCOPE_IDENTIFIERS = 0,
    SCOPE_KEYWORDS = 1
} ScopeKind;
Scope *scope_create(Arena *arena, Scope *parent, int identifier_count, int kind);
Symbol *scope_define_symbol(Scope *scope, InternResult *name, Type *type, SymbolValue kind, const char *filename, _Bool is_pub, AstNode *decl_node);
Symbol *scope_lookup_symbol(Scope *scope, InternResult *name, const char *caller_filename);
Symbol *scope_lookup_symbol_local(Scope *scope, InternResult *name);
Symbol *symbol_set_value_int(Symbol *symbol, int value);
Symbol *symbol_set_value_float(Symbol *symbol, float value);
Symbol *symbol_set_value_bool(Symbol *symbol, _Bool value);
size_t scope_get_symbol_count(Scope *scope);
void scope_set_flags(Scope *scope, InternResult *rec, int flags);
void scope_check_unused_symbols(Scope *scope);
void scope_print_symbols(Scope *scope, int indent);
void scope_print_hierarchy(Scope *scope);

typedef struct CompilationUnit {
    char *absolute_path;
    char *logical_path;
    AstNode *ast_root;
    Scope *global_scope;
    _Bool signatures_resolved;
    _Bool imports_resolved;
} CompilationUnit;
typedef struct {
    Arena *arena;
    Options *opts;
    DenseArenaInterner *keywords;
    DenseArenaInterner *identifiers;
    DenseArenaInterner *strings;
    HashMap *units;
    HashMap *units_by_logical_path;
    DynArray *units_ordered;
    char *project_root;
} ModuleLoader;
ModuleLoader* module_loader_create(Arena *arena, Options *opts,
                                   DenseArenaInterner *keywords,
                                   DenseArenaInterner *identifiers,
                                   DenseArenaInterner *strings);
int load_module_recursive(ModuleLoader *loader, const char *path, const char *logical_path, const char *importer_path, int depth);
CompilationUnit* module_loader_get_unit(ModuleLoader *loader, const char *path);
typedef enum {
 P_ALL,
 P_PID,
 P_PGID
} idtype_t;
typedef __darwin_pid_t pid_t;
typedef __darwin_id_t id_t;
typedef int sig_atomic_t;
struct __darwin_arm_exception_state
{
 __uint32_t __exception;
 __uint32_t __fsr;
 __uint32_t __far;
};
struct __darwin_arm_exception_state64
{
 __uint64_t __far;
 __uint32_t __esr;
 __uint32_t __exception;
};
struct __darwin_arm_exception_state64_v2
{
 __uint64_t __far;
 __uint64_t __esr;
};
struct __darwin_arm_thread_state
{
 __uint32_t __r[13];
 __uint32_t __sp;
 __uint32_t __lr;
 __uint32_t __pc;
 __uint32_t __cpsr;
};
struct __darwin_arm_thread_state64
{
 __uint64_t __x[29];
 __uint64_t __fp;
 __uint64_t __lr;
 __uint64_t __sp;
 __uint64_t __pc;
 __uint32_t __cpsr;
 __uint32_t __pad;
};
struct __darwin_arm_vfp_state
{
 __uint32_t __r[64];
 __uint32_t __fpscr;
};
struct __darwin_arm_neon_state64
{
 __uint128_t __v[32];
 __uint32_t __fpsr;
 __uint32_t __fpcr;
};
struct __darwin_arm_neon_state
{
 __uint128_t __v[16];
 __uint32_t __fpsr;
 __uint32_t __fpcr;
};
struct __arm_pagein_state
{
 int __pagein_error;
};
struct __darwin_arm_sme_state
{
 __uint64_t __svcr;
 __uint64_t __tpidr2_el0;
 __uint16_t __svl_b;
};
struct __darwin_arm_sve_z_state
{
 char __z[16][256];
} __attribute__((aligned(4)));
struct __darwin_arm_sve_p_state
{
 char __p[16][256 / 8];
} __attribute__((aligned(4)));
struct __darwin_arm_sme_za_state
{
 char __za[4096];
} __attribute__((aligned(4)));
struct __darwin_arm_sme2_state
{
 char __zt0[64];
} __attribute__((aligned(4)));
struct __arm_legacy_debug_state
{
 __uint32_t __bvr[16];
 __uint32_t __bcr[16];
 __uint32_t __wvr[16];
 __uint32_t __wcr[16];
};
struct __darwin_arm_debug_state32
{
 __uint32_t __bvr[16];
 __uint32_t __bcr[16];
 __uint32_t __wvr[16];
 __uint32_t __wcr[16];
 __uint64_t __mdscr_el1;
};
struct __darwin_arm_debug_state64
{
 __uint64_t __bvr[16];
 __uint64_t __bcr[16];
 __uint64_t __wvr[16];
 __uint64_t __wcr[16];
 __uint64_t __mdscr_el1;
};
struct __darwin_arm_cpmu_state64
{
 __uint64_t __ctrs[16];
};
struct __darwin_mcontext32
{
 struct __darwin_arm_exception_state __es;
 struct __darwin_arm_thread_state __ss;
 struct __darwin_arm_vfp_state __fs;
};
struct __darwin_mcontext64
{
 struct __darwin_arm_exception_state64 __es;
 struct __darwin_arm_thread_state64 __ss;
 struct __darwin_arm_neon_state64 __ns;
};
typedef struct __darwin_mcontext64 *mcontext_t;

typedef __darwin_pthread_attr_t pthread_attr_t;

struct __darwin_sigaltstack
{
 void *ss_sp;
 __darwin_size_t ss_size;
 int ss_flags;
};
typedef struct __darwin_sigaltstack stack_t;
struct __darwin_ucontext
{
 int uc_onstack;
 __darwin_sigset_t uc_sigmask;
 struct __darwin_sigaltstack uc_stack;
 struct __darwin_ucontext *uc_link;
 __darwin_size_t uc_mcsize;
 struct __darwin_mcontext64 *uc_mcontext;
};
typedef struct __darwin_ucontext ucontext_t;
typedef __darwin_sigset_t sigset_t;
typedef __darwin_uid_t uid_t;

union sigval {
 int sival_int;
 void *sival_ptr;
};
struct sigevent {
 int sigev_notify;
 int sigev_signo;
 union sigval sigev_value;
 void (*sigev_notify_function)(union sigval);
 pthread_attr_t *sigev_notify_attributes;
};
typedef struct __siginfo {
 int si_signo;
 int si_errno;
 int si_code;
 pid_t si_pid;
 uid_t si_uid;
 int si_status;
 void *si_addr;
 union sigval si_value;
 long si_band;
 unsigned long __pad[7];
} siginfo_t;
union __sigaction_u {
 void (*__sa_handler)(int);
 void (*__sa_sigaction)(int, struct __siginfo *,
     void *);
};
struct __sigaction {
 union __sigaction_u __sigaction_u;
 void (*sa_tramp)(void *, int, int, siginfo_t *, void *);
 sigset_t sa_mask;
 int sa_flags;
};
struct sigaction {
 union __sigaction_u __sigaction_u;
 sigset_t sa_mask;
 int sa_flags;
};
typedef void (*sig_t)(int);
struct sigvec {
 void (*sv_handler)(int);
 int sv_mask;
 int sv_flags;
};
struct sigstack {
 char *ss_sp;
 int ss_onstack;
};
void(*signal(int, void (*)(int)))(int);
struct timeval
{
 __darwin_time_t tv_sec;
 __darwin_suseconds_t tv_usec;
};
typedef __uint64_t rlim_t;
struct rusage {
 struct timeval ru_utime;
 struct timeval ru_stime;
 long ru_maxrss;
 long ru_ixrss;
 long ru_idrss;
 long ru_isrss;
 long ru_minflt;
 long ru_majflt;
 long ru_nswap;
 long ru_inblock;
 long ru_oublock;
 long ru_msgsnd;
 long ru_msgrcv;
 long ru_nsignals;
 long ru_nvcsw;
 long ru_nivcsw;
};
typedef void *rusage_info_t;
struct rusage_info_v0 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
};
struct rusage_info_v1 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
};
struct rusage_info_v2 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
 uint64_t ri_diskio_bytesread;
 uint64_t ri_diskio_byteswritten;
};
struct rusage_info_v3 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
 uint64_t ri_diskio_bytesread;
 uint64_t ri_diskio_byteswritten;
 uint64_t ri_cpu_time_qos_default;
 uint64_t ri_cpu_time_qos_maintenance;
 uint64_t ri_cpu_time_qos_background;
 uint64_t ri_cpu_time_qos_utility;
 uint64_t ri_cpu_time_qos_legacy;
 uint64_t ri_cpu_time_qos_user_initiated;
 uint64_t ri_cpu_time_qos_user_interactive;
 uint64_t ri_billed_system_time;
 uint64_t ri_serviced_system_time;
};
struct rusage_info_v4 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
 uint64_t ri_diskio_bytesread;
 uint64_t ri_diskio_byteswritten;
 uint64_t ri_cpu_time_qos_default;
 uint64_t ri_cpu_time_qos_maintenance;
 uint64_t ri_cpu_time_qos_background;
 uint64_t ri_cpu_time_qos_utility;
 uint64_t ri_cpu_time_qos_legacy;
 uint64_t ri_cpu_time_qos_user_initiated;
 uint64_t ri_cpu_time_qos_user_interactive;
 uint64_t ri_billed_system_time;
 uint64_t ri_serviced_system_time;
 uint64_t ri_logical_writes;
 uint64_t ri_lifetime_max_phys_footprint;
 uint64_t ri_instructions;
 uint64_t ri_cycles;
 uint64_t ri_billed_energy;
 uint64_t ri_serviced_energy;
 uint64_t ri_interval_max_phys_footprint;
 uint64_t ri_runnable_time;
};
struct rusage_info_v5 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
 uint64_t ri_diskio_bytesread;
 uint64_t ri_diskio_byteswritten;
 uint64_t ri_cpu_time_qos_default;
 uint64_t ri_cpu_time_qos_maintenance;
 uint64_t ri_cpu_time_qos_background;
 uint64_t ri_cpu_time_qos_utility;
 uint64_t ri_cpu_time_qos_legacy;
 uint64_t ri_cpu_time_qos_user_initiated;
 uint64_t ri_cpu_time_qos_user_interactive;
 uint64_t ri_billed_system_time;
 uint64_t ri_serviced_system_time;
 uint64_t ri_logical_writes;
 uint64_t ri_lifetime_max_phys_footprint;
 uint64_t ri_instructions;
 uint64_t ri_cycles;
 uint64_t ri_billed_energy;
 uint64_t ri_serviced_energy;
 uint64_t ri_interval_max_phys_footprint;
 uint64_t ri_runnable_time;
 uint64_t ri_flags;
};
struct rusage_info_v6 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
 uint64_t ri_diskio_bytesread;
 uint64_t ri_diskio_byteswritten;
 uint64_t ri_cpu_time_qos_default;
 uint64_t ri_cpu_time_qos_maintenance;
 uint64_t ri_cpu_time_qos_background;
 uint64_t ri_cpu_time_qos_utility;
 uint64_t ri_cpu_time_qos_legacy;
 uint64_t ri_cpu_time_qos_user_initiated;
 uint64_t ri_cpu_time_qos_user_interactive;
 uint64_t ri_billed_system_time;
 uint64_t ri_serviced_system_time;
 uint64_t ri_logical_writes;
 uint64_t ri_lifetime_max_phys_footprint;
 uint64_t ri_instructions;
 uint64_t ri_cycles;
 uint64_t ri_billed_energy;
 uint64_t ri_serviced_energy;
 uint64_t ri_interval_max_phys_footprint;
 uint64_t ri_runnable_time;
 uint64_t ri_flags;
 uint64_t ri_user_ptime;
 uint64_t ri_system_ptime;
 uint64_t ri_pinstructions;
 uint64_t ri_pcycles;
 uint64_t ri_energy_nj;
 uint64_t ri_penergy_nj;
 uint64_t ri_secure_time_in_system;
 uint64_t ri_secure_ptime_in_system;
 uint64_t ri_neural_footprint;
 uint64_t ri_lifetime_max_neural_footprint;
 uint64_t ri_interval_max_neural_footprint;
 uint64_t ri_reserved[9];
};
typedef struct rusage_info_v6 rusage_info_current;
struct rlimit {
 rlim_t rlim_cur;
 rlim_t rlim_max;
};
struct proc_rlimit_control_wakeupmon {
 uint32_t wm_flags;
 int32_t wm_rate;
};
int getpriority(int, id_t);
int getiopolicy_np(int, int) __attribute__((availability(macosx,introduced=10.5)));
int getrlimit(int, struct rlimit *) __asm("_" "getrlimit" );
int getrusage(int, struct rusage *);
int setpriority(int, id_t, int);
int setiopolicy_np(int, int, int) __attribute__((availability(macosx,introduced=10.5)));
int setrlimit(int, const struct rlimit *) __asm("_" "setrlimit" );
static inline
__uint16_t
_OSSwapInt16(
 __uint16_t _data
 )
{
 return (__uint16_t)(_data << 8 | _data >> 8);
}
static inline
__uint32_t
_OSSwapInt32(
 __uint32_t _data
 )
{
 _data = __builtin_bswap32(_data);
 return _data;
}
static inline
__uint64_t
_OSSwapInt64(
 __uint64_t _data
 )
{
 return __builtin_bswap64(_data);
}
union wait {
 int w_status;
 struct {
  unsigned int w_Termsig:7,
      w_Coredump:1,
      w_Retcode:8,
      w_Filler:16;
 } w_T;
 struct {
  unsigned int w_Stopval:8,
      w_Stopsig:8,
      w_Filler:16;
 } w_S;
};
pid_t wait(int *) __asm("_" "wait" );
pid_t waitpid(pid_t, int *, int) __asm("_" "waitpid" );
int waitid(idtype_t, id_t, siginfo_t *, int) __asm("_" "waitid" );
pid_t wait3(int *, int, struct rusage *);
pid_t wait4(pid_t, int *, int, struct rusage *);

void * alloca(size_t __size);
typedef __darwin_ct_rune_t ct_rune_t;
typedef __darwin_rune_t rune_t;
typedef struct {
 int quot;
 int rem;
} div_t;
typedef struct {
 long quot;
 long rem;
} ldiv_t;
typedef struct {
 long long quot;
 long long rem;
} lldiv_t;
extern int __mb_cur_max;
typedef unsigned long long malloc_type_id_t;

__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_malloc(size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1)));
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_calloc(size_t count, size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1,2)));
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void malloc_type_free(void * ptr, malloc_type_id_t type_id);
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_realloc(void * ptr, size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(2)));
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_valloc(size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1)));
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_aligned_alloc(size_t alignment, size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_align(1))) __attribute__((alloc_size(2)));
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
int malloc_type_posix_memalign(void * *memptr, size_t alignment, size_t size, malloc_type_id_t type_id) ;
typedef struct _malloc_zone_t malloc_zone_t;
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_zone_malloc(malloc_zone_t *zone, size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(2)));
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_zone_calloc(malloc_zone_t *zone, size_t count, size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(2,3)));
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void malloc_type_zone_free(malloc_zone_t *zone, void * ptr, malloc_type_id_t type_id);
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_zone_realloc(malloc_zone_t *zone, void * ptr, size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(3)));
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_zone_valloc(malloc_zone_t *zone, size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(2)));
__attribute__((availability(macos,introduced=14.0))) __attribute__((availability(ios,introduced=17.0))) __attribute__((availability(tvos,introduced=17.0))) __attribute__((availability(watchos,introduced=10.0))) __attribute__((availability(visionos,introduced=1.0))) __attribute__((availability(driverkit,introduced=23.0)))
void * malloc_type_zone_memalign(malloc_zone_t *zone, size_t alignment, size_t size, malloc_type_id_t type_id) __attribute__((__warn_unused_result__)) __attribute__((alloc_align(2))) __attribute__((alloc_size(3)));
void * malloc(size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1))) ;
void * calloc(size_t __count, size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1,2))) ;
void free(void * );
void * realloc(void * __ptr, size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(2))) ;
void * reallocf(void * __ptr, size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(2)));
void * valloc(size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1))) ;
void * aligned_alloc(size_t __alignment, size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_align(1))) __attribute__((alloc_size(2))) __attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(tvos,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0)));
int posix_memalign(void * *__memptr, size_t __alignment, size_t __size) __attribute__((availability(macosx,introduced=10.6)));
void abort(void) __attribute__((__cold__)) __attribute__((__noreturn__));
int abs(int) __attribute__((__const__));
int atexit(void (* _Nonnull)(void));
int at_quick_exit(void (*)(void));
double atof(const char *);
int atoi(const char *);
long atol(const char *);
long long
  atoll(const char *);
void *bsearch(const void * __key, const void * __base, size_t __nel,
     size_t __width, int (* _Nonnull __compar)(const void *, const void *));
div_t div(int, int) __attribute__((__const__));
void exit(int) __attribute__((__noreturn__));
char * getenv(const char *);
long labs(long) __attribute__((__const__));
ldiv_t ldiv(long, long) __attribute__((__const__));
long long
  llabs(long long);
lldiv_t lldiv(long long, long long);
int mblen(const char * __s, size_t __n);
size_t mbstowcs(wchar_t * restrict , const char * restrict, size_t __n);
int mbtowc(wchar_t * restrict, const char * restrict , size_t __n);
void qsort(void * __base, size_t __nel, size_t __width,
     int (* _Nonnull __compar)(const void *, const void *));
void quick_exit(int) __attribute__((__noreturn__));
int rand(void) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
void srand(unsigned) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
double strtod(const char *, char * *) __asm("_" "strtod" );
float strtof(const char *, char * *) __asm("_" "strtof" );
long strtol(const char *__str, char * *__endptr, int __base);
long double
  strtold(const char *, char * *);
long long
  strtoll(const char *__str, char * *__endptr, int __base);
unsigned long
  strtoul(const char *__str, char * *__endptr, int __base);
unsigned long long
  strtoull(const char *__str, char * *__endptr, int __base);
__attribute__((__availability__(swift, unavailable, message="Use posix_spawn APIs or NSTask instead. (On iOS, process spawning is unavailable.)")))
__attribute__((availability(macos,introduced=10.0))) __attribute__((availability(ios,unavailable)))
__attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)))
int system(const char *) __asm("_" "system" );
size_t wcstombs(char * restrict , const wchar_t * restrict, size_t __n);
int wctomb(char *, wchar_t);
void _Exit(int) __attribute__((__noreturn__));
long a64l(const char *);
double drand48(void);
char * ecvt(double, int, int *restrict, int *restrict);
double erand48(unsigned short[3]);
char * fcvt(double, int, int *restrict, int *restrict);
char * gcvt(double, int, char *) ;
int getsubopt(char * *, char * const *, char * *);
int grantpt(int);
char *
  initstate(unsigned, char *, size_t __size);
long jrand48(unsigned short[3]) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
char *l64a(long);
void lcong48(unsigned short[7]);
long lrand48(void) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
__attribute__((__deprecated__("This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of mktemp(3), it is highly recommended that you use mkstemp(3) instead.")))
char * mktemp(char *);
int mkstemp(char *);
long mrand48(void) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
long nrand48(unsigned short[3]) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
int posix_openpt(int);
char * ptsname(int);
int ptsname_r(int fildes, char * buffer, size_t buflen) __attribute__((availability(macos,introduced=10.13.4))) __attribute__((availability(ios,introduced=11.3))) __attribute__((availability(tvos,introduced=11.3))) __attribute__((availability(watchos,introduced=4.3)));
int putenv(char *) __asm("_" "putenv" );
long random(void) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
int rand_r(unsigned *) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
char * realpath(const char * restrict, char * restrict ) __asm("_" "realpath" "$DARWIN_EXTSN");
unsigned short * seed48(unsigned short[3]);
int setenv(const char * __name, const char * __value, int __overwrite) __asm("_" "setenv" );
void setkey(const char *) __asm("_" "setkey" );
char * setstate(const char *);
void srand48(long);
void srandom(unsigned);
int unlockpt(int);
int unsetenv(const char *) __asm("_" "unsetenv" );
typedef __darwin_dev_t dev_t;
typedef __darwin_mode_t mode_t;
uint32_t arc4random(void);
void arc4random_addrandom(unsigned char * , int __datlen)
    __attribute__((availability(macosx,introduced=10.0))) __attribute__((availability(macosx,deprecated=10.12,message="use arc4random_stir")))
    __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(ios,deprecated=10.0,message="use arc4random_stir")))
    __attribute__((availability(tvos,introduced=2.0))) __attribute__((availability(tvos,deprecated=10.0,message="use arc4random_stir")))
    __attribute__((availability(watchos,introduced=1.0))) __attribute__((availability(watchos,deprecated=3.0,message="use arc4random_stir")));
void arc4random_buf(void * __buf, size_t __nbytes) __attribute__((availability(macosx,introduced=10.7)));
void arc4random_stir(void);
uint32_t
  arc4random_uniform(uint32_t __upper_bound) __attribute__((availability(macosx,introduced=10.7)));
int atexit_b(void (^ _Nonnull)(void)) __attribute__((availability(macosx,introduced=10.6)));
void *bsearch_b(const void * __key, const void * __base, size_t __nel,
     size_t __width, int (^ _Nonnull __compar)(const void *, const void *) __attribute__((__noescape__)))
     __attribute__((availability(macosx,introduced=10.6)));
char * cgetcap(char *, const char *, int);
int cgetclose(void);
int cgetent(char * *, char * *, const char *);
int cgetfirst(char * *, char * *);
int cgetmatch(const char *, const char *);
int cgetnext(char * *, char * *);
int cgetnum(char *, const char *, long *);
int cgetset(const char *);
int cgetstr(char *, const char *, char * *);
int cgetustr(char *, const char *, char * *);
int daemon(int, int) __asm("_" "daemon" ) __attribute__((availability(macosx,introduced=10.0,deprecated=10.5,message="Use posix_spawn APIs instead."))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
char * devname(dev_t, mode_t);
char * devname_r(dev_t, mode_t, char * buf, int len);
char * getbsize(int *, long *);
int getloadavg(double [], int __nelem);
const char
 *getprogname(void);
void setprogname(const char *);
int heapsort(void * __base, size_t __nel, size_t __width,
     int (* _Nonnull __compar)(const void *, const void *));
int heapsort_b(void * __base, size_t __nel, size_t __width,
     int (^ _Nonnull __compar)(const void *, const void *) __attribute__((__noescape__)))
     __attribute__((availability(macosx,introduced=10.6)));
int mergesort(void * __base, size_t __nel, size_t __width,
     int (* _Nonnull __compar)(const void *, const void *));
int mergesort_b(void * __base, size_t __nel, size_t __width,
     int (^ _Nonnull __compar)(const void *, const void *) __attribute__((__noescape__)))
     __attribute__((availability(macosx,introduced=10.6)));
void psort(void * __base, size_t __nel, size_t __width,
     int (* _Nonnull __compar)(const void *, const void *))
     __attribute__((availability(macosx,introduced=10.6)));
void psort_b(void * __base, size_t __nel, size_t __width,
     int (^ _Nonnull __compar)(const void *, const void *) __attribute__((__noescape__)))
     __attribute__((availability(macosx,introduced=10.6)));
void psort_r(void * __base, size_t __nel, size_t __width, void *,
     int (* _Nonnull __compar)(void *, const void *, const void *))
     __attribute__((availability(macosx,introduced=10.6)));
void qsort_b(void * __base, size_t __nel, size_t __width,
     int (^ _Nonnull __compar)(const void *, const void *) __attribute__((__noescape__)))
     __attribute__((availability(macosx,introduced=10.6)));
void qsort_r(void * __base, size_t __nel, size_t __width, void *,
     int (* _Nonnull __compar)(void *, const void *, const void *));
int radixsort(const unsigned char * * __base, int __nel, const unsigned char * __table,
     unsigned __endbyte);
int rpmatch(const char *)
 __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(tvos,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0)));
int sradixsort(const unsigned char * * __base, int __nel, const unsigned char * __table,
     unsigned __endbyte);
void sranddev(void);
void srandomdev(void);
long long
 strtonum(const char *__numstr, long long __minval, long long __maxval, const char * *__errstrp)
 __attribute__((availability(macos,introduced=11.0))) __attribute__((availability(ios,introduced=14.0))) __attribute__((availability(tvos,introduced=14.0))) __attribute__((availability(watchos,introduced=7.0)));
long long
  strtoq(const char *__str, char * *__endptr, int __base);
unsigned long long
  strtouq(const char *__str, char * *__endptr, int __base);
extern char * suboptarg;
char *read_file(const char *filename);
void free_file_content(char *content);
int read_line_from_file(const char *filename, size_t line_no,
                        char *buf, size_t buf_size, size_t *out_len);
void print_source_excerpt(const char *filename, size_t line_no, size_t col);
void print_source_excerpt_span(const char *filename, size_t line_no, size_t start_col, size_t end_col);
typedef struct Lexer {
    const char *source;
    size_t source_len;
    size_t pos;
    size_t line;
    size_t col;
    Arena *arena;
    const char *cur;
    const char *end;
    DenseArenaInterner *keywords;
    DenseArenaInterner *identifiers;
    DenseArenaInterner *strings;
    DynArray *tokens;
} Lexer;
void lexer_populate_default_keywords(DenseArenaInterner *keywords);
Lexer* lexer_create(const char *source, size_t source_len, Arena *arena);
Lexer* lexer_create_ex(const char *source, size_t source_len, Arena *arena,
                      DenseArenaInterner *keywords,
                      DenseArenaInterner *identifiers,
                      DenseArenaInterner *strings);
void lexer_destroy(Lexer *lexer);
_Bool lexer_at_end(const Lexer *lexer);
Token lexer_next_token(Lexer *lexer);
_Bool lexer_lex_all(Lexer *lexer);
Token* lexer_get_tokens(Lexer *lexer, size_t *count);
const char* token_type_to_string(TokenType type);
void lexer_reset(Lexer *lexer);
void print_token(const Token *tok);
typedef struct {
    DynArray *tokens;
    size_t current;
    size_t end;
    char *filename;
    Arena *arena;
} Parser;
typedef struct {
    char *message;
    Token *token;
    Parser *p;
    int use_prev_token;
} ParseError;
Parser *parser_create(DynArray *tokens, char *filename, Arena *arena);
void parser_free(Parser *parser);
Token *current_token(Parser *p);
Token *peek(Parser *p, size_t offset);
Token *parser_advance(Parser *p);
Token *consume(Parser *p, TokenType expected);
int parser_match(Parser *p, TokenType expected);
void create_parse_error(ParseError *err_out, Parser *p, const char *message, Token *token);
void print_parse_error(ParseError *error);
AstNode *new_node_or_err(Parser *p, AstNodeType kind, ParseError *err, const char *oom_msg);
DynArray *alloc_dynarray(Parser *p, ParseError *err, size_t elem_size, int initial_capacity, const char *oom_msg);
AstNode *parse_statement(Parser *p, ParseError *err);
AstNode *parse_block(Parser *p, ParseError *err);
AstNode *parse_if_statement(Parser *p, ParseError *err);
AstNode *parse_while_statement(Parser *p, ParseError *err);
AstNode *parse_for_statement(Parser *p, ParseError *err);
AstNode *parse_return_statement(Parser *p, ParseError *err);
AstNode *parse_break_statement(Parser *p, ParseError *err);
AstNode *parse_continue_statement(Parser *p, ParseError *err);
AstNode *parse_defer_statement(Parser *p, ParseError *err);
AstNode *parse_expression_statement(Parser *p, ParseError *err);
AstNode *parse_program(Parser *p, ParseError *err);
AstNode *parse_declaration(Parser *p, ParseError *err);
AstNode *parse_import_declaration(Parser *p, ParseError *err);
AstNode *parse_alias_declaration(Parser *p, ParseError *err);
AstNode *parse_struct_declaration(Parser *p, ParseError *err);
AstNode *parse_declaration_stmt(Parser *p, ParseError *err);
AstNode *parse_variable_declaration(Parser *p, ParseError *err);
AstNode *parse_function_declaration(Parser *p, ParseError *err);
int parse_parameter_list(Parser *p, AstNode *func_decl, ParseError *err);

struct timespec
{
 __darwin_time_t tv_sec;
 long tv_nsec;
};
typedef __darwin_blkcnt_t blkcnt_t;
typedef __darwin_blksize_t blksize_t;

typedef __darwin_ino_t ino_t;
typedef __darwin_ino64_t ino64_t;
typedef __uint16_t nlink_t;

typedef __darwin_gid_t gid_t;

typedef __darwin_time_t time_t;
struct ostat {
 __uint16_t st_dev;
 ino_t st_ino;
 mode_t st_mode;
 nlink_t st_nlink;
 __uint16_t st_uid;
 __uint16_t st_gid;
 __uint16_t st_rdev;
 __int32_t st_size;
 struct timespec st_atimespec;
 struct timespec st_mtimespec;
 struct timespec st_ctimespec;
 __int32_t st_blksize;
 __int32_t st_blocks;
 __uint32_t st_flags;
 __uint32_t st_gen;
};
struct stat { dev_t st_dev; mode_t st_mode; nlink_t st_nlink; __darwin_ino64_t st_ino; uid_t st_uid; gid_t st_gid; dev_t st_rdev; struct timespec st_atimespec; struct timespec st_mtimespec; struct timespec st_ctimespec; struct timespec st_birthtimespec; off_t st_size; blkcnt_t st_blocks; blksize_t st_blksize; __uint32_t st_flags; __uint32_t st_gen; __int32_t st_lspare; __int64_t st_qspare[2]; };
int chmod(const char *, mode_t) __asm("_" "chmod" );
int fchmod(int, mode_t) __asm("_" "fchmod" );
int fstat(int, struct stat *) __asm("_" "fstat" );
int lstat(const char *, struct stat *) __asm("_" "lstat" );
int mkdir(const char *, mode_t);
int mkfifo(const char *, mode_t);
int stat(const char *, struct stat *) __asm("_" "stat" );
int mknod(const char *, mode_t, dev_t);
mode_t umask(mode_t);
int fchmodat(int, const char *, mode_t, int) __attribute__((availability(macosx,introduced=10.10)));
int fstatat(int, const char *, struct stat *, int) __asm("_" "fstatat" ) __attribute__((availability(macosx,introduced=10.10)));
int mkdirat(int, const char *, mode_t) __attribute__((availability(macosx,introduced=10.10)));
int mkfifoat(int, const char *, mode_t) __attribute__((availability(macos,introduced=13.0))) __attribute__((availability(ios,introduced=16.0))) __attribute__((availability(tvos,introduced=16.0))) __attribute__((availability(watchos,introduced=9.0)));
int mknodat(int, const char *, mode_t, dev_t) __attribute__((availability(macos,introduced=13.0))) __attribute__((availability(ios,introduced=16.0))) __attribute__((availability(tvos,introduced=16.0))) __attribute__((availability(watchos,introduced=9.0)));
int futimens(int __fd, const struct timespec __times[2]) __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0)));
int utimensat(int __fd, const char *__path, const struct timespec __times[2],
    int __flag) __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0)));
struct _filesec;
typedef struct _filesec *filesec_t;
int chflags(const char *, __uint32_t);
int chmodx_np(const char *, filesec_t);
int fchflags(int, __uint32_t);
int fchmodx_np(int, filesec_t);
int fstatx_np(int, struct stat *, filesec_t) __asm("_" "fstatx_np" );
int lchflags(const char *, __uint32_t) __attribute__((availability(macosx,introduced=10.5)));
int lchmod(const char *, mode_t) __attribute__((availability(macosx,introduced=10.5)));
int lstatx_np(const char *, struct stat *, filesec_t) __asm("_" "lstatx_np" );
int mkdirx_np(const char *, filesec_t);
int mkfifox_np(const char *, filesec_t);
int statx_np(const char *, struct stat *, filesec_t) __asm("_" "statx_np" );
int umaskx_np(filesec_t) __attribute__((availability(macosx,introduced=10.4,deprecated=10.6)));
typedef __builtin_va_list __gnuc_va_list;
typedef __builtin_va_list va_list;
typedef struct {
    char *buf;
    size_t len;
    size_t cap;
    Arena *arena;
} StrBuf;
static void strbuf_init(StrBuf *sb, Arena *arena) {
    sb->arena = arena;
    sb->cap = 128;
    sb->len = 0;
    sb->buf = arena_alloc(arena, sb->cap);
    sb->buf[0] = '\0';
}
static void strbuf_append(StrBuf *sb, const char *s) {
    if (!s) return;
    size_t slen = strlen(s);
    if (sb->len + slen + 1 > sb->cap) {
        size_t new_cap = sb->cap * 2;
        while (sb->len + slen + 1 > new_cap) new_cap *= 2;
        char *new_buf = arena_alloc(sb->arena, new_cap);
        __builtin___memcpy_chk (new_buf, sb->buf, sb->len + 1, __builtin_object_size (new_buf, 0));
        sb->buf = new_buf;
        sb->cap = new_cap;
    }
    __builtin___memcpy_chk (sb->buf + sb->len, s, slen, __builtin_object_size (sb->buf + sb->len, 0));
    sb->len += slen;
    sb->buf[sb->len] = '\0';
}
static void strbuf_append_fmt(StrBuf *sb, const char *fmt, ...) {
    va_list args;
    __builtin_va_start(args, fmt);
    char tmp[1024];
    int n = __builtin___vsnprintf_chk (tmp, sizeof(tmp), 0, __builtin_object_size (tmp, 2 > 1 ? 1 : 0), fmt, args);
    __builtin_va_end(args);
    if (n < 0) return;
    if ((size_t)n < sizeof(tmp)) {
        strbuf_append(sb, tmp);
    } else {
        char *big_tmp = xmalloc(n + 1);
        __builtin_va_start(args, fmt);
        __builtin___vsnprintf_chk (big_tmp, n + 1, 0, __builtin_object_size (big_tmp, 2 > 1 ? 1 : 0), fmt, args);
        __builtin_va_end(args);
        strbuf_append(sb, big_tmp);
        free(big_tmp);
    }
}
ModuleLoader* module_loader_create(Arena *arena, Options *opts,
                                   DenseArenaInterner *keywords,
                                   DenseArenaInterner *identifiers,
                                   DenseArenaInterner *strings) {
    ModuleLoader *loader = arena_alloc(arena, sizeof(ModuleLoader));
    loader->arena = arena;
    loader->opts = opts;
    loader->keywords = keywords;
    loader->identifiers = identifiers;
    loader->strings = strings;
    loader->units = hashmap_create(16);
    loader->units_by_logical_path = hashmap_create(16);
    loader->units_ordered = arena_alloc(arena, sizeof(DynArray));
    dynarray_init_in_arena(loader->units_ordered, arena, sizeof(CompilationUnit*), 8);
    loader->project_root = ((void*)0);
    return loader;
}
static char* get_absolute_path_real(Arena *arena, const char *path) {
    char *abs = realpath(path, ((void*)0));
    if (!abs) return ((void*)0);
    char *interned = arena_alloc(arena, strlen(abs) + 1);
    __builtin___strcpy_chk (interned, abs, __builtin_object_size (interned, 2 > 1 ? 1 : 0));
    free(abs);
    return interned;
}
CompilationUnit* module_loader_get_unit(ModuleLoader *loader, const char *path) {
    return (CompilationUnit*)hashmap_get(loader->units, (void*)path, str_hash, str_cmp);
}
static _Bool file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && (((st.st_mode) & 0170000) == 0100000);
}
int load_module_recursive(ModuleLoader *loader, const char *path, const char *logical_path, const char *importer_path, int depth) {
    if (depth > 256) {
        fprintf(__stderrp, "Error: Maximum recursion depth (%d) exceeded while loading modules.\n", 256);
        return 2;
    }
    char *abs_path = get_absolute_path_real(loader->arena, path);
    if (!abs_path) {
        StrBuf fallback_sb;
        strbuf_init(&fallback_sb, loader->arena);
        strbuf_append_fmt(&fallback_sb, "%s/module.tn", path);
        abs_path = get_absolute_path_real(loader->arena, fallback_sb.buf);
        if (!abs_path) {
            if (importer_path) {
                fprintf(__stderrp, "Error in %s: Could not resolve module path '%s'\n", importer_path, path);
            } else {
                fprintf(__stderrp, "Error: Could not resolve module path '%s'\n", path);
            }
            return 2;
        }
    }
    if (!loader->project_root) {
        char *dir = xstrdup(abs_path);
        char *last_slash = strrchr(dir, '/');
        if (last_slash) *last_slash = '\0';
        loader->project_root = arena_alloc(loader->arena, strlen(dir) + 1);
        __builtin___strcpy_chk (loader->project_root, dir, __builtin_object_size (loader->project_root, 2 > 1 ? 1 : 0));
        free(dir);
    }
    CompilationUnit *unit = module_loader_get_unit(loader, abs_path);
    if (unit) {
        if (logical_path) {
            hashmap_put(loader->units_by_logical_path, (void*)logical_path, unit, str_hash, str_cmp);
            if (!unit->logical_path) unit->logical_path = (char*)logical_path;
        }
        return 0;
    }
    if (loader->opts->verbose) printf("Loading module: %s\n", abs_path);
    char *src = read_file(abs_path);
    if (!src) {
        fprintf(__stderrp, "Error: Failed to read file: %s\n", abs_path);
        return 2;
    }
    size_t src_len = strlen(src);
    Lexer *lexer = lexer_create_ex(src, src_len, loader->arena, loader->keywords, loader->identifiers, loader->strings);
    if (!lexer_lex_all(lexer)) {
        fprintf(__stderrp, "Error: Lexing failed for %s\n", abs_path);
        free(src);
        return 3;
    }
    Parser *parser = parser_create(lexer->tokens, abs_path, loader->arena);
    ParseError parse_err = {0};
    AstNode *module_ast = parse_program(parser, &parse_err);
    if (parse_err.message) {
        print_parse_error(&parse_err);
        free(src);
        return 4;
    }
    if (!module_ast) {
        free(src);
        return 0;
    }
    unit = arena_alloc(loader->arena, sizeof(CompilationUnit));
    unit->absolute_path = abs_path;
    unit->logical_path = (char*)logical_path;
    unit->ast_root = module_ast;
    unit->global_scope = ((void*)0);
    unit->signatures_resolved = 0;
    unit->imports_resolved = 0;
    hashmap_put(loader->units, abs_path, unit, str_hash, str_cmp);
    if (logical_path) {
        hashmap_put(loader->units_by_logical_path, (void*)logical_path, unit, str_hash, str_cmp);
    }
    AstProgram *module_prog = &module_ast->data.program;
    StrBuf current_dir_sb;
    strbuf_init(&current_dir_sb, loader->arena);
    const char *last_slash = strrchr(abs_path, '/');
    if (last_slash) {
        size_t len = (size_t)(last_slash - abs_path);
        char *tmp = xmalloc(len + 1);
        __builtin___memcpy_chk (tmp, abs_path, len, __builtin_object_size (tmp, 0));
        tmp[len] = '\0';
        strbuf_append(&current_dir_sb, tmp);
        free(tmp);
    } else {
        strbuf_append(&current_dir_sb, ".");
    }
    for (size_t i = 0; i < module_prog->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(module_prog->decls, i);
        if (decl->node_type == AST_IMPORT_DECLARATION) {
            AstImportDeclaration *imp = &decl->data.import_declaration;
            StrBuf cp_sb, cl_sb;
            strbuf_init(&cp_sb, loader->arena);
            strbuf_init(&cl_sb, loader->arena);
            for (size_t j = 0; j < imp->module_path->count; j++) {
                InternResult *part = *(InternResult**)dynarray_get(imp->module_path, j);
                Slice *s = (Slice*)part->key;
                if (j > 0) strbuf_append(&cp_sb, "/");
                strbuf_append_fmt(&cp_sb, "%.*s", (int)s->len, s->ptr);
                if (j > 0) strbuf_append(&cl_sb, ".");
                strbuf_append_fmt(&cl_sb, "%.*s", (int)s->len, s->ptr);
            }
            StrBuf mod_path_full_sb;
            strbuf_init(&mod_path_full_sb, loader->arena);
            char *target_logical = ((void*)0);
            if (imp->leading_dots > 0) {
                StrBuf base_dir_sb;
                strbuf_init(&base_dir_sb, loader->arena);
                strbuf_append(&base_dir_sb, current_dir_sb.buf);
                for (int d = 1; d < imp->leading_dots; d++) {
                    char *up = strrchr(base_dir_sb.buf, '/');
                    if (up) {
                        *up = '\0';
                        base_dir_sb.len = strlen(base_dir_sb.buf);
                    }
                }
                strbuf_append_fmt(&mod_path_full_sb, "%s/%s", base_dir_sb.buf, cp_sb.buf);
                if (unit->logical_path) {
                    size_t t_len = strlen(unit->logical_path) + cl_sb.len + 2;
                    target_logical = arena_alloc(loader->arena, t_len);
                    __builtin___snprintf_chk (target_logical, t_len, 0, __builtin_object_size (target_logical, 2 > 1 ? 1 : 0), "%s.%s", unit->logical_path, cl_sb.buf);
                } else {
                    target_logical = arena_alloc(loader->arena, cl_sb.len + 1);
                    __builtin___strcpy_chk (target_logical, cl_sb.buf, __builtin_object_size (target_logical, 2 > 1 ? 1 : 0));
                }
            } else if (imp->is_root_relative) {
                strbuf_append_fmt(&mod_path_full_sb, "%s/%s", loader->project_root, cp_sb.buf);
                target_logical = arena_alloc(loader->arena, cl_sb.len + 1);
                __builtin___strcpy_chk (target_logical, cl_sb.buf, __builtin_object_size (target_logical, 2 > 1 ? 1 : 0));
            } else {
                strbuf_append_fmt(&mod_path_full_sb, "%s/%s", loader->opts->stdlib_path, cp_sb.buf);
                target_logical = arena_alloc(loader->arena, cl_sb.len + 1);
                __builtin___strcpy_chk (target_logical, cl_sb.buf, __builtin_object_size (target_logical, 2 > 1 ? 1 : 0));
            }
            StrBuf target_file_sb;
            strbuf_init(&target_file_sb, loader->arena);
            strbuf_append_fmt(&target_file_sb, "%s.tn", mod_path_full_sb.buf);
            if (!file_exists(target_file_sb.buf)) {
                 target_file_sb.len = 0;
                 target_file_sb.buf[0] = '\0';
                 strbuf_append_fmt(&target_file_sb, "%s/module.tn", mod_path_full_sb.buf);
            }
            int res = load_module_recursive(loader, target_file_sb.buf, target_logical, abs_path, depth + 1);
            if (res == 0) {
                decl->data.import_declaration.resolved_logical_path = target_logical;
            } else {
                hashmap_remove(loader->units, abs_path, str_hash, str_cmp, ((void*)0), ((void*)0));
                if (logical_path) {
                    hashmap_remove(loader->units_by_logical_path, (void*)logical_path, str_hash, str_cmp, ((void*)0), ((void*)0));
                }
                free(src);
                return res;
            }
        }
    }
    dynarray_push_value(loader->units_ordered, &unit);
    free(src);
    return 0;
}

typedef __darwin_clock_t clock_t;
struct tm {
 int tm_sec;
 int tm_min;
 int tm_hour;
 int tm_mday;
 int tm_mon;
 int tm_year;
 int tm_wday;
 int tm_yday;
 int tm_isdst;
 long tm_gmtoff;
 char * tm_zone;
};
extern char * tzname[];
extern int getdate_err;
extern long timezone __asm("_" "timezone" );
extern int daylight;
char * asctime(const struct tm *);
clock_t clock(void) __asm("_" "clock" );
char * ctime(const time_t *);
double difftime(time_t, time_t);
struct tm *getdate(const char *);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
time_t mktime(struct tm *) __asm("_" "mktime" );
size_t strftime(char * restrict, size_t __maxsize, const char * restrict, const struct tm * restrict) __asm("_" "strftime" );
char * strptime(const char * restrict, const char * restrict, struct tm * restrict) __asm("_" "strptime" );
time_t time(time_t *);
void tzset(void);
char * asctime_r(const struct tm * restrict, char * restrict );
char * ctime_r(const time_t *, char *);
struct tm *gmtime_r(const time_t * restrict, struct tm * restrict);
struct tm *localtime_r(const time_t * restrict, struct tm * restrict);
time_t posix2time(time_t);
void tzsetwall(void);
time_t time2posix(time_t);
time_t timelocal(struct tm * const);
time_t timegm(struct tm * const);
int nanosleep(const struct timespec *__rqtp, struct timespec *__rmtp) __asm("_" "nanosleep" );
typedef enum {
_CLOCK_REALTIME __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) = 0,
_CLOCK_MONOTONIC __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) = 6,
_CLOCK_MONOTONIC_RAW __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) = 4,
_CLOCK_MONOTONIC_RAW_APPROX __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) = 5,
_CLOCK_UPTIME_RAW __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) = 8,
_CLOCK_UPTIME_RAW_APPROX __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) = 9,
_CLOCK_PROCESS_CPUTIME_ID __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) = 12,
_CLOCK_THREAD_CPUTIME_ID __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) = 16
} clockid_t;
__attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0)))
int clock_getres(clockid_t __clock_id, struct timespec *__res);
__attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0)))
int clock_gettime(clockid_t __clock_id, struct timespec *__tp);
__attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0)))
__uint64_t clock_gettime_nsec_np(clockid_t __clock_id);
__attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,unavailable)))
__attribute__((availability(tvos,unavailable))) __attribute__((availability(watchos,unavailable)))
int clock_settime(clockid_t __clock_id, const struct timespec *__tp);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(tvos,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0)))
int timespec_get(struct timespec *ts, int base);
typedef struct fd_set {
 __int32_t fds_bits[((((1024) % ((sizeof(__int32_t) * 8))) == 0) ? ((1024) / ((sizeof(__int32_t) * 8))) : (((1024) / ((sizeof(__int32_t) * 8))) + 1))];
} fd_set;
int __darwin_check_fd_set_overflow(int, const void *, int) __attribute__((availability(macos,introduced=11.0))) __attribute__((availability(ios,introduced=14.0))) __attribute__((availability(tvos,introduced=14.0))) __attribute__((availability(watchos,introduced=7.0)));
inline __attribute__ ((__always_inline__)) int
__darwin_check_fd_set(int _a, const void *_b)
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunguarded-availability-new"
 if ((uintptr_t)&__darwin_check_fd_set_overflow != (uintptr_t) 0) {
  return __darwin_check_fd_set_overflow(_a, _b, 0);
 } else {
  return 1;
 }
#pragma clang diagnostic pop
}
inline __attribute__ ((__always_inline__)) int
__darwin_fd_isset(int _fd, const struct fd_set *_p)
{
 if (__darwin_check_fd_set(_fd, (const void *) _p)) {
  return _p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] & ((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8))));
 }
 return 0;
}
inline __attribute__ ((__always_inline__)) void
__darwin_fd_set(int _fd, struct fd_set *const _p)
{
 if (__darwin_check_fd_set(_fd, (const void *) _p)) {
  (_p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] |= ((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8)))));
 }
}
inline __attribute__ ((__always_inline__)) void
__darwin_fd_clr(int _fd, struct fd_set *const _p)
{
 if (__darwin_check_fd_set(_fd, (const void *) _p)) {
  (_p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] &= ~((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8)))));
 }
}
struct timeval64 {
 __int64_t tv_sec;
 __int64_t tv_usec;
};
typedef __darwin_suseconds_t suseconds_t;
struct itimerval {
 struct timeval it_interval;
 struct timeval it_value;
};
struct timezone {
 int tz_minuteswest;
 int tz_dsttime;
};
struct clockinfo {
 int hz;
 int tick;
 int tickadj;
 int stathz;
 int profhz;
};
int adjtime(const struct timeval *, struct timeval *);
int futimes(int, const struct timeval *);
int lutimes(const char *, const struct timeval *) __attribute__((availability(macosx,introduced=10.5)));
int settimeofday(const struct timeval *, const struct timezone *);
int getitimer(int, struct itimerval *);
int gettimeofday(struct timeval * restrict, void * restrict);
int select(int, fd_set * restrict, fd_set * restrict,
    fd_set * restrict, struct timeval * restrict)
__asm("_" "select" )
;
int setitimer(int, const struct itimerval * restrict,
    struct itimerval * restrict);
int utimes(const char *, const struct timeval *);
double now_seconds(void) {
    struct timespec ts;
    clock_gettime(_CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}
size_t get_peak_rss_kb(void) {
    struct rusage r;
    getrusage(0, &r);
    return (size_t)r.ru_maxrss / 1024;
}
void *xmalloc(size_t size) {
    void *p = malloc(size);
    if (!p && size > 0) {
        fprintf(__stderrp, "fatal: out of memory (malloc %zu bytes)\n", size);
        abort();
    }
    return p;
}
void *xcalloc(size_t nmemb, size_t size) {
    void *p = calloc(nmemb, size);
    if (!p && nmemb > 0 && size > 0) {
        fprintf(__stderrp, "fatal: out of memory (calloc %zu * %zu bytes)\n", nmemb, size);
        abort();
    }
    return p;
}
char *xstrdup(const char *s) {
    if (!s) return ((void*)0);
    char *p = strdup(s);
    if (!p) {
        fprintf(__stderrp, "fatal: out of memory (strdup)\n");
        abort();
    }
    return p;
}
typedef struct AstNode AstNode;
void ice_impl(const char *file, int line, const char *fmt, ...) __attribute__((noreturn));
void ice_impl_at(const char *file, int line, const char *src_file, Span span, const char *fmt, ...) __attribute__((noreturn));
typedef void (*os_function_t)(void *_Nullable);
typedef void (^os_block_t)(void);

typedef __darwin_uuid_t uuid_t;
typedef __darwin_uuid_string_t uuid_string_t;
static const uuid_t UUID_NULL __attribute__ ((unused)) = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void uuid_clear(uuid_t uu);
int uuid_compare(const uuid_t uu1, const uuid_t uu2);
void uuid_copy(uuid_t dst, const uuid_t src);
void uuid_generate(uuid_t out);
void uuid_generate_random(uuid_t out);
void uuid_generate_time(uuid_t out);
int uuid_is_null(const uuid_t uu);
int uuid_parse(const uuid_string_t in, uuid_t uu);
void uuid_unparse(const uuid_t uu, uuid_string_t out);
void uuid_unparse_lower(const uuid_t uu, uuid_string_t out);
void uuid_unparse_upper(const uuid_t uu, uuid_string_t out);
int backtrace(void **, int __size) __attribute__((availability(macosx,introduced=10.5)));
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(tvos,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0)))
extern __attribute__((__visibility__("default")))
int backtrace_from_fp(void *startfp, void ** array, int size);
char * * backtrace_symbols(void* const* , int __size) __attribute__((availability(macosx,introduced=10.5)));
void backtrace_symbols_fd(void* const* ,int __size,int) __attribute__((availability(macosx,introduced=10.5)));
struct image_offset {
 uuid_t uuid;
 uint32_t offset;
};
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(tvos,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0)))
extern __attribute__((__visibility__("default")))
void backtrace_image_offsets(void* const* array,
  struct image_offset *image_offsets, int size);
__attribute__((availability(macos,introduced=12.0))) __attribute__((availability(ios,introduced=15.0))) __attribute__((availability(tvos,introduced=15.0))) __attribute__((availability(watchos,introduced=8.0)))
size_t backtrace_async(void** array, size_t length, uint32_t *task_id);

void ice_impl(const char *file, int line, const char *fmt, ...) {
    fprintf(__stderrp, "\033[1;31mINTERNAL COMPILER ERROR\033[0m at %s:%d\n", file, line);
    va_list args;
    __builtin_va_start(args, fmt);
    fprintf(__stderrp, "Message: ");
    vfprintf(__stderrp, fmt, args);
    fprintf(__stderrp, "\n\n");
    __builtin_va_end(args);
    void *buffer[100];
    int nptrs = backtrace(buffer, 100);
    fprintf(__stderrp, "Stack Trace:\n");
    backtrace_symbols_fd(buffer, nptrs, fileno(__stderrp));
    fprintf(__stderrp, "\nThis is a bug in the compiler. Please report it.\n");
    abort();
}
void ice_impl_at(const char *file, int line, const char *src_file, Span span, const char *fmt, ...) {
    fprintf(__stderrp, "\033[1;31mINTERNAL COMPILER ERROR\033[0m at %s:%d\n", file, line);
    fprintf(__stderrp, "  Source: %s:%zu:%zu\n", src_file ? src_file : "?", span.start_line, span.start_col);
    va_list args;
    __builtin_va_start(args, fmt);
    fprintf(__stderrp, "Message: ");
    vfprintf(__stderrp, fmt, args);
    fprintf(__stderrp, "\n\n");
    __builtin_va_end(args);
    void *buffer[100];
    int nptrs = backtrace(buffer, 100);
    fprintf(__stderrp, "Stack Trace:\n");
    backtrace_symbols_fd(buffer, nptrs, fileno(__stderrp));
    fprintf(__stderrp, "\nThis is a bug in the compiler. Please report it.\n");
    abort();
}


char *read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("fopen");
        return ((void*)0);
    }
    fseek(file, 0, 2);
    long length = ftell(file);
    if (length < 0) {
        perror("ftell");
        fclose(file);
        return ((void*)0);
    }
    rewind(file);
    char *buffer = malloc(length + 1);
    if (!buffer) {
        perror("malloc");
        fclose(file);
        return ((void*)0);
    }
    if (fread(buffer, 1, length, file) != (size_t)length) {
        perror("fread");
        free(buffer);
        fclose(file);
        return ((void*)0);
    }
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}
void free_file_content(char *content) {
    if (content) {
        free(content);
    }
}
int read_line_from_file(const char *filename, size_t line_no,
                               char *buf, size_t buf_size, size_t *out_len) {
    if (!filename) return -1;
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    size_t current_line = 1;
    while (fgets(buf, (int)buf_size, f)) {
        if (current_line == line_no) {
            *out_len = strlen(buf);
            fclose(f);
            return 0;
        }
        current_line++;
    }
    fclose(f);
    return -1;
}
void print_source_excerpt_span(const char *filename, size_t line_no, size_t start_col, size_t end_col) {
    if (!filename || line_no == 0) return;
    char buf[512]; size_t len = 0;
    if (read_line_from_file(filename, line_no, buf, sizeof(buf), &len) != 0) return;
    if (len > 0 && buf[len-1] == '\n') { buf[len - 1] = '\0'; len--; }
    fprintf(__stderrp, "\x1b[33m%4zu\x1b[0m | %s\n", line_no, buf);
    fprintf(__stderrp, "     | ");
    for (size_t i = 1; i < start_col; i++) fputc(' ', __stderrp);
    fprintf(__stderrp, "\x1b[31m");
    size_t width = (end_col >= start_col) ? (end_col - start_col) : 1;
    if (width == 0) width = 1;
    for (size_t i = 0; i < width; i++) fputc('^', __stderrp);
    fprintf(__stderrp, "\x1b[0m\n");
}
void print_source_excerpt(const char *filename, size_t line_no, size_t col) {
    print_source_excerpt_span(filename, line_no, col, col + 1);
}

static size_t align_up(size_t v, size_t a) {
    return (v + a - 1) & ~(a - 1);
}
Arena *arena_create(size_t initial_capacity) {
    if (initial_capacity == 0) initial_capacity = 1024;
    if (initial_capacity > (18446744073709551615UL / 2)) initial_capacity = 1024;
    Arena *arena = malloc(sizeof(Arena));
    if (!arena) return ((void*)0);
    size_t header = sizeof(ArenaBlock);
    size_t alloc_req;
    if (initial_capacity > 18446744073709551615UL - header) { free(arena); return ((void*)0); }
    alloc_req = header + initial_capacity;
    ArenaBlock *block = malloc(alloc_req);
    if (!block) { free(arena); return ((void*)0); }
    block->next = ((void*)0);
    block->capacity = initial_capacity;
    block->used = 0;
    arena->blocks = block;
    arena->block_size = initial_capacity;
    return arena;
}
void arena_destroy(Arena *arena) {
    if (!arena) return;
    ArenaBlock *b = arena->blocks;
    while (b) {
        ArenaBlock *n = b->next;
        free(b);
        b = n;
    }
    free(arena);
}
void arena_reset(Arena *arena) {
    if (!arena) return;
    ArenaBlock *b = arena->blocks->next;
    while (b) {
        ArenaBlock *n = b->next;
        free(b);
        b = n;
    }
    arena->blocks->next = ((void*)0);
    arena->blocks->used = 0;
}
void *arena_alloc(Arena *arena, size_t size) {
    if (!arena) return ((void*)0);
    if (size == 0) return ((void*)0);
    const size_t align = _Alignof(max_align_t);
    ArenaBlock *block = arena->blocks;
    if (!block) return ((void*)0);
    size_t offset = align_up(block->used, align);
    if (offset + size > block->capacity) {
        size_t new_capacity = arena->block_size;
        while (new_capacity < size) {
            if (new_capacity > 18446744073709551615UL / 2) { new_capacity = size; break; }
            new_capacity *= 2;
        }
        size_t header = sizeof(ArenaBlock);
        if (new_capacity > 18446744073709551615UL - header) return ((void*)0);
        ArenaBlock *new_block = malloc(header + new_capacity);
        if (!new_block) return ((void*)0);
        new_block->next = arena->blocks;
        new_block->capacity = new_capacity;
        new_block->used = 0;
        arena->blocks = new_block;
        block = new_block;
        offset = 0;
    }
    void *ptr = (void*)(block->data + offset);
    block->used = offset + align_up(size, align);
    return ptr;
}
void *arena_calloc(Arena *arena, size_t size) {
    void *p = arena_alloc(arena, size);
    if (!p) return ((void*)0);
    __builtin___memset_chk (p, 0, size, __builtin_object_size (p, 0));
    return p;
}
size_t arena_bytes_used(const Arena *arena) {
    if (!arena) return 0;
    size_t total = 0;
    for (const ArenaBlock *b = arena->blocks; b; b = b->next)
        total += b->used;
    return total;
}
size_t arena_bytes_capacity(const Arena *arena) {
    if (!arena) return 0;
    size_t total = 0;
    for (const ArenaBlock *b = arena->blocks; b; b = b->next)
        total += b->capacity;
    return total;
}
size_t arena_block_count(const Arena *arena) {
    if (!arena) return 0;
    size_t count = 0;
    for (const ArenaBlock *b = arena->blocks; b; b = b->next)
        count++;
    return count;
}
size_t arena_total_allocated(const Arena *arena) {
    if (!arena) return 0;
    size_t total = 0;
    for (const ArenaBlock *b = arena->blocks; b; b = b->next)
        total += b->used;
    return total;
}

Scope *scope_create(Arena *arena, Scope *parent, int identifier_count, int kind) {
    Scope *scope = arena_calloc(arena, sizeof(Scope));
    if (!scope) return ((void*)0);
    scope->symbols = arena_calloc(arena, sizeof(Symbol *) * identifier_count);
    if (!scope->symbols) {
        return ((void*)0);
    }
    dynarray_init_in_arena(&scope->symbols_list, arena, sizeof(Symbol *), identifier_count > 0 ? identifier_count / 4 : 8);
    scope->depth = parent ? parent->depth + 1 : 0;
    scope->parent = parent;
    scope->arena = arena;
    scope->capacity = identifier_count;
    scope->kind = kind;
    scope->unit = ((void*)0);
    return scope;
}
Symbol *scope_define_symbol(Scope *scope, InternResult *rec, Type *type, SymbolValue kind, const char *filename, _Bool is_pub, AstNode *decl_node) {
    if (!scope || !rec) {
        return ((void*)0);
    }
    if ((size_t)rec->entry->dense_index >= scope->capacity) {
        size_t new_cap = scope->capacity ? scope->capacity * 2 : 16;
        while (new_cap <= (size_t)rec->entry->dense_index) {
            new_cap *= 2;
        }
        Symbol **new_symbols = arena_calloc(scope->arena, sizeof(Symbol *) * new_cap);
        if (!new_symbols) return ((void*)0);
        if (scope->symbols) {
            __builtin___memcpy_chk (new_symbols, scope->symbols, sizeof(Symbol *) * scope->capacity, __builtin_object_size (new_symbols, 0));
        }
        scope->symbols = new_symbols;
        scope->capacity = new_cap;
    }
    if (scope_lookup_symbol_local(scope, rec)) {
        return ((void*)0);
    }
    Symbol *symbol = arena_calloc(scope->arena, sizeof(Symbol));
    if (!symbol) {
        return ((void*)0);
    }
    symbol->name_rec = rec;
    symbol->type = type;
    symbol->kind = kind;
    symbol->flags = SYMBOL_FLAG_NONE;
    symbol->filename = filename;
    symbol->is_pub = is_pub;
    symbol->decl_node = decl_node;
    symbol->module_scope = ((void*)0);
    scope->symbols[rec->entry->dense_index] = symbol;
    scope->symbol_count++;
    dynarray_push_value(&scope->symbols_list, &symbol);
    return symbol;
}
Symbol *scope_lookup_symbol_local(Scope *scope, InternResult *rec) {
    if (!scope || !rec) return ((void*)0);
    if ((size_t)rec->entry->dense_index >= scope->capacity) return ((void*)0);
    return scope->symbols[rec->entry->dense_index];
}
Symbol *scope_lookup_symbol(Scope *scope, InternResult *rec, const char *caller_filename) {
    if (!scope || !rec) return ((void*)0);
    _Bool is_keyword_key = (rec->entry->meta != ((void*)0));
    Scope *current = scope;
    while (current) {
        _Bool is_keyword_scope = (current->kind == SCOPE_KEYWORDS);
        if (is_keyword_key == is_keyword_scope) {
             Symbol *symbol = scope_lookup_symbol_local(current, rec);
             if (symbol) {
                 while (symbol && symbol->kind == SYMBOL_VALUE_ALIAS) {
                     symbol = symbol->target_symbol;
                 }
                 if (!symbol) {
                      current = current->parent;
                      continue;
                 }
                 if (current->unit && caller_filename && strcmp(current->unit->absolute_path, caller_filename) == 0) {
                     return symbol;
                 }
                 if (current->depth > 0 && !current->unit) {
                     return symbol;
                 }
                 if (symbol->is_pub) {
                     return symbol;
                 }
                 if (!current->unit) return symbol;
                 current = current->parent;
                 continue;
             }
        }
        current = current->parent;
    }
    return ((void*)0);
}
Symbol *symbol_set_value_int(Symbol *symbol, int value){
    if (!symbol) return ((void*)0);
    symbol->kind = SYMBOL_VALUE_INT;
    symbol->value.int_val = (int64_t)value;
    return symbol;
}
Symbol *symbol_set_value_float(Symbol *symbol, float value){
    if (!symbol) return ((void*)0);
    symbol->kind = SYMBOL_VALUE_FLOAT;
    symbol->value.float_val = (double)value;
    return symbol;
}
Symbol *symbol_set_value_bool(Symbol *symbol, _Bool value){
    if (!symbol) return ((void*)0);
    symbol->kind = SYMBOL_VALUE_BOOL;
    symbol->value.bool_val = value;
    return symbol;
}
size_t scope_get_symbol_count(Scope *scope){
    if (!scope) return 0;
    return scope->symbol_count;
}
void scope_set_flags(Scope *scope, InternResult *rec, int flags){
    if (!scope || !rec) return;
    Symbol *symbol = scope_lookup_symbol(scope, rec, ((void*)0));
    if (symbol) {
        symbol->flags |= flags;
    }
}
void scope_check_unused_symbols(Scope *scope){
    if (!scope) return;
    for (size_t i = 0; i < scope->symbols_list.count; i++) {
        Symbol *symbol = *(Symbol**)dynarray_get(&scope->symbols_list, i);
        if (symbol && !(symbol->flags & SYMBOL_FLAG_USED)) {
            printf("Warning: Unused symbol '%s'\n", symbol->name_rec->key ? (char*)symbol->name_rec->key : "(unknown)");
        }
    }
}
void scope_print_symbols(Scope *scope, int indent) {
    if (!scope) return;
    for (size_t i = 0; i < scope->symbols_list.count; ++i) {
        Symbol *s = *(Symbol**)dynarray_get(&scope->symbols_list, i);
        if (!s) continue;
        const char *name = s->name_rec && s->name_rec->key ? (char*)s->name_rec->key : "(unknown)";
        const char *type_name = s->type ? "(type present)" : "(none)";
        printf("%*s- Symbol: '%s', type: %s, flags: 0x%02x\n", indent, "", name, type_name, (unsigned)s->flags);
    }
}
void scope_print_hierarchy(Scope *scope) {
    if (!scope) return;
    int indent = 0;
    Scope *cur = scope;
    while (cur) {
        printf("%*s- Scope (depth %zu):\n", indent, "", cur->depth);
        scope_print_symbols(cur, indent + 2);
        cur = cur->parent;
        indent += 2;
    }
}

HashMap* hashmap_create(size_t bucket_count) {
    if (bucket_count == 0) bucket_count = 64;
    HashMap *map = calloc(1, sizeof(HashMap));
    if (!map) return ((void*)0);
    map->buckets = calloc(bucket_count, sizeof(DynArray));
    if (!map->buckets) {
        free(map);
        return ((void*)0);
    }
    for (size_t i = 0; i < bucket_count; i++) {
        dynarray_init(&map->buckets[i], sizeof(KeyValue));
    }
    map->bucket_count = bucket_count;
    map->size = 0;
    return map;
}
void hashmap_destroy(
    HashMap* map,
    void (*free_key)(void*),
    void (*free_value)(void*)
) {
    if (!map) return;
    for (size_t i = 0; i < map->bucket_count; i++) {
        DynArray *bucket = &map->buckets[i];
        if (!bucket) continue;
        for (size_t j = 0; j < bucket->count; j++) {
            KeyValue *kv = (KeyValue*)dynarray_get(bucket, j);
            if (!kv) continue;
            if (free_key) free_key(kv->key);
            if (free_value) free_value(kv->value);
        }
        dynarray_free(bucket);
    }
    free(map->buckets);
    free(map);
}
_Bool hashmap_rehash(
    HashMap* map,
    size_t new_bucket_count,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
) {
    if (!map || new_bucket_count == 0 || !hash || !cmp) return 0;
    DynArray *new_buckets = calloc(new_bucket_count, sizeof(DynArray));
    if (!new_buckets) return 0;
    for (size_t i = 0; i < new_bucket_count; i++) {
        dynarray_init(&new_buckets[i], sizeof(KeyValue));
    }
    for (size_t i = 0; i < map->bucket_count; i++) {
        DynArray *bucket = &map->buckets[i];
        if (!bucket) continue;
        for (size_t j = 0; j < bucket->count; j++) {
            KeyValue *old_kv = (KeyValue*)dynarray_get(bucket, j);
            if (!old_kv) continue;
            KeyValue kv_copy;
            kv_copy.key = old_kv->key;
            kv_copy.value = old_kv->value;
            size_t new_index = hash(kv_copy.key) % new_bucket_count;
            if (dynarray_push_value(&new_buckets[new_index], &kv_copy) != 0) {
                for (size_t k = 0; k < new_bucket_count; k++) {
                    dynarray_free(&new_buckets[k]);
                }
                free(new_buckets);
                return 0;
            }
        }
    }
    for (size_t i = 0; i < map->bucket_count; i++) {
        dynarray_free(&map->buckets[i]);
    }
    free(map->buckets);
    map->buckets = new_buckets;
    map->bucket_count = new_bucket_count;
    return 1;
}
_Bool hashmap_put(
    HashMap* map,
    void* key,
    void* value,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
) {
    if (!map || !hash || !cmp) return 0;
    if (map->size >= (map->bucket_count * 3) / 4) {
        size_t new_bucket_count = map->bucket_count * 2;
        if (!hashmap_rehash(map, new_bucket_count, hash, cmp)) {
        }
    }
    size_t bucket_index = hash(key) % map->bucket_count;
    DynArray *bucket = &map->buckets[bucket_index];
    for (size_t i = 0; i < bucket->count; i++) {
        KeyValue *kv = (KeyValue*)dynarray_get(bucket, i);
        if (kv && cmp(kv->key, key) == 0) {
            kv->value = value;
            return 1;
        }
    }
    KeyValue kv = {key, value};
    if (dynarray_push_value(bucket, &kv) != 0) {
        return 0;
    }
    map->size++;
    return 1;
}
void* hashmap_get(
    HashMap* map,
    void* key,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
) {
    if (!map || !hash || !cmp) return ((void*)0);
    size_t bucket_index = hash(key) % map->bucket_count;
    DynArray *bucket = &map->buckets[bucket_index];
    for (size_t i = 0; i < bucket->count; i++) {
        KeyValue *kv = (KeyValue*)dynarray_get(bucket, i);
        if (kv && cmp(kv->key, key) == 0) {
            return kv->value;
        }
    }
    return ((void*)0);
}
_Bool hashmap_remove(
    HashMap* map,
    void* key,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*),
    void (*free_key)(void*),
    void (*free_value)(void*)
) {
    if (!map || !hash || !cmp) return 0;
    size_t bucket_index = hash(key) % map->bucket_count;
    DynArray *bucket = &map->buckets[bucket_index];
    for (size_t i = 0; i < bucket->count; i++) {
        KeyValue *kv = (KeyValue*)dynarray_get(bucket, i);
        if (kv && cmp(kv->key, key) == 0) {
            if (free_key) free_key(kv->key);
            if (free_value) free_value(kv->value);
            dynarray_remove(bucket, i);
            map->size--;
            return 1;
        }
    }
    return 0;
}
void hashmap_foreach(
    HashMap* map,
    void (*callback)(void*, void*)
) {
    if (!map || !callback) return;
    for (size_t i = 0; i < map->bucket_count; i++) {
        DynArray *bucket = &map->buckets[i];
        for (size_t j = 0; j < bucket->count; j++) {
            KeyValue *kv = (KeyValue*)dynarray_get(bucket, j);
            if (kv) callback(kv->key, kv->value);
        }
    }
}
size_t hashmap_size(HashMap* map) {
    return map ? map->size : 0;
}
void* string_copy_func(Arena *arena, const void *data, size_t len) {
    char *buf = arena_alloc(arena, len + 1);
    if (!buf) return ((void*)0);
    __builtin___memcpy_chk (buf, data, len, __builtin_object_size (buf, 0));
    buf[len] = '\0';
    return buf;
}
void* binary_copy_func(Arena *arena, const void *data, size_t len) {
    void *buf = arena_alloc(arena, len);
    if (!buf) return ((void*)0);
    __builtin___memcpy_chk (buf, data, len, __builtin_object_size (buf, 0));
    return buf;
}
DenseArenaInterner* intern_table_create(HashMap *hashmap, Arena *arena, CopyFunc copy_func,
                                       size_t (*hash_func)(void*), int (*cmp_func)(void*, void*)){
    if (!hashmap || !arena || !copy_func || !hash_func || !cmp_func) return ((void*)0);
    DenseArenaInterner *interner = arena_alloc(arena, sizeof(DenseArenaInterner));
    if (!interner) return ((void*)0);
    interner->arena = arena;
    interner->hashmap = hashmap;
    interner->dense_index_count = 0;
    interner->copy_func = copy_func;
    interner->hash_func = hash_func;
    interner->cmp_func = cmp_func;
    interner->dense_array = arena_alloc(arena, sizeof(DynArray));
    if (!interner->dense_array) {
        return ((void*)0);
    }
    dynarray_init_in_arena(interner->dense_array, arena, sizeof(InternResult*), 0);
    return interner;
}
void intern_table_destroy(DenseArenaInterner *interner, void (*free_key)(void*), void (*free_value)(void*)) {
    if (!interner) return;
    hashmap_destroy(interner->hashmap, free_key, free_value);
    if (interner->dense_array) {
        dynarray_free(interner->dense_array);
        interner->dense_array = ((void*)0);
    }
}
InternResult* intern(DenseArenaInterner *interner,
                     Slice *slice,
                     void *meta)
{
    if (!interner || !slice || !slice->ptr || slice->len == 0) return ((void*)0);
    InternResult *found = hashmap_get(interner->hashmap, slice, interner->hash_func, interner->cmp_func);
    if (found) return found;
    Slice *key_slice = arena_alloc(interner->arena, sizeof(Slice));
    if (!key_slice) return ((void*)0);
    InternResult *res = arena_alloc(interner->arena, sizeof(InternResult));
    if (!res) return ((void*)0);
    Entry *ent = arena_alloc(interner->arena, sizeof(Entry));
    if (!ent) return ((void*)0);
    void *canonical_data = interner->copy_func(interner->arena, slice->ptr, slice->len);
    if (!canonical_data) return ((void*)0);
    key_slice->ptr = canonical_data;
    key_slice->len = slice->len;
    ent->meta = meta;
    ent->dense_index = interner->dense_index_count;
    res->entry = ent;
    res->key = key_slice;
    hashmap_put(interner->hashmap, key_slice, res, interner->hash_func, interner->cmp_func);
    InternResult *res_ptr = res;
    if (dynarray_push_value(interner->dense_array, &res_ptr) != 0) {
        return ((void*)0);
    }
    interner->dense_index_count++;
    return res;
}
void* intern_ptr(DenseArenaInterner *I, Slice* slice, void *meta) {
    InternResult *r = intern(I, slice, meta);
    if (!r) return ((void*)0);
    return r->key;
}
int intern_idx(DenseArenaInterner *I, Slice* slice, void *meta) {
    InternResult *r = intern(I, slice, meta);
    if (!r) return -1;
    return r->entry->dense_index;
}
InternResult* intern_peek(DenseArenaInterner *interner, Slice *slice)
{
    if (!interner || !slice || !slice->ptr || slice->len == 0) return ((void*)0);
    return hashmap_get(interner->hashmap, slice, interner->hash_func, interner->cmp_func);
}
const char *interner_get_cstr(DenseArenaInterner *I, int idx) {
    if (!I) return ((void*)0);
    if (idx < 0 || idx >= I->dense_index_count) return ((void*)0);
    if (!I->dense_array) return ((void*)0);
    size_t count = I->dense_array->count;
    if ((size_t)idx >= count) return ((void*)0);
    void *elem_ptr = dynarray_get(I->dense_array, (size_t)idx);
    if (!elem_ptr) return ((void*)0);
    InternResult *res = *(InternResult **)elem_ptr;
    if (!res || !res->key) return ((void*)0);
    Slice *ks = (Slice *)res->key;
    return ks->ptr;
}
InternResult *interner_get_result(DenseArenaInterner *I, int idx) {
    if (!I) return ((void*)0);
    size_t count = I->dense_array->count;
    if (idx < 0) return ((void*)0);
    if ((size_t)idx >= count) return ((void*)0);
    void *elem_ptr = dynarray_get(I->dense_array, (size_t)idx);
    if (!elem_ptr) return ((void*)0);
    return *(InternResult **)elem_ptr;
}
void interner_foreach(const DenseArenaInterner *I,
                      InternerIterFn cb,
                      void *user)
{
    if (!I || !cb) return;
    for (size_t i = 0; i < I->dense_array->count; i++) {
        InternResult *res = *(InternResult**)dynarray_get(I->dense_array, i);
        cb(res->entry->dense_index, res->key, res->entry->meta, user);
    }
}

void dynarray_init(DynArray *da, size_t elem_size) {
    if (!da) return;
    da->data = ((void*)0);
    da->elem_size = elem_size;
    da->count = 0;
    da->capacity = 0;
    da->arena = ((void*)0);
}
void dynarray_free(DynArray *da) {
    if (!da) return;
    if (da->arena == ((void*)0)) {
        free(da->data);
    } else {
        (void)da;
    }
    da->data = ((void*)0);
    da->count = 0;
    da->capacity = 0;
    da->elem_size = 0;
    da->arena = ((void*)0);
}
int dynarray_reserve(DynArray *da, size_t min_capacity) {
    if (!da) return -1;
    if (da->capacity >= min_capacity) return 0;
    if (da->arena) return dynarray_reserve_in_arena(da, min_capacity);
    size_t newcap = da->capacity ? da->capacity * 2 : 4;
    while (newcap < min_capacity) newcap *= 2;
    void *newbuf = realloc(da->data, newcap * da->elem_size);
    if (!newbuf) return -1;
    da->data = newbuf;
    da->capacity = newcap;
    return 0;
}
int dynarray_reserve_in_arena(DynArray *da, size_t min_capacity) {
    if (!da || !da->arena) return -1;
    if (da->capacity >= min_capacity) return 0;
    size_t newcap = da->capacity ? da->capacity * 2 : 8;
    while (newcap < min_capacity) newcap *= 2;
    void *newbuf = arena_alloc(da->arena, newcap * da->elem_size);
    if (!newbuf) return -1;
    if (da->data && da->count > 0) {
        __builtin___memcpy_chk (newbuf, da->data, da->count * da->elem_size, __builtin_object_size (newbuf, 0));
    }
    da->data = newbuf;
    da->capacity = newcap;
    return 0;
}
int dynarray_push_value(DynArray *da, const void *value) {
    if (!da) return -1;
    if (dynarray_reserve(da, da->count + 1) != 0) return -1;
    void *dst = (char*)da->data + da->count * da->elem_size;
    da->count += 1;
    if (value) {
        __builtin___memcpy_chk (dst, value, da->elem_size, __builtin_object_size (dst, 0));
    } else {
        __builtin___memset_chk (dst, 0, da->elem_size, __builtin_object_size (dst, 0));
    }
    return 0;
}
void *dynarray_push_uninit(DynArray *da) {
    if (!da) return ((void*)0);
    if (dynarray_reserve(da, da->count + 1) != 0) return ((void*)0);
    void *slot = (char*)da->data + da->count * da->elem_size;
    da->count += 1;
    return slot;
}
void dynarray_pop(DynArray *da) {
    if (!da) return;
    if (da->count == 0) return;
    da->count -= 1;
}
void dynarray_remove(DynArray *da, size_t index) {
    if (!da) return;
    if (index >= da->count) return;
    if (index < da->count - 1) {
        void *dst = (char*)da->data + index * da->elem_size;
        void *src = (char*)da->data + (index + 1) * da->elem_size;
        size_t n = da->count - index - 1;
        __builtin___memmove_chk (dst, src, n * da->elem_size, __builtin_object_size (dst, 0));
    }
    da->count -= 1;
}
void *dynarray_get(DynArray *da, size_t index) {
    if (!da) return ((void*)0);
    if (index >= da->count) return ((void*)0);
    return (char*)da->data + index * da->elem_size;
}
int dynarray_set(DynArray *da, size_t index, const void *value) {
    if (!da || !value) return -1;
    if (index >= da->count) return -1;
    void *dst = (char*)da->data + index * da->elem_size;
    __builtin___memcpy_chk (dst, value, da->elem_size, __builtin_object_size (dst, 0));
    return 0;
}
void dynarray_init_in_arena(DynArray *da, Arena *arena, size_t elem_size, size_t initial_capacity) {
    if (!da) return;
    da->data = ((void*)0);
    da->elem_size = elem_size;
    da->count = 0;
    da->capacity = 0;
    da->arena = arena;
    if (initial_capacity > 0) {
        dynarray_reserve_in_arena(da, initial_capacity);
    }
}
typedef __darwin_wint_t wint_t;
typedef struct {
 __darwin_rune_t __min;
 __darwin_rune_t __max;
 __darwin_rune_t __map;
 __uint32_t * __types;
} _RuneEntry;
typedef struct {
 int __nranges;
 _RuneEntry * __ranges;
} _RuneRange;
typedef struct {
 char __name[14];
 __uint32_t __mask;
} _RuneCharClass;
typedef struct {
 char __magic[8];
 char __encoding[32];
 __darwin_rune_t (*__sgetrune)(const char * __string, __darwin_size_t __n, char const * *);
 int (*__sputrune)(__darwin_rune_t, char * __string, __darwin_size_t __n, char * *);
 __darwin_rune_t __invalid_rune;
 __uint32_t __runetype[(1 <<8 )];
 __darwin_rune_t __maplower[(1 <<8 )];
 __darwin_rune_t __mapupper[(1 <<8 )];
 _RuneRange __runetype_ext;
 _RuneRange __maplower_ext;
 _RuneRange __mapupper_ext;
 void * __variable;
 int __variable_len;
 int __ncharclasses;
 _RuneCharClass * __charclasses;
} _RuneLocale;
extern _RuneLocale _DefaultRuneLocale;
extern _RuneLocale *_CurrentRuneLocale;
unsigned long ___runetype(__darwin_ct_rune_t);
__darwin_ct_rune_t ___tolower(__darwin_ct_rune_t);
__darwin_ct_rune_t ___toupper(__darwin_ct_rune_t);
inline int
isascii(int _c)
{
 return ((_c & ~0x7F) == 0);
}
int __maskrune(__darwin_ct_rune_t, unsigned long);
inline int
__istype(__darwin_ct_rune_t _c, unsigned long _f)
{
 return (isascii(_c) ? !!(_DefaultRuneLocale.__runetype[_c] & _f)
  : !!__maskrune(_c, _f));
}
inline __darwin_ct_rune_t
__isctype(__darwin_ct_rune_t _c, unsigned long _f)
{
 return (_c < 0 || _c >= (1 <<8 )) ? 0 :
  !!(_DefaultRuneLocale.__runetype[_c] & _f);
}
__darwin_ct_rune_t __toupper(__darwin_ct_rune_t);
__darwin_ct_rune_t __tolower(__darwin_ct_rune_t);
inline int
__wcwidth(__darwin_ct_rune_t _c)
{
 unsigned int _x;
 if (_c == 0)
  return (0);
 _x = (unsigned int)__maskrune(_c, 0xe0000000L|0x00040000L);
 if ((_x & 0xe0000000L) != 0)
  return ((_x & 0xe0000000L) >> 30);
 return ((_x & 0x00040000L) != 0 ? 1 : -1);
}
inline int
isalnum(int _c)
{
 return (__istype(_c, 0x00000100L|0x00000400L));
}
inline int
isalpha(int _c)
{
 return (__istype(_c, 0x00000100L));
}
inline int
isblank(int _c)
{
 return (__istype(_c, 0x00020000L));
}
inline int
iscntrl(int _c)
{
 return (__istype(_c, 0x00000200L));
}
inline int
isdigit(int _c)
{
 return (__isctype(_c, 0x00000400L));
}
inline int
isgraph(int _c)
{
 return (__istype(_c, 0x00000800L));
}
inline int
islower(int _c)
{
 return (__istype(_c, 0x00001000L));
}
inline int
isprint(int _c)
{
 return (__istype(_c, 0x00040000L));
}
inline int
ispunct(int _c)
{
 return (__istype(_c, 0x00002000L));
}
inline int
isspace(int _c)
{
 return (__istype(_c, 0x00004000L));
}
inline int
isupper(int _c)
{
 return (__istype(_c, 0x00008000L));
}
inline int
isxdigit(int _c)
{
 return (__isctype(_c, 0x00010000L));
}
inline int
toascii(int _c)
{
 return (_c & 0x7F);
}
inline int
tolower(int _c)
{
        return (__tolower(_c));
}
inline int
toupper(int _c)
{
        return (__toupper(_c));
}
inline int
digittoint(int _c)
{
 return (__maskrune(_c, 0x0F));
}
inline int
ishexnumber(int _c)
{
 return (__istype(_c, 0x00010000L));
}
inline int
isideogram(int _c)
{
 return (__istype(_c, 0x00080000L));
}
inline int
isnumber(int _c)
{
 return (__istype(_c, 0x00000400L));
}
inline int
isphonogram(int _c)
{
 return (__istype(_c, 0x00200000L));
}
inline int
isrune(int _c)
{
 return (__istype(_c, 0xFFFFFFF0L));
}
inline int
isspecial(int _c)
{
 return (__istype(_c, 0x00100000L));
}

static const struct {
    const char *word;
    TokenType type;
} KEYWORDS[] = {
    {"fn", TOK_FN},
    {"if", TOK_IF},
    {"else", TOK_ELSE},
    {"while", TOK_WHILE},
    {"for", TOK_FOR},
    {"return", TOK_RETURN},
    {"break", TOK_BREAK},
    {"continue", TOK_CONTINUE},
    {"defer", TOK_DEFER},
    {"const", TOK_CONST},
    {"pub", TOK_PUB},
    {"import", TOK_IMPORT},
    {"alias", TOK_ALIAS},
    {"struct", TOK_STRUCT},
    {"as", TOK_AS},
    {"i32", TOK_I32},
    {"i64", TOK_I64},
    {"bool", TOK_BOOL},
    {"f32", TOK_F32},
    {"f64", TOK_F64},
    {"str", TOK_STRING},
    {"char", TOK_CHAR},
    {"void", TOK_VOID},
    {"true", TOK_TRUE},
    {"false", TOK_FALSE},
    {((void*)0), TOK_UNKNOWN}
};
static inline char lexer_peek(const Lexer *lexer) {
    return lexer->cur < lexer->end ? *lexer->cur : '\0';
}
static inline char lexer_advance(Lexer *lexer) {
    if (lexer->cur >= lexer->end) return '\0';
    char c = *lexer->cur++;
    lexer->pos++;
    if (c == '\n') {
        lexer->line++;
        lexer->col = 1;
    } else {
        lexer->col++;
    }
    return c;
}
static inline _Bool is_alpha(char c) {
    return c == '_' || isalpha((unsigned char)c);
}
static inline _Bool is_digit(char c) {
    return isdigit((unsigned char)c);
}
static Slice lexer_make_slice_from_ptrs(const char *start_ptr, const char *end_ptr) {
    return (Slice) { .ptr = (char*)start_ptr, .len = (size_t)(end_ptr - start_ptr) };
}
static _Bool lexer_add_token(Lexer *lexer, const Token *tok);
static void lexer_skip_whitespace(Lexer *lexer) {
    while (lexer->cur < lexer->end) {
        char c = *lexer->cur;
        if (c == '\n') {
            lexer_advance(lexer);
            continue;
        }
        if (c == '/' && (lexer->cur + 1) < lexer->end && *(lexer->cur + 1) == '/') {
            lexer_advance(lexer);
            lexer_advance(lexer);
            while (lexer->cur < lexer->end && *lexer->cur != '\n') lexer_advance(lexer);
            continue;
        }
        if (c == '/' && (lexer->cur + 1) < lexer->end && *(lexer->cur + 1) == '*') {
            lexer_advance(lexer);
            lexer_advance(lexer);
            while (lexer->cur < lexer->end) {
                if (*lexer->cur == '*' && (lexer->cur + 1) < lexer->end && *(lexer->cur + 1) == '/') {
                    lexer_advance(lexer);
                    lexer_advance(lexer);
                    break;
                }
                lexer_advance(lexer);
            }
            continue;
        }
        if (isspace((unsigned char)c)) {
            lexer_advance(lexer);
            continue;
        }
        break;
    }
}
static void *lexer_lex_identifier(Lexer *lexer, const char *start_ptr, const char *end_ptr, TokenType *out_type) {
    Slice slice = lexer_make_slice_from_ptrs(start_ptr, end_ptr);
    InternResult *kwres = intern_peek(lexer->keywords, &slice);
    if (kwres) {
        *out_type = (TokenType)(uintptr_t)kwres->entry->meta;
        return kwres;
    }
    InternResult *idres = intern(lexer->identifiers, &slice, ((void*)0));
    if (!idres) {
        *out_type = TOK_UNKNOWN;
        return ((void*)0);
    }
    *out_type = TOK_IDENTIFIER;
    return idres;
}
static TokenType lexer_lex_number(Lexer *lexer, const char *start_ptr, const char **out_end_ptr) {
    const char *p = start_ptr;
    if (*p == '0') {
        p++;
        if (p < lexer->end && (*p == 'x' || *p == 'X')) {
            p++;
            while (p < lexer->end && (isxdigit((unsigned char)*p) || *p == '_')) p++;
            *out_end_ptr = p;
            return TOK_INT_LIT;
        } else if (p < lexer->end && (*p == 'b' || *p == 'B')) {
            p++;
            while (p < lexer->end && (*p == '0' || *p == '1' || *p == '_')) p++;
            *out_end_ptr = p;
            return TOK_INT_LIT;
        }
    }
    while (p < lexer->end && (isdigit((unsigned char)*p) || *p == '_')) p++;
    if (p < lexer->end && *p == '.') {
        const char *next = p + 1;
        if (next < lexer->end && isdigit((unsigned char)*next)) {
             p++;
             while (p < lexer->end && (isdigit((unsigned char)*p) || *p == '_')) p++;
        } else {
             *out_end_ptr = p;
             return TOK_INT_LIT;
        }
        if (p < lexer->end && (*p == 'e' || *p == 'E')) {
            p++;
            if (p < lexer->end && (*p == '+' || *p == '-')) p++;
            while (p < lexer->end && (isdigit((unsigned char)*p) || *p == '_')) p++;
        }
        *out_end_ptr = p;
        return TOK_FLOAT_LIT;
    }
    *out_end_ptr = p;
    return TOK_INT_LIT;
}
static TokenType lexer_lex_string(const char **curptr, const char *endptr) {
    const char *p = *curptr;
    p++;
    while (p < endptr && *p != '"') {
        if (*p == '\\') {
            p++;
            if (p < endptr) p++;
        } else {
            p++;
        }
    }
    if (p >= endptr) {
        *curptr = p;
        return TOK_UNKNOWN;
    }
    p++;
    *curptr = p;
    return TOK_STRING_LIT;
}
static TokenType lexer_lex_char(const char **curptr, const char *endptr, uint32_t *out_codepoint) {
    const char *p = *curptr;
    p++;
    if (p >= endptr) {
        *curptr = p;
        return TOK_UNKNOWN;
    }
    uint32_t cp = 0;
    if (*p == '\\') {
        p++;
        if (p >= endptr) { *curptr = p; return TOK_UNKNOWN; }
        switch (*p) {
            case 'n': cp = '\n'; break;
            case 't': cp = '\t'; break;
            case 'r': cp = '\r'; break;
            case '\\': cp = '\\'; break;
            case '\'': cp = '\''; break;
            case '0': cp = '\0'; break;
            default:
                cp = (unsigned char)*p;
                break;
        }
        p++;
    } else {
        cp = (unsigned char)*p;
        p++;
    }
    if (p >= endptr || *(p) != '\'') {
        *curptr = p;
        return TOK_UNKNOWN;
    }
    p++;
    *curptr = p;
    *out_codepoint = cp;
    return TOK_CHAR_LIT;
}
static Slice unescape_string_into_arena(const Slice raw, Arena *arena) {
    if (raw.len == 0) return (Slice){ .ptr = ((void*)0), .len = 0 };
    char *out = arena_alloc(arena, raw.len + 1);
    if (!out) return (Slice){ .ptr = ((void*)0), .len = 0 };
    char *w = out;
    const char *r = raw.ptr;
    const char *end = raw.ptr + raw.len;
    while (r < end) {
        if (*r == '\\') {
            r++;
            if (r >= end) break;
            switch (*r) {
                case 'n': *w++ = '\n'; break;
                case 't': *w++ = '\t'; break;
                case 'r': *w++ = '\r'; break;
                case '\\': *w++ = '\\'; break;
                case '"': *w++ = '"'; break;
                case '\'': *w++ = '\''; break;
                case '0': *w++ = '\0'; break;
                default: *w++ = *r; break;
            }
            r++;
        } else {
            *w++ = *r++;
        }
    }
    size_t n = (size_t)(w - out);
    out[n] = '\0';
    return (Slice){ .ptr = out, .len = n };
}
void lexer_populate_default_keywords(DenseArenaInterner *keywords) {
    for (size_t i = 0; KEYWORDS[i].word; i++) {
        Slice slice = {
            .ptr = (char*)KEYWORDS[i].word,
            .len = strlen(KEYWORDS[i].word)
        };
        intern(keywords, &slice, (void*)(uintptr_t)KEYWORDS[i].type);
    }
}
Lexer* lexer_create(const char *source, size_t source_len, Arena *arena) {
    if (!source || !arena) return ((void*)0);
    DenseArenaInterner *keywords = intern_table_create(hashmap_create(32), arena, string_copy_func, slice_hash, slice_cmp);
    DenseArenaInterner *identifiers = intern_table_create(hashmap_create(128), arena, string_copy_func, slice_hash, slice_cmp);
    DenseArenaInterner *strings = intern_table_create(hashmap_create(64), arena, string_copy_func, slice_hash, slice_cmp);
    if (!keywords || !identifiers || !strings) return ((void*)0);
    lexer_populate_default_keywords(keywords);
    return lexer_create_ex(source, source_len, arena, keywords, identifiers, strings);
}
Lexer* lexer_create_ex(const char *source, size_t source_len, Arena *arena,
                      DenseArenaInterner *keywords,
                      DenseArenaInterner *identifiers,
                      DenseArenaInterner *strings) {
    if (!source || !arena) return ((void*)0);
    Lexer *lexer = arena_alloc(arena, sizeof(Lexer));
    if (!lexer) return ((void*)0);
    lexer->source = source;
    lexer->source_len = source_len;
    lexer->pos = 0;
    lexer->line = 1;
    lexer->col = 1;
    lexer->arena = arena;
    lexer->cur = source;
    lexer->end = source + source_len;
    lexer->keywords = keywords;
    lexer->identifiers = identifiers;
    lexer->strings = strings;
    lexer->tokens = arena_alloc(arena, sizeof(DynArray));
    if (!lexer->tokens) return ((void*)0);
    dynarray_init_in_arena(lexer->tokens, arena, sizeof(Token), 256);
    return lexer;
}
void lexer_destroy(Lexer *lexer) {
    if (!lexer) return;
    if (lexer->tokens) {
        dynarray_free(lexer->tokens);
        lexer->tokens = ((void*)0);
    }
}
_Bool lexer_at_end(const Lexer *lexer) {
    return lexer->cur >= lexer->end;
}
Token lexer_next_token(Lexer *lexer) {
    lexer_skip_whitespace(lexer);
    if (lexer_at_end(lexer)) {
        return (Token){
            .type = TOK_EOF,
            .slice = {.ptr = (char*)lexer->cur, .len = 0},
            .span = {lexer->line, lexer->col, lexer->line, lexer->col},
            .record = ((void*)0)
        };
    }
    const char *start_ptr = lexer->cur;
    size_t start_line = lexer->line;
    size_t start_col = lexer->col;
    char c = lexer_advance(lexer);
    TokenType token_type = TOK_UNKNOWN;
    void *rec = ((void*)0);
    Slice slice = { ((void*)0), 0 };
    if (is_alpha(c)) {
        const char *p = lexer->cur;
        while (p < lexer->end && (is_alpha(*p) || is_digit(*p))) p++;
        while (lexer->cur < p) lexer_advance(lexer);
        slice = lexer_make_slice_from_ptrs(start_ptr, lexer->cur);
        rec = lexer_lex_identifier(lexer, start_ptr, lexer->cur, &token_type);
    } else if (is_digit(c)) {
        const char *endptr = ((void*)0);
        token_type = lexer_lex_number(lexer, start_ptr, &endptr);
        while (lexer->cur < endptr) lexer_advance(lexer);
        slice = lexer_make_slice_from_ptrs(start_ptr, lexer->cur);
    } else if (c == '"') {
        const char *tmpcur = lexer->cur - 1;
        token_type = lexer_lex_string(&tmpcur, lexer->end);
        while (lexer->cur < tmpcur) lexer_advance(lexer);
        const char *raw_start = start_ptr + 1;
        const char *raw_end = lexer->cur - 1;
        slice = lexer_make_slice_from_ptrs(start_ptr, lexer->cur);
        if (token_type == TOK_STRING_LIT) {
            Slice raw_content = lexer_make_slice_from_ptrs(raw_start, raw_end);
            Slice unescaped = unescape_string_into_arena(raw_content, lexer->arena);
            if (unescaped.ptr && unescaped.len > 0) {
                InternResult *ires = intern(lexer->strings, &unescaped, ((void*)0));
                rec = ires;
            } else if (unescaped.ptr) {
                InternResult *ires = intern(lexer->strings, &unescaped, ((void*)0));
                rec = ires;
            } else {
                rec = ((void*)0);
            }
        }
    } else if (c == '\'') {
        const char *tmpcur = lexer->cur - 1;
        uint32_t cp = 0;
        token_type = lexer_lex_char(&tmpcur, lexer->end, &cp);
        while (lexer->cur < tmpcur) lexer_advance(lexer);
        slice = lexer_make_slice_from_ptrs(start_ptr, lexer->cur);
        if (token_type == TOK_CHAR_LIT) {
            rec = (void*)(uintptr_t)cp;
        }
    } else {
        char next = lexer_peek(lexer);
        switch (c) {
            case '+':
                if (next == '+') { lexer_advance(lexer); token_type = TOK_PLUSPLUS; }
                else if (next == '=') { lexer_advance(lexer); token_type = TOK_PLUS_EQ; }
                else token_type = TOK_PLUS;
                break;
            case '-':
                if (next == '-') { lexer_advance(lexer); token_type = TOK_MINUSMINUS; }
                else if (next == '=') { lexer_advance(lexer); token_type = TOK_MINUS_EQ; }
                else if (next == '>') { lexer_advance(lexer); token_type = TOK_ARROW; }
                else token_type = TOK_MINUS;
                break;
            case '=':
                if (next == '=') { lexer_advance(lexer); token_type = TOK_EQ_EQ; }
                else token_type = TOK_ASSIGN;
                break;
            case '!':
                if (next == '=') { lexer_advance(lexer); token_type = TOK_BANG_EQ; }
                else token_type = TOK_BANG;
                break;
            case '<':
                if (next == '=') { lexer_advance(lexer); token_type = TOK_LT_EQ; }
                else token_type = TOK_LT;
                break;
            case '>':
                if (next == '=') { lexer_advance(lexer); token_type = TOK_GT_EQ; }
                else token_type = TOK_GT;
                break;
            case '&':
                if (next == '&') { lexer_advance(lexer); token_type = TOK_AND_AND; }
                else token_type = TOK_AMP;
                break;
            case '|':
                if (next == '|') { lexer_advance(lexer); token_type = TOK_OR_OR; }
                else token_type = TOK_PIPE;
                break;
            case '(' : token_type = TOK_LPAREN; break;
            case ')' : token_type = TOK_RPAREN; break;
            case '{' : token_type = TOK_LBRACE; break;
            case '}' : token_type = TOK_RBRACE; break;
            case '[' : token_type = TOK_LBRACKET; break;
            case ']' : token_type = TOK_RBRACKET; break;
            case ',' : token_type = TOK_COMMA; break;
            case ';': token_type = TOK_SEMICOLON; break;
            case ':': token_type = TOK_COLON; break;
            case '@': token_type = TOK_AT; break;
            case '*':
                if (next == '=') { lexer_advance(lexer); token_type = TOK_STAR_EQ; }
                else token_type = TOK_STAR;
                break;
            case '/':
                if (next == '=') { lexer_advance(lexer); token_type = TOK_SLASH_EQ; }
                else token_type = TOK_SLASH;
                break;
            case '%':
                if (next == '=') { lexer_advance(lexer); token_type = TOK_PERCENT_EQ; }
                else token_type = TOK_PERCENT;
                break;
            case '.': token_type = TOK_DOT; break;
            default: token_type = TOK_UNKNOWN; break;
        }
        slice = lexer_make_slice_from_ptrs(start_ptr, lexer->cur);
    }
    Span span = { start_line, start_col, lexer->line, lexer->col };
    return (Token){ .type = token_type, .slice = slice, .span = span, .record = rec };
}
static _Bool lexer_add_token(Lexer *lexer, const Token *tok) {
    if (!lexer || !tok) return 0;
    return dynarray_push_value(lexer->tokens, tok) == 0;
}
_Bool lexer_lex_all(Lexer *lexer) {
    if (!lexer) return 0;
    for (;;) {
        Token token = lexer_next_token(lexer);
        if (!lexer_add_token(lexer, &token)) {
            return 0;
        }
        if (token.type == TOK_EOF) break;
    }
    return 1;
}
Token* lexer_get_tokens(Lexer *lexer, size_t *count) {
    if (!lexer || !count) return ((void*)0);
    *count = lexer->tokens->count;
    return (Token*)lexer->tokens->data;
}
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOK_FN: return "FN";
        case TOK_IF: return "IF";
        case TOK_ELSE: return "ELSE";
        case TOK_WHILE: return "WHILE";
        case TOK_FOR: return "FOR";
        case TOK_RETURN: return "RETURN";
        case TOK_BREAK: return "BREAK";
        case TOK_CONTINUE: return "CONTINUE";
        case TOK_CONST: return "CONST";
        case TOK_PUB: return "PUB";
        case TOK_IMPORT: return "IMPORT";
        case TOK_ALIAS: return "ALIAS";
        case TOK_STRUCT: return "STRUCT";
        case TOK_I32: return "I32";
        case TOK_I64: return "I64";
        case TOK_BOOL: return "BOOL";
        case TOK_F32: return "F32";
        case TOK_F64: return "F64";
        case TOK_CHAR: return "CHAR";
        case TOK_TRUE: return "TRUE";
        case TOK_FALSE: return "FALSE";
        case TOK_IDENTIFIER: return "IDENTIFIER";
        case TOK_INT_LIT: return "INT_LIT";
        case TOK_FLOAT_LIT: return "FLOAT_LIT";
        case TOK_STRING_LIT: return "STRING_LIT";
        case TOK_CHAR_LIT: return "CHAR_LIT";
        case TOK_EQ_EQ: return "EQUALSEQUALS";
        case TOK_BANG_EQ: return "BANGEQUALS";
        case TOK_LT_EQ: return "LESSEREQUALS";
        case TOK_GT_EQ: return "GREATEREQUALS";
        case TOK_PLUSPLUS: return "PLUSPLUS";
        case TOK_MINUSMINUS: return "MINUSMINUS";
        case TOK_PLUS_EQ: return "PLUSEQUALS";
        case TOK_MINUS_EQ: return "MINUSEQUALS";
        case TOK_STAR_EQ: return "STAREQUALS";
        case TOK_SLASH_EQ: return "SLAHSEQUALS";
        case TOK_PERCENT_EQ: return "PERCEQUALS";
        case TOK_AND_AND: return "ANDAND";
        case TOK_OR_OR: return "OROR";
        case TOK_ARROW: return "ARROW";
        case TOK_ASSIGN: return "ASSIGN";
        case TOK_PLUS: return "PLUS";
        case TOK_MINUS: return "MINUS";
        case TOK_STAR: return "STAR";
        case TOK_SLASH: return "SLASH";
        case TOK_PERCENT: return "PERCENT";
        case TOK_BANG: return "BANG";
        case TOK_AMP: return "AMP";
        case TOK_LT: return "LESS";
        case TOK_GT: return "GREATER";
        case TOK_DOT: return "DOT";
        case TOK_LPAREN: return "LPAREN";
        case TOK_RPAREN: return "RPAREN";
        case TOK_LBRACE: return "LBRACE";
        case TOK_RBRACE: return "RBRACE";
        case TOK_LBRACKET: return "LBRACKET";
        case TOK_RBRACKET: return "RBRACKET";
        case TOK_COMMA: return "COMMA";
        case TOK_SEMICOLON: return "SEMICOLON";
        case TOK_COLON: return "COLON";
        case TOK_EOF: return "EOF";
        case TOK_AS: return "AS";
        case TOK_VOID: return "VOID";
        case TOK_DEFER: return "DEFER";
        default: return "UNKNOWN";
    }
}
void lexer_reset(Lexer *lexer) {
    if (!lexer) return;
    lexer->pos = 0;
    lexer->line = 1;
    lexer->col = 1;
    lexer->cur = lexer->source;
    lexer->end = lexer->source + lexer->source_len;
    if (lexer->tokens) {
        lexer->tokens->count = 0;
    }
}
void print_token(const Token *tok) {
    const char *type_str = token_type_to_string(tok->type);
    printf("│ %3zu:%-3zu │ %-13s │ ",
           tok->span.start_line,
           tok->span.start_col,
           type_str);
    if (tok->slice.ptr && tok->slice.len > 0) {
        printf("'%.*s'", (int)tok->slice.len, tok->slice.ptr);
    } else {
        printf("(no-lexeme)");
    }
    if (tok->type == TOK_CHAR_LIT && tok->record) {
        uint32_t cp = (uint32_t)(uintptr_t)tok->record;
        printf("  (char: U+%04X)", cp);
    }
    printf("\n");
}


typedef struct Type Type;
typedef struct Symbol Symbol;
typedef struct Scope Scope;
typedef enum {
    TYPE_VOID,
    TYPE_PRIMITIVE,
    TYPE_POINTER,
    TYPE_ARRAY,
    TYPE_SLICE,
    TYPE_FUNCTION,
    TYPE_STRUCT,
    TYPE_ENUM
} TypeKind;
typedef enum {
    PRIM_I32, PRIM_I64,
    PRIM_F32, PRIM_F64,
    PRIM_BOOL,
    PRIM_CHAR
} PrimitiveKind;
typedef struct StructField {
    InternResult *name;
    Type *type;
} StructField;
struct Type {
    TypeKind kind;
    uint64_t cached_hash;
    union {
        PrimitiveKind primitive;
        struct {
            Type *base;
        } ptr;
        struct {
            Type *base;
            int64_t size;
        } array;
        struct {
            Type *base;
        } slice;
        struct {
            Type *return_type;
            Type **params;
            size_t param_count;
        } func;
        struct {
            InternResult *name;
            StructField *fields;
            size_t field_count;
            HashMap *field_map;
        } struct_type;
        struct {
            char *name;
            Symbol *decl_node;
        } user;
    } as;
};
typedef struct TypeStore {
    Arena *arena;
    DenseArenaInterner *type_interner;
    HashMap *primitive_registry;
    Type *t_void;
    Type *t_void_ptr;
    Type *t_i32, *t_i64;
    Type *t_f32, *t_f64;
    Type *t_bool;
    Type *t_char;
    Type *t_str;
    InternResult *kw_len;
} TypeStore;
TypeStore *typestore_create(Arena *arena, DenseArenaInterner *identifiers, DenseArenaInterner *keywords);
InternResult *intern_type(TypeStore *ts, Type *prototype);
void register_intrinsics(TypeStore *ts, Scope *global_scope, DenseArenaInterner *ids);
_Bool type_is_integer(Type *t);
_Bool type_is_float(Type *t);
_Bool type_is_bool(Type *t);
_Bool type_is_char(Type *t);
void type_print(FILE *out, const Type *type);
void type_print_store_dump(TypeStore *store, Scope *global_scope);
static const char *node_type_to_string(AstNodeType type) {
    switch (type) {
        case AST_PROGRAM: return "Program";
        case AST_VARIABLE_DECLARATION: return "VariableDeclaration";
        case AST_FUNCTION_DECLARATION: return "FunctionDeclaration";
        case AST_PARAM: return "Parameter";
        case AST_STRUCT_DECLARATION: return "StructDeclaration";
        case AST_IMPORT_DECLARATION: return "ImportDeclaration";
        case AST_INTRINSIC: return "IntrinsicCall";
        case AST_BLOCK: return "Block";
        case AST_IF_STATEMENT: return "IfStatement";
        case AST_WHILE_STATEMENT: return "WhileStatement";
        case AST_FOR_STATEMENT: return "ForStatement";
        case AST_RETURN_STATEMENT: return "ReturnStatement";
        case AST_BREAK_STATEMENT: return "BreakStatement";
        case AST_CONTINUE_STATEMENT: return "ContinueStatement";
        case AST_DEFER_STATEMENT: return "DeferStatement";
        case AST_EXPR_STATEMENT: return "ExpressionStatement";
        case AST_LITERAL: return "Literal";
        case AST_IDENTIFIER: return "Identifier";
        case AST_BINARY_EXPR: return "BinaryExpression";
        case AST_UNARY_EXPR: return "UnaryExpression";
        case AST_POSTFIX_EXPR: return "PostfixExpression";
        case AST_ASSIGNMENT_EXPR: return "AssignmentExpression";
        case AST_CALL_EXPR: return "CallExpression";
        case AST_SUBSCRIPT_EXPR: return "SubscriptExpression";
        case AST_MEMBER_EXPR: return "MemberExpression";
        case AST_STRUCT_LITERAL: return "StructLiteral";
        case AST_CAST: return "CastExpression";
        case AST_TYPE: return "Type";
        case AST_INITIALIZER_LIST: return "InitializerList";
        default: return "Unknown";
    }
}
static const char *type_kind_to_string(AstTypeKind kind) {
    switch (kind) {
        case AST_TYPE_PRIMITIVE: return "PrimitiveType";
        case AST_TYPE_PTR: return "PointerType";
        case AST_TYPE_ARRAY: return "ArrayType";
        case AST_TYPE_FUNC: return "FunctionType";
        default: return "UnknownType";
    }
}
static const char *literal_type_to_string(LiteralType type) {
    switch (type) {
        case INT_LITERAL: return "Integer";
        case FLOAT_LITERAL: return "Float";
        case BOOL_LITERAL: return "Boolean";
        case STRING_LITERAL: return "String";
        case CHAR_LITERAL: return "Character";
        default: return "UnknownLiteral";
    }
}
static void print_escaped_string(const char *str) {
    if (!str) {
        printf("\"\"");
        return;
    }
    printf("\"");
    for (const char *p = str; *p; p++) {
        switch (*p) {
            case '\n': printf("\\n"); break;
            case '\t': printf("\\t"); break;
            case '\r': printf("\\r"); break;
            case '\\': printf("\\\\"); break;
            case '"': printf("\\\""); break;
            case '\0': printf("\\0"); break;
            default:
                if (*p >= 32 && *p <= 126) {
                    printf("%c", *p);
                } else {
                    printf("\\x%02x", (unsigned char)*p);
                }
                break;
        }
    }
    printf("\"");
}
static void print_escaped_char(char c) {
    printf("'");
    switch (c) {
        case '\n': printf("\\n"); break;
        case '\t': printf("\\t"); break;
        case '\r': printf("\\r"); break;
        case '\\': printf("\\\\"); break;
        case '\'': printf("\\'"); break;
        case '\0': printf("\\0"); break;
        default:
            if (c >= 32 && c <= 126) {
                printf("%c", c);
            } else {
                printf("\\x%02x", (unsigned char)c);
            }
            break;
    }
    printf("'");
}
AstNode *ast_create_node(AstNodeType type, Arena *arena, const char *filename) {
    if (!arena) return ((void*)0);
    AstNode *node = (AstNode*)arena_calloc(arena, sizeof(AstNode));
    if (!node) return ((void*)0);
    node->node_type = type;
    node->filename = filename;
    node->flags = AST_FLAG_NONE;
    return node;
}
int is_lvalue_node(AstNode *node) {
    if (!node) return 0;
    switch (node->node_type) {
        case AST_IDENTIFIER:
            return 1;
        case AST_SUBSCRIPT_EXPR:
            return 1;
        case AST_MEMBER_EXPR:
            return 1;
        case AST_UNARY_EXPR:
            if (node->data.unary_expr.op == OP_DEREF) return 1;
            return 0;
        case AST_STRUCT_LITERAL:
        case AST_INITIALIZER_LIST:
            return 1;
        case AST_POSTFIX_EXPR: {
            OpKind k = node->data.postfix_expr.op;
            if(k == OP_POST_INC || k == OP_POST_DEC) {
                return 0;
            }
            return 0;
        }
        default:
            return 0;
    }
}
int is_assignment_op(TokenType type) {
    switch (type) {
        case TOK_ASSIGN:
        case TOK_PLUS_EQ:
        case TOK_MINUS_EQ:
        case TOK_STAR_EQ:
        case TOK_SLASH_EQ:
        case TOK_PERCENT_EQ:
            return 1;
        default:
            return 0;
    }
}
static int ancestor_is_last[64];
static void print_tree_prefix_tracked(int depth, int is_last) {
    if (depth == 0) return;
    for (int i = 0; i < depth - 1; ++i) {
        if (ancestor_is_last[i]) {
            printf("    ");
        } else {
            printf("│   ");
        }
    }
    if (is_last) {
        printf("└── ");
    } else {
        printf("├── ");
    }
}
static void print_tree_prefix(int depth, int is_last) {
    print_tree_prefix_tracked(depth, is_last);
}
static const char *op_to_string(OpKind op) {
    switch (op) {
        case OP_ADD: return "+";
        case OP_SUB: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "/";
        case OP_MOD: return "%";
        case OP_EQ: return "==";
        case OP_NEQ: return "!=";
        case OP_LT: return "<";
        case OP_GT: return ">";
        case OP_LE: return "<=";
        case OP_GE: return ">=";
        case OP_AND: return "&&";
        case OP_OR: return "||";
        case OP_NOT: return "!";
        case OP_ASSIGN: return "=";
        case OP_PLUS_EQ: return "+=";
        case OP_MINUS_EQ: return "-=";
        case OP_DEREF: return "*";
        case OP_ADRESS: return "&";
        case OP_POST_INC: return "++";
        case OP_POST_DEC: return "--";
        case OP_PRE_INC: return "++";
        case OP_PRE_DEC: return "--";
        default: return "?";
    }
}
void print_ast(AstNode *node, int depth, DenseArenaInterner *keywords, DenseArenaInterner *identifiers, DenseArenaInterner *strings) {
    print_ast_with_prefix(node, depth, 1, keywords, identifiers, strings);
}
void print_ast_with_prefix(AstNode *node, int depth, int is_last, DenseArenaInterner *keywords, DenseArenaInterner *identifiers, DenseArenaInterner *strings) {
    if (!node) {
        print_tree_prefix(depth, is_last);
        printf("(null)\n");
        return;
    }
    print_tree_prefix(depth, is_last);
    printf("%s", node_type_to_string(node->node_type));
    if (node->span.start_line > 0) {
        printf(" [%zu:%zu-%zu:%zu]",
               node->span.start_line, node->span.start_col,
               node->span.end_line, node->span.end_col);
    }
    if (node->type) {
        printf(" \033[36m<");
        type_print(__stdoutp, node->type);
        printf(">\033[0m");
    }
    if (node->is_foldable_const) {
        printf(" \033[33m(const:");
        switch (node->const_value.type) {
            case INT_LITERAL:
                printf("%lld", node->const_value.value.int_val);
                break;
            case FLOAT_LITERAL:
                printf("%f", node->const_value.value.float_val);
                break;
            case BOOL_LITERAL:
                printf("%s", node->const_value.value.bool_val ? "true" : "false");
                break;
            default:
                printf("...");
                break;
        }
        printf(")\033[0m");
    } else if (node->is_llvm_const_safe) {
        printf(" \033[33m(const-safe)\033[0m");
    }
    printf("\n");
    switch (node->node_type) {
        case AST_PROGRAM:
            if (node->data.program.decls && node->data.program.decls->count > 0) {
                for (size_t i = 0; i < node->data.program.decls->count; ++i) {
                    AstNode *decl = *(AstNode**)dynarray_get(node->data.program.decls, i);
                    print_ast_with_prefix(decl, depth + 1, i == node->data.program.decls->count - 1, keywords, identifiers, strings);
                }
            }
            break;
        case AST_IMPORT_DECLARATION:
            print_tree_prefix(depth + 1, 0);
            printf("module: ");
            if (node->data.import_declaration.module_path && node->data.import_declaration.module_path->count > 0) {
                for (size_t i = 0; i < node->data.import_declaration.module_path->count; ++i) {
                    InternResult *part = *(InternResult**)dynarray_get(node->data.import_declaration.module_path, i);
                    if (identifiers) {
                        const char *name = interner_get_cstr(identifiers, part->entry->dense_index);
                        printf("%s", name ? name : "?");
                    } else {
                        printf("?");
                    }
                    if (i < node->data.import_declaration.module_path->count - 1) printf(".");
                }
            } else {
                printf("(unknown)");
            }
            printf("\n");
            if (node->data.import_declaration.module_alias) {
                print_tree_prefix(depth + 1, node->data.import_declaration.specific_symbols ? 0 : 1);
                printf("alias: ");
                if (identifiers) {
                    const char *alias = interner_get_cstr(identifiers, node->data.import_declaration.module_alias->entry->dense_index);
                    printf("'%s'", alias ? alias : "?");
                }
                printf("\n");
            }
            if (node->data.import_declaration.specific_symbols && node->data.import_declaration.specific_symbols->count > 0) {
                print_tree_prefix(depth + 1, 1);
                printf("symbols:\n");
                for (size_t i = 0; i < node->data.import_declaration.specific_symbols->count; ++i) {
                    ImportSymbol *sym = *(ImportSymbol**)dynarray_get(node->data.import_declaration.specific_symbols, i);
                    print_tree_prefix(depth + 2, i == node->data.import_declaration.specific_symbols->count - 1);
                    if (sym->original_name && identifiers) {
                        const char *orig = interner_get_cstr(identifiers, sym->original_name->entry->dense_index);
                        printf("%s", orig ? orig : "?");
                    }
                    if (sym->alias_name && identifiers) {
                        const char *alias = interner_get_cstr(identifiers, sym->alias_name->entry->dense_index);
                        printf(" alias %s", alias ? alias : "?");
                    }
                    printf("\n");
                }
            }
            break;
        case AST_INTRINSIC:
            print_tree_prefix(depth + 1, 0);
            printf("intrinsic: ");
            if (node->data.intrinsic.kind == INTRINSIC_ALLOC) printf("@alloc\n");
            else if (node->data.intrinsic.kind == INTRINSIC_FREE) printf("@free\n");
            else printf("unknown\n");
            if (node->data.intrinsic.args && node->data.intrinsic.args->count > 0) {
                print_tree_prefix(depth + 1, 1);
                printf("arguments:\n");
                for (size_t i = 0; i < node->data.intrinsic.args->count; ++i) {
                    AstNode *arg = *(AstNode**)dynarray_get(node->data.intrinsic.args, i);
                    print_ast_with_prefix(arg, depth + 2, i == node->data.intrinsic.args->count - 1, keywords, identifiers, strings);
                }
            } else {
                print_tree_prefix(depth + 1, 1);
                printf("arguments: (none)\n");
            }
            break;
        case AST_STRUCT_DECLARATION: {
            print_tree_prefix(depth + 1, 0);
            printf("name: ");
            if (node->data.struct_declaration.intern_result &&
                node->data.struct_declaration.intern_result->entry && identifiers) {
                const char *name = interner_get_cstr(identifiers, node->data.struct_declaration.intern_result->entry->dense_index);
                printf("'%s'", name ? name : "?");
            } else {
                printf("(none)");
            }
            printf("\n");
            if (node->data.struct_declaration.fields && node->data.struct_declaration.fields->count > 0) {
                print_tree_prefix(depth + 1, 1);
                printf("fields:\n");
                for (size_t i = 0; i < node->data.struct_declaration.fields->count; ++i) {
                    AstFieldDecl *field = (AstFieldDecl*)dynarray_get(node->data.struct_declaration.fields, i);
                    print_tree_prefix(depth + 2, i == node->data.struct_declaration.fields->count - 1);
                    printf("Field '");
                    if (field->name && field->name->entry && identifiers) {
                        const char *fname = interner_get_cstr(identifiers, field->name->entry->dense_index);
                        printf("%s", fname ? fname : "?");
                    } else {
                        printf("?");
                    }
                    printf("':\n");
                    print_ast_with_prefix(field->type, depth + 3, 1, keywords, identifiers, strings);
                }
            }
            break;
        }
        case AST_STRUCT_LITERAL: {
            print_tree_prefix(depth + 1, 0);
            printf("type:\n");
            if (node->data.struct_literal.type_node) {
                print_ast_with_prefix(node->data.struct_literal.type_node, depth + 2, 1, keywords, identifiers, strings);
            } else {
                printf("(none)\n");
            }
            if (node->data.struct_literal.fields && node->data.struct_literal.fields->count > 0) {
                print_tree_prefix(depth + 1, 1);
                printf("fields:\n");
                for (size_t i = 0; i < node->data.struct_literal.fields->count; ++i) {
                    AstFieldInit *init = (AstFieldInit*)dynarray_get(node->data.struct_literal.fields, i);
                    print_tree_prefix(depth + 2, i == node->data.struct_literal.fields->count - 1);
                    printf("Field '");
                    if (init->name && init->name->entry && identifiers) {
                        const char *fname = interner_get_cstr(identifiers, init->name->entry->dense_index);
                        printf("%s", fname ? fname : "?");
                    } else {
                        printf("?");
                    }
                    printf("':\n");
                    print_ast_with_prefix(init->expr, depth + 3, 1, keywords, identifiers, strings);
                }
            }
            break;
        }
        case AST_VARIABLE_DECLARATION: {
            int has_type = node->data.variable_declaration.type != ((void*)0);
            int has_init = node->data.variable_declaration.initializer != ((void*)0);
            int child_count = 0;
            if (has_type) child_count++;
            if (has_init) child_count++;
            print_tree_prefix(depth + 1, child_count == 0);
            printf("name: ");
            if (node->data.variable_declaration.intern_result &&
                node->data.variable_declaration.intern_result->entry && identifiers) {
                const char *name = interner_get_cstr(identifiers, node->data.variable_declaration.intern_result->entry->dense_index);
                printf("'%s'", name ? name : "?");
            } else {
                printf("(none)");
            }
            if (node->data.variable_declaration.is_const) {
                printf(" [const]");
            }
            printf("\n");
            int current_child = 0;
            if (has_type) {
                current_child++;
                print_tree_prefix(depth + 1, current_child == child_count);
                printf("type:\n");
                print_ast_with_prefix(node->data.variable_declaration.type, depth + 2, 1, keywords, identifiers, strings);
            }
            if (has_init) {
                current_child++;
                print_tree_prefix(depth + 1, current_child == child_count);
                printf("initializer:\n");
                print_ast_with_prefix(node->data.variable_declaration.initializer, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        }
        case AST_FUNCTION_DECLARATION: {
            print_tree_prefix(depth + 1, 0);
            printf("name: ");
            if (node->data.function_declaration.intern_result &&
                node->data.function_declaration.intern_result->entry && identifiers) {
                const char *name = interner_get_cstr(identifiers, node->data.function_declaration.intern_result->entry->dense_index);
                printf("'%s'", name ? name : "?");
            } else {
                printf("(none)");
            }
            printf("\n");
            int has_body = node->data.function_declaration.body != ((void*)0);
            int has_params = node->data.function_declaration.params && node->data.function_declaration.params->count > 0;
            if (node->data.function_declaration.return_type) {
                print_tree_prefix(depth + 1, !(has_params || has_body));
                printf("return_type:\n");
                print_ast_with_prefix(node->data.function_declaration.return_type, depth + 2, !(has_params || has_body), keywords, identifiers, strings);
            }
            if (has_params) {
                print_tree_prefix(depth + 1, !has_body);
                printf("parameters:\n");
                for (size_t i = 0; i < node->data.function_declaration.params->count; ++i) {
                    AstNode *param = *(AstNode**)dynarray_get(node->data.function_declaration.params, i);
                    print_ast_with_prefix(param, depth + 2, i == node->data.function_declaration.params->count - 1, keywords, identifiers, strings);
                }
            }
            if (has_body) {
                print_tree_prefix(depth + 1, 1);
                printf("body:\n");
                print_ast_with_prefix(node->data.function_declaration.body, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        }
        case AST_PARAM: {
            print_tree_prefix(depth + 1, 0);
            printf("name: ");
            if (node->data.param.name_idx >= 0 && identifiers) {
                const char *name = interner_get_cstr(identifiers, node->data.param.name_idx);
                printf("'%s'", name ? name : "?");
            } else {
                printf("(anonymous)");
            }
            printf("\n");
            if (node->data.param.type) {
                print_tree_prefix(depth + 1, 1);
                printf("type:\n");
                print_ast_with_prefix(node->data.param.type, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        }
        case AST_BLOCK:
            if (node->data.block.statements && node->data.block.statements->count > 0) {
                for (size_t i = 0; i < node->data.block.statements->count; ++i) {
                    AstNode *stmt = *(AstNode**)dynarray_get(node->data.block.statements, i);
                    print_ast_with_prefix(stmt, depth + 1, i == node->data.block.statements->count - 1, keywords, identifiers, strings);
                }
            }
            break;
        case AST_IF_STATEMENT: {
            int has_else = node->data.if_statement.else_branch != ((void*)0);
            if (node->data.if_statement.condition) {
                print_tree_prefix(depth + 1, 0);
                printf("condition:\n");
                print_ast_with_prefix(node->data.if_statement.condition, depth + 2, 0, keywords, identifiers, strings);
            }
            if (node->data.if_statement.then_branch) {
                print_tree_prefix(depth + 1, !has_else);
                printf("then:\n");
                print_ast_with_prefix(node->data.if_statement.then_branch, depth + 2, !has_else, keywords, identifiers, strings);
            }
            if (has_else) {
                print_tree_prefix(depth + 1, 1);
                printf("else:\n");
                print_ast_with_prefix(node->data.if_statement.else_branch, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        }
        case AST_WHILE_STATEMENT:
            if (node->data.while_statement.condition) {
                print_tree_prefix(depth + 1, 0);
                printf("condition:\n");
                print_ast_with_prefix(node->data.while_statement.condition, depth + 2, 0, keywords, identifiers, strings);
            }
            if (node->data.while_statement.body) {
                print_tree_prefix(depth + 1, 1);
                printf("body:\n");
                print_ast_with_prefix(node->data.while_statement.body, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        case AST_FOR_STATEMENT: {
            int parts = 0;
            if (node->data.for_statement.init) parts++;
            if (node->data.for_statement.condition) parts++;
            if (node->data.for_statement.post) parts++;
            if (node->data.for_statement.body) parts++;
            int current = 0;
            if (node->data.for_statement.init) {
                current++;
                print_tree_prefix(depth + 1, current == parts);
                printf("init:\n");
                print_ast_with_prefix(node->data.for_statement.init, depth + 2, current == parts, keywords, identifiers, strings);
            }
            if (node->data.for_statement.condition) {
                current++;
                print_tree_prefix(depth + 1, current == parts);
                printf("condition:\n");
                print_ast_with_prefix(node->data.for_statement.condition, depth + 2, current == parts, keywords, identifiers, strings);
            }
            if (node->data.for_statement.post) {
                current++;
                print_tree_prefix(depth + 1, current == parts);
                printf("post:\n");
                print_ast_with_prefix(node->data.for_statement.post, depth + 2, current == parts, keywords, identifiers, strings);
            }
            if (node->data.for_statement.body) {
                current++;
                print_tree_prefix(depth + 1, 1);
                printf("body:\n");
                print_ast_with_prefix(node->data.for_statement.body, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        }
        case AST_RETURN_STATEMENT:
            if (node->data.return_statement.expression) {
                print_tree_prefix(depth + 1, 1);
                printf("expression:\n");
                print_ast_with_prefix(node->data.return_statement.expression, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        case AST_DEFER_STATEMENT:
            if (node->data.defer_statement.body) {
                print_tree_prefix(depth + 1, 1);
                printf("body:\n");
                print_ast_with_prefix(node->data.defer_statement.body, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        case AST_EXPR_STATEMENT:
            if (node->data.expr_statement.expression) {
                print_tree_prefix(depth + 1, 1);
                printf("expression:\n");
                print_ast_with_prefix(node->data.expr_statement.expression, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        case AST_LITERAL:
            print_tree_prefix(depth + 1, 1);
            printf("value: ");
            switch (node->data.literal.type) {
                case INT_LITERAL:
                    printf("%lld", node->data.literal.value.int_val);
                    break;
                case FLOAT_LITERAL:
                    printf("%f", node->data.literal.value.float_val);
                    break;
                case BOOL_LITERAL:
                    printf("%s", node->data.literal.value.bool_val ? "true" : "false");
                    break;
                case STRING_LITERAL: {
                    if (node->data.literal.value.string_val &&
                        node->data.literal.value.string_val->entry && strings) {
                        const char *str = interner_get_cstr(strings, node->data.literal.value.string_val->entry->dense_index);
                        print_escaped_string(str);
                    } else {
                        printf("\"\"");
                    }
                    break;
                }
                case CHAR_LITERAL:
                    print_escaped_char(node->data.literal.value.char_val);
                    break;
                default:
                    printf("?");
                    break;
            }
            printf(" (%s)\n", literal_type_to_string(node->data.literal.type));
            break;
        case AST_IDENTIFIER:
            print_tree_prefix(depth + 1, 1);
            printf("name: ");
            if (node->data.identifier.intern_result &&
                node->data.identifier.intern_result->entry && identifiers) {
                const char *name = interner_get_cstr(identifiers, node->data.identifier.intern_result->entry->dense_index);
                printf("'%s'", name ? name : "?");
            } else {
                printf("(unknown)");
            }
            printf("\n");
            break;
        case AST_BINARY_EXPR:
            print_tree_prefix(depth + 1, 0);
            printf("operator: '%s'\n", op_to_string(node->data.binary_expr.op));
            if (node->data.binary_expr.left) {
                print_tree_prefix(depth + 1, !node->data.binary_expr.right);
                printf("left:\n");
                print_ast_with_prefix(node->data.binary_expr.left, depth + 2, !node->data.binary_expr.right, keywords, identifiers, strings);
            }
            if (node->data.binary_expr.right) {
                print_tree_prefix(depth + 1, 1);
                printf("right:\n");
                print_ast_with_prefix(node->data.binary_expr.right, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        case AST_UNARY_EXPR:
            print_tree_prefix(depth + 1, 0);
            printf("operator: '%s'\n", op_to_string(node->data.unary_expr.op));
            if (node->data.unary_expr.expr) {
                print_tree_prefix(depth + 1, 1);
                printf("expression:\n");
                print_ast_with_prefix(node->data.unary_expr.expr, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        case AST_POSTFIX_EXPR:
            print_tree_prefix(depth + 1, 0);
            printf("operator: '%s'\n", op_to_string(node->data.postfix_expr.op));
            if (node->data.postfix_expr.expr) {
                print_tree_prefix(depth + 1, 1);
                printf("expression:\n");
                print_ast_with_prefix(node->data.postfix_expr.expr, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        case AST_ASSIGNMENT_EXPR:
            print_tree_prefix(depth + 1, 0);
            printf("operator: '%s'\n", op_to_string(node->data.assignment_expr.op));
            if (node->data.assignment_expr.lvalue) {
                print_tree_prefix(depth + 1, 0);
                printf("lvalue:\n");
                print_ast_with_prefix(node->data.assignment_expr.lvalue, depth + 2, 0, keywords, identifiers, strings);
            }
            if (node->data.assignment_expr.rvalue) {
                print_tree_prefix(depth + 1, 1);
                printf("rvalue:\n");
                print_ast_with_prefix(node->data.assignment_expr.rvalue, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        case AST_CALL_EXPR:
            if (node->data.call_expr.callee) {
                int has_args = node->data.call_expr.args && node->data.call_expr.args->count > 0;
                print_tree_prefix(depth + 1, !has_args);
                printf("callee:\n");
                print_ast_with_prefix(node->data.call_expr.callee, depth + 2, 0, keywords, identifiers, strings);
            }
            if (node->data.call_expr.args && node->data.call_expr.args->count > 0) {
                print_tree_prefix(depth + 1, 1);
                printf("arguments:\n");
                for (size_t i = 0; i < node->data.call_expr.args->count; ++i) {
                    AstNode *arg = *(AstNode**)dynarray_get(node->data.call_expr.args, i);
                    print_ast_with_prefix(arg, depth + 2, i == node->data.call_expr.args->count - 1, keywords, identifiers, strings);
                }
            }
            break;
        case AST_SUBSCRIPT_EXPR:
            if (node->data.subscript_expr.target) {
                print_tree_prefix(depth + 1, 0);
                printf("target:\n");
                print_ast_with_prefix(node->data.subscript_expr.target, depth + 2, 0, keywords, identifiers, strings);
            }
            if (node->data.subscript_expr.index) {
                print_tree_prefix(depth + 1, 1);
                printf("index:\n");
                print_ast_with_prefix(node->data.subscript_expr.index, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        case AST_MEMBER_EXPR:
            if (node->data.member_expr.target) {
                print_tree_prefix(depth + 1, 0);
                printf("target:\n");
                print_ast_with_prefix(node->data.member_expr.target, depth + 2, 0, keywords, identifiers, strings);
            }
            print_tree_prefix(depth + 1, 1);
            printf("member: ");
            if (node->data.member_expr.member &&
                node->data.member_expr.member->entry && identifiers) {
                const char *name = interner_get_cstr(identifiers, node->data.member_expr.member->entry->dense_index);
                printf("'%s'", name ? name : "?");
            } else {
                printf("(unknown)");
            }
            printf("\n");
            break;
        case AST_CAST: {
            if (node->data.cast_expr.expr) {
                print_tree_prefix(depth + 1, 1);
                printf("expression:\n");
                print_ast_with_prefix(node->data.cast_expr.expr, depth + 2, 1, keywords, identifiers, strings);
            }
            break;
        }
        case AST_TYPE: {
            print_tree_prefix(depth + 1, 0);
            printf("kind: %s", type_kind_to_string(node->data.ast_type.kind));
            if (node->data.ast_type.span.start_line > 0) {
                printf(" [%zu:%zu-%zu:%zu]",
                       node->data.ast_type.span.start_line, node->data.ast_type.span.start_col,
                       node->data.ast_type.span.end_line, node->data.ast_type.span.end_col);
            }
            printf("\n");
            switch (node->data.ast_type.kind) {
                case AST_TYPE_PRIMITIVE:
                    print_tree_prefix(depth + 1, 1);
                    printf("type_name: ");
                    if (node->data.ast_type.u.base.intern_result && node->data.ast_type.u.base.intern_result->entry) {
                        int dense_index = node->data.ast_type.u.base.intern_result->entry->dense_index;
                        const char *type_name = "?";
                        if (keywords) {
                            type_name = interner_get_cstr(keywords, dense_index);
                        }
                        if (!type_name && identifiers) {
                            type_name = interner_get_cstr(identifiers, dense_index);
                        }
                        printf("'%s'", type_name ? type_name : "?");
                    } else {
                        printf("(unknown)");
                    }
                    printf("\n");
                    break;
                case AST_TYPE_PTR:
                    if (node->data.ast_type.u.ptr.target) {
                        print_tree_prefix(depth + 1, 1);
                        printf("target_type:\n");
                        print_ast_with_prefix(node->data.ast_type.u.ptr.target, depth + 2, 1, keywords, identifiers, strings);
                    }
                    break;
                case AST_TYPE_ARRAY:
                    if (node->data.ast_type.u.array.elem) {
                        print_tree_prefix(depth + 1, !node->data.ast_type.u.array.size_expr);
                        printf("element_type:\n");
                        print_ast_with_prefix(node->data.ast_type.u.array.elem, depth + 2, !node->data.ast_type.u.array.size_expr, keywords, identifiers, strings);
                    }
                    if (node->data.ast_type.u.array.size_expr) {
                        print_tree_prefix(depth + 1, 1);
                        printf("size:\n");
                        print_ast_with_prefix(node->data.ast_type.u.array.size_expr, depth + 2, 1, keywords, identifiers, strings);
                    } else {
                        print_tree_prefix(depth + 1, 1);
                        printf("size: (unspecified)\n");
                    }
                    break;
                case AST_TYPE_FUNC: {
                    int has_return = node->data.ast_type.u.func.return_type != ((void*)0);
                    int has_params = node->data.ast_type.u.func.param_types && node->data.ast_type.u.func.param_types->count > 0;
                    if (has_params) {
                        print_tree_prefix(depth + 1, !has_return);
                        printf("parameters:\n");
                        for (size_t i = 0; i < node->data.ast_type.u.func.param_types->count; ++i) {
                            AstNode *param_type = *(AstNode**)dynarray_get(node->data.ast_type.u.func.param_types, i);
                            print_ast_with_prefix(param_type, depth + 2, i == node->data.ast_type.u.func.param_types->count - 1, keywords, identifiers, strings);
                        }
                    }
                    if (has_return) {
                        print_tree_prefix(depth + 1, 1);
                        printf("return_type:\n");
                        print_ast_with_prefix(node->data.ast_type.u.func.return_type, depth + 2, 1, keywords, identifiers, strings);
                    }
                    break;
                }
            }
            break;
        }
        case AST_INITIALIZER_LIST:
            if (node->data.initializer_list.elements && node->data.initializer_list.elements->count > 0) {
                print_tree_prefix(depth + 1, 1);
                printf("elements:\n");
                for (size_t i = 0; i < node->data.initializer_list.elements->count; ++i) {
                    AstNode *elem = *(AstNode**)dynarray_get(node->data.initializer_list.elements, i);
                    print_ast_with_prefix(elem, depth + 2, i == node->data.initializer_list.elements->count - 1, keywords, identifiers, strings);
                }
            }
            break;
        case AST_BREAK_STATEMENT:
        case AST_CONTINUE_STATEMENT:
            break;
        default:
            print_tree_prefix(depth + 1, 1);
            printf("(unhandled node type: %d)\n", node->node_type);
            break;
    }
}

AstNode *parse_expression(Parser *p, ParseError *err);
AstNode *parse_assignment(Parser *p, AstNode *lhs, ParseError *err);
AstNode *parse_logical_or(Parser *p, ParseError *err);
AstNode *parse_logical_and(Parser *p, ParseError *err);
AstNode *parse_equality(Parser *p, ParseError *err);
AstNode *parse_relational(Parser *p, ParseError *err);
AstNode *parse_additive(Parser *p, ParseError *err);
AstNode *parse_multiplicative(Parser *p, ParseError *err);
AstNode *parse_cast(Parser *p, ParseError *err);
AstNode *parse_unary(Parser *p, ParseError *err);
AstNode *parse_postfix(Parser *p, ParseError *err);
AstNode *parse_primary(Parser *p, ParseError *err);
AstNode *parse_initializer_list(Parser *p, ParseError *err);
int parse_argument_list(Parser *p, AstNode* call, ParseError *err);
AstNode *parse_type(Parser *p, ParseError *err);
AstNode *parse_type_atom(Parser *p, ParseError *err);
InternResult *get_base_type(Parser *p, ParseError *err);
AstNode *parse_function_type(Parser *p, ParseError *err);
AstNode *parse_program(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    AstNode *program = new_node_or_err(p, AST_PROGRAM, err, "out of memory creating program node");
    if (!program) return ((void*)0);
    program->data.program.decls = alloc_dynarray(p, err, sizeof(AstNode*), 8, "out of memory creating program decls");
    if (!program->data.program.decls) return ((void*)0);
    Span first_span = {0}, last_span = {0};
    _Bool have_any = 0;
    for (;;) {
        if (err && err->message) return ((void*)0);
        AstNode *decl = parse_declaration(p, err);
        if (!decl) break;
        if (dynarray_push_value(program->data.program.decls, &decl) != 0) {
            if (err) create_parse_error(err, p, "out of memory adding declaration to program", ((void*)0));
            return ((void*)0);
        }
        if (!have_any) {
            first_span = decl->span;
            have_any = 1;
        }
        last_span = decl->span;
    }
    if (p->current < p->end) {
        if (err && !err->message) {
            Token *t = current_token(p);
            create_parse_error(err, p, "trailing tokens after program end", t);
        }
        return ((void*)0);
    }
    if (have_any) program->span = span_join(&first_span, &last_span);
    else if (p->tokens && p->tokens->count > 0) {
        Token *first = (Token*)dynarray_get(p->tokens, 0);
        program->span = first->span;
    } else {
        program->span = (Span){0,0,0,0};
    }
    return program;
}
AstNode *parse_declaration(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    InternResult *link_name = ((void*)0);
    if (current_token(p) && current_token(p)->type == TOK_AT) {
        consume(p, TOK_AT);
        Token *attr_name = consume(p, TOK_IDENTIFIER);
        if (attr_name) {
            if (attr_name->slice.len == 4 && memcmp(attr_name->slice.ptr, "link", 4) == 0) {
                if (!consume(p, TOK_LPAREN)) {
                    if (err) create_parse_error(err, p, "expected '(' after @link", current_token(p));
                    return ((void*)0);
                }
                Token *name_lit = consume(p, TOK_STRING_LIT);
                if (!name_lit) {
                    if (err) create_parse_error(err, p, "expected string literal in @link", current_token(p));
                    return ((void*)0);
                }
                link_name = name_lit->record;
                if (!consume(p, TOK_RPAREN)) {
                    if (err) create_parse_error(err, p, "expected ')' after @link name", current_token(p));
                    return ((void*)0);
                }
            } else {
                if (err) create_parse_error(err, p, "unknown attribute", attr_name);
                return ((void*)0);
            }
        }
    }
    _Bool is_pub = (parser_match(p, TOK_PUB) != 0);
    Token *current = current_token(p);
    if (!current) {
        if (err) create_parse_error(err, p, "Unexpected end of input", ((void*)0));
        return ((void*)0);
    }
    if (current->type == TOK_EOF) {
        consume(p, TOK_EOF);
        return ((void*)0);
    }
    AstNode *decl = ((void*)0);
    switch (current->type) {
        case TOK_IMPORT:
            decl = parse_import_declaration(p, err);
            if (decl) {
                decl->data.import_declaration.is_pub = is_pub;
            }
            return decl;
        case TOK_ALIAS:
             if (is_pub) {
                if (err) create_parse_error(err, p, "public aliases are not supported", current);
                return ((void*)0);
            }
            decl = parse_alias_declaration(p, err);
            return decl;
        case TOK_FN:
            decl = parse_function_declaration(p, err);
            if (decl) {
                decl->data.function_declaration.is_pub = is_pub;
                decl->data.function_declaration.link_name = link_name;
            }
            return decl;
        case TOK_STRUCT:
            decl = parse_struct_declaration(p, err);
            if (decl) {
                decl->data.struct_declaration.is_pub = is_pub;
                if (link_name) {
                    if (err) create_parse_error(err, p, "@link attribute not supported for structs", current);
                }
            }
            return decl;
        case TOK_CONST:
        case TOK_IDENTIFIER:
            decl = parse_declaration_stmt(p, err);
            if (decl) {
                decl->data.variable_declaration.is_pub = is_pub;
                if (link_name) {
                    if (err) create_parse_error(err, p, "@link attribute not supported for variables", current);
                }
            }
            return decl;
        default:
            if (err) create_parse_error(err, p, "expected function, struct or variable declaration", current);
            return ((void*)0);
    }
}
AstNode *parse_alias_declaration(Parser *p, ParseError *err) {
    Token *alias_tok = consume(p, TOK_ALIAS);
    if (!alias_tok) return ((void*)0);
    AstNode *decl = new_node_or_err(p, AST_ALIAS_DECLARATION, err, "out of memory creating alias node");
    if (!decl) return ((void*)0);
    Token *name_tok = consume(p, TOK_IDENTIFIER);
    if (!name_tok) {
        if (err) create_parse_error(err, p, "expected alias name identifier", current_token(p));
        return ((void*)0);
    }
    decl->data.alias_declaration.alias_name = name_tok->record;
    if (!consume(p, TOK_ASSIGN)) {
        if (err) create_parse_error(err, p, "expected '=' after alias name", current_token(p));
        return ((void*)0);
    }
    AstNode *target = parse_postfix(p, err);
    if (!target) return ((void*)0);
    decl->data.alias_declaration.target = target;
    Token *semi = consume(p, TOK_SEMICOLON);
    if (!semi) {
        if (err) create_parse_error(err, p, "expected ';' after alias declaration", current_token(p));
        return ((void*)0);
    }
    decl->span = span_join(&alias_tok->span, &semi->span);
    return decl;
}
AstNode *parse_import_declaration(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *import_tok = consume(p, TOK_IMPORT);
    if (!import_tok) return ((void*)0);
    AstNode *decl = new_node_or_err(p, AST_IMPORT_DECLARATION, err, "out of memory creating import declaration node");
    if (!decl) return ((void*)0);
    decl->data.import_declaration.module_path = alloc_dynarray(p, err, sizeof(InternResult*), 4, "out of memory creating module path array");
    if (!decl->data.import_declaration.module_path) return ((void*)0);
    decl->data.import_declaration.module_alias = ((void*)0);
    decl->data.import_declaration.specific_symbols = ((void*)0);
    decl->data.import_declaration.leading_dots = 0;
    decl->data.import_declaration.is_root_relative = 0;
    while (current_token(p) && current_token(p)->type == TOK_DOT) {
        consume(p, TOK_DOT);
        decl->data.import_declaration.leading_dots++;
    }
    if (decl->data.import_declaration.leading_dots == 0) {
        if (parser_match(p, TOK_AT)) {
            decl->data.import_declaration.is_root_relative = 1;
        }
    }
    do {
        Token *part = consume(p, TOK_IDENTIFIER);
        if (!part) {
            if (err) create_parse_error(err, p, "expected identifier in module path", current_token(p));
            return ((void*)0);
        }
        dynarray_push_value(decl->data.import_declaration.module_path, &part->record);
    } while (parser_match(p, TOK_DOT));
    if (parser_match(p, TOK_LBRACE)) {
        decl->data.import_declaration.specific_symbols = alloc_dynarray(p, err, sizeof(ImportSymbol*), 4, "out of memory creating specific symbols array");
        if (!decl->data.import_declaration.specific_symbols) return ((void*)0);
        while (current_token(p) && current_token(p)->type != TOK_RBRACE && current_token(p)->type != TOK_EOF) {
            Token *sym_tok = consume(p, TOK_IDENTIFIER);
            if (!sym_tok) {
                if (err) create_parse_error(err, p, "expected identifier in import list", current_token(p));
                return ((void*)0);
            }
            ImportSymbol *sym = arena_alloc(p->arena, sizeof(ImportSymbol));
            sym->original_name = sym_tok->record;
            sym->alias_name = ((void*)0);
            if (parser_match(p, TOK_ALIAS)) {
                Token *alias_tok = consume(p, TOK_IDENTIFIER);
                if (!alias_tok) {
                    if (err) create_parse_error(err, p, "expected identifier after 'alias'", current_token(p));
                    return ((void*)0);
                }
                sym->alias_name = alias_tok->record;
            }
            dynarray_push_value(decl->data.import_declaration.specific_symbols, &sym);
            if (!parser_match(p, TOK_COMMA)) break;
        }
        if (!consume(p, TOK_RBRACE)) {
            if (err) create_parse_error(err, p, "expected '}' after import list", current_token(p));
            return ((void*)0);
        }
    }
    else if (parser_match(p, TOK_ALIAS)) {
        Token *alias_tok = consume(p, TOK_IDENTIFIER);
        if (!alias_tok) {
            if (err) create_parse_error(err, p, "expected identifier after 'alias'", current_token(p));
            return ((void*)0);
        }
        decl->data.import_declaration.module_alias = alias_tok->record;
    }
    Token *semi = consume(p, TOK_SEMICOLON);
    if (!semi) {
        if (err) create_parse_error(err, p, "expected ';' after import declaration", current_token(p));
        return ((void*)0);
    }
    decl->span = span_join(&import_tok->span, &semi->span);
    return decl;
}
AstNode *parse_struct_declaration(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *struct_kw = consume(p, TOK_STRUCT);
    if (!struct_kw) return ((void*)0);
    AstNode *decl = new_node_or_err(p, AST_STRUCT_DECLARATION, err, "out of memory creating struct declaration node");
    if (!decl) return ((void*)0);
    Token *name_tok = consume(p, TOK_IDENTIFIER);
    if (!name_tok) {
        if (err) create_parse_error(err, p, "expected identifier after 'struct'", current_token(p));
        return ((void*)0);
    }
    decl->data.struct_declaration.intern_result = name_tok->record;
    decl->data.struct_declaration.fields = arena_alloc(p->arena, sizeof(DynArray));
    if (!decl->data.struct_declaration.fields) {
        if (err) create_parse_error(err, p, "out of memory allocating struct fields array", current_token(p));
        return ((void*)0);
    }
    dynarray_init_in_arena(decl->data.struct_declaration.fields, p->arena, sizeof(AstFieldDecl), 8);
    if (!consume(p, TOK_LBRACE)) {
        if (err) create_parse_error(err, p, "expected '{' starting struct body", current_token(p));
        return ((void*)0);
    }
    Token *current = current_token(p);
    while (current && current->type != TOK_RBRACE && current->type != TOK_EOF) {
        AstFieldDecl field = {0};
        Token *field_name = consume(p, TOK_IDENTIFIER);
        if (!field_name) {
            if (err) create_parse_error(err, p, "expected field name identifier", current_token(p));
            return ((void*)0);
        }
        field.name = field_name->record;
        if (!consume(p, TOK_COLON)) {
            if (err) create_parse_error(err, p, "expected ':' after field name", current_token(p));
            return ((void*)0);
        }
        AstNode *type = parse_type(p, err);
        if (!type) return ((void*)0);
        field.type = type;
        if (!consume(p, TOK_SEMICOLON)) {
            if (err) create_parse_error(err, p, "expected ';' after field type", current_token(p));
            return ((void*)0);
        }
        dynarray_push_value(decl->data.struct_declaration.fields, &field);
        current = current_token(p);
    }
    Token *rbrace = consume(p, TOK_RBRACE);
    if (!rbrace) {
        if (err) create_parse_error(err, p, "expected '}' closing struct body", current_token(p));
        return ((void*)0);
    }
    decl->span = span_join(&struct_kw->span, &rbrace->span);
    return decl;
}
AstNode *parse_declaration_stmt(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    AstNode *declaration = parse_variable_declaration(p, err);
    if (!declaration) return ((void*)0);
    Token *semi = consume(p, TOK_SEMICOLON);
    if (!semi) {
        if (err) {err->use_prev_token = 1; create_parse_error(err, p, "expected ';' after variable declaration", current_token(p));}
        return ((void*)0);
    }
    declaration->span = span_join(&declaration->span, &semi->span);
    return declaration;
}
AstNode *parse_variable_declaration(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    AstNode *declaration = new_node_or_err(p, AST_VARIABLE_DECLARATION, err, "out of memory creating variable declaration node");
    if (!declaration) return ((void*)0);
    Token *tok = current_token(p);
    if (!tok) {
        if (err) create_parse_error(err, p, "unexpected end of input in variable declaration", ((void*)0));
        return ((void*)0);
    }
    if (tok->type == TOK_CONST) {
        Token *const_tok = consume(p, TOK_CONST);
        declaration->data.variable_declaration.is_const = 1;
        declaration->span = const_tok->span;
    } else {
        declaration->span = (Span){0,0,0,0};
    }
    Token *name_tok = consume(p, TOK_IDENTIFIER);
    if (!name_tok) {
        if (err) create_parse_error(err, p, "expected identifier in variable declaration", current_token(p));
        return ((void*)0);
    }
    declaration->data.variable_declaration.intern_result = name_tok->record;
    if (declaration->span.start_line == 0) declaration->span = name_tok->span;
    else declaration->span = span_join(&declaration->span, &name_tok->span);
    if (!consume(p, TOK_COLON)) {
        if (err) create_parse_error(err, p, "expected ':' after variable name", current_token(p));
        return ((void*)0);
    }
    AstNode *type = parse_type(p, err);
    if (!type) return ((void*)0);
    declaration->data.variable_declaration.type = type;
    AstNode *initializer = ((void*)0);
    if (parser_match(p, TOK_ASSIGN)) {
        Token *token = current_token(p);
        if (token && token->type == TOK_LBRACE) {
            initializer = parse_initializer_list(p, err);
        } else {
            initializer = parse_expression(p, err);
        }
        if (!initializer) return ((void*)0);
        declaration->span = span_join(&declaration->span, &initializer->span);
    } else {
        declaration->span = span_join(&declaration->span, &type->span);
    }
    declaration->data.variable_declaration.initializer = initializer;
    return declaration;
}
AstNode *parse_function_declaration(Parser *p, ParseError *err) {
    AstNode *func_decl = ast_create_node(AST_FUNCTION_DECLARATION, p->arena, p->filename);
    if (!func_decl) {
        if (err) create_parse_error(err, p, "out of memory creating function declaration node", ((void*)0));
        return ((void*)0);
    }
    func_decl->data.function_declaration.params = arena_alloc(p->arena, sizeof(DynArray));
    if (!func_decl->data.function_declaration.params) {
        if (err) create_parse_error(err, p, "out of memory creating function params", ((void*)0));
        return ((void*)0);
    }
    dynarray_init_in_arena(func_decl->data.function_declaration.params, p->arena, sizeof(AstNode*), 4);
    Token *fn_tok = consume(p, TOK_FN);
    if (!fn_tok) { create_parse_error(err, p, "expected 'fn' keyword at start of function declaration", current_token(p)); return ((void*)0); }
    func_decl->span = fn_tok->span;
    Token *name_tok = consume(p, TOK_IDENTIFIER);
    if (!name_tok) { create_parse_error(err, p, "expected function name", current_token(p)); return ((void*)0); }
    func_decl->data.function_declaration.intern_result = name_tok->record;
    if (!consume(p, TOK_LPAREN)) { create_parse_error(err, p, "expected '(' after function name", current_token(p)); return ((void*)0); }
    if (!parse_parameter_list(p, func_decl, err)) {
        return ((void*)0);
    }
    if (!consume(p, TOK_RPAREN)) { create_parse_error(err, p, "expected ')' after function parameters", current_token(p)); return ((void*)0); }
    Token *arrow_tok = current_token(p);
    if (arrow_tok && arrow_tok->type == TOK_ARROW) {
        consume(p, TOK_ARROW);
        AstNode *return_type = parse_type(p, err);
        if (!return_type) { return ((void*)0); }
        func_decl->data.function_declaration.return_type = return_type;
    } else {
        func_decl->data.function_declaration.return_type = ((void*)0);
    }
    Token *tok = current_token(p);
    if (tok && tok->type == TOK_SEMICOLON) {
        consume(p, TOK_SEMICOLON);
        func_decl->data.function_declaration.body = ((void*)0);
        func_decl->span = span_join(&func_decl->span, &tok->span);
    } else {
        func_decl->data.function_declaration.body = parse_block(p, err);
        if (!func_decl->data.function_declaration.body) return ((void*)0);
        func_decl->span = span_join(&func_decl->span, &func_decl->data.function_declaration.body->span);
    }
    return func_decl;
}
int parse_parameter_list(Parser *p, AstNode *func_decl, ParseError *err) {
    if (!func_decl || func_decl->node_type != AST_FUNCTION_DECLARATION) {
        if (err) create_parse_error(err, p, "internal error: parse_parameter_list called with non-function-declaration node", current_token(p));
        return 0;
    }
    Token *tok = current_token(p);
    if (!tok) {
        if (err) create_parse_error(err, p, "unexpected end of input in parameter list", ((void*)0));
        return 0;
    }
    if (tok->type == TOK_RPAREN) {
        return 1;
    }
    while (1) {
        tok = current_token(p);
        if (!tok) {
            if (err) create_parse_error(err, p, "unexpected end of input in parameter list", ((void*)0));
            return 0;
        }
        if (tok->type != TOK_IDENTIFIER) {
            if (err) create_parse_error(err, p, "expected identifier for parameter name", ((void*)0));
            return 0;
        }
        Span start_span = tok->span;
        AstNode *param = ast_create_node(AST_PARAM, p->arena, p->filename);
        if (!param) {
            if (err) create_parse_error(err, p, "out of memory creating parameter node", ((void*)0));
            return 0;
        }
        param->data.param.name_idx = tok->record ? tok->record->entry->dense_index : -1;
        consume(p, TOK_IDENTIFIER);
        if (!consume(p, TOK_COLON)) {
            if (err) create_parse_error(err, p, "expected ':' after parameter name", current_token(p));
            return 0;
        }
        param->data.param.type = parse_type(p, err);
        if (!param->data.param.type) {
            return 0;
        }
        param->span = span_join(&start_span, &param->data.param.type->data.ast_type.span);
        if (dynarray_push_value(func_decl->data.function_declaration.params, &param) != 0) {
            if (err) create_parse_error(err, p, "out of memory pushing parameter", ((void*)0));
            return 0;
        }
        tok = current_token(p);
        if (!tok) {
            if (err) create_parse_error(err, p, "unexpected end of input in parameter list", ((void*)0));
            return 0;
        }
        if (tok->type == TOK_RPAREN) {
            break;
        }
        if (!consume(p, TOK_COMMA)) {
            if (err) create_parse_error(err, p, "expected ',' or ')' after parameter", tok);
            return 0;
        }
        tok = current_token(p);
        if (tok && tok->type == TOK_RPAREN) break;
    }
    return 1;
}
 typedef float float_t;
    typedef double double_t;
extern int __math_errhandling(void);
extern int __fpclassifyf(float);
extern int __fpclassifyd(double);
extern int __fpclassifyl(long double);
inline __attribute__ ((__always_inline__)) int __inline_isfinitef(float);
inline __attribute__ ((__always_inline__)) int __inline_isfinited(double);
inline __attribute__ ((__always_inline__)) int __inline_isfinitel(long double);
inline __attribute__ ((__always_inline__)) int __inline_isinff(float);
inline __attribute__ ((__always_inline__)) int __inline_isinfd(double);
inline __attribute__ ((__always_inline__)) int __inline_isinfl(long double);
inline __attribute__ ((__always_inline__)) int __inline_isnanf(float);
inline __attribute__ ((__always_inline__)) int __inline_isnand(double);
inline __attribute__ ((__always_inline__)) int __inline_isnanl(long double);
inline __attribute__ ((__always_inline__)) int __inline_isnormalf(float);
inline __attribute__ ((__always_inline__)) int __inline_isnormald(double);
inline __attribute__ ((__always_inline__)) int __inline_isnormall(long double);
inline __attribute__ ((__always_inline__)) int __inline_signbitf(float);
inline __attribute__ ((__always_inline__)) int __inline_signbitd(double);
inline __attribute__ ((__always_inline__)) int __inline_signbitl(long double);
inline __attribute__ ((__always_inline__)) int __inline_isfinitef(float __x) {
    return __x == __x && __builtin_fabsf(__x) != __builtin_inff();
}
inline __attribute__ ((__always_inline__)) int __inline_isfinited(double __x) {
    return __x == __x && __builtin_fabs(__x) != __builtin_inf();
}
inline __attribute__ ((__always_inline__)) int __inline_isfinitel(long double __x) {
    return __x == __x && __builtin_fabsl(__x) != __builtin_infl();
}
inline __attribute__ ((__always_inline__)) int __inline_isinff(float __x) {
    return __builtin_fabsf(__x) == __builtin_inff();
}
inline __attribute__ ((__always_inline__)) int __inline_isinfd(double __x) {
    return __builtin_fabs(__x) == __builtin_inf();
}
inline __attribute__ ((__always_inline__)) int __inline_isinfl(long double __x) {
    return __builtin_fabsl(__x) == __builtin_infl();
}
inline __attribute__ ((__always_inline__)) int __inline_isnanf(float __x) {
    return __x != __x;
}
inline __attribute__ ((__always_inline__)) int __inline_isnand(double __x) {
    return __x != __x;
}
inline __attribute__ ((__always_inline__)) int __inline_isnanl(long double __x) {
    return __x != __x;
}
inline __attribute__ ((__always_inline__)) int __inline_signbitf(float __x) {
    union { float __f; unsigned int __u; } __u;
    __u.__f = __x;
    return (int)(__u.__u >> 31);
}
inline __attribute__ ((__always_inline__)) int __inline_signbitd(double __x) {
    union { double __f; unsigned long long __u; } __u;
    __u.__f = __x;
    return (int)(__u.__u >> 63);
}
inline __attribute__ ((__always_inline__)) int __inline_signbitl(long double __x) {
    union { long double __f; unsigned long long __u;} __u;
    __u.__f = __x;
    return (int)(__u.__u >> 63);
}
inline __attribute__ ((__always_inline__)) int __inline_isnormalf(float __x) {
    return __inline_isfinitef(__x) && __builtin_fabsf(__x) >= 1.17549435e-38F;
}
inline __attribute__ ((__always_inline__)) int __inline_isnormald(double __x) {
    return __inline_isfinited(__x) && __builtin_fabs(__x) >= 2.2250738585072014e-308;
}
inline __attribute__ ((__always_inline__)) int __inline_isnormall(long double __x) {
    return __inline_isfinitel(__x) && __builtin_fabsl(__x) >= 2.2250738585072014e-308L;
}
extern float acosf(float);
extern double acos(double);
extern long double acosl(long double);
extern float asinf(float);
extern double asin(double);
extern long double asinl(long double);
extern float atanf(float);
extern double atan(double);
extern long double atanl(long double);
extern float atan2f(float, float);
extern double atan2(double, double);
extern long double atan2l(long double, long double);
extern float cosf(float);
extern double cos(double);
extern long double cosl(long double);
extern float sinf(float);
extern double sin(double);
extern long double sinl(long double);
extern float tanf(float);
extern double tan(double);
extern long double tanl(long double);
extern float acoshf(float);
extern double acosh(double);
extern long double acoshl(long double);
extern float asinhf(float);
extern double asinh(double);
extern long double asinhl(long double);
extern float atanhf(float);
extern double atanh(double);
extern long double atanhl(long double);
extern float coshf(float);
extern double cosh(double);
extern long double coshl(long double);
extern float sinhf(float);
extern double sinh(double);
extern long double sinhl(long double);
extern float tanhf(float);
extern double tanh(double);
extern long double tanhl(long double);
extern float expf(float);
extern double exp(double);
extern long double expl(long double);
extern float exp2f(float);
extern double exp2(double);
extern long double exp2l(long double);
extern float expm1f(float);
extern double expm1(double);
extern long double expm1l(long double);
extern float logf(float);
extern double log(double);
extern long double logl(long double);
extern float log10f(float);
extern double log10(double);
extern long double log10l(long double);
extern float log2f(float);
extern double log2(double);
extern long double log2l(long double);
extern float log1pf(float);
extern double log1p(double);
extern long double log1pl(long double);
extern float logbf(float);
extern double logb(double);
extern long double logbl(long double);
extern float modff(float, float *);
extern double modf(double, double *);
extern long double modfl(long double, long double *);
extern float ldexpf(float, int);
extern double ldexp(double, int);
extern long double ldexpl(long double, int);
extern float frexpf(float, int *);
extern double frexp(double, int *);
extern long double frexpl(long double, int *);
extern int ilogbf(float);
extern int ilogb(double);
extern int ilogbl(long double);
extern float scalbnf(float, int);
extern double scalbn(double, int);
extern long double scalbnl(long double, int);
extern float scalblnf(float, long int);
extern double scalbln(double, long int);
extern long double scalblnl(long double, long int);
extern float fabsf(float);
extern double fabs(double);
extern long double fabsl(long double);
extern float cbrtf(float);
extern double cbrt(double);
extern long double cbrtl(long double);
extern float hypotf(float, float);
extern double hypot(double, double);
extern long double hypotl(long double, long double);
extern float powf(float, float);
extern double pow(double, double);
extern long double powl(long double, long double);
extern float sqrtf(float);
extern double sqrt(double);
extern long double sqrtl(long double);
extern float erff(float);
extern double erf(double);
extern long double erfl(long double);
extern float erfcf(float);
extern double erfc(double);
extern long double erfcl(long double);
extern float lgammaf(float);
extern double lgamma(double);
extern long double lgammal(long double);
extern float tgammaf(float);
extern double tgamma(double);
extern long double tgammal(long double);
extern float ceilf(float);
extern double ceil(double);
extern long double ceill(long double);
extern float floorf(float);
extern double floor(double);
extern long double floorl(long double);
extern float nearbyintf(float);
extern double nearbyint(double);
extern long double nearbyintl(long double);
extern float rintf(float);
extern double rint(double);
extern long double rintl(long double);
extern long int lrintf(float);
extern long int lrint(double);
extern long int lrintl(long double);
extern float roundf(float);
extern double round(double);
extern long double roundl(long double);
extern long int lroundf(float);
extern long int lround(double);
extern long int lroundl(long double);
extern long long int llrintf(float);
extern long long int llrint(double);
extern long long int llrintl(long double);
extern long long int llroundf(float);
extern long long int llround(double);
extern long long int llroundl(long double);
extern float truncf(float);
extern double trunc(double);
extern long double truncl(long double);
extern float fmodf(float, float);
extern double fmod(double, double);
extern long double fmodl(long double, long double);
extern float remainderf(float, float);
extern double remainder(double, double);
extern long double remainderl(long double, long double);
extern float remquof(float, float, int *);
extern double remquo(double, double, int *);
extern long double remquol(long double, long double, int *);
extern float copysignf(float, float);
extern double copysign(double, double);
extern long double copysignl(long double, long double);
extern float nanf(const char *);
extern double nan(const char *);
extern long double nanl(const char *);
extern float nextafterf(float, float);
extern double nextafter(double, double);
extern long double nextafterl(long double, long double);
extern double nexttoward(double, long double);
extern float nexttowardf(float, long double);
extern long double nexttowardl(long double, long double);
extern float fdimf(float, float);
extern double fdim(double, double);
extern long double fdiml(long double, long double);
extern float fmaxf(float, float);
extern double fmax(double, double);
extern long double fmaxl(long double, long double);
extern float fminf(float, float);
extern double fmin(double, double);
extern long double fminl(long double, long double);
extern float fmaf(float, float, float);
extern double fma(double, double, double);
extern long double fmal(long double, long double, long double);
extern float __exp10f(float) __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0)));
extern double __exp10(double) __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0)));
inline __attribute__ ((__always_inline__)) void __sincosf(float __x, float *__sinp, float *__cosp);
inline __attribute__ ((__always_inline__)) void __sincos(double __x, double *__sinp, double *__cosp);
extern float __cospif(float) __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0)));
extern double __cospi(double) __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0)));
extern float __sinpif(float) __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0)));
extern double __sinpi(double) __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0)));
extern float __tanpif(float) __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0)));
extern double __tanpi(double) __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0)));
extern _Float16 __fabsf16(_Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __hypotf16(_Float16, _Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __sqrtf16(_Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __ceilf16(_Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __floorf16(_Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __rintf16(_Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __roundf16(_Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __truncf16(_Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __copysignf16(_Float16, _Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __nextafterf16(_Float16, _Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __fmaxf16(_Float16, _Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __fminf16(_Float16, _Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
extern _Float16 __fmaf16(_Float16, _Float16, _Float16) __attribute__((availability(macos,introduced=15.0))) __attribute__((availability(ios,introduced=18.0))) __attribute__((availability(watchos,introduced=11.0))) __attribute__((availability(tvos,introduced=18.0)));
inline __attribute__ ((__always_inline__)) void __sincospif(float __x, float *__sinp, float *__cosp);
inline __attribute__ ((__always_inline__)) void __sincospi(double __x, double *__sinp, double *__cosp);
struct __float2 { float __sinval; float __cosval; };
struct __double2 { double __sinval; double __cosval; };
extern struct __float2 __sincosf_stret(float);
extern struct __double2 __sincos_stret(double);
extern struct __float2 __sincospif_stret(float);
extern struct __double2 __sincospi_stret(double);
inline __attribute__ ((__always_inline__)) void __sincosf(float __x, float *__sinp, float *__cosp) {
    const struct __float2 __stret = __sincosf_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}
inline __attribute__ ((__always_inline__)) void __sincos(double __x, double *__sinp, double *__cosp) {
    const struct __double2 __stret = __sincos_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}
inline __attribute__ ((__always_inline__)) void __sincospif(float __x, float *__sinp, float *__cosp) {
    const struct __float2 __stret = __sincospif_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}
inline __attribute__ ((__always_inline__)) void __sincospi(double __x, double *__sinp, double *__cosp) {
    const struct __double2 __stret = __sincospi_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}
extern double j0(double) __attribute__((availability(macos,introduced=10.0))) __attribute__((availability(ios,introduced=3.2)));
extern double j1(double) __attribute__((availability(macos,introduced=10.0))) __attribute__((availability(ios,introduced=3.2)));
extern double jn(int, double) __attribute__((availability(macos,introduced=10.0))) __attribute__((availability(ios,introduced=3.2)));
extern double y0(double) __attribute__((availability(macos,introduced=10.0))) __attribute__((availability(ios,introduced=3.2)));
extern double y1(double) __attribute__((availability(macos,introduced=10.0))) __attribute__((availability(ios,introduced=3.2)));
extern double yn(int, double) __attribute__((availability(macos,introduced=10.0))) __attribute__((availability(ios,introduced=3.2)));
extern double scalb(double, double);
extern int signgam;
struct exception {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
};

static inline _Bool parse_int_lit(const char *s, size_t len, long long *out) {
    if (len == 0) return 0;
    int base = 10;
    size_t start = 0;
    if (len > 2 && s[0] == '0') {
        if (s[1] == 'x' || s[1] == 'X') {
            base = 16;
            start = 2;
        } else if (s[1] == 'b' || s[1] == 'B') {
            base = 2;
            start = 2;
        }
    }
    uint64_t val = 0;
    _Bool any_digits = 0;
    for (size_t i = start; i < len; i++) {
        if (s[i] == '_') continue;
        unsigned int d = 0;
        char c = s[i];
        if (c >= '0' && c <= '9') d = (unsigned int)(c - '0');
        else if (c >= 'a' && c <= 'f') d = (unsigned int)(10 + (c - 'a'));
        else if (c >= 'A' && c <= 'F') d = (unsigned int)(10 + (c - 'A'));
        else return 0;
        if (d >= (unsigned int)base) return 0;
        if (val > ((9223372036854775807LL*2ULL+1ULL) - d) / (unsigned int)base) return 0;
        val = val * (unsigned int)base + d;
        any_digits = 1;
    }
    if (!any_digits) return 0;
    if (base == 10 && val > 9223372036854775807LL) return 0;
    *out = (long long)val;
    return 1;
}
static inline _Bool parse_float_lit(const char *s, size_t len, double *out) {
    double val = 0.0;
    size_t i = 0;
    for (; i < len && s[i] >= '0' && s[i] <= '9'; i++) {
        val = val * 10.0 + (s[i] - '0');
    }
    if (i < len && s[i] == '.') {
        i++;
        double frac = 0.0, base = 0.1;
        while (i < len && s[i] >= '0' && s[i] <= '9') {
            frac += (s[i] - '0') * base;
            base *= 0.1;
            i++;
        }
        val += frac;
    }
    if (i < len && (s[i] == 'e' || s[i] == 'E')) {
        i++;
        int exp_sign = 1;
        if (i < len && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') exp_sign = -1;
            i++;
        }
        int exp_val = 0;
        while (i < len && s[i] >= '0' && s[i] <= '9') {
            exp_val = exp_val * 10 + (s[i] - '0');
            i++;
        }
        val *= pow(10.0, exp_sign * exp_val);
    }
    if (i != len) return 0;
    *out = val;
    return 1;
}
typedef AstNode *(*operand_parser_fn)(Parser *p, ParseError *err);
typedef OpKind (*map_token_to_op_fn)(Token *tok);
static AstNode *parse_left_assoc_binary(Parser *p, ParseError *err,
                        operand_parser_fn parse_operand,
                        map_token_to_op_fn map_op,
                        const char *oom_msg)
{
    AstNode *lhs = parse_operand(p, err);
    if (!lhs) return ((void*)0);
    Token *token = current_token(p);
    int op;
    while (token && (op = (int)map_op(token)) != OP_NULL) {
        Token op_token = *token;
        consume(p, token->type);
        AstNode *rhs = parse_operand(p, err);
        if (!rhs) return ((void*)0);
        AstNode *bin = new_node_or_err(p, AST_BINARY_EXPR, err, oom_msg);
        if (!bin) {
            if (err) create_parse_error(err, p, oom_msg, &op_token);
            return ((void*)0);
        }
        bin->data.binary_expr.left = lhs;
        bin->data.binary_expr.right = rhs;
        bin->data.binary_expr.op = (OpKind)op;
        bin->span = span_join(&lhs->span, &rhs->span);
        lhs = bin;
        token = current_token(p);
    }
    return lhs;
}
AstNode *parse_expression(Parser *p, ParseError *err) {
    AstNode *lhs = parse_logical_or(p, err);
    if (!lhs) return ((void*)0);
    Token *token = current_token(p);
    if (token && is_assignment_op(token->type)) {
        AstNode *assignment = parse_assignment(p, lhs, err);
        if (!assignment) return ((void*)0);
        return assignment;
    }
    return lhs;
}
static OpKind map_assignment_op(Token *tok) {
    if (!tok) return OP_NULL;
    switch (tok->type) {
        case TOK_ASSIGN: return OP_ASSIGN;
        case TOK_PLUS_EQ: return OP_PLUS_EQ;
        case TOK_MINUS_EQ: return OP_MINUS_EQ;
        case TOK_STAR_EQ: return OP_MUL_EQ;
        case TOK_SLASH_EQ: return OP_DIV_EQ;
        case TOK_PERCENT_EQ: return OP_MOD_EQ;
        default: return OP_NULL;
    }
}
AstNode* parse_assignment(Parser *p, AstNode *lhs, ParseError *err) {
    if (!p || !lhs) return ((void*)0);
    if (!is_lvalue_node(lhs)) {
        if (err) create_parse_error(err, p, "left-hand side of assignment must be an lvalue", ((void*)0));
        return ((void*)0);
    }
    Token *op_tok = current_token(p);
    if (!op_tok || !is_assignment_op(op_tok->type)) {
        if (err) create_parse_error(err, p, "expected assignment operator", current_token(p));
        return ((void*)0);
    }
    consume(p, op_tok->type);
    AstNode *rhs = parse_expression(p, err);
    if (!rhs) return ((void*)0);
    AstNode *assign = new_node_or_err(p, AST_ASSIGNMENT_EXPR, err, "out of memory creating assignment node");
    if (!assign) return ((void*)0);
    assign->data.assignment_expr.lvalue = lhs;
    assign->data.assignment_expr.rvalue = rhs;
    assign->data.assignment_expr.op = map_assignment_op(op_tok);
    assign->span = span_join(&lhs->span, &rhs->span);
    return assign;
}
static OpKind map_logical_or_op(Token *tok) {
    if (!tok) return OP_NULL;
    if (tok->type == TOK_OR_OR) return OP_OR;
    return OP_NULL;
}
AstNode *parse_logical_or(Parser *p, ParseError *err) {
    return parse_left_assoc_binary(p, err, parse_logical_and, map_logical_or_op, "out of memory creating logical-or node");
}
static OpKind map_logical_and_op(Token *tok) {
    if (!tok) return OP_NULL;
    if (tok->type == TOK_AND_AND) return OP_AND;
    return OP_NULL;
}
AstNode *parse_logical_and(Parser *p, ParseError *err) {
    return parse_left_assoc_binary(p, err, parse_equality, map_logical_and_op, "out of memory creating logical-and node");
}
static OpKind map_equality_op(Token *tok) {
    if (!tok) return OP_NULL;
    switch (tok->type) {
        case TOK_EQ_EQ: return OP_EQ;
        case TOK_BANG_EQ: return OP_NEQ;
        default: return OP_NULL;
    }
}
AstNode *parse_equality(Parser *p, ParseError *err) {
    return parse_left_assoc_binary(p, err, parse_relational, map_equality_op, "out of memory creating equality node");
}
static OpKind map_relational_op(Token *tok) {
    if (!tok) return OP_NULL;
    switch (tok->type) {
        case TOK_LT: return OP_LT;
        case TOK_GT: return OP_GT;
        case TOK_LT_EQ: return OP_LE;
        case TOK_GT_EQ: return OP_GE;
        default: return OP_NULL;
    }
}
AstNode *parse_relational(Parser *p, ParseError *err) {
    return parse_left_assoc_binary(p, err, parse_additive, map_relational_op, "out of memory creating relational node");
}
static OpKind map_additive_op(Token *tok) {
    if (!tok) return OP_NULL;
    switch (tok->type) {
        case TOK_PLUS: return OP_ADD;
        case TOK_MINUS: return OP_SUB;
        default: return OP_NULL;
    }
}
AstNode *parse_additive(Parser *p, ParseError *err) {
    return parse_left_assoc_binary(p, err, parse_multiplicative, map_additive_op, "out of memory creating additive node");
}
static OpKind map_multiplicative_op(Token *tok) {
    if (!tok) return OP_NULL;
    switch (tok->type) {
        case TOK_STAR: return OP_MUL;
        case TOK_SLASH: return OP_DIV;
        case TOK_PERCENT: return OP_MOD;
        default: return OP_NULL;
    }
}
AstNode *parse_multiplicative(Parser *p, ParseError *err) {
    return parse_left_assoc_binary(p, err, parse_cast, map_multiplicative_op, "out of memory creating multiplicative node");
}
AstNode *parse_cast(Parser *p, ParseError *err) {
    AstNode *expr = parse_unary(p, err);
    if (!expr) return ((void*)0);
    while (current_token(p) && current_token(p)->type == TOK_AS) {
        consume(p, TOK_AS);
        AstNode *target_type_node = parse_type(p, err);
        if (!target_type_node) return ((void*)0);
        AstNode *cast = new_node_or_err(p, AST_CAST, err, "out of memory creating cast node");
        if (!cast) return ((void*)0);
        cast->data.cast_expr.expr = expr;
        cast->data.cast_expr.target_type = ((void*)0);
        cast->data.cast_expr.target_type_node = target_type_node;
        cast->span = span_join(&expr->span, &target_type_node->span);
        expr = cast;
    }
    return expr;
}
static OpKind map_unary_op(Token *tok) {
    if (!tok) return OP_NULL;
    switch (tok->type) {
        case TOK_PLUS: return OP_ADD;
        case TOK_MINUS: return OP_SUB;
        case TOK_BANG: return OP_NOT;
        case TOK_STAR: return OP_DEREF;
        case TOK_AMP: return OP_ADRESS;
        case TOK_PLUSPLUS: return OP_PRE_INC;
        case TOK_MINUSMINUS: return OP_PRE_DEC;
        default: return OP_NULL;
    }
}
AstNode *parse_unary(Parser *p, ParseError *err) {
    Token *token = current_token(p);
    if (token && (token->type == TOK_PLUS || token->type == TOK_MINUS || token->type == TOK_BANG || token->type == TOK_STAR || token->type == TOK_AMP || token->type == TOK_PLUSPLUS || token->type == TOK_MINUSMINUS)) {
        Token *op_token = consume(p, token->type);
        if (!op_token) { if (err) create_parse_error(err, p, "failed to consume prefix operator", token); return ((void*)0); }
        AstNode *operand = parse_unary(p, err);
        if (!operand) return ((void*)0);
        AstNode *unary = new_node_or_err(p, AST_UNARY_EXPR, err, "out of memory creating unary node");
        if (!unary) return ((void*)0);
        unary->data.unary_expr.expr = operand;
        unary->data.unary_expr.op = map_unary_op(op_token);
        unary->span = span_join(&op_token->span, &operand->span);
        return unary;
    }
    return parse_postfix(p, err);
}
AstNode *parse_postfix(Parser *p, ParseError *err) {
    AstNode *primary = parse_primary(p, err);
    if (!primary) return ((void*)0);
    Token *token = current_token(p);
    while (token && (token->type == TOK_PLUSPLUS || token->type == TOK_MINUSMINUS || token->type == TOK_LBRACKET || token->type == TOK_LPAREN || token->type == TOK_DOT || token->type == TOK_LBRACE)) {
        if (token->type == TOK_PLUSPLUS || token->type == TOK_MINUSMINUS) {
            Token *op_tok = token;
            AstNode *postfix = new_node_or_err(p, AST_UNARY_EXPR, err, "out of memory creating postfix node");
            if (!postfix) return ((void*)0);
            postfix->data.unary_expr.expr = primary;
            postfix->data.unary_expr.op = (op_tok->type == TOK_PLUSPLUS) ? OP_POST_INC : OP_POST_DEC;
            postfix->span = span_join(&primary->span, &op_tok->span);
            consume(p, op_tok->type);
            primary = postfix;
        } else if (token->type == TOK_LBRACKET) {
            consume(p, TOK_LBRACKET);
            AstNode *index = parse_expression(p, err);
            if (!index) return ((void*)0);
            Token *rbr = consume(p, TOK_RBRACKET);
            if (!rbr) { if (err) create_parse_error(err, p, "expected ']' after array index expression", token); return ((void*)0); }
            AstNode *array_access = new_node_or_err(p, AST_SUBSCRIPT_EXPR, err, "out of memory creating subscript node");
            if (!array_access) return ((void*)0);
            array_access->data.subscript_expr.target = primary;
            array_access->data.subscript_expr.index = index;
            array_access->span = span_join(&primary->span, &rbr->span);
            primary = array_access;
        } else if (token->type == TOK_LPAREN) {
            consume(p, TOK_LPAREN);
            AstNode *func_call = new_node_or_err(p, AST_CALL_EXPR, err, "out of memory creating function call node");
            if (!func_call) return ((void*)0);
            func_call->data.call_expr.args = alloc_dynarray(p, err, sizeof(AstNode*), 4, "out of memory creating function call args array");
            if (!func_call->data.call_expr.args) return ((void*)0);
            if (!parse_argument_list(p, func_call, err)) return ((void*)0);
            Token *rparen = consume(p, TOK_RPAREN);
            if (!rparen) { if (err) create_parse_error(err, p, "expected ')' after function call arguments", token); return ((void*)0); }
            func_call->data.call_expr.callee = primary;
            func_call->span = span_join(&primary->span, &rparen->span);
            primary = func_call;
        } else if (token->type == TOK_DOT) {
            consume(p, TOK_DOT);
            Token *name_tok = consume(p, TOK_IDENTIFIER);
            if (!name_tok) {
                if (err) create_parse_error(err, p, "expected identifier after '.'", current_token(p));
                return ((void*)0);
            }
            AstNode *member_access = new_node_or_err(p, AST_MEMBER_EXPR, err, "out of memory creating member access node");
            if (!member_access) return ((void*)0);
            member_access->data.member_expr.target = primary;
            member_access->data.member_expr.member = name_tok->record;
            member_access->span = span_join(&primary->span, &name_tok->span);
            primary = member_access;
        } else if (token->type == TOK_LBRACE) {
            if (primary->node_type != AST_MEMBER_EXPR) {
                break;
            }
            Token *peek_2 = peek(p, 1);
            Token *peek_3 = peek(p, 2);
            _Bool is_struct_lit = 0;
            if (peek_2 && peek_2->type == TOK_RBRACE) {
                is_struct_lit = 1;
            } else if (peek_2 && peek_2->type == TOK_IDENTIFIER && peek_3 && peek_3->type == TOK_COLON) {
                is_struct_lit = 1;
            }
            if (!is_struct_lit) break;
            AstNode *struct_lit = new_node_or_err(p, AST_STRUCT_LITERAL, err, "out of memory creating struct literal node");
            if (!struct_lit) return ((void*)0);
            struct_lit->data.struct_literal.type_node = primary;
            consume(p, TOK_LBRACE);
            struct_lit->data.struct_literal.fields = arena_alloc(p->arena, sizeof(DynArray));
            if (!struct_lit->data.struct_literal.fields) {
                if (err) create_parse_error(err, p, "out of memory allocating struct literal fields", current_token(p));
                return ((void*)0);
            }
            dynarray_init_in_arena(struct_lit->data.struct_literal.fields, p->arena, sizeof(AstFieldInit), 8);
            Token *current = current_token(p);
            while (current && current->type != TOK_RBRACE && current->type != TOK_EOF) {
                AstFieldInit init = {0};
                Token *field_name = consume(p, TOK_IDENTIFIER);
                if (!field_name) {
                    if (err) create_parse_error(err, p, "expected field name in struct literal", current_token(p));
                    return ((void*)0);
                }
                init.name = field_name->record;
                if (!consume(p, TOK_COLON)) {
                    if (err) create_parse_error(err, p, "expected ':' after field name", current_token(p));
                    return ((void*)0);
                }
                init.expr = parse_expression(p, err);
                if (!init.expr) return ((void*)0);
                dynarray_push_value(struct_lit->data.struct_literal.fields, &init);
                current = current_token(p);
                if (current && current->type == TOK_COMMA) {
                    consume(p, TOK_COMMA);
                    current = current_token(p);
                } else {
                    break;
                }
            }
            Token *rbrace = consume(p, TOK_RBRACE);
            if (!rbrace) {
                if (err) create_parse_error(err, p, "expected '}' or ',' in struct literal", current_token(p));
                return ((void*)0);
            }
            struct_lit->span = span_join(&primary->span, &rbrace->span);
            primary = struct_lit;
        }
        token = current_token(p);
    }
    return primary;
}
static LiteralType get_literal_type(TokenType type) {
    switch (type) {
        case TOK_INT_LIT: return INT_LITERAL;
        case TOK_FLOAT_LIT: return FLOAT_LITERAL;
        case TOK_TRUE: case TOK_FALSE: return BOOL_LITERAL;
        case TOK_STRING_LIT: return STRING_LITERAL;
        case TOK_CHAR_LIT: return CHAR_LITERAL;
        default: return LIT_UNKNOWN;
    }
}
int parse_argument_list(Parser *p, AstNode* call, ParseError *err) {
    Token *tok = current_token(p);
    if (!tok) { if (err) create_parse_error(err, p, "unexpected end of input in argument list", ((void*)0)); return 0; }
    if (tok->type == TOK_RPAREN) return 1;
    while (1) {
        tok = current_token(p);
        if (!tok) { if (err) create_parse_error(err, p, "unexpected end of input in argument list", ((void*)0)); return 0; }
        AstNode *argument = ((void*)0);
        if (tok->type == TOK_LBRACE) {
            argument = parse_initializer_list(p, err);
            if (!argument) return 0;
        } else {
            argument = parse_expression(p, err);
            if (!argument) return 0;
        }
        if (dynarray_push_value(call->data.call_expr.args, &argument) != 0) { if (err) create_parse_error(err, p, "out of memory adding argument to call", ((void*)0)); return 0; }
        tok = current_token(p);
        if (!tok) { if (err) create_parse_error(err, p, "unexpected end of input in argument list", ((void*)0)); return 0; }
        if (tok->type == TOK_RPAREN) break;
        if (!consume(p, TOK_COMMA)) { if (err) create_parse_error(err, p, "expected a ',' or ')'", tok); return 0; }
        tok = current_token(p);
        if (tok && tok->type == TOK_RPAREN) break;
    }
    return 1;
}
AstNode *parse_primary(Parser *p, ParseError *err) {
    Token *token = current_token(p);
    if (!token) { if (err) create_parse_error(err, p, "unexpected end of input, expected primary expression", ((void*)0)); return ((void*)0); }
    switch (token->type) {
        case TOK_AT: {
            consume(p, TOK_AT);
            Token *name_tok = consume(p, TOK_IDENTIFIER);
            if (!name_tok) {
                if (err) create_parse_error(err, p, "expected intrinsic name after '@'", current_token(p));
                return ((void*)0);
            }
            AstNode *intrinsic = new_node_or_err(p, AST_INTRINSIC, err, "out of memory creating intrinsic node");
            if (!intrinsic) return ((void*)0);
            if (name_tok->slice.len == 5 && memcmp(name_tok->slice.ptr, "alloc", 5) == 0) {
                intrinsic->data.intrinsic.kind = INTRINSIC_ALLOC;
            } else if (name_tok->slice.len == 4 && memcmp(name_tok->slice.ptr, "free", 4) == 0) {
                intrinsic->data.intrinsic.kind = INTRINSIC_FREE;
            } else {
                if (err) create_parse_error(err, p, "unknown compiler intrinsic", name_tok);
                return ((void*)0);
            }
            intrinsic->data.intrinsic.args = alloc_dynarray(p, err, sizeof(AstNode*), 4, "out of memory");
            if (!consume(p, TOK_LPAREN)) {
                if (err) create_parse_error(err, p, "expected '(' after intrinsic name", current_token(p));
                return ((void*)0);
            }
            if (current_token(p)->type != TOK_RPAREN) {
                while (1) {
                    Token *peek_tok = current_token(p);
                    AstNode *arg = ((void*)0);
                    if (peek_tok && (peek_tok->type >= TOK_I32 && peek_tok->type <= TOK_VOID)) {
                         arg = parse_type(p, err);
                    } else {
                         arg = parse_expression(p, err);
                    }
                    if (!arg) return ((void*)0);
                    dynarray_push_value(intrinsic->data.intrinsic.args, &arg);
                    if (current_token(p)->type == TOK_RPAREN) break;
                    if (!consume(p, TOK_COMMA)) {
                        if (err) create_parse_error(err, p, "expected ',' or ')'", current_token(p));
                        return ((void*)0);
                    }
                }
            }
            Token *rparen = consume(p, TOK_RPAREN);
            intrinsic->span = span_join(&name_tok->span, &rparen->span);
            return intrinsic;
        }
        case TOK_INT_LIT: case TOK_FLOAT_LIT: case TOK_TRUE: case TOK_FALSE: case TOK_CHAR_LIT: case TOK_STRING_LIT: {
            AstNode *literal = new_node_or_err(p, AST_LITERAL, err, "out of memory creating literal node");
            if (!literal) return ((void*)0);
            literal->data.literal.type = get_literal_type(token->type);
            switch (token->type) {
                case TOK_INT_LIT: {
                    long long v;
                    if (parse_int_lit(token->slice.ptr, token->slice.len, &v)) {
                        literal->data.literal.value.int_val = v;
                    } else {
                        create_parse_error(err, p, "invalid integer literal or overflow", token);
                        return ((void*)0);
                    }
                    break;
                }
                case TOK_FLOAT_LIT: {
                    double v;
                    if (parse_float_lit(token->slice.ptr, token->slice.len, &v)) {
                        literal->data.literal.value.float_val = v;
                    } else {
                        create_parse_error(err, p, "invalid float literal or overflow", token);
                        return ((void*)0);
                    }
                    break;
                }
                case TOK_TRUE:
                    literal->data.literal.value.bool_val = 1;
                    break;
                case TOK_FALSE:
                    literal->data.literal.value.bool_val = 0;
                    break;
                case TOK_CHAR_LIT:
                    literal->data.literal.value.char_val = (char)(uintptr_t)token->record;
                    break;
                case TOK_STRING_LIT:
                    literal->data.literal.value.string_val = token->record;
                    break;
                default:
                    literal->data.literal.value.int_val = 0;
                    break;
            }
            literal->is_foldable_const = 0;
            literal->is_llvm_const_safe = 0;
            literal->span = token->span;
            consume(p, token->type);
            return literal;
        }
        case TOK_IDENTIFIER: {
            Token *peek_tok = peek(p, 1);
            if (peek_tok && peek_tok->type == TOK_LBRACE) {
                Token *peek_2 = peek(p, 2);
                Token *peek_3 = peek(p, 3);
                _Bool is_struct_lit = 0;
                if (peek_2 && peek_2->type == TOK_RBRACE) {
                    is_struct_lit = 1;
                } else if (peek_2 && peek_2->type == TOK_IDENTIFIER && peek_3 && peek_3->type == TOK_COLON) {
                    is_struct_lit = 1;
                }
                if (is_struct_lit) {
                    AstNode *struct_lit = new_node_or_err(p, AST_STRUCT_LITERAL, err, "out of memory creating struct literal node");
                    if (!struct_lit) return ((void*)0);
                    AstNode *type_ident = new_node_or_err(p, AST_IDENTIFIER, err, "out of memory");
                    if (!type_ident) return ((void*)0);
                    type_ident->data.identifier.intern_result = token->record;
                    type_ident->span = token->span;
                    struct_lit->data.struct_literal.type_node = type_ident;
                    Span start_span = token->span;
                    consume(p, TOK_IDENTIFIER);
                    consume(p, TOK_LBRACE);
                    struct_lit->data.struct_literal.fields = arena_alloc(p->arena, sizeof(DynArray));
                    if (!struct_lit->data.struct_literal.fields) {
                        if (err) create_parse_error(err, p, "out of memory allocating struct literal fields", current_token(p));
                        return ((void*)0);
                    }
                    dynarray_init_in_arena(struct_lit->data.struct_literal.fields, p->arena, sizeof(AstFieldInit), 8);
                    Token *current = current_token(p);
                    while (current && current->type != TOK_RBRACE && current->type != TOK_EOF) {
                        AstFieldInit init = {0};
                        Token *field_name = consume(p, TOK_IDENTIFIER);
                        if (!field_name) {
                            if (err) create_parse_error(err, p, "expected field name in struct literal", current_token(p));
                            return ((void*)0);
                        }
                        init.name = field_name->record;
                        if (!consume(p, TOK_COLON)) {
                            if (err) create_parse_error(err, p, "expected ':' after field name", current_token(p));
                            return ((void*)0);
                        }
                        init.expr = parse_expression(p, err);
                        if (!init.expr) return ((void*)0);
                        dynarray_push_value(struct_lit->data.struct_literal.fields, &init);
                        current = current_token(p);
                        if (current && current->type == TOK_COMMA) {
                            consume(p, TOK_COMMA);
                            current = current_token(p);
                        } else {
                            break;
                        }
                    }
                    Token *rbrace = consume(p, TOK_RBRACE);
                    if (!rbrace) {
                        if (err) create_parse_error(err, p, "expected '}' or ',' in struct literal", current_token(p));
                        return ((void*)0);
                    }
                    struct_lit->span = span_join(&start_span, &rbrace->span);
                    return struct_lit;
                }
            }
            AstNode *identifier = new_node_or_err(p, AST_IDENTIFIER, err, "out of memory creating identifier node");
            if (!identifier) return ((void*)0);
            identifier->data.identifier.intern_result = token->record;
            identifier->span = token->span;
            consume(p, TOK_IDENTIFIER);
            return identifier;
        }
        case TOK_LPAREN: {
            Token *lpar = consume(p, TOK_LPAREN);
            AstNode *expr = parse_expression(p, err);
            if (!expr) return ((void*)0);
            Token *r = consume(p, TOK_RPAREN);
            if (!r) { if (err) err->use_prev_token = 1; create_parse_error(err, p, "expected ')' after expression", current_token(p)); return ((void*)0); }
            expr->span = span_join(&lpar->span, &r->span);
            return expr;
        }
        case TOK_LBRACE:
            return parse_initializer_list(p, err);
        default:
            if (err) {err->use_prev_token = 1; create_parse_error(err, p, "expected primary expression (literal, identifier, or parenthesized expression)", current_token(p));}
            return ((void*)0);
    }
}
AstNode *parse_initializer_list(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *start_tok = consume(p, TOK_LBRACE);
    if (!start_tok) {
        if (err) create_parse_error(err, p, "expected '{' to start initializer list", current_token(p));
        return ((void*)0);
    }
    Span start_span = start_tok->span;
    AstNode *init = ast_create_node(AST_INITIALIZER_LIST, p->arena, p->filename);
    if (!init) {
        if (err) create_parse_error(err, p, "out of memory creating initializer node", ((void*)0));
        return ((void*)0);
    }
    init->data.initializer_list.elements = arena_alloc(p->arena, sizeof(DynArray));
    if (!init->data.initializer_list.elements) {
        if (err) create_parse_error(err, p, "out of memory creating initializer elements", ((void*)0));
        return ((void*)0);
    }
    dynarray_init_in_arena(init->data.initializer_list.elements, p->arena, sizeof(AstNode*), 4);
    Token *tok = current_token(p);
    if (!tok) {
        create_parse_error(err, p, "unexpected end of input in initializer list", ((void*)0));
        return ((void*)0);
    }
    if (tok->type == TOK_RBRACE) {
        Token *rbrace = consume(p, TOK_RBRACE);
        init->span = span_join(&start_span, &rbrace->span);
        return init;
    }
    while (1) {
        tok = current_token(p);
        if (!tok) {
            create_parse_error(err, p, "unexpected end of input in initializer list", ((void*)0));
            return ((void*)0);
        }
        AstNode *element = ((void*)0);
        if (tok->type == TOK_LBRACE) {
            element = parse_initializer_list(p, err);
            if (!element) return ((void*)0);
        } else {
            element = parse_expression(p, err);
            if (!element) return ((void*)0);
        }
        if (dynarray_push_value(init->data.initializer_list.elements, &element) != 0) {
            create_parse_error(err, p, "out of memory adding element to initializer list", ((void*)0));
            return ((void*)0);
        }
        tok = current_token(p);
        if (!tok) {
            create_parse_error(err, p, "unexpected end of input in initializer list", ((void*)0));
            return ((void*)0);
        }
        if (tok->type == TOK_COMMA) {
            consume(p, TOK_COMMA);
            tok = current_token(p);
            if (tok && tok->type == TOK_RBRACE) {
                Token *rbrace = consume(p, TOK_RBRACE);
                init->span = span_join(&start_span, &rbrace->span);
                return init;
            }
            continue;
        } else if (tok->type == TOK_RBRACE) {
            Token *rbrace = consume(p, TOK_RBRACE);
            init->span = span_join(&start_span, &rbrace->span);
            return init;
        } else {
            err->use_prev_token = 1;
            create_parse_error(err, p, "expected ',' or '}' in initializer list", tok);
            return ((void*)0);
        }
    }
    return init;
}
extern int * __error(void);

AstNode *parse_block(Parser *p, ParseError *err) {
    AstNode *block = ast_create_node(AST_BLOCK, p->arena, p->filename);
    if (!block) {
        if (err) create_parse_error(err, p, "out of memory creating block node", ((void*)0));
        return ((void*)0);
    }
    block->data.block.statements = arena_alloc(p->arena, sizeof(DynArray));
    if (!block->data.block.statements) {
        if (err) create_parse_error(err, p, "out of memory creating block statements array", ((void*)0));
        return ((void*)0);
    }
    dynarray_init_in_arena(block->data.block.statements, p->arena, sizeof(AstNode*), 4);
    Token *lbrace = consume(p, TOK_LBRACE);
    if (!lbrace) { create_parse_error(err, p, "expected '{' at start of block", current_token(p)); return ((void*)0); }
    Span start_span = lbrace->span;
    while (1) {
        Token *current = current_token(p);
        if (!current) {
            err->use_prev_token = 1;
            if (err) create_parse_error(err, p, "unexpected end of input in block, expected '}'", current);
            return ((void*)0);
        }
        if (current->type == TOK_EOF) {
            if (err) create_parse_error(err, p, "unexpected end of input in block, expected '}'", current);
            return ((void*)0);
        }
        if (current->type == TOK_RBRACE) {
            Token *rbrace = consume(p, TOK_RBRACE);
            block->span = span_join(&start_span, &rbrace->span);
            break;
        }
        AstNode *stmt = parse_statement(p, err);
        if (!stmt) return ((void*)0);
        if (dynarray_push_value(block->data.block.statements, &stmt) != 0) {
            if (err) create_parse_error(err, p, "out of memory adding statement to block", ((void*)0));
            return ((void*)0);
        }
    }
    return block;
}
AstNode *parse_defer_statement(Parser *p, ParseError *err) {
    Token *defer_tok = consume(p, TOK_DEFER);
    if (!defer_tok) {
        if (err) create_parse_error(err, p, "expected 'defer' keyword", current_token(p));
        return ((void*)0);
    }
    Span start_span = defer_tok->span;
    AstNode *defer_stmt = new_node_or_err(p, AST_DEFER_STATEMENT, err, "out of memory creating defer statement node");
    if (!defer_stmt) return ((void*)0);
    Token *current = current_token(p);
    if (!current) {
        if (err) create_parse_error(err, p, "expected block or expression after 'defer'", ((void*)0));
        return ((void*)0);
    }
    AstNode *body = ((void*)0);
    if (current->type == TOK_LBRACE) {
        body = parse_block(p, err);
    } else {
        body = parse_statement(p, err);
    }
    if (!body) return ((void*)0);
    defer_stmt->data.defer_statement.body = body;
    defer_stmt->span = span_join(&start_span, &body->span);
    return defer_stmt;
}
AstNode *parse_statement(Parser *p, ParseError *err) {
    Token *tok = current_token(p);
    if (!tok) {
        if (err) create_parse_error(err, p, "unexpected end of input in statement", ((void*)0));
        return ((void*)0);
    }
    AstNode *stmt = ((void*)0);
    switch (tok->type) {
        case TOK_IF:
            stmt = parse_if_statement(p, err);
            break;
        case TOK_WHILE:
            stmt = parse_while_statement(p, err);
            break;
        case TOK_FOR:
            stmt = parse_for_statement(p, err);
            break;
        case TOK_RETURN:
            stmt = parse_return_statement(p, err);
            break;
        case TOK_BREAK:
            stmt = parse_break_statement(p, err);
            break;
        case TOK_CONTINUE:
            stmt = parse_continue_statement(p, err);
            break;
        case TOK_DEFER:
            stmt = parse_defer_statement(p, err);
            break;
        case TOK_LBRACE:
            stmt = parse_block(p, err);
            break;
        case TOK_FN:
            if (err) create_parse_error(err, p, "function declarations are not allowed inside statements or blocks", tok);
            return ((void*)0);
        case TOK_CONST:
            stmt = parse_declaration_stmt(p, err);
            break;
        case TOK_IDENTIFIER: {
            Token *next = peek(p, 1);
            if (!next) {
                if (err) create_parse_error(err, p, "unexpected end of input after identifier", tok);
                return ((void*)0);
            }
            if (next->type == TOK_COLON) {
                stmt = parse_declaration_stmt(p, err);
            } else {
                stmt = parse_expression_statement(p, err);
            }
            break;
        }
        default:
            stmt = parse_expression_statement(p, err);
            break;
    }
    return stmt;
}
AstNode *parse_if_statement(Parser *p, ParseError *err) {
    Token *if_tok = consume(p, TOK_IF);
    if (!if_tok) {
        if (err) create_parse_error(err, p, "expected 'if' keyword", current_token(p));
        return ((void*)0);
    }
    Span start_span = if_tok->span;
    AstNode *if_stmt = ast_create_node(AST_IF_STATEMENT, p->arena, p->filename);
    if (!if_stmt) {
        if (err) create_parse_error(err, p, "out of memory creating if statement node", current_token(p));
        return ((void*)0);
    }
    if_stmt->data.if_statement.condition = parse_expression(p, err);
    if (!if_stmt->data.if_statement.condition) {
        return ((void*)0);
    }
    if_stmt->data.if_statement.then_branch = parse_block(p, err);
    if (!if_stmt->data.if_statement.then_branch) {
        return ((void*)0);
    }
    Span end_span = if_stmt->data.if_statement.then_branch->span;
    Token *else_tok = consume(p, TOK_ELSE);
    if (else_tok) {
        Token *next = current_token(p);
        if (!next) {
            if (err) create_parse_error(err, p, "unexpected end after 'else'", current_token(p));
            return ((void*)0);
        }
        if (next->type == TOK_IF) {
            AstNode *else_if = parse_if_statement(p, err);
            if (!else_if) {
                return ((void*)0);
            }
            if_stmt->data.if_statement.else_branch = else_if;
            end_span = else_if->span;
        } else {
            AstNode *else_block = parse_block(p, err);
            if (!else_block) {
                return ((void*)0);
            }
            if_stmt->data.if_statement.else_branch = else_block;
            end_span = else_block->span;
        }
    }
    if_stmt->span = span_join(&start_span, &end_span);
    return if_stmt;
}
AstNode *parse_while_statement(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *while_tok = consume(p, TOK_WHILE);
    if (!while_tok) { if (err) create_parse_error(err, p, "expected 'while' keyword", current_token(p)); return ((void*)0); }
    AstNode *while_stmt = new_node_or_err(p, AST_WHILE_STATEMENT, err, "out of memory creating while statement node");
    if (!while_stmt) return ((void*)0);
    while_stmt->data.while_statement.condition = parse_expression(p, err);
    if (!while_stmt->data.while_statement.condition) return ((void*)0);
    while_stmt->data.while_statement.body = parse_block(p, err);
    if (!while_stmt->data.while_statement.body) return ((void*)0);
    while_stmt->span = span_join(&while_tok->span, &while_stmt->data.while_statement.body->span);
    return while_stmt;
}
AstNode *parse_for_statement(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *for_tok = consume(p, TOK_FOR);
    if (!for_tok) {
        if (err) create_parse_error(err, p, "expected 'for' keyword", current_token(p));
        return ((void*)0);
    }
    AstNode *for_node = ast_create_node(AST_FOR_STATEMENT, p->arena, p->filename);
    if (!for_node) return ((void*)0);
    if (!consume(p, TOK_LPAREN)) {
        if (err) create_parse_error(err, p, "expected '(' after 'for'", current_token(p));
        return ((void*)0);
    }
    if (current_token(p)->type != TOK_SEMICOLON) {
        AstNode *init = parse_statement(p, err);
        if (!init) return ((void*)0);
        for_node->data.for_statement.init = init;
    } else {
        consume(p, TOK_SEMICOLON);
    }
    if (current_token(p)->type != TOK_SEMICOLON) {
        for_node->data.for_statement.condition = parse_expression(p, err);
        if (!for_node->data.for_statement.condition) return ((void*)0);
    }
    if (!consume(p, TOK_SEMICOLON)) {
         if (err) create_parse_error(err, p, "expected ';' after condition", current_token(p));
         return ((void*)0);
    }
    if (current_token(p)->type != TOK_RPAREN) {
        for_node->data.for_statement.post = parse_expression(p, err);
        if (!for_node->data.for_statement.post) return ((void*)0);
    }
    Token *rparen = consume(p, TOK_RPAREN);
    if (!rparen) {
        if (err) create_parse_error(err, p, "expected ')' after for clauses", current_token(p));
        return ((void*)0);
    }
    for_node->data.for_statement.body = parse_block(p, err);
    if (!for_node->data.for_statement.body) return ((void*)0);
    for_node->span = span_join(&for_tok->span, &for_node->data.for_statement.body->span);
    return for_node;
}
AstNode *parse_return_statement(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *return_tok = consume(p, TOK_RETURN);
    if (!return_tok) { if (err) create_parse_error(err, p, "expected 'return' keyword", current_token(p)); return ((void*)0); }
    AstNode *return_stmt = new_node_or_err(p, AST_RETURN_STATEMENT, err, "out of memory creating return statement node");
    if (!return_stmt) return ((void*)0);
    Token *semi = current_token(p);
    if (semi && semi->type == TOK_SEMICOLON) {
        return_stmt->data.return_statement.expression = ((void*)0);
        return_stmt->span = return_tok->span;
    } else {
        return_stmt->data.return_statement.expression = parse_expression(p, err);
        if (!return_stmt->data.return_statement.expression) return ((void*)0);
        return_stmt->span = span_join(&return_tok->span, &return_stmt->data.return_statement.expression->span);
    }
    semi = consume(p, TOK_SEMICOLON);
    if (!semi) { if (err) create_parse_error(err, p, "expected ';' after return statement", current_token(p)); return ((void*)0); }
    return_stmt->span = span_join(&return_stmt->span, &semi->span);
    return return_stmt;
}
AstNode *parse_break_statement(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *break_tok = consume(p, TOK_BREAK);
    if (!break_tok) { if (err) create_parse_error(err, p, "expected 'break' keyword", current_token(p)); return ((void*)0); }
    AstNode *break_stmt = new_node_or_err(p, AST_BREAK_STATEMENT, err, "out of memory creating break statement node");
    if (!break_stmt) return ((void*)0);
    break_stmt->span = break_tok->span;
    Token *semi = consume(p, TOK_SEMICOLON);
    if (!semi) { if (err) create_parse_error(err, p, "expected ';' after break statement", current_token(p)); return ((void*)0); }
    break_stmt->span = span_join(&break_stmt->span, &semi->span);
    return break_stmt;
}
AstNode *parse_continue_statement(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *cont_tok = consume(p, TOK_CONTINUE);
    if (!cont_tok) { if (err) create_parse_error(err, p, "expected 'continue' keyword", current_token(p)); return ((void*)0); }
    AstNode *cont_stmt = new_node_or_err(p, AST_CONTINUE_STATEMENT, err, "out of memory creating continue statement node");
    if (!cont_stmt) return ((void*)0);
    cont_stmt->span = cont_tok->span;
    Token *semi = consume(p, TOK_SEMICOLON);
    if (!semi) { if (err) create_parse_error(err, p, "expected ';' after continue statement", current_token(p)); return ((void*)0); }
    cont_stmt->span = span_join(&cont_stmt->span, &semi->span);
    return cont_stmt;
}
AstNode *parse_expression_statement(Parser *p, ParseError *err) {
    AstNode *expr = parse_expression(p, err);
    if (!expr) return ((void*)0);
    Token *semi = consume(p, TOK_SEMICOLON);
    if (!semi) {
        err->use_prev_token = 1;
        create_parse_error(err, p, "expected ';' at end of expression statement", current_token(p));
        return ((void*)0);
    }
    AstNode *stmt = ast_create_node(AST_EXPR_STATEMENT, p->arena, p->filename);
    if (!stmt) {
        if (err) create_parse_error(err, p, "out of memory creating expression statement node", ((void*)0));
        return ((void*)0);
    }
    stmt->data.expr_statement.expression = expr;
    stmt->span = span_join(&expr->span, &semi->span);
    return stmt;
}
static AstNode *parse_path(Parser *p, ParseError *err) {
    Token *tok = current_token(p);
    if (!tok || tok->type != TOK_IDENTIFIER) {
        if (err) create_parse_error(err, p, "expected identifier", tok);
        return ((void*)0);
    }
    AstNode *primary = new_node_or_err(p, AST_IDENTIFIER, err, "out of memory");
    if (!primary) return ((void*)0);
    primary->data.identifier.intern_result = tok->record;
    primary->span = tok->span;
    consume(p, TOK_IDENTIFIER);
    while (current_token(p) && current_token(p)->type == TOK_DOT) {
        consume(p, TOK_DOT);
        Token *name_tok = consume(p, TOK_IDENTIFIER);
        if (!name_tok) {
            if (err) create_parse_error(err, p, "expected identifier after '.'", current_token(p));
            return ((void*)0);
        }
        AstNode *member_access = new_node_or_err(p, AST_MEMBER_EXPR, err, "out of memory");
        if (!member_access) return ((void*)0);
        member_access->data.member_expr.target = primary;
        member_access->data.member_expr.member = name_tok->record;
        member_access->span = span_join(&primary->span, &name_tok->span);
        primary = member_access;
    }
    return primary;
}
AstNode *parse_type(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    DynArray *prefix_ptrs = alloc_dynarray(p, err, sizeof(Token), 4, "out of memory for pointer prefixes");
    if (!prefix_ptrs) return ((void*)0);
    Token *token = current_token(p);
    while (token && token->type == TOK_STAR) {
        Token *star = consume(p, TOK_STAR);
        dynarray_push_value(prefix_ptrs, star);
        token = current_token(p);
    }
    AstNode *base = parse_type_atom(p, err);
    if (!base) return ((void*)0);
    for (size_t i = prefix_ptrs->count; i > 0; i--) {
        Token *star = (Token*)dynarray_get(prefix_ptrs, (int)i - 1);
        AstNode *ptr_type = new_node_or_err(p, AST_TYPE, err, "out of memory creating pointer type node");
        if (!ptr_type) return ((void*)0);
        ptr_type->data.ast_type.kind = AST_TYPE_PTR;
        ptr_type->data.ast_type.u.ptr.target = base;
        ptr_type->data.ast_type.span = span_join(&star->span, &base->span);
        base = ptr_type;
    }
    token = current_token(p);
    DynArray *dims = alloc_dynarray(p, err, sizeof(AstNode*), 4, "out of memory for array dimensions");
    if (!dims) return ((void*)0);
    while (token && token->type == TOK_LBRACKET) {
        Token *lbr = consume(p, TOK_LBRACKET);
        if (!lbr) { if (err) create_parse_error(err, p, "expected '['", current_token(p)); return ((void*)0); }
        AstNode *size_expr = ((void*)0);
        Token *peek_tok = current_token(p);
        if (peek_tok && peek_tok->type != TOK_RBRACKET) {
            size_expr = parse_expression(p, err);
            if (!size_expr && err && err->message) return ((void*)0);
        }
        Token *rbr = consume(p, TOK_RBRACKET);
        if (!rbr) { if (err) err->use_prev_token = 1; create_parse_error(err, p, "expected ']'", current_token(p)); return ((void*)0); }
        AstNode *array_type = new_node_or_err(p, AST_TYPE, err, "out of memory");
        if (!array_type) return ((void*)0);
        array_type->data.ast_type.kind = AST_TYPE_ARRAY;
        array_type->data.ast_type.u.array.size_expr = size_expr;
        array_type->data.ast_type.u.array.elem = ((void*)0);
        array_type->span = span_join(&lbr->span, &rbr->span);
        if (dynarray_push_value(dims, &array_type) != 0) {
             if (err) create_parse_error(err, p, "out of memory pushing array dim", ((void*)0));
             return ((void*)0);
        }
        token = current_token(p);
    }
    for (size_t i = dims->count; i > 0; i--) {
        AstNode *dim_node = *(AstNode**)dynarray_get(dims, (int)i - 1);
        dim_node->data.ast_type.u.array.elem = base;
        dim_node->span = span_join(&base->span, &dim_node->span);
        base = dim_node;
    }
    token = current_token(p);
    while (token && token->type == TOK_STAR) {
        Token *star = consume(p, TOK_STAR);
        if (!star) { if (err) create_parse_error(err, p, "expected '*'", current_token(p)); return ((void*)0); }
        AstNode *ptr_type = new_node_or_err(p, AST_TYPE, err, "out of memory creating pointer type node");
        if (!ptr_type) return ((void*)0);
        ptr_type->data.ast_type.kind = AST_TYPE_PTR;
        ptr_type->data.ast_type.u.ptr.target = base;
        ptr_type->data.ast_type.span = span_join(&base->span, &star->span);
        base = ptr_type;
        token = current_token(p);
    }
    return base;
}
AstNode *parse_type_atom(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *tok = current_token(p);
    if (!tok) { if (err) create_parse_error(err, p, "unexpected end of input in type", ((void*)0)); return ((void*)0); }
    if (tok->type == TOK_LPAREN) {
        Token *lpar = consume(p, TOK_LPAREN);
        AstNode *inner = parse_type(p, err);
        if (!inner) return ((void*)0);
        Token *rparen = consume(p, TOK_RPAREN);
        if (!rparen) { if (err) create_parse_error(err, p, "expected ')' after type", current_token(p)); return ((void*)0); }
        inner->span = span_join(&lpar->span, &rparen->span);
        return inner;
    }
    if (tok->type == TOK_FN) {
        AstNode *func_type = parse_function_type(p, err);
        if (!func_type) return ((void*)0);
        return func_type;
    }
    if ((tok->type >= TOK_I32 && tok->type <= TOK_VOID) || tok->type == TOK_IDENTIFIER) {
        AstNode *type_node = new_node_or_err(p, AST_TYPE, err, "out of memory creating type node");
        if (!type_node) return ((void*)0);
        type_node->data.ast_type.kind = AST_TYPE_PRIMITIVE;
        if (tok->type >= TOK_I32 && tok->type <= TOK_VOID) {
            type_node->data.ast_type.u.base.intern_result = tok->record;
            type_node->data.ast_type.u.base.path = ((void*)0);
            type_node->data.ast_type.span = tok->span;
            consume(p, tok->type);
        } else {
            AstNode *primary = parse_path(p, err);
            if (!primary) return ((void*)0);
            type_node->data.ast_type.span = primary->span;
            if (primary->node_type == AST_IDENTIFIER) {
                type_node->data.ast_type.u.base.intern_result = primary->data.identifier.intern_result;
                type_node->data.ast_type.u.base.path = ((void*)0);
            } else if (primary->node_type == AST_MEMBER_EXPR) {
                type_node->data.ast_type.u.base.intern_result = ((void*)0);
                type_node->data.ast_type.u.base.path = primary;
            } else {
                 type_node->data.ast_type.u.base.intern_result = ((void*)0);
                 type_node->data.ast_type.u.base.path = primary;
            }
        }
        return type_node;
    }
    if (err) create_parse_error(err, p, "expected type name, path, or (type)", tok);
    return ((void*)0);
}
InternResult *get_base_type(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *tok = current_token(p);
    if (!tok) { if (err) create_parse_error(err, p, "unexpected end of input while looking for base type", ((void*)0)); return ((void*)0); }
    if (((tok->type >= TOK_I32 && tok->type <= TOK_VOID) && tok->type != TOK_STRUCT) || tok->type == TOK_IDENTIFIER) {
        consume(p, tok->type);
        return tok->record;
    }
    if (err) create_parse_error(err, p, "expected base type", tok);
    return ((void*)0);
}
AstNode *parse_function_type(Parser *p, ParseError *err) {
    if (!p) return ((void*)0);
    Token *fn_tok = consume(p, TOK_FN);
    if (!fn_tok) { if (err) create_parse_error(err, p, "expected 'fn' keyword", current_token(p)); return ((void*)0); }
    AstNode *type_node = new_node_or_err(p, AST_TYPE, err, "out of memory creating function type node");
    if (!type_node) return ((void*)0);
    type_node->data.ast_type.kind = AST_TYPE_FUNC;
    type_node->data.ast_type.span = fn_tok->span;
    Token *lparen = consume(p, TOK_LPAREN);
    if (!lparen) { if (err) create_parse_error(err, p, "expected '(' after 'fn type'", current_token(p)); return ((void*)0); }
    Token *maybe = current_token(p);
    if (maybe && maybe->type == TOK_RPAREN) {
        Token *r = consume(p, TOK_RPAREN);
        type_node->data.ast_type.u.func.param_types = ((void*)0);
        type_node->data.ast_type.span = span_join(&type_node->data.ast_type.span, &r->span);
    } else {
        DynArray *params = alloc_dynarray(p, err, sizeof(AstNode*), 4, "out of memory creating param types array");
        if (!params) return ((void*)0);
        AstNode *param = parse_type(p, err);
        if (!param) return ((void*)0);
        if (dynarray_push_value(params, &param) != 0) { if (err) create_parse_error(err, p, "out of memory adding param type", ((void*)0)); return ((void*)0); }
        Token *sep = current_token(p);
        while (sep && sep->type == TOK_COMMA) {
            consume(p, TOK_COMMA);
            param = parse_type(p, err);
            if (!param) return ((void*)0);
            if (dynarray_push_value(params, &param) != 0) { if (err) create_parse_error(err, p, "out of memory adding param type", ((void*)0)); return ((void*)0); }
            sep = current_token(p);
        }
        Token *rparen = consume(p, TOK_RPAREN);
        if (!rparen) { if (err) create_parse_error(err, p, "expected ')' after function parameter types", current_token(p)); return ((void*)0); }
        type_node->data.ast_type.u.func.param_types = params;
        type_node->data.ast_type.span = span_join(&type_node->data.ast_type.span, &rparen->span);
    }
    Token *arrow = current_token(p);
    if (arrow && arrow->type == TOK_ARROW) {
        consume(p, TOK_ARROW);
        AstNode *ret = parse_type(p, err);
        if (!ret) return ((void*)0);
        type_node->data.ast_type.u.func.return_type = ret;
        type_node->data.ast_type.span = span_join(&type_node->data.ast_type.span, &ret->span);
    } else {
        type_node->data.ast_type.u.func.return_type = ((void*)0);
    }
    return type_node;
}

Parser *parser_create(DynArray *tokens, char *filename, Arena *arena) {
    if (!arena) return ((void*)0);
    Parser *p = arena_alloc(arena, sizeof(Parser));
    if (!p) return ((void*)0);
    p->tokens = tokens;
    p->current = 0;
    p->end = tokens->count;
    p->arena = arena;
    p->filename = filename;
    return p;
}
void parser_free(Parser *parser) {
    (void)parser;
}
Token *current_token(Parser *p) {
    if (!p) return ((void*)0);
    if (p->current >= p->end) return ((void*)0);
    return (Token*)dynarray_get(p->tokens, p->current);
}
Token *peek(Parser *p, size_t offset) {
    if (!p) return ((void*)0);
    size_t index = p->current + offset;
    if (index >= p->end) return ((void*)0);
    return (Token*)dynarray_get(p->tokens, index);
}
Token *parser_advance(Parser *p) {
    if (!p) return ((void*)0);
    if (p->current >= p->end) return ((void*)0);
    Token *tok = (Token*)dynarray_get(p->tokens, p->current);
    p->current++;
    return tok;
}
Token *consume(Parser *p, TokenType expected) {
    if (!p) return ((void*)0);
    Token *tok = current_token(p);
    if (!tok || tok->type != expected) return ((void*)0);
    p->current++;
    return tok;
}
int parser_match(Parser *p, TokenType expected) {
    if (!p) return 0;
    Token *tok = current_token(p);
    if (!tok || tok->type != expected) return 0;
    p->current++;
    return 1;
}
void create_parse_error(ParseError *err_out, Parser *p, const char *message, Token *token) {
    if (!err_out || !p || !message) return;
    err_out->p = p;
    err_out->message = (char*)arena_alloc(p->arena, strlen(message) + 1);
    if (err_out->message) {
        __builtin___strcpy_chk (err_out->message, message, __builtin_object_size (err_out->message, 2 > 1 ? 1 : 0));
    }
    err_out->token = token;
}
AstNode *new_node_or_err(Parser *p, AstNodeType kind, ParseError *err, const char *oom_msg) {
    AstNode *n = ast_create_node(kind, p->arena, p->filename);
    if (!n) {
        if (err) create_parse_error(err, p, oom_msg, ((void*)0));
    }
    return n;
}
DynArray *alloc_dynarray(Parser *p, ParseError *err, size_t elem_size, int initial_capacity, const char *oom_msg) {
    DynArray *arr = arena_alloc(p->arena, sizeof(DynArray));
    if (!arr) {
        if (err) create_parse_error(err, p, oom_msg, ((void*)0));
        return ((void*)0);
    }
    dynarray_init_in_arena(arr, p->arena, elem_size, initial_capacity);
    return arr;
}
void print_parse_error(ParseError *error) {
    if (!error || !error->p || !error->message) return;
    const char *filename = error->p->filename ? error->p->filename : "<unknown>";
    Token *orig_tok = error->token;
    fprintf(__stderrp, "\033[31m" "error:" "\033[0m" " %s\n", error->message);
    if (!orig_tok) {
        fprintf(__stderrp, "   %s\n", filename);
        return;
    }
    Token display_tok = *orig_tok;
    if (error->use_prev_token) {
        Token *prev = peek(error->p, -1);
        if (prev) {
            display_tok = *prev;
            display_tok.span.start_col += (size_t)display_tok.slice.len;
        }
    }
    fprintf(__stderrp, "   %s:%zu:%zu\n",
            filename,
            display_tok.span.start_line,
            display_tok.span.start_col);
    if (error->use_prev_token) {
        print_source_excerpt(filename, display_tok.span.start_line, display_tok.span.start_col);
    } else {
        if (display_tok.span.start_line == display_tok.span.end_line &&
            display_tok.span.end_col > display_tok.span.start_col) {
            print_source_excerpt_span(filename,
                                    display_tok.span.start_line,
                                    display_tok.span.start_col,
                                    display_tok.span.end_col);
        } else {
            print_source_excerpt(filename, display_tok.span.start_line, display_tok.span.start_col);
        }
    }
}
typedef enum {
    TE_NONE = 0,
    TE_UNKNOWN_TYPE,
    TE_REDECLARATION,
    TE_UNDECLARED,
    TE_INCOMPLETE_TYPE,
    TE_EXPECTED_TYPE_ARG,
    TE_TYPE_MISMATCH,
    TE_RETURN_MISMATCH,
    TE_VARIABLE_TYPE_RESOLUTION_FAILED,
    TE_DIMENSION_MISMATCH,
    TE_ARRAY_SIZE_MISMATCH,
    TE_EXPECTED_ARRAY,
    TE_UNEXPECTED_LIST,
    TE_BINOP_MISMATCH,
    TE_UNOP_MISMATCH,
    TE_NOT_CALLABLE,
    TE_NOT_INDEXABLE,
    TE_FIELD_ACCESS,
    TE_NOT_MEMBER_ACCESSIBLE,
    TE_INDEX_OUT_OF_BOUNDS,
    TE_CONST_ASSIGN,
    TE_ARG_COUNT_MISMATCH,
    TE_NOT_CONST,
    TE_NOT_LVALUE,
    TE_RECURSIVE_CONST
} TypeErrorKind;
typedef struct {
    TypeErrorKind kind;
    Span span;
    const char *filename;
    union {
        struct { const char *name; } name;
        struct {
            Type *expected;
            Type *actual;
        } mismatch;
        struct {
            int expected_ndim;
            int actual_ndim;
        } dims;
        struct {
            size_t expected_size;
            size_t actual_size;
        } size;
        struct {
            OpKind op;
            Type *left;
            Type *right;
        } binop;
        struct {
            OpKind op;
            Type *operand;
        } unop;
        struct { Type *actual; } bad_usage;
        struct { size_t expected; size_t actual; } arg_count;
        struct {
            const char *name;
            Type *type;
        } field;
    } as;
} TypeError;
void print_type_error(TypeError *err);
typedef struct {
    AstNode *program;
    TypeStore *store;
    DenseArenaInterner *identifiers;
    DenseArenaInterner *keywords;
    const char *filename;
    DynArray *errors;
    ModuleLoader *loader;
    int current_pass;
} TypeCheckContext;
TypeCheckContext typecheck_context_create(Arena *arena, TypeStore *store, DenseArenaInterner *identifiers, DenseArenaInterner *keywords, const char *filename, ModuleLoader *loader);
void typecheck_program(TypeCheckContext *ctx);
Type *resolve_ast_type(TypeCheckContext *ctx, Scope *scope, AstNode *node);
void check_variable_declaration(TypeCheckContext *ctx, Scope *scope, AstNode *var_node);
void define_symbol_or_error(TypeCheckContext *ctx, Scope *scope, InternResult *name, Type *type, SymbolValue kind, Span span, _Bool is_pub, const char *filename, AstNode *decl_node);
int is_lvalue_node(AstNode *node);

void define_symbol_or_error(TypeCheckContext *ctx, Scope *scope, InternResult *name, Type *type, SymbolValue kind, Span span, _Bool is_pub, const char *filename, AstNode *decl_node) {
    if (!scope || !name) return;
    Symbol *existing = scope_lookup_symbol_local(scope, name);
    if (existing && existing->decl_node == decl_node && decl_node != ((void*)0)) {
        return;
    }
    Symbol *sym = scope_define_symbol(scope, name, type, kind, filename, is_pub, decl_node);
    if (!sym) {
        const char *name_str = ((Slice*)name->key)->ptr;
        TypeError err = {
            .kind = TE_REDECLARATION,
            .span = span,
            .filename = ctx->filename,
            .as.name.name = name_str
        };
        dynarray_push_value(ctx->errors, &err);
    }
}
_Bool type_can_implicit_cast(Type *target, Type *source);
_Bool type_can_explicit_cast(Type *target, Type *source);
void insert_cast(TypeCheckContext *ctx, AstNode *node, Type *to_type);
Type* coerce_or_error(TypeCheckContext *ctx, AstNode *node, Type *expected);
void fold_cast_node(AstNode *cast_node);
_Bool type_is_integer(Type *t);
_Bool type_is_float(Type *t);
_Bool type_is_bool(Type *t);
_Bool type_is_char(Type *t);
_Bool type_is_void(Type *t);
_Bool type_is_pointer_to_void(Type *t);
_Bool type_is_pointer_like(Type *t);
_Bool type_is_numeric(Type *t);
_Bool type_can_implicit_cast(Type *target, Type *source) {
    if (!target || !source) return 0;
    if (target == source) return 1;
    if (source->kind == TYPE_PRIMITIVE && target->kind == TYPE_PRIMITIVE) {
        PrimitiveKind s = source->as.primitive;
        PrimitiveKind t = target->as.primitive;
        if (s == PRIM_I32 && t == PRIM_I64) return 1;
        if (s == PRIM_F32 && t == PRIM_F64) return 1;
        if (s == PRIM_I32 && t == PRIM_F64) return 1;
    }
    if (target->kind == TYPE_SLICE && source->kind == TYPE_ARRAY) {
        return target->as.slice.base == source->as.array.base;
    }
    if (target->kind == TYPE_POINTER && source->kind == TYPE_POINTER) {
        if (type_is_void(target->as.ptr.base)) return 1;
        Type *sb = source->as.ptr.base;
        Type *tb = target->as.ptr.base;
        if (sb->kind == TYPE_ARRAY && tb->kind == TYPE_SLICE) {
             return tb->as.slice.base == sb->as.array.base;
        }
    }
    if (target->kind == TYPE_POINTER && source->kind == TYPE_ARRAY) {
        return target->as.ptr.base == source->as.array.base;
    }
    return 0;
}
_Bool type_can_explicit_cast(Type *target, Type *source) {
    if (!target || !source) return 0;
    if (type_can_implicit_cast(target, source)) return 1;
    if ((type_is_numeric(source) || type_is_char(source)) &&
        (type_is_numeric(target) || type_is_char(target))) {
        return 1;
    }
    if (type_is_bool(source) && (type_is_numeric(target) || type_is_char(target))) {
        return 1;
    }
    if (source->kind == TYPE_POINTER && target->kind == TYPE_POINTER) {
        return 1;
    }
    if ((source->kind == TYPE_POINTER && type_is_integer(target)) ||
        (type_is_integer(source) && target->kind == TYPE_POINTER)) {
        Type *int_type = (source->kind == TYPE_POINTER) ? target : source;
        if (int_type->kind == TYPE_PRIMITIVE && int_type->as.primitive == PRIM_I64) {
            return 1;
        }
    }
    if (source->kind == TYPE_ARRAY && target->kind == TYPE_SLICE) {
        if (source->as.array.base == target->as.slice.base) {
            return 1;
        }
    }
    return 0;
}
void fold_cast_node(AstNode *node) {
    if (node->node_type != AST_CAST) return;
    AstCastExpr *cast = &node->data.cast_expr;
    AstNode *expr = cast->expr;
    Type *to_type = cast->target_type;
    if (!expr->is_foldable_const) return;
    node->is_foldable_const = 1;
    node->is_llvm_const_safe = 1;
    node->const_value = expr->const_value;
    if (type_is_bool(expr->type)) {
        if (type_is_integer(to_type) || type_is_char(to_type)) {
             node->const_value.type = type_is_char(to_type) ? CHAR_LITERAL : INT_LITERAL;
             node->const_value.value.int_val = expr->const_value.value.bool_val ? 1 : 0;
        }
    }
    else if (type_is_float(to_type)) {
        node->const_value.type = FLOAT_LITERAL;
        if (type_is_integer(expr->type)) {
            node->const_value.value.float_val = (double)expr->const_value.value.int_val;
        } else if (type_is_char(expr->type)) {
            node->const_value.value.float_val = (double)expr->const_value.value.char_val;
        }
    }
    else if (type_is_integer(to_type) || type_is_char(to_type)) {
        node->const_value.type = type_is_char(to_type) ? CHAR_LITERAL : INT_LITERAL;
        if (type_is_float(expr->type)) {
            node->const_value.value.int_val = (int64_t)expr->const_value.value.float_val;
        }
    }
}
void insert_cast(TypeCheckContext *ctx, AstNode *node, Type *to_type) {
    if (!node || !to_type) return;
    if (node->type == to_type) return;
    AstNode *original = arena_alloc(ctx->store->arena, sizeof(AstNode));
    __builtin___memcpy_chk (original, node, sizeof(AstNode), __builtin_object_size (original, 0));
    node->node_type = AST_CAST;
    node->type = to_type;
    node->span = original->span;
    node->data.cast_expr.expr = original;
    node->data.cast_expr.target_type = to_type;
    node->data.cast_expr.target_type_node = ((void*)0);
    fold_cast_node(node);
}
Type* coerce_or_error(TypeCheckContext *ctx, AstNode *node, Type *expected) {
    if (!node || !expected) return node ? node->type : ((void*)0);
    Type *actual = node->type;
    if (actual == expected) return actual;
    if (type_can_implicit_cast(expected, actual)) {
        insert_cast(ctx, node, expected);
        return expected;
    }
    TypeError err = {
        .kind = TE_TYPE_MISMATCH,
        .span = node->span,
        .filename = ctx->filename,
        .as.mismatch = { .expected = expected, .actual = actual }
    };
    dynarray_push_value(ctx->errors, &err);
    return ((void*)0);
}
static void type_print_internal(FILE *out, const Type *type) {
    if (!type) {
        fprintf(out, "null");
        return;
    }
    switch (type->kind) {
        case TYPE_VOID:
            fprintf(out, "void");
            break;
        case TYPE_PRIMITIVE: {
            switch (type->as.primitive) {
                case PRIM_I32: fprintf(out, "i32"); break;
                case PRIM_I64: fprintf(out, "i64"); break;
                case PRIM_F32: fprintf(out, "f32"); break;
                case PRIM_F64: fprintf(out, "f64"); break;
                case PRIM_BOOL: fprintf(out, "bool"); break;
                case PRIM_CHAR: fprintf(out, "char"); break;
            }
            break;
        }
        case TYPE_POINTER: {
            fprintf(out, "*");
            type_print_internal(out, type->as.ptr.base);
            break;
        }
        case TYPE_ARRAY: {
            fprintf(out, "[%lld]", (long long)type->as.array.size);
            type_print_internal(out, type->as.array.base);
            break;
        }
        case TYPE_SLICE: {
            fprintf(out, "[]");
            type_print_internal(out, type->as.slice.base);
            break;
        }
        case TYPE_STRUCT: {
            if (type->as.struct_type.name && type->as.struct_type.name->key) {
                Slice *s = (Slice*)type->as.struct_type.name->key;
                fprintf(out, "%.*s", (int)s->len, s->ptr);
            } else {
                fprintf(out, "struct");
            }
            break;
        }
        case TYPE_FUNCTION: {
            fprintf(out, "fn(");
            for (size_t i = 0; i < type->as.func.param_count; i++) {
                if (i > 0) fprintf(out, ", ");
                type_print_internal(out, type->as.func.params[i]);
            }
            fprintf(out, ") -> ");
            type_print_internal(out, type->as.func.return_type);
            break;
        }
        case TYPE_ENUM: {
             fprintf(out, "enum");
             break;
        }
    }
}
void type_print(FILE *out, const Type *type) {
    type_print_internal(out, type);
}
static const char* get_kind_name(const Type *type) {
    if (!type) return "NULL";
    switch (type->kind) {
        case TYPE_VOID: return "Void";
        case TYPE_PRIMITIVE: return "Primitive";
        case TYPE_POINTER: return "Pointer";
        case TYPE_ARRAY: return "Array";
        case TYPE_SLICE: return "Slice";
        case TYPE_STRUCT: return "Struct";
        case TYPE_FUNCTION: return "Function";
        case TYPE_ENUM: return "Enum";
        default: return "Unknown";
    }
}
static const char* get_kind_color(const Type *type) {
    if (!type) return "\033[0m";
    switch (type->kind) {
        case TYPE_VOID: return "\033[2m";
        case TYPE_PRIMITIVE: return "\033[36m";
        case TYPE_POINTER: return "\033[33m";
        case TYPE_ARRAY: return "\033[32m";
        case TYPE_SLICE: return "\033[34m";
        case TYPE_STRUCT: return "\033[35m";
        case TYPE_FUNCTION: return "\033[31m";
        case TYPE_ENUM: return "\033[2m";
        default: return "\033[2m";
    }
}
static const char* symbol_kind_to_str(SymbolValue kind) {
    switch (kind) {
        case SYMBOL_VARIABLE: return "Variable";
        case SYMBOL_VALUE_FUNCTION: return "Function";
        case SYMBOL_VALUE_TYPE: return "Type/Struct";
        case SYMBOL_VALUE_ALIAS: return "Alias";
        case SYMBOL_VALUE_MODULE: return "Module";
        case SYMBOL_VALUE_NAMESPACE:return "Namespace";
        case SYMBOL_VALUE_INTRINSIC:return "Intrinsic";
        default: return "Unknown";
    }
}
static void print_header(void) {
    printf("\n" "\033[1m" "═══════════════════════════════════════════════════════════════════" "\033[0m" "\n");
    printf("\033[1m" "                    COMPILER STATE ANALYSIS" "\033[0m" "\n");
    printf("\033[1m" "═══════════════════════════════════════════════════════════════════" "\033[0m" "\n");
}
static int digits_for_count(int count) {
    int digits = 1;
    int value = count > 0 ? count - 1 : 0;
    while (value >= 10) {
        value /= 10;
        digits++;
    }
    return digits;
}
static void print_interned_type_header(int index_width) {
    int index_col_width = index_width + 2;
    if (index_col_width < 5) index_col_width = 5;
    printf("  " "\033[1m" "%-*s  %-9s  %s" "\033[0m" "\n",
        index_col_width, "Index", "Kind", "Type");
}
static void print_interned_type_line(int index, int index_width, const Type *type) {
    int index_col_width = index_width + 2;
    if (index_col_width < 5) index_col_width = 5;
    printf("  " "\033[2m" "[%*d]" "\033[0m" "%*s", index_width, index,
        (int)(index_col_width - (index_width + 2) + 2), "");
    printf("%s%-9s" "\033[0m" "  ", get_kind_color(type), get_kind_name(type));
    type_print_internal(__stdoutp, type);
    printf("\n");
}
static const char *safe_symbol_name(InternResult *name_rec) {
    if (!name_rec || !name_rec->key) return "(unknown)";
    return (const char *)((Slice *)name_rec->key)->ptr;
}
void type_print_store_dump(TypeStore *store, Scope *global_scope) {
    if (!store || !store->type_interner) return;
    print_header();
    printf("Total unique types interned: " "\033[33m" "%d" "\033[0m" "\n", store->type_interner->dense_index_count);
    printf("\n" "\033[1m" "Interned Types:" "\033[0m" "\n");
    printf("--------------\n");
    int count = store->type_interner->dense_index_count;
    if (count <= 0) {
        printf(" " "\033[2m" "(none)" "\033[0m" "\n");
    } else {
        int index_width = digits_for_count(count);
        print_interned_type_header(index_width);
        for (int i = 0; i < count; i++) {
            InternResult **result_ptr = (InternResult **)dynarray_get(store->type_interner->dense_array, i);
            if (!result_ptr || !*result_ptr) continue;
            InternResult *result = *result_ptr;
            Slice *key_slice = (Slice *)result->key;
            if (!key_slice || !key_slice->ptr) continue;
            Type *type = (Type *)key_slice->ptr;
            print_interned_type_line(i, index_width, type);
        }
    }
    if (!global_scope) return;
    printf("\n" "\033[1m" "Global Symbol Table:" "\033[0m" "\n");
    printf("--------------------\n");
    if (global_scope->symbols_list.count == 0) {
         printf(" " "\033[2m" "(no symbols in global scope)" "\033[0m" "\n");
    }
    for (size_t i = 0; i < global_scope->symbols_list.count; i++) {
        Symbol *sym = *(Symbol**)dynarray_get(&global_scope->symbols_list, i);
        if (!sym) continue;
        const char *name = safe_symbol_name(sym->name_rec);
        printf("  " "\033[1m" "%s" "\033[0m" " " "\033[2m" "[%s]" "\033[0m", name, symbol_kind_to_str(sym->kind));
        if (sym->is_pub) printf("\033[32m" " pub" "\033[0m");
        if (sym->flags & SYMBOL_FLAG_CONST) printf("\033[33m" " const" "\033[0m");
        printf("\n");
        printf("    symbol ptr: " "\033[2m" "%p" "\033[0m" "\n", (void *)sym->name_rec);
        if (sym->type) {
            printf("    type:   ");
            type_print_internal(__stdoutp, sym->type);
            printf("\n");
            if (sym->type->kind == TYPE_STRUCT && sym->kind == SYMBOL_VALUE_TYPE) {
                printf("    fields:\n");
                for (size_t f = 0; f < sym->type->as.struct_type.field_count; f++) {
                    StructField *field = &sym->type->as.struct_type.fields[f];
                    printf("      - %s: ", safe_symbol_name(field->name));
                    type_print_internal(__stdoutp, field->type);
                    printf(" %s(%s)" "\033[0m" "\n", get_kind_color(field->type), get_kind_name(field->type));
                }
            }
            if (sym->type->kind == TYPE_FUNCTION) {
                size_t param_count = sym->type->as.func.param_count;
                printf("    params (%zu):\n", param_count);
                for (size_t p = 0; p < param_count; p++) {
                    Type *param_type = sym->type->as.func.params[p];
                    printf("      param[%zu]: ", p);
                    type_print_internal(__stdoutp, param_type);
                    printf(" %s(%s)" "\033[0m" "\n", get_kind_color(param_type), get_kind_name(param_type));
                }
                Type *return_type = sym->type->as.func.return_type;
                if (return_type) {
                    printf("    return: ");
                    type_print_internal(__stdoutp, return_type);
                    printf(" %s(%s)" "\033[0m" "\n", get_kind_color(return_type), get_kind_name(return_type));
                }
            }
        } else if (sym->kind != SYMBOL_VALUE_MODULE && sym->kind != SYMBOL_VALUE_ALIAS) {
            printf("    type:   " "\033[35m" "none" "\033[0m" "\n");
        }
        if (sym->kind == SYMBOL_VALUE_ALIAS && sym->target_symbol) {
             printf("    target: " "\033[36m" "%s" "\033[0m" "\n", safe_symbol_name(sym->target_symbol->name_rec));
        }
        if (sym->flags & SYMBOL_FLAG_COMPUTED_VALUE) {
            if (type_is_integer(sym->type)) {
                printf("    value:  " "\033[33m" "%lld" "\033[0m" "\n", (long long)sym->value.int_val);
            } else if (type_is_float(sym->type)) {
                printf("    value:  " "\033[33m" "%f" "\033[0m" "\n", sym->value.float_val);
            }
        }
        if (sym->kind == SYMBOL_VALUE_MODULE && sym->filename) {
            printf("    path:   " "\033[2m" "%s" "\033[0m" "\n", sym->filename);
        }
        printf("\n");
    }
}
static const char* op_kind_to_str(OpKind op) {
    switch (op) {
        case OP_ADD: return "+";
        case OP_SUB: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "/";
        case OP_MOD: return "%";
        case OP_EQ: return "==";
        case OP_NEQ: return "!=";
        case OP_LT: return "<";
        case OP_GT: return ">";
        case OP_LE: return "<=";
        case OP_GE: return ">=";
        case OP_AND: return "&&";
        case OP_OR: return "||";
        case OP_NOT: return "!";
        case OP_ASSIGN: return "=";
        case OP_PLUS_EQ: return "+=";
        case OP_MINUS_EQ: return "-=";
        case OP_MUL_EQ: return "*=";
        case OP_DIV_EQ: return "/=";
        case OP_MOD_EQ: return "%=";
        default: return "?";
    }
}
static void print_type_quoted(FILE *f, const Type *type) {
    fprintf(f, "'%s", "\033[1;33m");
    type_print(f, type);
    fprintf(f, "%s'", "\033[0m");
}
void print_type_error(TypeError *err) {
    if (!err) return;
    fprintf(__stderrp, "%s%s:%zu:%zu: %serror:%s ",
        "\033[1m",
        err->filename ? err->filename : "<input>",
        err->span.start_line, err->span.start_col,
        "\033[1;31m", "\033[0m");
    switch (err->kind) {
        case TE_UNKNOWN_TYPE:
            fprintf(__stderrp, "Unknown type '%s%s%s'.\n", "\033[1;33m", err->as.name.name, "\033[0m");
            break;
        case TE_INCOMPLETE_TYPE:
             fprintf(__stderrp, "Incomplete type: '%s%s%s'.\n", "\033[1;33m", err->as.name.name, "\033[0m");
             break;
        case TE_EXPECTED_TYPE_ARG:
            fprintf(__stderrp, "Expected a type as argument, but found expression of type ");
            print_type_quoted(__stderrp, err->as.mismatch.actual);
            fprintf(__stderrp, ".\n");
            break;
        case TE_REDECLARATION:
            fprintf(__stderrp, "Redefinition of symbol '%s%s%s'.\n", "\033[1;33m", err->as.name.name, "\033[0m");
            break;
        case TE_UNDECLARED:
            fprintf(__stderrp, "Use of undeclared identifier '%s%s%s'.\n", "\033[1;33m", err->as.name.name, "\033[0m");
            break;
        case TE_TYPE_MISMATCH:
            fprintf(__stderrp, "Type mismatch: expected ");
            print_type_quoted(__stderrp, err->as.mismatch.expected);
            fprintf(__stderrp, " but found ");
            if (err->as.mismatch.actual) print_type_quoted(__stderrp, err->as.mismatch.actual);
            else fprintf(__stderrp, "unknown/invalid");
            fprintf(__stderrp, ".\n");
            break;
        case TE_DIMENSION_MISMATCH:
            fprintf(__stderrp, "Dimension mismatch: expected %d dimensions, but got %d.\n",
                err->as.dims.expected_ndim, err->as.dims.actual_ndim);
            break;
        case TE_ARRAY_SIZE_MISMATCH:
            fprintf(__stderrp, "Array size mismatch: dimension has size %zu, but initializer has size %zu.\n",
                err->as.size.expected_size, err->as.size.actual_size);
            break;
        case TE_INDEX_OUT_OF_BOUNDS:
            fprintf(__stderrp, "Array index out of bounds: index %zu is >= array size %zu.\n",
                 err->as.size.actual_size, err->as.size.expected_size);
            break;
        case TE_EXPECTED_ARRAY:
            fprintf(__stderrp, "Type mismatch: expected array type ");
            print_type_quoted(__stderrp, err->as.mismatch.expected);
            fprintf(__stderrp, ", but found scalar expression of type ");
            if (err->as.mismatch.actual) print_type_quoted(__stderrp, err->as.mismatch.actual);
            else fprintf(__stderrp, "unknown");
            fprintf(__stderrp, ".\n");
            break;
        case TE_UNEXPECTED_LIST:
            fprintf(__stderrp, "Type mismatch: expected scalar type ");
            print_type_quoted(__stderrp, err->as.mismatch.expected);
            fprintf(__stderrp, ", but found an initializer list.\n");
            break;
        case TE_RETURN_MISMATCH:
            fprintf(__stderrp, "Function return type mismatch: expected ");
            print_type_quoted(__stderrp, err->as.mismatch.expected);
            fprintf(__stderrp, " but found ");
            print_type_quoted(__stderrp, err->as.mismatch.actual);
            fprintf(__stderrp, ".\n");
            break;
        case TE_VARIABLE_TYPE_RESOLUTION_FAILED:
            fprintf(__stderrp, "Failed to resolve type for variable '%s%s%s'.\n", "\033[1;33m", err->as.name.name, "\033[0m");
            break;
        case TE_BINOP_MISMATCH:
            fprintf(__stderrp, "Invalid operands for binary operator '%s%s%s'. Left: ", "\033[1;35m", op_kind_to_str(err->as.binop.op), "\033[0m");
            print_type_quoted(__stderrp, err->as.binop.left);
            fprintf(__stderrp, " Right: ");
            print_type_quoted(__stderrp, err->as.binop.right);
            fprintf(__stderrp, ".\n");
            break;
        case TE_UNOP_MISMATCH:
            fprintf(__stderrp, "Invalid operand for unary operator '%s%s%s'. Operand: ", "\033[1;35m", op_kind_to_str(err->as.unop.op), "\033[0m");
            print_type_quoted(__stderrp, err->as.unop.operand);
            fprintf(__stderrp, ".\n");
            break;
        case TE_NOT_CALLABLE:
            fprintf(__stderrp, "Expression of type ");
            print_type_quoted(__stderrp, err->as.bad_usage.actual);
            fprintf(__stderrp, " is not callable.\n");
            break;
        case TE_NOT_INDEXABLE:
            fprintf(__stderrp, "Expression of type ");
            print_type_quoted(__stderrp, err->as.bad_usage.actual);
            fprintf(__stderrp, " is not indexable.\n");
            break;
        case TE_FIELD_ACCESS:
            fprintf(__stderrp, "Type ");
            if (err->as.field.type) print_type_quoted(__stderrp, err->as.field.type);
            else fprintf(__stderrp, "of expression");
            fprintf(__stderrp, " has no field named '%s%s%s'.\n", "\033[1;33m", err->as.field.name ? err->as.field.name : "unknown", "\033[0m");
            break;
        case TE_NOT_MEMBER_ACCESSIBLE:
            fprintf(__stderrp, "Expression of type ");
            print_type_quoted(__stderrp, err->as.bad_usage.actual);
            fprintf(__stderrp, " does not support member access.\n");
            break;
        case TE_CONST_ASSIGN:
             fprintf(__stderrp, "Cannot assign to immutable variable/parameter.\n");
             break;
        case TE_ARG_COUNT_MISMATCH:
             fprintf(__stderrp, "Argument count mismatch. Expected %zu, found %zu.\n", err->as.arg_count.expected, err->as.arg_count.actual);
             break;
        case TE_NOT_CONST:
            fprintf(__stderrp, "Expression must be a constant expression.\n");
            break;
        case TE_NOT_LVALUE:
            fprintf(__stderrp, "Expression is not an lvalue.\n");
            break;
        case TE_RECURSIVE_CONST:
            fprintf(__stderrp, "Recursive constant definition detected (cycle).\n");
            break;
        default:
            fprintf(__stderrp, "Unknown Semantic Error.\n");
            break;
    }
    if (err->filename && err->span.start_line > 0) {
        if (err->span.start_line == err->span.end_line && err->span.end_col > err->span.start_col) {
            print_source_excerpt_span(err->filename, err->span.start_line, err->span.start_col, err->span.end_col);
        } else {
            print_source_excerpt(err->filename, err->span.start_line, err->span.start_col);
        }
    }
}
_Bool type_is_integer(Type *t) {
    if (!t) return 0;
    if (t->kind != TYPE_PRIMITIVE) return 0;
    return t->as.primitive == PRIM_I32 || t->as.primitive == PRIM_I64;
}
_Bool type_is_float(Type *t) {
    if (!t) return 0;
    if (t->kind != TYPE_PRIMITIVE) return 0;
    return t->as.primitive == PRIM_F32 || t->as.primitive == PRIM_F64;
}
_Bool type_is_bool(Type *t) {
    if (!t) return 0;
    if (t->kind != TYPE_PRIMITIVE) return 0;
    return t->as.primitive == PRIM_BOOL;
}
_Bool type_is_char(Type *t) {
    if (!t) return 0;
    if (t->kind != TYPE_PRIMITIVE) return 0;
    return t->as.primitive == PRIM_CHAR;
}
_Bool type_is_void(Type *t) {
    return t && t->kind == TYPE_VOID;
}
_Bool type_is_pointer_to_void(Type *t) {
    if (!t || t->kind != TYPE_POINTER) return 0;
    return type_is_void(t->as.ptr.base);
}
_Bool type_is_pointer_like(Type *t) {
    if (!t) return 0;
    return (t->kind == TYPE_POINTER);
}
_Bool type_is_numeric(Type *t) {
    return type_is_integer(t) || type_is_float(t);
    }
static inline size_t hash_combine(size_t seed, size_t value) {
    seed ^= value;
    seed *= 0x100000001b3ULL;
    return seed;
}
static size_t type_hasher(void *ptr) {
    const Slice *slice = (const Slice*)ptr;
    const Type *type = (const Type*)slice->ptr;
    size_t h = 0xcbf29ce484222325ULL;
    h = hash_combine(h, (size_t)type->kind);
    switch (type->kind) {
        case TYPE_PRIMITIVE:
            h = hash_combine(h, (size_t)type->as.primitive);
            break;
        case TYPE_POINTER:
            h = hash_combine(h, type->as.ptr.base->cached_hash);
            break;
        case TYPE_ARRAY:
            h = hash_combine(h, type->as.array.base->cached_hash);
            h = hash_combine(h, (size_t)type->as.array.size);
            break;
        case TYPE_SLICE:
            h = hash_combine(h, type->as.slice.base->cached_hash);
            break;
        case TYPE_FUNCTION:
            h = hash_combine(h, type->as.func.return_type->cached_hash);
            h = hash_combine(h, (size_t)type->as.func.param_count);
            for (size_t i = 0; i < type->as.func.param_count; i++) {
                h = hash_combine(h, type->as.func.params[i]->cached_hash);
            }
            break;
        default:
            break;
    }
    return h;
}
static int type_comparator(void *a, void *b) {
    const Slice *slice_a = (const Slice*)a;
    const Slice *slice_b = (const Slice*)b;
    const Type *ta = (const Type*)slice_a->ptr;
    const Type *tb = (const Type*)slice_b->ptr;
    if (ta == tb) return 0;
    if (ta->kind != tb->kind) return 1;
    switch (ta->kind) {
        case TYPE_PRIMITIVE:
            return (ta->as.primitive == tb->as.primitive) ? 0 : 1;
        case TYPE_POINTER:
            return (ta->as.ptr.base == tb->as.ptr.base) ? 0 : 1;
        case TYPE_ARRAY:
            if (ta->as.array.size != tb->as.array.size) return 1;
            return (ta->as.array.base == tb->as.array.base) ? 0 : 1;
        case TYPE_FUNCTION:
            if (ta->as.func.return_type != tb->as.func.return_type) return 1;
            if (ta->as.func.param_count != tb->as.func.param_count) return 1;
            if (ta->as.func.param_count > 0) {
                return memcmp(ta->as.func.params, tb->as.func.params,
                              ta->as.func.param_count * sizeof(Type*));
            }
            return 0;
        default:
            return 1;
    }
}
static void *type_copy_func(Arena *arena, const void *data, size_t len) {
    if (!arena || !data) return ((void*)0);
    const Type *src = (const Type*)data;
    Type *copy = arena_alloc(arena, sizeof(Type));
    if (!copy) return ((void*)0);
    __builtin___memcpy_chk (copy, src, sizeof(Type), __builtin_object_size (copy, 0));
    if (src->kind == TYPE_FUNCTION && src->as.func.param_count > 0) {
        size_t params_size = sizeof(Type*) * src->as.func.param_count;
        Type **new_params = arena_alloc(arena, params_size);
        if (new_params) {
            __builtin___memcpy_chk (new_params, src->as.func.params, params_size, __builtin_object_size (new_params, 0));
            copy->as.func.params = new_params;
        }
    }
    return copy;
}
InternResult *intern_type(TypeStore *ts, Type *prototype) {
    if (!ts || !prototype) return ((void*)0);
    prototype->cached_hash = type_hasher(&(Slice){.ptr = (char*)prototype, .len = sizeof(Type)});
    Slice slice = { .ptr = (const char*)prototype, .len = sizeof(Type) };
    InternResult *result = intern(ts->type_interner, &slice, ((void*)0));
    if (!result) return ((void*)0);
    return result;
}
static void register_prim(TypeStore *ts, DenseArenaInterner *ids, const char *name, Type *t) {
    Slice s = { .ptr = (char*)name, .len = strlen(name) };
    InternResult *res = intern(ids, &s, ((void*)0));
    if (res && res->key) {
        hashmap_put(ts->primitive_registry, res->key, t, ptr_hash, ptr_cmp);
    }
}
static Type *create_primitive(TypeStore *ts, PrimitiveKind kind) {
    Type proto = {0};
    proto.kind = TYPE_PRIMITIVE;
    proto.as.primitive = kind;
    proto.cached_hash = type_hasher(&(Slice){.ptr = (char*)&proto, .len = sizeof(Type)});
    InternResult *res = intern(ts->type_interner, &(Slice){.ptr = (char*)&proto, .len = sizeof(Type)}, ((void*)0));
    if (!res) return ((void*)0);
    return (Type*)((Slice*)res->key)->ptr;
}
TypeStore *typestore_create(Arena *arena, DenseArenaInterner *identifiers, DenseArenaInterner *keywords) {
    if (!arena) return ((void*)0);
    TypeStore *ts = arena_alloc(arena, sizeof(TypeStore));
    if (!ts) return ((void*)0);
    ts->arena = arena;
    HashMap *tm = hashmap_create(64);
    if (!tm) return ((void*)0);
    ts->type_interner = intern_table_create(tm, arena, type_copy_func, type_hasher, type_comparator);
    if (!ts->type_interner) return ((void*)0);
    ts->primitive_registry = hashmap_create(64);
    ts->t_i32 = create_primitive(ts, PRIM_I32);
    ts->t_i64 = create_primitive(ts, PRIM_I64);
    ts->t_f32 = create_primitive(ts, PRIM_F32);
    ts->t_f64 = create_primitive(ts, PRIM_F64);
    ts->t_bool = create_primitive(ts, PRIM_BOOL);
    ts->t_char = create_primitive(ts, PRIM_CHAR);
    Type str_proto = { .kind = TYPE_POINTER, .as.ptr.base = ts->t_char };
    InternResult *str_res = intern_type(ts, &str_proto);
    ts->t_str = (Type*)((Slice*)str_res->key)->ptr;
    Type void_proto = { .kind = TYPE_VOID };
    InternResult *void_res = intern_type(ts, &void_proto);
    ts->t_void = (Type*)((Slice*)void_res->key)->ptr;
    Type void_ptr_proto = { .kind = TYPE_POINTER, .as.ptr.base = ts->t_void };
    InternResult *vp_res = intern_type(ts, &void_ptr_proto);
    ts->t_void_ptr = (Type*)((Slice*)vp_res->key)->ptr;
    register_prim(ts, keywords, "i32", ts->t_i32);
    register_prim(ts, keywords, "i64", ts->t_i64);
    register_prim(ts, keywords, "f32", ts->t_f32);
    register_prim(ts, keywords, "f64", ts->t_f64);
    register_prim(ts, keywords, "bool", ts->t_bool);
    register_prim(ts, keywords, "char", ts->t_char);
    register_prim(ts, keywords, "str", ts->t_str);
    register_prim(ts, keywords, "void", ts->t_void);
    Slice len_slice = { .ptr = "len", .len = 3 };
    ts->kw_len = intern(identifiers, &len_slice, ((void*)0));
    return ts;
}
void register_intrinsics(TypeStore *ts, Scope *global_scope, DenseArenaInterner *ids) {
    {
        Slice s = { .ptr = "print", .len = 5 };
        InternResult *res = intern(ids, &s, ((void*)0));
        Symbol *sym = scope_define_symbol(global_scope, res, ts->t_void, SYMBOL_VALUE_INTRINSIC, ((void*)0), 1, ((void*)0));
        if (sym) sym->intrinsic_kind = INTRINSIC_PRINT;
    }
    {
        Slice s = { .ptr = "println", .len = 7 };
        InternResult *res = intern(ids, &s, ((void*)0));
        Symbol *sym = scope_define_symbol(global_scope, res, ts->t_void, SYMBOL_VALUE_INTRINSIC, ((void*)0), 1, ((void*)0));
        if (sym) sym->intrinsic_kind = INTRINSIC_PRINT_NEWLINE;
    }
}
Type* check_literal(TypeCheckContext *ctx, AstNode *expr, Type *expected_type);
Type* check_identifier(TypeCheckContext *ctx, Scope *scope, AstNode *expr);
Type* check_call_expr(TypeCheckContext *ctx, Scope *scope, AstNode *expr);
Type* check_subscript(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type);
Type* check_binary(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type);
Type* check_unary(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type);
Type* check_assignment(TypeCheckContext *ctx, Scope *scope, AstNode *expr);
Type* check_initializer_list(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type);
Type* check_expression(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type);
void insert_cast(TypeCheckContext *ctx, AstNode *node, Type *to_type);
Type* coerce_or_error(TypeCheckContext *ctx, AstNode *node, Type *expected);
static void fold_unary_op(AstNode *node, OpKind op, AstNode *operand) {
    if (!operand->is_foldable_const) return;
    LiteralType type = operand->const_value.type;
    if (op == OP_NOT && type == BOOL_LITERAL) {
        node->is_foldable_const = 1;
        node->is_llvm_const_safe = 1;
        node->const_value.type = BOOL_LITERAL;
        node->const_value.value.bool_val = !operand->const_value.value.bool_val;
        return;
    }
    if (op == OP_SUB) {
        node->is_foldable_const = 1;
        node->is_llvm_const_safe = 1;
        node->const_value.type = type;
        if (type == INT_LITERAL) {
            node->const_value.value.int_val = -operand->const_value.value.int_val;
        } else if (type == FLOAT_LITERAL) {
            node->const_value.value.float_val = -operand->const_value.value.float_val;
        }
    }
}
static void fold_binary_op(AstNode *node, OpKind op, AstNode *l, AstNode *r) {
    if (!l->is_foldable_const || !r->is_foldable_const) return;
    LiteralType ltype = l->const_value.type;
    LiteralType rtype = r->const_value.type;
    if (ltype == FLOAT_LITERAL || rtype == FLOAT_LITERAL) {
        double v1 = (ltype == FLOAT_LITERAL) ? l->const_value.value.float_val : (double)l->const_value.value.int_val;
        double v2 = (rtype == FLOAT_LITERAL) ? r->const_value.value.float_val : (double)r->const_value.value.int_val;
        double res = 0.0;
        _Bool is_bool = 0;
        switch (op) {
            case OP_ADD: res = v1 + v2; break;
            case OP_SUB: res = v1 - v2; break;
            case OP_MUL: res = v1 * v2; break;
            case OP_DIV: if(v2==0) return; res = v1 / v2; break;
            case OP_MOD: if(v2==0) return; res = fmod(v1, v2); break;
            case OP_EQ: res = (v1 == v2); is_bool = 1; break;
            case OP_NEQ: res = (v1 != v2); is_bool = 1; break;
            case OP_LT: res = (v1 < v2); is_bool = 1; break;
            case OP_GT: res = (v1 > v2); is_bool = 1; break;
            case OP_LE: res = (v1 <= v2); is_bool = 1; break;
            case OP_GE: res = (v1 >= v2); is_bool = 1; break;
            default: return;
        }
        node->is_foldable_const = 1;
        node->is_llvm_const_safe = 1;
        if (is_bool) {
            node->const_value.type = BOOL_LITERAL;
            node->const_value.value.bool_val = (_Bool)res;
        } else {
            node->const_value.type = FLOAT_LITERAL;
            node->const_value.value.float_val = res;
        }
    } else if (ltype == INT_LITERAL && rtype == INT_LITERAL) {
        int64_t v1 = l->const_value.value.int_val;
        int64_t v2 = r->const_value.value.int_val;
        int64_t res = 0;
        _Bool is_bool = 0;
        switch (op) {
            case OP_ADD: res = v1 + v2; break;
            case OP_SUB: res = v1 - v2; break;
            case OP_MUL: res = v1 * v2; break;
            case OP_DIV: if(v2==0) return; res = v1 / v2; break;
            case OP_MOD: if(v2==0) return; res = v1 % v2; break;
            case OP_EQ: res = (v1 == v2); is_bool = 1; break;
            case OP_NEQ: res = (v1 != v2); is_bool = 1; break;
            case OP_LT: res = (v1 < v2); is_bool = 1; break;
            case OP_GT: res = (v1 > v2); is_bool = 1; break;
            case OP_LE: res = (v1 <= v2); is_bool = 1; break;
            case OP_GE: res = (v1 >= v2); is_bool = 1; break;
            case OP_AND: res = (v1 && v2); is_bool = 1; break;
            case OP_OR: res = (v1 || v2); is_bool = 1; break;
            default: return;
        }
        node->is_foldable_const = 1;
        node->is_llvm_const_safe = 1;
        if (is_bool) {
            node->const_value.type = BOOL_LITERAL;
            node->const_value.value.bool_val = (_Bool)res;
        } else {
            node->const_value.type = INT_LITERAL;
            node->const_value.value.int_val = res;
        }
    }
}
static Type* resolve_literal_type(TypeCheckContext *ctx, LiteralType lit_kind, Type *expected) {
    TypeStore *s = ctx->store;
    switch (lit_kind) {
        case INT_LITERAL:
            if (expected && type_is_float(expected)) return expected;
            if (expected && type_is_integer(expected)) return expected;
            return s->t_i64;
        case FLOAT_LITERAL:
            if (expected && type_is_float(expected)) return expected;
            return s->t_f64;
        case BOOL_LITERAL: return s->t_bool;
        case CHAR_LITERAL: return s->t_char;
        case STRING_LITERAL: return s->t_str;
        default: return ((void*)0);
    }
}
Type* check_literal(TypeCheckContext *ctx, AstNode *expr, Type *expected_type) {
    Type *type = resolve_literal_type(ctx, expr->data.literal.type, expected_type);
    if (expr->data.literal.type == INT_LITERAL && type && type_is_float(type)) {
        expr->data.literal.type = FLOAT_LITERAL;
        expr->data.literal.value.float_val = (double)expr->data.literal.value.int_val;
    }
    expr->is_foldable_const = 1;
    expr->is_llvm_const_safe = 1;
    expr->const_value.type = expr->data.literal.type;
    expr->const_value.value = expr->data.literal.value;
    expr->type = type;
    return type;
}
static Scope* get_module_scope(Scope *scope) {
    while (scope && scope->depth > 1) {
        scope = scope->parent;
    }
    return scope;
}
Type* check_identifier(TypeCheckContext *ctx, Scope *scope, AstNode *expr) {
    AstIdentifier *ident = &expr->data.identifier;
    Symbol *sym = scope_lookup_symbol(scope, ident->intern_result, ctx->filename);
    if (!sym) {
        const char *name = (ident->intern_result && ident->intern_result->key)
            ? ((Slice*)ident->intern_result->key)->ptr
            : "<unknown>";
        TypeError err = {
            .kind = TE_UNDECLARED,
            .span = expr->span,
            .filename = ctx->filename,
            .as.name.name = name
        };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    ident->symbol = sym;
    _Bool is_unresolved_const = (sym->flags & SYMBOL_FLAG_CONST) &&
                              !(sym->flags & SYMBOL_FLAG_COMPUTED_VALUE);
    if (is_unresolved_const && sym->decl_node) {
        Scope *module_scope = get_module_scope(scope);
        if (module_scope) {
            check_variable_declaration(ctx, module_scope, sym->decl_node);
        }
    }
    expr->type = sym->type;
    expr->is_foldable_const = 0;
    expr->is_llvm_const_safe = 0;
    _Bool is_computed_const = (sym->flags & SYMBOL_FLAG_CONST) &&
                            (sym->flags & SYMBOL_FLAG_COMPUTED_VALUE);
    if (is_computed_const) {
        if (type_is_integer(sym->type)) {
            expr->is_foldable_const = 1;
            expr->const_value = (ConstValue){ .type = INT_LITERAL, .value.int_val = sym->value.int_val };
        } else if (type_is_float(sym->type)) {
            expr->is_foldable_const = 1;
            expr->const_value = (ConstValue){ .type = FLOAT_LITERAL, .value.float_val = sym->value.float_val };
        } else if (type_is_bool(sym->type)) {
            expr->is_foldable_const = 1;
            expr->const_value = (ConstValue){ .type = BOOL_LITERAL, .value.bool_val = sym->value.bool_val };
        } else if (type_is_char(sym->type)) {
            expr->is_foldable_const = 1;
            expr->const_value = (ConstValue){ .type = CHAR_LITERAL, .value.char_val = (char)sym->value.int_val };
        }
        _Bool is_aggregate = sym->type->kind == TYPE_STRUCT ||
                           sym->type->kind == TYPE_ARRAY ||
                           sym->type->kind == TYPE_SLICE;
        expr->is_llvm_const_safe = expr->is_foldable_const || is_aggregate;
    }
    return sym->type;
}
Type* check_call_expr(TypeCheckContext *ctx, Scope *scope, AstNode *expr) {
    AstCallExpr *call = &expr->data.call_expr;
    if (call->callee->node_type == AST_IDENTIFIER) {
        Symbol *sym = scope_lookup_symbol(scope, call->callee->data.identifier.intern_result, ctx->filename);
        if (sym && sym->kind == SYMBOL_VALUE_INTRINSIC) {
            expr->type = ctx->store->t_void;
            size_t arg_count = call->args ? call->args->count : 0;
            for (size_t i = 0; i < arg_count; i++) {
                AstNode *arg = *(AstNode**)dynarray_get(call->args, i);
                check_expression(ctx, scope, arg, ((void*)0));
            }
            call->callee->type = sym->type;
            call->callee->data.identifier.symbol = sym;
            return expr->type;
        }
    }
    Type *callee_type = check_expression(ctx, scope, call->callee, ((void*)0));
    if (!callee_type) return ((void*)0);
    if (callee_type->kind != TYPE_FUNCTION) {
        TypeError err = { .kind = TE_NOT_CALLABLE, .span = call->callee->span, .filename = ctx->filename, .as.bad_usage.actual = callee_type };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    size_t param_count = callee_type->as.func.param_count;
    size_t arg_count = call->args ? call->args->count : 0;
    if (arg_count != param_count) {
        TypeError err = { .kind = TE_ARG_COUNT_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.arg_count = { .expected = param_count, .actual = arg_count } };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    for (size_t i = 0; i < arg_count; i++) {
        AstNode *arg = *(AstNode**)dynarray_get(call->args, i);
        Type *param_type = callee_type->as.func.params[i];
        if (check_expression(ctx, scope, arg, param_type)) {
            coerce_or_error(ctx, arg, param_type);
        }
    }
    return callee_type->as.func.return_type;
}
Type* check_subscript(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type) {
    AstSubscriptExpr *subscript = &expr->data.subscript_expr;
    Type *target_expected = ((void*)0);
    if (expected_type) {
        Type proto = {0};
        proto.kind = TYPE_SLICE;
        proto.as.slice.base = expected_type;
        InternResult *res = intern_type(ctx->store, &proto);
        target_expected = res ? (Type*)((Slice*)res->key)->ptr : ((void*)0);
    }
    Type *base_type = check_expression(ctx, scope, subscript->target, target_expected);
    if (!base_type) return ((void*)0);
    if (base_type->kind != TYPE_ARRAY && base_type->kind != TYPE_SLICE && base_type->kind != TYPE_POINTER) {
        TypeError err = {
            .kind = TE_NOT_INDEXABLE,
            .span = subscript->target->span,
            .filename = ctx->filename,
            .as.bad_usage.actual = base_type
        };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    Type *index_type = check_expression(ctx, scope, subscript->index, ctx->store->t_i64);
    if (index_type) {
        coerce_or_error(ctx, subscript->index, ctx->store->t_i64);
    } else {
        return ((void*)0);
    }
    if (base_type->kind == TYPE_ARRAY) {
        _Bool is_const = subscript->index->is_foldable_const;
        if (!is_const && subscript->index->node_type == AST_LITERAL && subscript->index->data.literal.type == INT_LITERAL) {
             is_const = 1;
        }
        if (is_const) {
            int64_t idx = subscript->index->const_value.value.int_val;
            int64_t limit = base_type->as.array.size;
            if (idx < 0 || idx >= limit) {
                TypeError err = {
                    .kind = TE_INDEX_OUT_OF_BOUNDS,
                    .span = subscript->index->span,
                    .filename = ctx->filename,
                    .as.size = { .expected_size = (size_t)limit, .actual_size = (size_t)idx }
                };
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
        }
    }
    return (base_type->kind == TYPE_ARRAY) ? base_type->as.array.base :
           (base_type->kind == TYPE_SLICE) ? base_type->as.slice.base :
           base_type->as.ptr.base;
}
Type* check_assignment(TypeCheckContext *ctx, Scope *scope, AstNode *expr) {
    AstAssignmentExpr *assign = &expr->data.assignment_expr;
    Type *lhs = check_expression(ctx, scope, assign->lvalue, ((void*)0));
    Type *rhs = check_expression(ctx, scope, assign->rvalue, lhs);
    if (!is_lvalue_node(assign->lvalue)) {
        TypeError err = { .kind = TE_NOT_LVALUE, .span = assign->lvalue->span, .filename = ctx->filename };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    if (!lhs || !rhs) return ((void*)0);
    if (assign->op != OP_ASSIGN) {
        if (!type_is_numeric(lhs) || !type_is_numeric(rhs)) {
            TypeError err = { .kind = TE_BINOP_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.binop = { .op = assign->op, .left = lhs, .right = rhs } };
            dynarray_push_value(ctx->errors, &err);
            return ((void*)0);
        }
    }
    if (lhs != rhs) {
        coerce_or_error(ctx, assign->rvalue, lhs);
    }
    expr->type = lhs;
    return lhs;
}
static int get_type_rank(Type *t) {
    int rank = 0;
    while (t) {
        if (t->kind == TYPE_ARRAY) {
            rank++;
            t = t->as.array.base;
        } else if (t->kind == TYPE_SLICE) {
            rank++;
            t = t->as.slice.base;
        } else {
            break;
        }
    }
    return rank;
}
static int get_initializer_rank(AstNode *node) {
    if (!node || node->node_type != AST_INITIALIZER_LIST) return 0;
    if (node->data.initializer_list.elements->count == 0) return 1;
    AstNode *first = *(AstNode**)dynarray_get(node->data.initializer_list.elements, 0);
    return 1 + get_initializer_rank(first);
}
Type* check_initializer_list(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type) {
    if (!expr || expr->node_type != AST_INITIALIZER_LIST) return ((void*)0);
    AstInitializeList *list = &expr->data.initializer_list;
    size_t elem_count = list->elements ? list->elements->count : 0;
    if (!expected_type) {
        if (elem_count == 0) return ((void*)0);
        AstNode **first_ptr = (AstNode**)dynarray_get(list->elements, 0);
        Type *first_ty = check_expression(ctx, scope, *first_ptr, ((void*)0));
        if (!first_ty) return ((void*)0);
        Type proto = {0};
        proto.kind = TYPE_ARRAY;
        proto.as.array.base = first_ty;
        proto.as.array.size = (int64_t)elem_count;
        InternResult *res = intern_type(ctx->store, &proto);
        expected_type = res ? (Type*)((Slice*)res->key)->ptr : ((void*)0);
        if (!expected_type) return ((void*)0);
    }
    if (expected_type->kind != TYPE_ARRAY && expected_type->kind != TYPE_SLICE) {
         TypeError err = {
            .kind = TE_UNEXPECTED_LIST,
            .span = expr->span,
            .filename = ctx->filename,
            .as.mismatch = { .expected = expected_type, .actual = ((void*)0) }
        };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    int type_rank = get_type_rank(expected_type);
    int init_rank = get_initializer_rank(expr);
    if (type_rank != init_rank) {
        TypeError err = {
            .kind = TE_DIMENSION_MISMATCH,
            .span = expr->span,
            .filename = ctx->filename,
            .as.dims = { .expected_ndim = type_rank, .actual_ndim = init_rank }
        };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    if (expected_type->kind == TYPE_ARRAY) {
        if (elem_count != (size_t)expected_type->as.array.size) {
             TypeError err = {
                .kind = TE_ARRAY_SIZE_MISMATCH,
                .span = expr->span,
                .filename = ctx->filename,
                .as.size = { .expected_size = expected_type->as.array.size, .actual_size = elem_count }
            };
            dynarray_push_value(ctx->errors, &err);
            return ((void*)0);
        }
    }
    Type *base_expected = (expected_type->kind == TYPE_ARRAY) ? expected_type->as.array.base : expected_type->as.slice.base;
    Type *common_base = ((void*)0);
    _Bool any_error = 0;
    for (size_t i = 0; i < elem_count; i++) {
        AstNode **node_ptr = (AstNode**)dynarray_get(list->elements, i);
        AstNode *node = *node_ptr;
        Type *actual_elem_type = check_expression(ctx, scope, node, base_expected);
        if (!actual_elem_type) {
            any_error = 1;
            break;
        }
        if ((base_expected->kind == TYPE_ARRAY || base_expected->kind == TYPE_SLICE) &&
            (actual_elem_type->kind != TYPE_ARRAY && actual_elem_type->kind != TYPE_SLICE)) {
             TypeError err = {
                .kind = TE_EXPECTED_ARRAY,
                .span = node->span,
                .filename = ctx->filename,
                .as.mismatch = { .expected = base_expected, .actual = actual_elem_type }
            };
            dynarray_push_value(ctx->errors, &err);
            return ((void*)0);
        }
        if ((base_expected->kind != TYPE_ARRAY && base_expected->kind != TYPE_SLICE) &&
            (actual_elem_type->kind == TYPE_ARRAY || actual_elem_type->kind == TYPE_SLICE)) {
             TypeError err = {
                .kind = TE_TYPE_MISMATCH,
                .span = node->span,
                .filename = ctx->filename,
                .as.mismatch = { .expected = base_expected, .actual = actual_elem_type }
            };
            dynarray_push_value(ctx->errors, &err);
            return ((void*)0);
        }
        if (actual_elem_type != base_expected) {
            if (coerce_or_error(ctx, node, base_expected)) {
                actual_elem_type = base_expected;
            } else {
                return ((void*)0);
            }
        }
        if (i == 0) {
            common_base = actual_elem_type;
        }
    }
    if (any_error) return ((void*)0);
    Type *final_base = common_base ? common_base : base_expected;
    Type new_type = {0};
    new_type.kind = TYPE_ARRAY;
    new_type.as.array.base = final_base;
    new_type.as.array.size = elem_count;
    InternResult *res = intern_type(ctx->store, &new_type);
    Type *concrete_type = (Type*)((Slice*)res->key)->ptr;
    _Bool all_llvm_const = 1;
    for (size_t i = 0; i < elem_count; i++) {
        AstNode **node_ptr = (AstNode**)dynarray_get(list->elements, i);
        AstNode *node = *node_ptr;
        if (!node->is_llvm_const_safe) {
            all_llvm_const = 0;
            break;
        }
    }
    expr->is_foldable_const = 0;
    expr->is_llvm_const_safe = all_llvm_const ? 1 : 0;
    expr->type = concrete_type;
    return concrete_type;
}
static Type* check_struct_literal(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type) {
    AstStructLiteral *lit = &expr->data.struct_literal;
    Type *struct_type = ((void*)0);
    if (lit->type_node) {
         struct_type = resolve_ast_type(ctx, scope, lit->type_node);
    }
    if (!struct_type || struct_type->kind != TYPE_STRUCT) {
        const char *name_str = "<unknown>";
        TypeError err = { .kind = TE_UNKNOWN_TYPE, .span = expr->span, .filename = ctx->filename, .as.name.name = name_str };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    expr->type = struct_type;
    size_t defined_field_count = struct_type->as.struct_type.field_count;
    size_t lit_field_count = lit->fields ? lit->fields->count : 0;
    if (lit_field_count != defined_field_count) {
        TypeError err = { .kind = TE_ARG_COUNT_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.arg_count = { .expected = defined_field_count, .actual = lit_field_count } };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    _Bool all_llvm_const = 1;
    for (size_t i = 0; i < lit_field_count; i++) {
        AstFieldInit *init = (AstFieldInit*)dynarray_get(lit->fields, i);
        void *field_idx_ptr = hashmap_get(struct_type->as.struct_type.field_map, init->name->key, ptr_hash, ptr_cmp);
        if (!field_idx_ptr) {
            const char *name_str = "<unknown>";
            if (init->name && init->name->key) name_str = ((Slice*)init->name->key)->ptr;
            TypeError err = { .kind = TE_FIELD_ACCESS, .span = init->expr->span, .filename = ctx->filename, .as.name.name = name_str };
            dynarray_push_value(ctx->errors, &err);
            return ((void*)0);
        }
        size_t field_idx = (size_t)(uintptr_t)field_idx_ptr - 1;
        StructField *def_field = &struct_type->as.struct_type.fields[field_idx];
        if (check_expression(ctx, scope, init->expr, def_field->type)) {
            coerce_or_error(ctx, init->expr, def_field->type);
        }
        if (!init->expr->is_llvm_const_safe) {
            all_llvm_const = 0;
        }
    }
    expr->is_foldable_const = 0;
    expr->is_llvm_const_safe = all_llvm_const ? 1 : 0;
    return struct_type;
}
static Type *check_intrinsic(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type) {
    AstNode *node = expr;
    IntrinsicKind kind = node->data.intrinsic.kind;
    size_t arg_count = node->data.intrinsic.args ? node->data.intrinsic.args->count : 0;
    if (kind == INTRINSIC_ALLOC) {
        if (arg_count < 2 || arg_count > 3) {
            TypeError err = { .kind = TE_ARG_COUNT_MISMATCH, .span = node->span, .filename = ctx->filename };
            err.as.arg_count.expected = 2;
            err.as.arg_count.actual = arg_count;
            dynarray_push_value(ctx->errors, &err);
            return ctx->store->t_void_ptr;
        }
        AstNode *type_arg = *(AstNode**)dynarray_get(node->data.intrinsic.args, 0);
        AstNode *alloc_arg = *(AstNode**)dynarray_get(node->data.intrinsic.args, 1);
        AstNode *count_arg = arg_count == 3 ? *(AstNode**)dynarray_get(node->data.intrinsic.args, 2) : ((void*)0);
        Type *allocated_type = resolve_ast_type(ctx, scope, type_arg);
        if (allocated_type) {
            type_arg->type = allocated_type;
        } else {
            Type *actual = check_expression(ctx, scope, type_arg, ((void*)0));
            TypeError err = { .kind = TE_EXPECTED_TYPE_ARG, .span = type_arg->span, .filename = ctx->filename };
            err.as.mismatch.expected = ((void*)0);
            err.as.mismatch.actual = actual;
            dynarray_push_value(ctx->errors, &err);
        }
        Type *alloc_ty = check_expression(ctx, scope, alloc_arg, ((void*)0));
        if (alloc_ty) {
            Type *underlying = alloc_ty;
            if (underlying->kind == TYPE_POINTER) underlying = underlying->as.ptr.base;
            if (underlying->kind != TYPE_STRUCT) {
                TypeError err = { .kind = TE_TYPE_MISMATCH, .span = alloc_arg->span, .filename = ctx->filename };
                err.as.mismatch.expected = ctx->store->t_void;
                err.as.mismatch.actual = alloc_ty;
                dynarray_push_value(ctx->errors, &err);
            }
        }
        if (count_arg) {
            Type *count_ty = check_expression(ctx, scope, count_arg, ctx->store->t_i64);
            if (count_ty && !type_is_integer(count_ty)) {
                TypeError err = { .kind = TE_TYPE_MISMATCH, .span = count_arg->span, .filename = ctx->filename };
                err.as.mismatch.expected = ctx->store->t_i64;
                err.as.mismatch.actual = count_ty;
                dynarray_push_value(ctx->errors, &err);
            }
        }
        if (allocated_type) {
            Type proto = { .kind = TYPE_POINTER, .as.ptr.base = allocated_type };
            InternResult *res = intern_type(ctx->store, &proto);
            if (res && res->key) node->type = (Type*)((Slice*)res->key)->ptr;
        }
        if (!node->type) node->type = ctx->store->t_void_ptr;
        return node->type;
    }
    else if (kind == INTRINSIC_FREE) {
        if (arg_count != 2) {
            TypeError err = { .kind = TE_ARG_COUNT_MISMATCH, .span = node->span, .filename = ctx->filename };
            err.as.arg_count.expected = 2;
            err.as.arg_count.actual = arg_count;
            dynarray_push_value(ctx->errors, &err);
            return ctx->store->t_void;
        }
        AstNode *alloc_arg = *(AstNode**)dynarray_get(node->data.intrinsic.args, 0);
        AstNode *ptr_arg = *(AstNode**)dynarray_get(node->data.intrinsic.args, 1);
        Type *alloc_ty = check_expression(ctx, scope, alloc_arg, ((void*)0));
        if (alloc_ty) {
            Type *underlying = alloc_ty;
            if (underlying->kind == TYPE_POINTER) underlying = underlying->as.ptr.base;
            if (underlying->kind != TYPE_STRUCT) {
                TypeError err = { .kind = TE_TYPE_MISMATCH, .span = alloc_arg->span, .filename = ctx->filename };
                err.as.mismatch.expected = ctx->store->t_void;
                err.as.mismatch.actual = alloc_ty;
                dynarray_push_value(ctx->errors, &err);
            }
        }
        Type *ptr_ty = check_expression(ctx, scope, ptr_arg, ((void*)0));
        if (ptr_ty && ptr_ty->kind != TYPE_POINTER) {
            TypeError err = { .kind = TE_TYPE_MISMATCH, .span = ptr_arg->span, .filename = ctx->filename };
            err.as.mismatch.expected = ctx->store->t_void_ptr;
            err.as.mismatch.actual = ptr_ty;
            dynarray_push_value(ctx->errors, &err);
        }
        return ctx->store->t_void;
    }
    return ctx->store->t_void;
}
Type* check_unary(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type) {
    AstUnaryExpr *unary = &expr->data.unary_expr;
    Type *hint = ((void*)0);
    if (expected_type && type_is_numeric(expected_type)) {
        if (unary->op == OP_SUB || unary->op == OP_ADD) {
             hint = expected_type;
        }
    }
    if (unary->op == OP_NOT && expected_type == ctx->store->t_bool) {
        hint = expected_type;
    }
    Type *operand_type = check_expression(ctx, scope, unary->expr, hint);
    if (!operand_type) return ((void*)0);
    switch (unary->op) {
        case OP_NOT:
            if (operand_type != ctx->store->t_bool) {
                TypeError err = { .kind = TE_UNOP_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.unop = { .op = unary->op, .operand = operand_type } };
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
            if (unary->expr->is_foldable_const) fold_unary_op(expr, unary->op, unary->expr);
            return ctx->store->t_bool;
        case OP_SUB:
            if (!type_is_numeric(operand_type)) {
                TypeError err = { .kind = TE_UNOP_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.unop = { .op = unary->op, .operand = operand_type } };
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
            if (unary->expr->is_foldable_const) fold_unary_op(expr, unary->op, unary->expr);
            return operand_type;
        case OP_ADRESS:
            if (!is_lvalue_node(unary->expr)) {
                TypeError err = { .kind = TE_NOT_LVALUE, .span = unary->expr->span, .filename = ctx->filename };
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
            {
                Type proto = { .kind = TYPE_POINTER, .as.ptr.base = operand_type };
                InternResult *res = intern_type(ctx->store, &proto);
                return res ? (Type*)((Slice*)res->key)->ptr : ((void*)0);
            }
        case OP_DEREF:
            if (operand_type->kind != TYPE_POINTER) {
                TypeError err = { .kind = TE_UNOP_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.unop = { .op = unary->op, .operand = operand_type } };
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
            if (type_is_void(operand_type->as.ptr.base)) {
                TypeError err = { .kind = TE_UNOP_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.unop = { .op = unary->op, .operand = operand_type } };
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
            return operand_type->as.ptr.base;
        default: return ((void*)0);
    }
}
Type* check_binary(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type) {
    AstBinaryExpr *bin = &expr->data.binary_expr;
    OpKind op = bin->op;
    Type *lhs_hint = ((void*)0);
    if (expected_type && type_is_numeric(expected_type)) {
        if (op == OP_ADD || op == OP_SUB || op == OP_MUL || op == OP_DIV || op == OP_MOD) {
            lhs_hint = expected_type;
        }
    }
    Type *lhs = check_expression(ctx, scope, bin->left, lhs_hint);
    Type *rhs_hint = ((void*)0);
    if (lhs && type_is_numeric(lhs)) {
        rhs_hint = lhs;
    } else if (expected_type && type_is_numeric(expected_type) && lhs_hint) {
        rhs_hint = expected_type;
    }
    Type *rhs = check_expression(ctx, scope, bin->right, rhs_hint);
    if (!lhs || !rhs) return ((void*)0);
    if (bin->left->node_type == AST_LITERAL && lhs != rhs) {
         lhs = check_expression(ctx, scope, bin->left, rhs);
    }
    else if (bin->right->node_type == AST_LITERAL && lhs != rhs) {
         rhs = check_expression(ctx, scope, bin->right, lhs);
    }
    if (lhs != rhs) {
        TypeError err = { .kind = TE_BINOP_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.binop = { .op = op, .left = lhs, .right = rhs } };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    Type *result_type = ((void*)0);
    if (op == OP_ADD || op == OP_SUB || op == OP_MUL || op == OP_DIV || op == OP_MOD) {
        if (!type_is_numeric(lhs)) {
            TypeError err = { .kind = TE_BINOP_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.binop = { .op = op, .left = lhs, .right = rhs } };
            dynarray_push_value(ctx->errors, &err);
            return ((void*)0);
        }
        result_type = lhs;
    }
    else if (op == OP_EQ || op == OP_NEQ || op == OP_LT || op == OP_GT || op == OP_LE || op == OP_GE) {
        if (lhs->kind != TYPE_PRIMITIVE && lhs->kind != TYPE_POINTER) {
             TypeError err = { .kind = TE_BINOP_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.binop = { .op = op, .left = lhs, .right = rhs } };
             dynarray_push_value(ctx->errors, &err);
             return ((void*)0);
        }
        result_type = ctx->store->t_bool;
    }
    else if (op == OP_AND || op == OP_OR) {
        if (lhs != ctx->store->t_bool) {
            TypeError err = { .kind = TE_BINOP_MISMATCH, .span = expr->span, .filename = ctx->filename, .as.binop = { .op = op, .left = lhs, .right = rhs } };
            dynarray_push_value(ctx->errors, &err);
            return ((void*)0);
        }
        result_type = ctx->store->t_bool;
    }
    if (bin->left->is_foldable_const && bin->right->is_foldable_const) {
        fold_binary_op(expr, op, bin->left, bin->right);
        if (result_type && type_is_float(result_type) && expr->const_value.type == INT_LITERAL) {
            expr->const_value.type = FLOAT_LITERAL;
            expr->const_value.value.float_val = (double)expr->const_value.value.int_val;
        }
    }
    return result_type;
}
static Type* check_member_expr(TypeCheckContext *ctx, Scope *scope, AstNode *expr) {
    AstMemberExpr *member_expr = &expr->data.member_expr;
    member_expr->symbol = ((void*)0);
    Type *target_type = check_expression(ctx, scope, member_expr->target, ((void*)0));
    if (member_expr->target->node_type == AST_IDENTIFIER || member_expr->target->node_type == AST_MEMBER_EXPR) {
        Symbol *target_sym = ((void*)0);
        if (member_expr->target->node_type == AST_IDENTIFIER) {
            target_sym = scope_lookup_symbol(scope, member_expr->target->data.identifier.intern_result, ctx->filename);
        } else {
            target_sym = member_expr->target->data.member_expr.symbol;
        }
        if (target_sym && (target_sym->kind == SYMBOL_VALUE_MODULE || target_sym->kind == SYMBOL_VALUE_NAMESPACE)) {
            Symbol *member_sym = scope_lookup_symbol_local(target_sym->module_scope, member_expr->member);
            if (!member_sym || !member_sym->is_pub) {
                const char *field_name = "<unknown>";
                if (member_expr->member && member_expr->member->key) {
                    field_name = ((Slice*)member_expr->member->key)->ptr;
                }
                TypeError err = { .kind = TE_UNDECLARED, .span = expr->span, .filename = ctx->filename };
                err.as.name.name = field_name;
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
            member_expr->symbol = member_sym;
            expr->type = member_sym->type;
            return expr->type;
        }
    }
    if (!target_type) return ((void*)0);
    Type *underlying = target_type;
    if (underlying->kind == TYPE_POINTER) {
        underlying = underlying->as.ptr.base;
    }
    switch (underlying->kind) {
        case TYPE_ARRAY:
            if (member_expr->member == ctx->store->kw_len) {
                expr->node_type = AST_LITERAL;
                expr->data.literal.type = INT_LITERAL;
                expr->data.literal.value.int_val = underlying->as.array.size;
                expr->is_foldable_const = 1;
                expr->is_llvm_const_safe = 1;
                expr->const_value.type = INT_LITERAL;
                expr->const_value.value.int_val = underlying->as.array.size;
                expr->type = ctx->store->t_i64;
                return ctx->store->t_i64;
            } else {
                const char *field_name = "<unknown>";
                if (member_expr->member && member_expr->member->key) {
                    field_name = ((Slice*)member_expr->member->key)->ptr;
                }
                TypeError err = { .kind = TE_FIELD_ACCESS, .span = expr->span, .filename = ctx->filename };
                err.as.field.name = field_name;
                err.as.field.type = underlying;
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
        case TYPE_SLICE:
            if (member_expr->member == ctx->store->kw_len) {
                return ctx->store->t_i64;
            } else {
                const char *field_name = "<unknown>";
                if (member_expr->member && member_expr->member->key) {
                    field_name = ((Slice*)member_expr->member->key)->ptr;
                }
                TypeError err = { .kind = TE_FIELD_ACCESS, .span = expr->span, .filename = ctx->filename };
                err.as.field.name = field_name;
                err.as.field.type = underlying;
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
        case TYPE_STRUCT: {
            for (size_t i = 0; i < underlying->as.struct_type.field_count; i++) {
                if (underlying->as.struct_type.fields[i].name == member_expr->member) {
                    return underlying->as.struct_type.fields[i].type;
                }
            }
            const char *field_name = "<unknown>";
            if (member_expr->member && member_expr->member->key) {
                field_name = ((Slice*)member_expr->member->key)->ptr;
            }
            TypeError err = { .kind = TE_FIELD_ACCESS, .span = expr->span, .filename = ctx->filename };
            err.as.field.name = field_name;
            err.as.field.type = underlying;
            dynarray_push_value(ctx->errors, &err);
            return ((void*)0);
        }
        default:
            {
                TypeError err = { .kind = TE_NOT_MEMBER_ACCESSIBLE, .span = member_expr->target->span, .filename = ctx->filename, .as.bad_usage.actual = target_type };
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
    }
}
static Type* check_cast(TypeCheckContext *ctx, Scope *scope, AstNode *expr) {
    AstCastExpr *cast = &expr->data.cast_expr;
    if (cast->target_type_node) {
        cast->target_type = resolve_ast_type(ctx, scope, cast->target_type_node);
    }
    if (!cast->target_type) return ((void*)0);
    Type *src_type = check_expression(ctx, scope, cast->expr, ((void*)0));
    if (!src_type) return ((void*)0);
    if (!type_can_explicit_cast(cast->target_type, src_type)) {
        TypeError err = {
            .kind = TE_TYPE_MISMATCH,
            .span = expr->span,
            .filename = ctx->filename,
            .as.mismatch = { .expected = cast->target_type, .actual = src_type }
        };
        dynarray_push_value(ctx->errors, &err);
        return ((void*)0);
    }
    fold_cast_node(expr);
    return cast->target_type;
}
Type* check_expression(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type) {
    if (!expr) return ((void*)0);
    Type *result_type = ((void*)0);
    expr->is_foldable_const = 0;
    expr->is_llvm_const_safe = 0;
    switch (expr->node_type) {
        case AST_LITERAL:
            result_type = check_literal(ctx, expr, expected_type);
            break;
        case AST_IDENTIFIER:
            result_type = check_identifier(ctx, scope, expr);
            break;
        case AST_CALL_EXPR:
            result_type = check_call_expr(ctx, scope, expr);
            break;
        case AST_SUBSCRIPT_EXPR:
            result_type = check_subscript(ctx, scope, expr, expected_type);
            break;
        case AST_MEMBER_EXPR:
            result_type = check_member_expr(ctx, scope, expr);
            break;
        case AST_STRUCT_LITERAL:
            result_type = check_struct_literal(ctx, scope, expr, expected_type);
            break;
        case AST_BINARY_EXPR:
            result_type = check_binary(ctx, scope, expr, expected_type);
            break;
        case AST_UNARY_EXPR:
            result_type = check_unary(ctx, scope, expr, expected_type);
            break;
        case AST_ASSIGNMENT_EXPR:
            result_type = check_assignment(ctx, scope, expr);
            break;
        case AST_INITIALIZER_LIST:
            result_type = check_initializer_list(ctx, scope, expr, expected_type);
            break;
        case AST_CAST:
            result_type = check_cast(ctx, scope, expr);
            break;
        case AST_INTRINSIC:
            result_type = check_intrinsic(ctx, scope, expr, expected_type);
            break;
        default: break;
    }
    expr->type = result_type;
    return result_type;
}
size_t struct_field_index(Type *struct_type, const char *field_name);
size_t get_struct_field_index(Type *struct_type, InternResult *field_name);
static void check_statement(TypeCheckContext *ctx, Scope *scope, AstNode *stmt, Type *return_type);
static void check_block(TypeCheckContext *ctx, Scope *parent, AstNode *block_node, Type *return_type, _Bool create_new_scope);
static void validate_allocator_struct(TypeCheckContext *ctx, Scope *global_scope) {
    Slice name = { .ptr = "Allocator", .len = 9 };
    InternResult *res = intern_peek(ctx->identifiers, &name);
    if (!res) return;
    Symbol *sym = scope_lookup_symbol_local(global_scope, res);
    if (!sym || sym->kind != SYMBOL_VALUE_TYPE) return;
    if (sym->decl_node && sym->decl_node->filename && ctx->filename) {
        if (strcmp(sym->decl_node->filename, ctx->filename) != 0) return;
    }
    Type *t = sym->type;
    if (!t || t->kind != TYPE_STRUCT) return;
    if (t->as.struct_type.field_count != 3) {
        TypeError err = { .kind = TE_INCOMPLETE_TYPE, .span = sym->decl_node->span, .filename = ctx->filename,
                          .as.name.name = "Allocator struct must have exactly 3 fields: ctx, alloc, free" };
        dynarray_push_value(ctx->errors, &err);
        return;
    }
    const char *expected_fields[] = {"ctx", "alloc", "free"};
    for (int i = 0; i < 3; i++) {
        StructField *field = &t->as.struct_type.fields[i];
        if (!field->name || !field->name->key) {
             TypeError err = { .kind = TE_INCOMPLETE_TYPE, .span = sym->decl_node->span, .filename = ctx->filename,
                              .as.name.name = "Allocator struct fields must have names" };
            dynarray_push_value(ctx->errors, &err);
            return;
        }
        Slice *field_name = (Slice*)field->name->key;
        if (strncmp(field_name->ptr, expected_fields[i], field_name->len) != 0 || expected_fields[i][field_name->len] != '\0') {
            TypeError err = { .kind = TE_INCOMPLETE_TYPE, .span = sym->decl_node->span, .filename = ctx->filename,
                              .as.name.name = "Allocator struct fields must be named: ctx, alloc, free" };
            dynarray_push_value(ctx->errors, &err);
            return;
        }
    }
    StructField *ctx_field = &t->as.struct_type.fields[0];
    StructField *alloc_field = &t->as.struct_type.fields[1];
    StructField *free_field = &t->as.struct_type.fields[2];
    if (!ctx_field->type || ctx_field->type->kind != TYPE_POINTER) {
        TypeError err = { .kind = TE_TYPE_MISMATCH, .span = sym->decl_node->span, .filename = ctx->filename,
                          .as.name.name = "Allocator field 'ctx' must be a pointer" };
        dynarray_push_value(ctx->errors, &err);
    }
    if (!alloc_field->type || alloc_field->type->kind != TYPE_FUNCTION) {
        TypeError err = { .kind = TE_TYPE_MISMATCH, .span = sym->decl_node->span, .filename = ctx->filename,
                          .as.name.name = "Allocator field 'alloc' must be a function" };
        dynarray_push_value(ctx->errors, &err);
    } else {
        Type *alloc_ty = alloc_field->type;
        if (alloc_ty->as.func.param_count != 2 ||
            alloc_ty->as.func.params[0]->kind != TYPE_POINTER ||
            (alloc_ty->as.func.params[1]->kind != TYPE_PRIMITIVE || alloc_ty->as.func.params[1]->as.primitive != PRIM_I64) ||
            alloc_ty->as.func.return_type->kind != TYPE_POINTER) {
            TypeError err = { .kind = TE_TYPE_MISMATCH, .span = sym->decl_node->span, .filename = ctx->filename,
                              .as.name.name = "Allocator field 'alloc' must have signature: fn(ptr, i64) -> ptr" };
            dynarray_push_value(ctx->errors, &err);
        }
    }
    if (!free_field->type || free_field->type->kind != TYPE_FUNCTION) {
        TypeError err = { .kind = TE_TYPE_MISMATCH, .span = sym->decl_node->span, .filename = ctx->filename,
                          .as.name.name = "Allocator field 'free' must be a function" };
        dynarray_push_value(ctx->errors, &err);
    } else {
        Type *free_ty = free_field->type;
        if (free_ty->as.func.param_count != 2 ||
            free_ty->as.func.params[0]->kind != TYPE_POINTER ||
            free_ty->as.func.params[1]->kind != TYPE_POINTER ||
            !type_is_void(free_ty->as.func.return_type)) {
            TypeError err = { .kind = TE_TYPE_MISMATCH, .span = sym->decl_node->span, .filename = ctx->filename,
                              .as.name.name = "Allocator field 'free' must have signature: fn(ptr, ptr) -> void" };
            dynarray_push_value(ctx->errors, &err);
        }
    }
}
TypeCheckContext typecheck_context_create(Arena *arena, TypeStore *store, DenseArenaInterner *identifiers, DenseArenaInterner *keywords, const char *filename, ModuleLoader *loader) {
    DynArray *errors = arena_alloc(arena, sizeof(DynArray));
    dynarray_init_in_arena(errors, arena, sizeof(TypeError), 8);
    TypeCheckContext ctx = {
        .program = ((void*)0),
        .store = store,
        .identifiers = identifiers,
        .keywords = keywords,
        .filename = filename,
        .errors = errors,
        .loader = loader
    };
    return ctx;
}
static void patch_inferred_array_sizes(TypeCheckContext *ctx, AstNode *type_ast, Type *concrete_type) {
    if (!type_ast || !concrete_type) return;
    if (type_ast->node_type != AST_TYPE) return;
    if (type_ast->data.ast_type.kind == AST_TYPE_ARRAY) {
        if (concrete_type->kind == TYPE_ARRAY) {
            patch_inferred_array_sizes(ctx,
                type_ast->data.ast_type.u.array.elem,
                concrete_type->as.array.base
            );
            if (!type_ast->data.ast_type.u.array.size_expr) {
                AstNode *size_lit = ast_create_node(AST_LITERAL, ctx->store->arena, ctx->filename);
                if (size_lit) {
                    size_lit->node_type = AST_LITERAL;
                    size_lit->span = type_ast->span;
                    size_lit->type = ctx->store->t_i64;
                    size_lit->is_foldable_const = 1;
                    size_lit->is_llvm_const_safe = 1;
                    size_lit->data.literal.type = INT_LITERAL;
                    size_lit->data.literal.value.int_val = (int64_t)concrete_type->as.array.size;
                    size_lit->const_value.type = INT_LITERAL;
                    size_lit->const_value.value.int_val = (int64_t)concrete_type->as.array.size;
                    type_ast->data.ast_type.u.array.size_expr = size_lit;
                }
            }
        } else if (concrete_type->kind == TYPE_SLICE) {
            patch_inferred_array_sizes(ctx,
                type_ast->data.ast_type.u.array.elem,
                concrete_type->as.slice.base
            );
        }
    }
}
Type *resolve_ast_type(TypeCheckContext *ctx, Scope *scope, AstNode *node) {
    if (!ctx || !node) return ((void*)0);
    TypeStore *store = ctx->store;
    if (node->node_type == AST_IDENTIFIER) {
        Symbol *sym = scope_lookup_symbol(scope, node->data.identifier.intern_result, ctx->filename);
        if (sym) {
            if (sym->kind == SYMBOL_VALUE_TYPE) return sym->type;
            if (sym->kind == SYMBOL_VALUE_ALIAS) {
                Symbol *target = sym->target_symbol;
                while (target && target->kind == SYMBOL_VALUE_ALIAS) target = target->target_symbol;
                if (target && target->kind == SYMBOL_VALUE_TYPE) return target->type;
            }
        }
        Type *prim = (Type*)hashmap_get(store->primitive_registry, node->data.identifier.intern_result->key, ptr_hash, ptr_cmp);
        if (prim) return prim;
        return ((void*)0);
    }
    if (node->node_type == AST_MEMBER_EXPR) {
        check_expression(ctx, scope, node, ((void*)0));
        Symbol *sym = node->data.member_expr.symbol;
        if (sym) {
            Symbol *curr = sym;
            while (curr && curr->kind == SYMBOL_VALUE_ALIAS) curr = curr->target_symbol;
            if (curr && curr->kind == SYMBOL_VALUE_TYPE) return curr->type;
        }
        return ((void*)0);
    }
    if (node->node_type != AST_TYPE) return ((void*)0);
    AstType *ast_ty = &node->data.ast_type;
    switch (ast_ty->kind) {
        case AST_TYPE_PRIMITIVE: {
            if (ast_ty->u.base.path) {
                AstNode *path = ast_ty->u.base.path;
                check_expression(ctx, scope, path, ((void*)0));
                Symbol *sym = ((void*)0);
                if (path->node_type == AST_MEMBER_EXPR) sym = path->data.member_expr.symbol;
                else if (path->node_type == AST_IDENTIFIER) sym = path->data.identifier.symbol;
                if (sym) {
                    Symbol *curr = sym;
                    while (curr && curr->kind == SYMBOL_VALUE_ALIAS) curr = curr->target_symbol;
                    if (curr && curr->kind == SYMBOL_VALUE_TYPE) return curr->type;
                }
                TypeError err = { .kind = TE_UNKNOWN_TYPE, .span = node->span, .filename = ctx->filename, .as.name.name = "Path does not resolve to a type" };
                dynarray_push_value(ctx->errors, &err);
                return ((void*)0);
            }
            InternResult *name_res = ast_ty->u.base.intern_result;
            if (name_res && name_res->key) {
                Type *prim = (Type*)hashmap_get(store->primitive_registry, name_res->key, ptr_hash, ptr_cmp);
                if (prim) return prim;
                if (scope) {
                    Symbol *sym = scope_lookup_symbol(scope, name_res, ctx->filename);
                    if (sym) {
                        if (sym->kind == SYMBOL_VALUE_TYPE) return sym->type;
                        if (sym->kind == SYMBOL_VALUE_ALIAS) {
                             Symbol *target = sym->target_symbol;
                             while (target && target->kind == SYMBOL_VALUE_ALIAS) target = target->target_symbol;
                             if (target && target->kind == SYMBOL_VALUE_TYPE) return target->type;
                        }
                    }
                }
                const char *name_str = ((Slice*)name_res->key)->ptr;
                TypeError err = { .kind = TE_UNKNOWN_TYPE, .span = node->span, .filename = ctx->filename, .as.name.name = name_str };
                dynarray_push_value(ctx->errors, &err);
            }
            return ((void*)0);
        }
        case AST_TYPE_PTR: {
            Type *target = resolve_ast_type(ctx, scope, ast_ty->u.ptr.target);
            if (!target) return ((void*)0);
            Type proto = { .kind = TYPE_POINTER, .as.ptr.base = target };
            InternResult *res = intern_type(store, &proto);
            return res ? (Type*)((Slice*)res->key)->ptr : ((void*)0);
        }
        case AST_TYPE_ARRAY: {
            Type *elem = resolve_ast_type(ctx, scope, ast_ty->u.array.elem);
            if (!elem) return ((void*)0);
            int64_t size = 0;
            _Bool size_known = 0;
            AstNode *sz = ast_ty->u.array.size_expr;
            if (sz) {
                Type *sz_type = check_expression(ctx, scope, sz, store->t_i64);
                if (sz_type) {
                    if (!type_is_integer(sz_type)) {
                        TypeError err = { .kind = TE_TYPE_MISMATCH, .span = sz->span, .filename = ctx->filename, .as.mismatch = { .expected = store->t_i64, .actual = sz_type } };
                        dynarray_push_value(ctx->errors, &err);
                        return ((void*)0);
                    }
                    if (!sz->is_foldable_const) {
                        TypeError err = { .kind = TE_NOT_CONST, .span = sz->span, .filename = ctx->filename };
                        dynarray_push_value(ctx->errors, &err);
                        return ((void*)0);
                    }
                    size = sz->const_value.value.int_val;
                    size_known = 1;
                } else {
                    return ((void*)0);
                }
            }
            Type proto = {0};
            if (size_known) {
                proto.kind = TYPE_ARRAY;
                proto.as.array.base = elem;
                proto.as.array.size = size;
            } else {
                proto.kind = TYPE_SLICE;
                proto.as.slice.base = elem;
            }
            InternResult *res = intern_type(store, &proto);
            return res ? (Type*)((Slice*)res->key)->ptr : ((void*)0);
        }
        case AST_TYPE_FUNC: {
             Type *ret = resolve_ast_type(ctx, scope, ast_ty->u.func.return_type);
             if (!ret) ret = store->t_void;
             DynArray *params = ast_ty->u.func.param_types;
             size_t count = params ? params->count : 0;
             Type **param_types = ((void*)0);
             if (count > 0) {
                 if (count <= 64) param_types = __builtin_alloca(sizeof(Type*) * count);
                 else param_types = xmalloc(sizeof(Type*) * count);
             }
             for (size_t i = 0; i < count; i++) {
                 AstNode *p_node = (((AstNode**)(params)->data)[i]);
                 Type *pt = resolve_ast_type(ctx, scope, p_node);
                 if (!pt) {
                     if (count > 64) free(param_types);
                     return ((void*)0);
                 }
                 param_types[i] = pt;
             }
             Type proto = { .kind = TYPE_FUNCTION, .as.func.return_type = ret, .as.func.param_count = count, .as.func.params = param_types };
             InternResult *res = intern_type(store, &proto);
             if (count > 64) free(param_types);
             return res ? (Type*)((Slice*)res->key)->ptr : ((void*)0);
        }
    }
    return ((void*)0);
}
static void resolve_function_decl(TypeCheckContext *ctx, Scope *scope, AstNode *func_node) {
    if (func_node->node_type != AST_FUNCTION_DECLARATION) return;
    AstFunctionDeclaration *decl = &func_node->data.function_declaration;
    Type *ret_type = resolve_ast_type(ctx, scope, decl->return_type);
    if (!ret_type) ret_type = ctx->store->t_void;
    size_t param_count = decl->params ? decl->params->count : 0;
    Type **param_types = ((void*)0);
    if (param_count > 0) param_types = xmalloc(sizeof(Type*) * param_count);
    for (size_t i = 0; i < param_count; i++) {
        AstNode *param_node = *(AstNode**)dynarray_get(decl->params, i);
        Type *pt = resolve_ast_type(ctx, scope, param_node->data.param.type);
        if (!pt) pt = ctx->store->t_void;
        if (type_is_void(pt)) {
            TypeError err = { .kind = TE_TYPE_MISMATCH, .span = param_node->span, .filename = ctx->filename, .as.name.name = "Parameter cannot have type 'void'" };
            dynarray_push_value(ctx->errors, &err);
        }
        param_types[i] = pt;
        param_node->type = pt;
    }
    Type proto = {0};
    proto.kind = TYPE_FUNCTION;
    proto.as.func.return_type = ret_type;
    proto.as.func.param_count = param_count;
    proto.as.func.params = param_types;
    InternResult *res = intern_type(ctx->store, &proto);
    if (res) func_node->type = (Type*)((Slice*)res->key)->ptr;
    free(param_types);
}
static _Bool check_struct_cycle(TypeCheckContext *ctx, Type *t, DynArray *path) {
    if (!t || t->kind != TYPE_STRUCT) return 0;
    for (size_t i = 0; i < path->count; i++) {
        if (*(Type**)dynarray_get(path, i) == t) return 1;
    }
    dynarray_push_value(path, &t);
    for (size_t i = 0; i < t->as.struct_type.field_count; i++) {
        Type *ft = t->as.struct_type.fields[i].type;
        if (!ft) continue;
        if (ft->kind == TYPE_STRUCT) {
            if (check_struct_cycle(ctx, ft, path)) return 1;
        } else if (ft->kind == TYPE_ARRAY) {
            Type *base = ft->as.array.base;
            while (base && base->kind == TYPE_ARRAY) base = base->as.array.base;
            if (base && base->kind == TYPE_STRUCT) {
                if (check_struct_cycle(ctx, base, path)) return 1;
            }
        }
    }
    dynarray_pop(path);
    return 0;
}
static void register_program_structs(TypeCheckContext *ctx, Scope *global_scope) {
    if (!ctx || !ctx->program) return;
    AstProgram *program = &ctx->program->data.program;
    if (!program->decls) return;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl || decl->node_type != AST_STRUCT_DECLARATION) continue;
        ctx->filename = decl->filename;
        AstStructDeclaration *struct_decl = &decl->data.struct_declaration;
        if (!struct_decl->intern_result) continue;
        if (scope_lookup_symbol_local(global_scope, struct_decl->intern_result)) continue;
        Type *struct_type = arena_alloc(ctx->store->arena, sizeof(Type));
        struct_type->kind = TYPE_STRUCT;
        struct_type->as.struct_type.name = struct_decl->intern_result;
        struct_type->as.struct_type.field_count = struct_decl->fields ? struct_decl->fields->count : 0;
        struct_type->as.struct_type.fields = ((void*)0);
        decl->type = struct_type;
        define_symbol_or_error(ctx, global_scope, struct_decl->intern_result, decl->type, SYMBOL_VALUE_TYPE, decl->span, struct_decl->is_pub, decl->filename, decl);
    }
}
static void register_program_globals(TypeCheckContext *ctx, Scope *global_scope) {
    if (!ctx || !ctx->program) return;
    AstProgram *program = &ctx->program->data.program;
    if (!program->decls) return;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl || decl->node_type != AST_VARIABLE_DECLARATION) continue;
        ctx->filename = decl->filename;
        AstVariableDeclaration *var_decl = &decl->data.variable_declaration;
        if (var_decl->intern_result && !scope_lookup_symbol_local(global_scope, var_decl->intern_result)) {
            define_symbol_or_error(ctx, global_scope, var_decl->intern_result, ((void*)0), SYMBOL_VARIABLE, decl->span, var_decl->is_pub, decl->filename, decl);
        }
    }
}
static void register_program_functions(TypeCheckContext *ctx, Scope *global_scope) {
    if (!ctx || !ctx->program) return;
    AstProgram *program = &ctx->program->data.program;
    if (!program->decls) return;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl || decl->node_type != AST_FUNCTION_DECLARATION) continue;
        ctx->filename = decl->filename;
        AstFunctionDeclaration *func = &decl->data.function_declaration;
        if (func->intern_result && !scope_lookup_symbol_local(global_scope, func->intern_result)) {
            define_symbol_or_error(ctx, global_scope, func->intern_result, ((void*)0), SYMBOL_VALUE_FUNCTION, decl->span, func->is_pub, decl->filename, decl);
        }
    }
}
static void register_program_aliases(TypeCheckContext *ctx, Scope *global_scope) {
    if (!ctx || !ctx->program) return;
    AstProgram *program = &ctx->program->data.program;
    if (!program->decls) return;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl || decl->node_type != AST_ALIAS_DECLARATION) continue;
        ctx->filename = decl->filename;
        AstAliasDeclaration *alias = &decl->data.alias_declaration;
        if (alias->alias_name && !scope_lookup_symbol_local(global_scope, alias->alias_name)) {
            scope_define_symbol(global_scope, alias->alias_name, ((void*)0), SYMBOL_VALUE_ALIAS, decl->filename, 0, decl);
        }
    }
}
static void resolve_program_structs(TypeCheckContext *ctx, Scope *global_scope) {
    if (!ctx || !ctx->program) return;
    AstProgram *program = &ctx->program->data.program;
    if (!program->decls) return;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl || decl->node_type != AST_STRUCT_DECLARATION) continue;
        ctx->filename = decl->filename;
        AstStructDeclaration *struct_decl = &decl->data.struct_declaration;
        Type *struct_type = decl->type;
        if (!struct_type || !struct_decl->fields) continue;
        if (struct_type->as.struct_type.fields) continue;
        struct_type->as.struct_type.fields = arena_alloc(ctx->store->arena, sizeof(StructField) * struct_type->as.struct_type.field_count);
        struct_type->as.struct_type.field_map = hashmap_create(struct_type->as.struct_type.field_count);
        for (size_t j = 0; j < struct_type->as.struct_type.field_count; j++) {
            AstFieldDecl *fdecl = (AstFieldDecl*)dynarray_get(struct_decl->fields, j);
            struct_type->as.struct_type.fields[j].name = fdecl->name;
            struct_type->as.struct_type.fields[j].type = resolve_ast_type(ctx, global_scope, fdecl->type);
            hashmap_put(struct_type->as.struct_type.field_map, fdecl->name->key, (void*)(uintptr_t)(j + 1), ptr_hash, ptr_cmp);
        }
    }
    DynArray path;
    dynarray_init(&path, sizeof(Type*));
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl || decl->node_type != AST_STRUCT_DECLARATION) continue;
        ctx->filename = decl->filename;
        path.count = 0;
        if (check_struct_cycle(ctx, decl->type, &path)) {
            TypeError err = { .kind = TE_INCOMPLETE_TYPE, .span = decl->span, .filename = ctx->filename };
            err.as.name.name = "Recursive struct definition (infinite size)";
            dynarray_push_value(ctx->errors, &err);
        }
    }
    dynarray_free(&path);
}
static void resolve_program_globals(TypeCheckContext *ctx, Scope *global_scope) {
    if (!ctx || !ctx->program) return;
    AstProgram *program = &ctx->program->data.program;
    if (!program->decls) return;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl || decl->node_type != AST_VARIABLE_DECLARATION) continue;
        ctx->filename = decl->filename;
        AstVariableDeclaration *var_decl = &decl->data.variable_declaration;
        Type *var_type = resolve_ast_type(ctx, global_scope, var_decl->type);
        if (!var_type) continue;
        decl->type = var_type;
        Symbol *sym = scope_lookup_symbol_local(global_scope, var_decl->intern_result);
        if (sym) {
            sym->type = var_type;
            if (var_decl->is_const) sym->flags |= SYMBOL_FLAG_CONST;
        }
    }
}
static void resolve_program_functions(TypeCheckContext *ctx, Scope *global_scope) {
    if (!ctx || !ctx->program) return;
    AstProgram *program = &ctx->program->data.program;
    if (!program->decls) return;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl || decl->node_type != AST_FUNCTION_DECLARATION) continue;
        ctx->filename = decl->filename;
        AstFunctionDeclaration *func = &decl->data.function_declaration;
        resolve_function_decl(ctx, global_scope, decl);
        Symbol *sym = scope_lookup_symbol_local(global_scope, func->intern_result);
        if (sym) {
            sym->type = decl->type;
        }
    }
}
static void resolve_program_aliases(TypeCheckContext *ctx, Scope *global_scope) {
    if (!ctx || !ctx->program) return;
    AstProgram *program = &ctx->program->data.program;
    if (!program->decls) return;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl || decl->node_type != AST_ALIAS_DECLARATION) continue;
        ctx->filename = decl->filename;
        AstAliasDeclaration *alias = &decl->data.alias_declaration;
        Symbol *my_alias_sym = scope_lookup_symbol_local(global_scope, alias->alias_name);
        if (!my_alias_sym) continue;
        Symbol *target_sym = ((void*)0);
        if (alias->target->node_type == AST_IDENTIFIER) {
            target_sym = scope_lookup_symbol(global_scope, alias->target->data.identifier.intern_result, ctx->filename);
        } else if (alias->target->node_type == AST_MEMBER_EXPR) {
            check_expression(ctx, global_scope, alias->target, ((void*)0));
            if (alias->target->node_type == AST_MEMBER_EXPR) {
                target_sym = alias->target->data.member_expr.symbol;
            } else if (alias->target->node_type == AST_IDENTIFIER) {
                target_sym = alias->target->data.identifier.symbol;
            }
        } else {
             TypeError err = { .kind = TE_TYPE_MISMATCH, .span = alias->target->span, .filename = ctx->filename };
             err.as.name.name = "Alias target must be a symbol or path";
             dynarray_push_value(ctx->errors, &err);
             continue;
        }
        if (!target_sym) {
             TypeError err = { .kind = TE_UNDECLARED, .span = alias->target->span, .filename = ctx->filename };
             err.as.name.name = "Could not resolve alias target";
             dynarray_push_value(ctx->errors, &err);
             continue;
        }
        my_alias_sym->target_symbol = target_sym;
        my_alias_sym->type = target_sym->type;
    }
}
static void check_initializer(TypeCheckContext *ctx, Scope *scope, AstNode *var_node, AstNode *initializer, Type *var_type, Symbol *sym) {
    if (!initializer) return;
    Type *actual_type = check_expression(ctx, scope, initializer, var_type);
    if (!actual_type) return;
    if (actual_type && var_type && actual_type != var_type) {
        _Bool is_inference = (var_type->kind == TYPE_SLICE && actual_type->kind == TYPE_ARRAY &&
                             var_type->as.slice.base == actual_type->as.array.base &&
                             initializer->node_type == AST_INITIALIZER_LIST);
        if (is_inference) {
            var_node->type = actual_type;
            if (sym) sym->type = actual_type;
            if (var_node->node_type == AST_VARIABLE_DECLARATION) {
                patch_inferred_array_sizes(ctx, var_node->data.variable_declaration.type, actual_type);
            }
            return;
        }
        coerce_or_error(ctx, initializer, var_type);
    }
}
static _Bool is_type_complete(Type *t) {
    if (!t) return 0;
    if (t->kind == TYPE_ARRAY) {
        return is_type_complete(t->as.array.base);
    }
    return 1;
}
void check_variable_declaration(TypeCheckContext *ctx, Scope *scope, AstNode *var_node) {
    if (var_node->node_type != AST_VARIABLE_DECLARATION) return;
    if (var_node->last_checked_pass == ctx->current_pass) return;
    const char *old_filename = ctx->filename;
    ctx->filename = var_node->filename;
    AstVariableDeclaration *var_decl = &var_node->data.variable_declaration;
    Symbol *existing = scope_lookup_symbol_local(scope, var_decl->intern_result);
    _Bool is_us = (existing && existing->decl_node == var_node);
    if (is_us && (existing->flags & SYMBOL_FLAG_INITIALIZED)) {
        var_node->last_checked_pass = ctx->current_pass;
        ctx->filename = old_filename;
        return;
    }
    if (is_us && (existing->flags & SYMBOL_FLAG_COMPUTING)) {
        TypeError err = { .kind = TE_RECURSIVE_CONST, .span = var_node->span, .filename = ctx->filename };
        dynarray_push_value(ctx->errors, &err);
        ctx->filename = old_filename;
        return;
    }
    Symbol *my_sym = is_us ? existing : ((void*)0);
    Type *var_type = my_sym ? my_sym->type : resolve_ast_type(ctx, scope, var_decl->type);
    if (!var_type) {
        ctx->filename = old_filename;
        return;
    }
    if (type_is_void(var_type)) {
        TypeError err = {
            .kind = TE_TYPE_MISMATCH,
            .span = var_node->span,
            .filename = ctx->filename,
            .as.name.name = "Variable cannot have type 'void'"
        };
        dynarray_push_value(ctx->errors, &err);
        ctx->filename = old_filename;
        return;
    }
    if (!var_decl->initializer) {
        if (!is_type_complete(var_type)) {
            TypeError err = {
                .kind = TE_INCOMPLETE_TYPE,
                .span = var_node->span,
                .filename = ctx->filename,
                .as.name.name = "Variable declared with incomplete type (missing array size)"
            };
            dynarray_push_value(ctx->errors, &err);
        }
    }
    var_node->type = var_type;
    _Bool is_global = (scope->depth <= 1);
    if (is_global) {
        if (!my_sym) {
            define_symbol_or_error(ctx, scope, var_decl->intern_result, var_type, SYMBOL_VARIABLE, var_node->span, var_decl->is_pub, var_node->filename, var_node);
            my_sym = scope_lookup_symbol_local(scope, var_decl->intern_result);
            if (my_sym && my_sym->decl_node != var_node) my_sym = ((void*)0);
        }
        if (my_sym) {
            my_sym->flags |= SYMBOL_FLAG_COMPUTING;
            check_initializer(ctx, scope, var_node, var_decl->initializer, var_type, my_sym);
            my_sym->flags &= ~SYMBOL_FLAG_COMPUTING;
            my_sym->flags |= SYMBOL_FLAG_INITIALIZED;
        } else {
            check_initializer(ctx, scope, var_node, var_decl->initializer, var_type, ((void*)0));
        }
    } else {
        check_initializer(ctx, scope, var_node, var_decl->initializer, var_type, ((void*)0));
        define_symbol_or_error(ctx, scope, var_decl->intern_result, var_type, SYMBOL_VARIABLE, var_node->span, var_decl->is_pub, var_node->filename, var_node);
        my_sym = scope_lookup_symbol_local(scope, var_decl->intern_result);
        if (my_sym && my_sym->decl_node != var_node) my_sym = ((void*)0);
        if (my_sym) my_sym->flags |= SYMBOL_FLAG_INITIALIZED;
    }
    if (my_sym && var_decl->is_const && var_decl->initializer && var_decl->initializer->is_foldable_const) {
        my_sym->flags |= SYMBOL_FLAG_CONST | SYMBOL_FLAG_COMPUTED_VALUE;
        ConstValue *cv = &var_decl->initializer->const_value;
        switch (cv->type) {
            case INT_LITERAL: my_sym->value.int_val = cv->value.int_val; break;
            case FLOAT_LITERAL: my_sym->value.float_val = cv->value.float_val; break;
            case BOOL_LITERAL: my_sym->value.bool_val = (_Bool)cv->value.bool_val; break;
            case CHAR_LITERAL: my_sym->value.int_val = (int64_t)cv->value.char_val; break;
            default: break;
        }
    }
    var_node->last_checked_pass = ctx->current_pass;
    ctx->filename = old_filename;
}
static void check_block(TypeCheckContext *ctx, Scope *parent, AstNode *block_node, Type *return_type, _Bool create_new_scope) {
    if (block_node->node_type != AST_BLOCK) return;
    Scope *scope = parent;
    if (create_new_scope) scope = scope_create(ctx->store->arena, parent, 16, SCOPE_IDENTIFIERS);
    AstBlock *b = &block_node->data.block;
    if (!b->statements) return;
    for (size_t i = 0; i < b->statements->count; i++) {
        AstNode *stmt = (((AstNode**)(b->statements)->data)[i]);
        check_statement(ctx, scope, stmt, return_type);
    }
}
static void check_statement(TypeCheckContext *ctx, Scope *scope, AstNode *stmt, Type *return_type) {
    if (!stmt) return;
    switch (stmt->node_type) {
        case AST_RETURN_STATEMENT: {
            AstReturnStatement *ret = &stmt->data.return_statement;
            Type *actual = ctx->store->t_void;
            if (ret->expression) actual = check_expression(ctx, scope, ret->expression, return_type);
            if (actual && return_type && actual != return_type) {
                 coerce_or_error(ctx, ret->expression, return_type);
            }
            break;
        }
        case AST_DEFER_STATEMENT: {
            check_statement(ctx, scope, stmt->data.defer_statement.body, return_type);
            break;
        }
        case AST_BLOCK:
            check_block(ctx, scope, stmt, return_type, 1);
            break;
        case AST_VARIABLE_DECLARATION:
            check_variable_declaration(ctx, scope, stmt);
            break;
        case AST_IF_STATEMENT: {
            AstIfStatement *ifs = &stmt->data.if_statement;
            check_expression(ctx, scope, ifs->condition, ctx->store->t_bool);
            check_statement(ctx, scope, ifs->then_branch, return_type);
            if (ifs->else_branch) check_statement(ctx, scope, ifs->else_branch, return_type);
            break;
        }
        case AST_WHILE_STATEMENT: {
            AstWhileStatement *ws = &stmt->data.while_statement;
            check_expression(ctx, scope, ws->condition, ctx->store->t_bool);
            check_statement(ctx, scope, ws->body, return_type);
            break;
        }
        case AST_FOR_STATEMENT: {
            AstForStatement *fs = &stmt->data.for_statement;
            Scope *for_scope = scope_create(ctx->store->arena, scope, 8, SCOPE_IDENTIFIERS);
            if (fs->init) check_statement(ctx, for_scope, fs->init, return_type);
            if (fs->condition) check_expression(ctx, for_scope, fs->condition, ctx->store->t_bool);
            if (fs->post) check_expression(ctx, for_scope, fs->post, ((void*)0));
            check_statement(ctx, for_scope, fs->body, return_type);
            break;
        }
        case AST_EXPR_STATEMENT:
            check_expression(ctx, scope, stmt->data.expr_statement.expression, ((void*)0));
            break;
        case AST_ASSIGNMENT_EXPR:
        case AST_CALL_EXPR:
        case AST_UNARY_EXPR:
        case AST_INTRINSIC:
            check_expression(ctx, scope, stmt, ((void*)0));
            break;
        default:
            break;
    }
}
static void check_function(TypeCheckContext *ctx, Scope *parent_scope, AstNode *func_node) {
    const char *old_filename = ctx->filename;
    ctx->filename = func_node->filename;
    AstFunctionDeclaration *decl = &func_node->data.function_declaration;
    Type *func_type = func_node->type;
    Scope *fn_scope = scope_create(ctx->store->arena, parent_scope, 32, SCOPE_IDENTIFIERS);
    if (decl->params) {
        for (size_t i = 0; i < decl->params->count; i++) {
            AstNode *param = *(AstNode**)dynarray_get(decl->params, i);
            if (param->data.param.name_idx != -1) {
                InternResult *name_rec = interner_get_result(ctx->identifiers, param->data.param.name_idx);
                define_symbol_or_error(ctx, fn_scope, name_rec, param->type, SYMBOL_VARIABLE, param->span, 0, param->filename, param);
            }
        }
    }
    if (decl->body) {
        check_block(ctx, fn_scope, decl->body, func_type->as.func.return_type, 0);
    }
    func_node->last_checked_pass = ctx->current_pass;
    ctx->filename = old_filename;
}
static void resolve_imports(TypeCheckContext *ctx, CompilationUnit *unit) {
    if (!unit->ast_root) return;
    AstProgram *program = &unit->ast_root->data.program;
    if (!program->decls) return;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (decl->node_type != AST_IMPORT_DECLARATION) continue;
        AstImportDeclaration *import = &decl->data.import_declaration;
        const char *logical_path_str = import->resolved_logical_path;
        if (!logical_path_str) {
             char rebuilt[512] = {0};
             size_t r_len = 0;
             for (size_t j = 0; j < import->module_path->count; j++) {
                InternResult *part = *(InternResult**)dynarray_get(import->module_path, j);
                Slice *s = (Slice*)part->key;
                if (r_len + s->len + 1 < sizeof(rebuilt)) {
                    if (j > 0) rebuilt[r_len++] = '.';
                    __builtin___memcpy_chk (rebuilt + r_len, s->ptr, s->len, __builtin_object_size (rebuilt + r_len, 0));
                    r_len += s->len;
                }
             }
             rebuilt[r_len] = '\0';
             logical_path_str = rebuilt;
        }
        CompilationUnit *target = (CompilationUnit*)hashmap_get(ctx->loader->units_by_logical_path, (void*)logical_path_str, str_hash, str_cmp);
        if (!target) {
            TypeError err = { .kind = TE_UNDECLARED, .span = decl->span, .filename = unit->absolute_path };
            err.as.name.name = "Module not found";
            dynarray_push_value(ctx->errors, &err);
            continue;
        }
        Scope *current_bind_scope = unit->global_scope;
        for (size_t j = 0; j < import->module_path->count; j++) {
            InternResult *part = *(InternResult**)dynarray_get(import->module_path, j);
            _Bool is_last = (j == import->module_path->count - 1);
            if (is_last) {
                Symbol *mod_sym = scope_define_symbol(current_bind_scope, part, ((void*)0), SYMBOL_VALUE_MODULE, target->absolute_path, 1, ((void*)0));
                if (mod_sym) {
                    mod_sym->module_scope = target->global_scope;
                    if (current_bind_scope == unit->global_scope) {
                        mod_sym->is_pub = import->is_pub;
                    }
                }
            } else {
                Symbol *existing = scope_lookup_symbol_local(current_bind_scope, part);
                if (existing) {
                    if (existing->kind != SYMBOL_VALUE_MODULE && existing->kind != SYMBOL_VALUE_NAMESPACE) {
                         TypeError err = { .kind = TE_REDECLARATION, .span = decl->span, .filename = unit->absolute_path };
                         err.as.name.name = "Import path component conflicts with existing symbol";
                         dynarray_push_value(ctx->errors, &err);
                         break;
                    }
                    current_bind_scope = existing->module_scope;
                } else {
                    Symbol *ns_sym = scope_define_symbol(current_bind_scope, part, ((void*)0), SYMBOL_VALUE_NAMESPACE, ((void*)0), 1, ((void*)0));
                    ns_sym->module_scope = scope_create(ctx->store->arena, ((void*)0), 16, SCOPE_IDENTIFIERS);
                    if (current_bind_scope == unit->global_scope) {
                        ns_sym->is_pub = import->is_pub;
                    }
                    current_bind_scope = ns_sym->module_scope;
                }
            }
        }
        if (import->specific_symbols) {
            for (size_t j = 0; j < import->specific_symbols->count; j++) {
                ImportSymbol *sym_imp = *(ImportSymbol**)dynarray_get(import->specific_symbols, j);
                Symbol *target_sym = scope_lookup_symbol_local(target->global_scope, sym_imp->original_name);
                if (!target_sym || !target_sym->is_pub) {
                    const char *missing_name = "<unknown>";
                    if (sym_imp->original_name && sym_imp->original_name->key) {
                        missing_name = ((Slice*)sym_imp->original_name->key)->ptr;
                    }
                    TypeError err = { .kind = TE_UNDECLARED, .span = decl->span, .filename = unit->absolute_path };
                    err.as.name.name = missing_name;
                    dynarray_push_value(ctx->errors, &err);
                    continue;
                }
                InternResult *local_name = sym_imp->alias_name ? sym_imp->alias_name : sym_imp->original_name;
                scope_define_symbol(unit->global_scope, local_name, target_sym->type, target_sym->kind, target->absolute_path, import->is_pub, target_sym->decl_node);
            }
        } else if (import->is_star) {
            for (size_t j = 0; j < target->global_scope->symbols_list.count; j++) {
                Symbol *sym = *(Symbol**)dynarray_get(&target->global_scope->symbols_list, j);
                if (sym && sym->is_pub && sym->kind != SYMBOL_VALUE_MODULE) {
                     scope_define_symbol(unit->global_scope, sym->name_rec, sym->type, sym->kind, target->absolute_path, import->is_pub, sym->decl_node);
                }
            }
        } else if (import->module_alias) {
            Symbol *mod_sym = scope_define_symbol(unit->global_scope, import->module_alias, ((void*)0), SYMBOL_VALUE_MODULE, target->absolute_path, import->is_pub, ((void*)0));
            if (mod_sym) {
                mod_sym->module_scope = target->global_scope;
            }
        } else {
        }
    }
}
void typecheck_program(TypeCheckContext *ctx) {
    if (!ctx || !ctx->loader) return;
    Arena *scope_arena = ctx->store->arena;
    int universe_count = (ctx->keywords ? ctx->keywords->dense_index_count : 0) + 32;
    Scope *universe_scope = scope_create(scope_arena, ((void*)0), universe_count, SCOPE_KEYWORDS);
    for (size_t i = 0; i < ctx->loader->units_ordered->count; i++) {
        CompilationUnit *unit = *(CompilationUnit**)dynarray_get(ctx->loader->units_ordered, i);
        int id_count = (ctx->identifiers ? ctx->identifiers->dense_index_count : 0) + 64;
        unit->global_scope = scope_create(scope_arena, universe_scope, id_count, SCOPE_IDENTIFIERS);
        unit->global_scope->unit = unit;
        register_intrinsics(ctx->store, unit->global_scope, ctx->identifiers);
    }
    for (size_t i = 0; i < ctx->loader->units_ordered->count; i++) {
        CompilationUnit *unit = *(CompilationUnit**)dynarray_get(ctx->loader->units_ordered, i);
        ctx->filename = unit->absolute_path;
        ctx->program = unit->ast_root;
        register_program_structs(ctx, unit->global_scope);
        register_program_globals(ctx, unit->global_scope);
        register_program_functions(ctx, unit->global_scope);
        register_program_aliases(ctx, unit->global_scope);
        resolve_imports(ctx, unit);
        unit->imports_resolved = 1;
        resolve_program_aliases(ctx, unit->global_scope);
        resolve_program_structs(ctx, unit->global_scope);
        resolve_program_globals(ctx, unit->global_scope);
        resolve_program_functions(ctx, unit->global_scope);
        unit->signatures_resolved = 1;
    }
    ctx->current_pass = 1;
    for (size_t i = 0; i < ctx->loader->units_ordered->count; i++) {
        CompilationUnit *unit = *(CompilationUnit**)dynarray_get(ctx->loader->units_ordered, i);
        ctx->filename = unit->absolute_path;
        ctx->program = unit->ast_root;
        validate_allocator_struct(ctx, unit->global_scope);
        AstProgram *program = &unit->ast_root->data.program;
        if (!program->decls) continue;
        for (size_t j = 0; j < program->decls->count; j++) {
            AstNode *decl = *(AstNode**)dynarray_get(program->decls, j);
            switch (decl->node_type) {
                case AST_VARIABLE_DECLARATION: check_variable_declaration(ctx, unit->global_scope, decl); break;
                case AST_FUNCTION_DECLARATION: check_function(ctx, unit->global_scope, decl); break;
                default: break;
            }
        }
    }
}
typedef struct CodegenContext CodegenContext;
CodegenContext* codegen_context_create(TypeStore *store, const char *module_name, int opt_level, ModuleLoader *loader);
void codegen_context_destroy(CodegenContext *ctx);
void codegen_initialize(void);
int codegen_program(CodegenContext *ctx);
void codegen_dump_module(CodegenContext *ctx);
void codegen_emit_object(CodegenContext *ctx, const char *filename);
int codegen_run_jit(CodegenContext *ctx);

#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
typedef void (*LLVMFatalErrorHandler)(const char *Reason);
__attribute__((visibility("default"))) void LLVMInstallFatalErrorHandler(LLVMFatalErrorHandler Handler);
__attribute__((visibility("default"))) void LLVMResetFatalErrorHandler(void);
__attribute__((visibility("default"))) void LLVMEnablePrettyStackTrace(void);
#pragma clang diagnostic pop
__attribute__((availability(macosx,introduced=10.4)))
extern intmax_t
imaxabs(intmax_t j);
typedef struct {
 intmax_t quot;
 intmax_t rem;
} imaxdiv_t;
__attribute__((availability(macosx,introduced=10.4)))
extern imaxdiv_t
imaxdiv(intmax_t __numer, intmax_t __denom);
__attribute__((availability(macosx,introduced=10.4)))
extern intmax_t
strtoimax(const char * restrict __nptr,
   char * * restrict __endptr,
   int __base);
__attribute__((availability(macosx,introduced=10.4)))
extern uintmax_t
strtoumax(const char * restrict __nptr,
   char * * restrict __endptr,
   int __base);
__attribute__((availability(macosx,introduced=10.4)))
extern intmax_t
wcstoimax(const wchar_t * restrict __nptr,
   wchar_t * * restrict __endptr,
   int __base);
__attribute__((availability(macosx,introduced=10.4)))
extern uintmax_t
wcstoumax(const wchar_t * restrict __nptr,
   wchar_t * * restrict __endptr,
   int __base);
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;

typedef unsigned long u_long;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef u_int64_t u_quad_t;
typedef int64_t quad_t;
typedef quad_t * qaddr_t;
typedef char * caddr_t;

typedef int32_t daddr_t;
typedef u_int32_t fixpt_t;
typedef __uint32_t in_addr_t;
typedef __uint16_t in_port_t;
typedef __int32_t key_t;
typedef int32_t segsz_t;
typedef int32_t swblk_t;
typedef __darwin_useconds_t useconds_t;
typedef __int32_t fd_mask;
typedef __darwin_pthread_cond_t pthread_cond_t;
typedef __darwin_pthread_condattr_t pthread_condattr_t;
typedef __darwin_pthread_mutex_t pthread_mutex_t;
typedef __darwin_pthread_mutexattr_t pthread_mutexattr_t;
typedef __darwin_pthread_once_t pthread_once_t;
typedef __darwin_pthread_rwlock_t pthread_rwlock_t;
typedef __darwin_pthread_rwlockattr_t pthread_rwlockattr_t;
typedef __darwin_pthread_t pthread_t;
typedef __darwin_pthread_key_t pthread_key_t;
typedef __darwin_fsblkcnt_t fsblkcnt_t;
typedef __darwin_fsfilcnt_t fsfilcnt_t;
#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
typedef int LLVMBool;
typedef struct LLVMOpaqueMemoryBuffer *LLVMMemoryBufferRef;
typedef struct LLVMOpaqueContext *LLVMContextRef;
typedef struct LLVMOpaqueModule *LLVMModuleRef;
typedef struct LLVMOpaqueType *LLVMTypeRef;
typedef struct LLVMOpaqueValue *LLVMValueRef;
typedef struct LLVMOpaqueBasicBlock *LLVMBasicBlockRef;
typedef struct LLVMOpaqueMetadata *LLVMMetadataRef;
typedef struct LLVMOpaqueNamedMDNode *LLVMNamedMDNodeRef;
typedef struct LLVMOpaqueValueMetadataEntry LLVMValueMetadataEntry;
typedef struct LLVMOpaqueBuilder *LLVMBuilderRef;
typedef struct LLVMOpaqueDIBuilder *LLVMDIBuilderRef;
typedef struct LLVMOpaqueModuleProvider *LLVMModuleProviderRef;
typedef struct LLVMOpaquePassManager *LLVMPassManagerRef;
typedef struct LLVMOpaqueUse *LLVMUseRef;
typedef struct LLVMOpaqueOperandBundle *LLVMOperandBundleRef;
typedef struct LLVMOpaqueAttributeRef *LLVMAttributeRef;
typedef struct LLVMOpaqueDiagnosticInfo *LLVMDiagnosticInfoRef;
typedef struct LLVMComdat *LLVMComdatRef;
typedef struct LLVMOpaqueModuleFlagEntry LLVMModuleFlagEntry;
typedef struct LLVMOpaqueJITEventListener *LLVMJITEventListenerRef;
typedef struct LLVMOpaqueBinary *LLVMBinaryRef;
typedef struct LLVMOpaqueDbgRecord *LLVMDbgRecordRef;
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
typedef enum {
  LLVMRet = 1,
  LLVMBr = 2,
  LLVMSwitch = 3,
  LLVMIndirectBr = 4,
  LLVMInvoke = 5,
  LLVMUnreachable = 7,
  LLVMCallBr = 67,
  LLVMFNeg = 66,
  LLVMAdd = 8,
  LLVMFAdd = 9,
  LLVMSub = 10,
  LLVMFSub = 11,
  LLVMMul = 12,
  LLVMFMul = 13,
  LLVMUDiv = 14,
  LLVMSDiv = 15,
  LLVMFDiv = 16,
  LLVMURem = 17,
  LLVMSRem = 18,
  LLVMFRem = 19,
  LLVMShl = 20,
  LLVMLShr = 21,
  LLVMAShr = 22,
  LLVMAnd = 23,
  LLVMOr = 24,
  LLVMXor = 25,
  LLVMAlloca = 26,
  LLVMLoad = 27,
  LLVMStore = 28,
  LLVMGetElementPtr = 29,
  LLVMTrunc = 30,
  LLVMZExt = 31,
  LLVMSExt = 32,
  LLVMFPToUI = 33,
  LLVMFPToSI = 34,
  LLVMUIToFP = 35,
  LLVMSIToFP = 36,
  LLVMFPTrunc = 37,
  LLVMFPExt = 38,
  LLVMPtrToInt = 39,
  LLVMIntToPtr = 40,
  LLVMBitCast = 41,
  LLVMAddrSpaceCast = 60,
  LLVMICmp = 42,
  LLVMFCmp = 43,
  LLVMPHI = 44,
  LLVMCall = 45,
  LLVMSelect = 46,
  LLVMUserOp1 = 47,
  LLVMUserOp2 = 48,
  LLVMVAArg = 49,
  LLVMExtractElement = 50,
  LLVMInsertElement = 51,
  LLVMShuffleVector = 52,
  LLVMExtractValue = 53,
  LLVMInsertValue = 54,
  LLVMFreeze = 68,
  LLVMFence = 55,
  LLVMAtomicCmpXchg = 56,
  LLVMAtomicRMW = 57,
  LLVMResume = 58,
  LLVMLandingPad = 59,
  LLVMCleanupRet = 61,
  LLVMCatchRet = 62,
  LLVMCatchPad = 63,
  LLVMCleanupPad = 64,
  LLVMCatchSwitch = 65
} LLVMOpcode;
typedef enum {
  LLVMVoidTypeKind = 0,
  LLVMHalfTypeKind = 1,
  LLVMFloatTypeKind = 2,
  LLVMDoubleTypeKind = 3,
  LLVMX86_FP80TypeKind = 4,
  LLVMFP128TypeKind = 5,
  LLVMPPC_FP128TypeKind = 6,
  LLVMLabelTypeKind = 7,
  LLVMIntegerTypeKind = 8,
  LLVMFunctionTypeKind = 9,
  LLVMStructTypeKind = 10,
  LLVMArrayTypeKind = 11,
  LLVMPointerTypeKind = 12,
  LLVMVectorTypeKind = 13,
  LLVMMetadataTypeKind = 14,
  LLVMTokenTypeKind = 16,
  LLVMScalableVectorTypeKind = 17,
  LLVMBFloatTypeKind = 18,
  LLVMX86_AMXTypeKind = 19,
  LLVMTargetExtTypeKind = 20,
} LLVMTypeKind;
typedef enum {
  LLVMExternalLinkage,
  LLVMAvailableExternallyLinkage,
  LLVMLinkOnceAnyLinkage,
  LLVMLinkOnceODRLinkage,
  LLVMLinkOnceODRAutoHideLinkage,
  LLVMWeakAnyLinkage,
  LLVMWeakODRLinkage,
  LLVMAppendingLinkage,
  LLVMInternalLinkage,
  LLVMPrivateLinkage,
  LLVMDLLImportLinkage,
  LLVMDLLExportLinkage,
  LLVMExternalWeakLinkage,
  LLVMGhostLinkage,
  LLVMCommonLinkage,
  LLVMLinkerPrivateLinkage,
  LLVMLinkerPrivateWeakLinkage
} LLVMLinkage;
typedef enum {
  LLVMDefaultVisibility,
  LLVMHiddenVisibility,
  LLVMProtectedVisibility
} LLVMVisibility;
typedef enum {
  LLVMNoUnnamedAddr,
  LLVMLocalUnnamedAddr,
  LLVMGlobalUnnamedAddr
} LLVMUnnamedAddr;
typedef enum {
  LLVMDefaultStorageClass = 0,
  LLVMDLLImportStorageClass = 1,
  LLVMDLLExportStorageClass = 2
} LLVMDLLStorageClass;
typedef enum {
  LLVMCCallConv = 0,
  LLVMFastCallConv = 8,
  LLVMColdCallConv = 9,
  LLVMGHCCallConv = 10,
  LLVMHiPECallConv = 11,
  LLVMAnyRegCallConv = 13,
  LLVMPreserveMostCallConv = 14,
  LLVMPreserveAllCallConv = 15,
  LLVMSwiftCallConv = 16,
  LLVMCXXFASTTLSCallConv = 17,
  LLVMX86StdcallCallConv = 64,
  LLVMX86FastcallCallConv = 65,
  LLVMARMAPCSCallConv = 66,
  LLVMARMAAPCSCallConv = 67,
  LLVMARMAAPCSVFPCallConv = 68,
  LLVMMSP430INTRCallConv = 69,
  LLVMX86ThisCallCallConv = 70,
  LLVMPTXKernelCallConv = 71,
  LLVMPTXDeviceCallConv = 72,
  LLVMSPIRFUNCCallConv = 75,
  LLVMSPIRKERNELCallConv = 76,
  LLVMIntelOCLBICallConv = 77,
  LLVMX8664SysVCallConv = 78,
  LLVMWin64CallConv = 79,
  LLVMX86VectorCallCallConv = 80,
  LLVMHHVMCallConv = 81,
  LLVMHHVMCCallConv = 82,
  LLVMX86INTRCallConv = 83,
  LLVMAVRINTRCallConv = 84,
  LLVMAVRSIGNALCallConv = 85,
  LLVMAVRBUILTINCallConv = 86,
  LLVMAMDGPUVSCallConv = 87,
  LLVMAMDGPUGSCallConv = 88,
  LLVMAMDGPUPSCallConv = 89,
  LLVMAMDGPUCSCallConv = 90,
  LLVMAMDGPUKERNELCallConv = 91,
  LLVMX86RegCallCallConv = 92,
  LLVMAMDGPUHSCallConv = 93,
  LLVMMSP430BUILTINCallConv = 94,
  LLVMAMDGPULSCallConv = 95,
  LLVMAMDGPUESCallConv = 96
} LLVMCallConv;
typedef enum {
  LLVMArgumentValueKind,
  LLVMBasicBlockValueKind,
  LLVMMemoryUseValueKind,
  LLVMMemoryDefValueKind,
  LLVMMemoryPhiValueKind,
  LLVMFunctionValueKind,
  LLVMGlobalAliasValueKind,
  LLVMGlobalIFuncValueKind,
  LLVMGlobalVariableValueKind,
  LLVMBlockAddressValueKind,
  LLVMConstantExprValueKind,
  LLVMConstantArrayValueKind,
  LLVMConstantStructValueKind,
  LLVMConstantVectorValueKind,
  LLVMUndefValueValueKind,
  LLVMConstantAggregateZeroValueKind,
  LLVMConstantDataArrayValueKind,
  LLVMConstantDataVectorValueKind,
  LLVMConstantIntValueKind,
  LLVMConstantFPValueKind,
  LLVMConstantPointerNullValueKind,
  LLVMConstantTokenNoneValueKind,
  LLVMMetadataAsValueValueKind,
  LLVMInlineAsmValueKind,
  LLVMInstructionValueKind,
  LLVMPoisonValueValueKind,
  LLVMConstantTargetNoneValueKind,
  LLVMConstantPtrAuthValueKind,
} LLVMValueKind;
typedef enum {
  LLVMIntEQ = 32,
  LLVMIntNE,
  LLVMIntUGT,
  LLVMIntUGE,
  LLVMIntULT,
  LLVMIntULE,
  LLVMIntSGT,
  LLVMIntSGE,
  LLVMIntSLT,
  LLVMIntSLE
} LLVMIntPredicate;
typedef enum {
  LLVMRealPredicateFalse,
  LLVMRealOEQ,
  LLVMRealOGT,
  LLVMRealOGE,
  LLVMRealOLT,
  LLVMRealOLE,
  LLVMRealONE,
  LLVMRealORD,
  LLVMRealUNO,
  LLVMRealUEQ,
  LLVMRealUGT,
  LLVMRealUGE,
  LLVMRealULT,
  LLVMRealULE,
  LLVMRealUNE,
  LLVMRealPredicateTrue
} LLVMRealPredicate;
typedef enum {
  LLVMNotThreadLocal = 0,
  LLVMGeneralDynamicTLSModel,
  LLVMLocalDynamicTLSModel,
  LLVMInitialExecTLSModel,
  LLVMLocalExecTLSModel
} LLVMThreadLocalMode;
typedef enum {
  LLVMAtomicOrderingNotAtomic = 0,
  LLVMAtomicOrderingUnordered = 1,
  LLVMAtomicOrderingMonotonic = 2,
  LLVMAtomicOrderingAcquire = 4,
  LLVMAtomicOrderingRelease = 5,
  LLVMAtomicOrderingAcquireRelease = 6,
  LLVMAtomicOrderingSequentiallyConsistent = 7
} LLVMAtomicOrdering;
typedef enum {
  LLVMAtomicRMWBinOpXchg,
  LLVMAtomicRMWBinOpAdd,
  LLVMAtomicRMWBinOpSub,
  LLVMAtomicRMWBinOpAnd,
  LLVMAtomicRMWBinOpNand,
  LLVMAtomicRMWBinOpOr,
  LLVMAtomicRMWBinOpXor,
  LLVMAtomicRMWBinOpMax,
  LLVMAtomicRMWBinOpMin,
  LLVMAtomicRMWBinOpUMax,
  LLVMAtomicRMWBinOpUMin,
  LLVMAtomicRMWBinOpFAdd,
  LLVMAtomicRMWBinOpFSub,
  LLVMAtomicRMWBinOpFMax,
  LLVMAtomicRMWBinOpFMin,
  LLVMAtomicRMWBinOpUIncWrap,
  LLVMAtomicRMWBinOpUDecWrap,
  LLVMAtomicRMWBinOpUSubCond,
  LLVMAtomicRMWBinOpUSubSat,
  LLVMAtomicRMWBinOpFMaximum,
  LLVMAtomicRMWBinOpFMinimum,
} LLVMAtomicRMWBinOp;
typedef enum {
    LLVMDSError,
    LLVMDSWarning,
    LLVMDSRemark,
    LLVMDSNote
} LLVMDiagnosticSeverity;
typedef enum {
  LLVMInlineAsmDialectATT,
  LLVMInlineAsmDialectIntel
} LLVMInlineAsmDialect;
typedef enum {
  LLVMModuleFlagBehaviorError,
  LLVMModuleFlagBehaviorWarning,
  LLVMModuleFlagBehaviorRequire,
  LLVMModuleFlagBehaviorOverride,
  LLVMModuleFlagBehaviorAppend,
  LLVMModuleFlagBehaviorAppendUnique,
} LLVMModuleFlagBehavior;
enum {
  LLVMAttributeReturnIndex = 0U,
  LLVMAttributeFunctionIndex = -1,
};
typedef unsigned LLVMAttributeIndex;
typedef enum {
  LLVMTailCallKindNone = 0,
  LLVMTailCallKindTail = 1,
  LLVMTailCallKindMustTail = 2,
  LLVMTailCallKindNoTail = 3,
} LLVMTailCallKind;
enum {
  LLVMFastMathAllowReassoc = (1 << 0),
  LLVMFastMathNoNaNs = (1 << 1),
  LLVMFastMathNoInfs = (1 << 2),
  LLVMFastMathNoSignedZeros = (1 << 3),
  LLVMFastMathAllowReciprocal = (1 << 4),
  LLVMFastMathAllowContract = (1 << 5),
  LLVMFastMathApproxFunc = (1 << 6),
  LLVMFastMathNone = 0,
  LLVMFastMathAll = LLVMFastMathAllowReassoc | LLVMFastMathNoNaNs |
                    LLVMFastMathNoInfs | LLVMFastMathNoSignedZeros |
                    LLVMFastMathAllowReciprocal | LLVMFastMathAllowContract |
                    LLVMFastMathApproxFunc,
};
typedef unsigned LLVMFastMathFlags;
enum {
  LLVMGEPFlagInBounds = (1 << 0),
  LLVMGEPFlagNUSW = (1 << 1),
  LLVMGEPFlagNUW = (1 << 2),
};
typedef unsigned LLVMGEPNoWrapFlags;
__attribute__((visibility("default"))) void LLVMShutdown(void);
__attribute__((visibility("default"))) void LLVMGetVersion(unsigned *Major, unsigned *Minor,
                               unsigned *Patch);
__attribute__((visibility("default"))) char *LLVMCreateMessage(const char *Message);
__attribute__((visibility("default"))) void LLVMDisposeMessage(char *Message);
typedef void (*LLVMDiagnosticHandler)(LLVMDiagnosticInfoRef, void *);
typedef void (*LLVMYieldCallback)(LLVMContextRef, void *);
__attribute__((visibility("default"))) LLVMContextRef LLVMContextCreate(void);
__attribute__((visibility("default"))) LLVMContextRef LLVMGetGlobalContext(void);
__attribute__((visibility("default"))) void LLVMContextSetDiagnosticHandler(LLVMContextRef C,
                                                LLVMDiagnosticHandler Handler,
                                                void *DiagnosticContext);
__attribute__((visibility("default"))) LLVMDiagnosticHandler
LLVMContextGetDiagnosticHandler(LLVMContextRef C);
__attribute__((visibility("default"))) void *LLVMContextGetDiagnosticContext(LLVMContextRef C);
__attribute__((visibility("default"))) void LLVMContextSetYieldCallback(LLVMContextRef C,
                                            LLVMYieldCallback Callback,
                                            void *OpaqueHandle);
__attribute__((visibility("default"))) LLVMBool LLVMContextShouldDiscardValueNames(LLVMContextRef C);
__attribute__((visibility("default"))) void LLVMContextSetDiscardValueNames(LLVMContextRef C,
                                                LLVMBool Discard);
__attribute__((visibility("default"))) void LLVMContextDispose(LLVMContextRef C);
__attribute__((visibility("default"))) char *LLVMGetDiagInfoDescription(LLVMDiagnosticInfoRef DI);
__attribute__((visibility("default"))) LLVMDiagnosticSeverity
LLVMGetDiagInfoSeverity(LLVMDiagnosticInfoRef DI);
__attribute__((visibility("default"))) unsigned LLVMGetMDKindIDInContext(LLVMContextRef C, const char *Name,
                                             unsigned SLen);
__attribute__((visibility("default"))) unsigned LLVMGetMDKindID(const char *Name, unsigned SLen);
__attribute__((visibility("default"))) unsigned LLVMGetSyncScopeID(LLVMContextRef C, const char *Name,
                                       size_t SLen);
__attribute__((visibility("default"))) unsigned LLVMGetEnumAttributeKindForName(const char *Name,
                                                    size_t SLen);
__attribute__((visibility("default"))) unsigned LLVMGetLastEnumAttributeKind(void);
__attribute__((visibility("default"))) LLVMAttributeRef LLVMCreateEnumAttribute(LLVMContextRef C,
                                                    unsigned KindID,
                                                    uint64_t Val);
__attribute__((visibility("default"))) unsigned LLVMGetEnumAttributeKind(LLVMAttributeRef A);
__attribute__((visibility("default"))) uint64_t LLVMGetEnumAttributeValue(LLVMAttributeRef A);
__attribute__((visibility("default"))) LLVMAttributeRef LLVMCreateTypeAttribute(LLVMContextRef C,
                                                    unsigned KindID,
                                                    LLVMTypeRef type_ref);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetTypeAttributeValue(LLVMAttributeRef A);
__attribute__((visibility("default"))) LLVMAttributeRef LLVMCreateConstantRangeAttribute(
    LLVMContextRef C, unsigned KindID, unsigned NumBits,
    const uint64_t LowerWords[], const uint64_t UpperWords[]);
__attribute__((visibility("default"))) LLVMAttributeRef LLVMCreateStringAttribute(LLVMContextRef C,
                                                      const char *K,
                                                      unsigned KLength,
                                                      const char *V,
                                                      unsigned VLength);
__attribute__((visibility("default"))) const char *LLVMGetStringAttributeKind(LLVMAttributeRef A,
                                                  unsigned *Length);
__attribute__((visibility("default"))) const char *LLVMGetStringAttributeValue(LLVMAttributeRef A,
                                                   unsigned *Length);
__attribute__((visibility("default"))) LLVMBool LLVMIsEnumAttribute(LLVMAttributeRef A);
__attribute__((visibility("default"))) LLVMBool LLVMIsStringAttribute(LLVMAttributeRef A);
__attribute__((visibility("default"))) LLVMBool LLVMIsTypeAttribute(LLVMAttributeRef A);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetTypeByName2(LLVMContextRef C, const char *Name);
__attribute__((visibility("default"))) LLVMModuleRef LLVMModuleCreateWithName(const char *ModuleID);
__attribute__((visibility("default"))) LLVMModuleRef LLVMModuleCreateWithNameInContext(const char *ModuleID,
                                                           LLVMContextRef C);
__attribute__((visibility("default"))) LLVMModuleRef LLVMCloneModule(LLVMModuleRef M);
__attribute__((visibility("default"))) void LLVMDisposeModule(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMBool LLVMIsNewDbgInfoFormat(LLVMModuleRef M);
__attribute__((visibility("default"))) void LLVMSetIsNewDbgInfoFormat(LLVMModuleRef M,
                                          LLVMBool UseNewFormat);
__attribute__((visibility("default"))) const char *LLVMGetModuleIdentifier(LLVMModuleRef M, size_t *Len);
__attribute__((visibility("default"))) void LLVMSetModuleIdentifier(LLVMModuleRef M, const char *Ident,
                                        size_t Len);
__attribute__((visibility("default"))) const char *LLVMGetSourceFileName(LLVMModuleRef M, size_t *Len);
__attribute__((visibility("default"))) void LLVMSetSourceFileName(LLVMModuleRef M, const char *Name,
                                      size_t Len);
__attribute__((visibility("default"))) const char *LLVMGetDataLayoutStr(LLVMModuleRef M);
__attribute__((visibility("default"))) const char *LLVMGetDataLayout(LLVMModuleRef M);
__attribute__((visibility("default"))) void LLVMSetDataLayout(LLVMModuleRef M, const char *DataLayoutStr);
__attribute__((visibility("default"))) const char *LLVMGetTarget(LLVMModuleRef M);
__attribute__((visibility("default"))) void LLVMSetTarget(LLVMModuleRef M, const char *Triple);
__attribute__((visibility("default"))) LLVMModuleFlagEntry *LLVMCopyModuleFlagsMetadata(LLVMModuleRef M,
                                                            size_t *Len);
__attribute__((visibility("default"))) void LLVMDisposeModuleFlagsMetadata(LLVMModuleFlagEntry *Entries);
__attribute__((visibility("default"))) LLVMModuleFlagBehavior LLVMModuleFlagEntriesGetFlagBehavior(
    LLVMModuleFlagEntry *Entries, unsigned Index);
__attribute__((visibility("default"))) const char *LLVMModuleFlagEntriesGetKey(LLVMModuleFlagEntry *Entries,
                                                   unsigned Index, size_t *Len);
__attribute__((visibility("default"))) LLVMMetadataRef
LLVMModuleFlagEntriesGetMetadata(LLVMModuleFlagEntry *Entries, unsigned Index);
__attribute__((visibility("default"))) LLVMMetadataRef LLVMGetModuleFlag(LLVMModuleRef M, const char *Key,
                                             size_t KeyLen);
__attribute__((visibility("default"))) void LLVMAddModuleFlag(LLVMModuleRef M,
                                  LLVMModuleFlagBehavior Behavior,
                                  const char *Key, size_t KeyLen,
                                  LLVMMetadataRef Val);
__attribute__((visibility("default"))) void LLVMDumpModule(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMBool LLVMPrintModuleToFile(LLVMModuleRef M, const char *Filename,
                                          char **ErrorMessage);
__attribute__((visibility("default"))) char *LLVMPrintModuleToString(LLVMModuleRef M);
__attribute__((visibility("default"))) const char *LLVMGetModuleInlineAsm(LLVMModuleRef M, size_t *Len);
__attribute__((visibility("default"))) void LLVMSetModuleInlineAsm2(LLVMModuleRef M, const char *Asm,
                                        size_t Len);
__attribute__((visibility("default"))) void LLVMAppendModuleInlineAsm(LLVMModuleRef M, const char *Asm,
                                          size_t Len);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetInlineAsm(
    LLVMTypeRef Ty, const char *AsmString, size_t AsmStringSize,
    const char *Constraints, size_t ConstraintsSize, LLVMBool HasSideEffects,
    LLVMBool IsAlignStack, LLVMInlineAsmDialect Dialect, LLVMBool CanThrow);
__attribute__((visibility("default"))) const char *LLVMGetInlineAsmAsmString(LLVMValueRef InlineAsmVal,
                                                 size_t *Len);
__attribute__((visibility("default"))) const char *
LLVMGetInlineAsmConstraintString(LLVMValueRef InlineAsmVal, size_t *Len);
__attribute__((visibility("default"))) LLVMInlineAsmDialect
LLVMGetInlineAsmDialect(LLVMValueRef InlineAsmVal);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetInlineAsmFunctionType(LLVMValueRef InlineAsmVal);
__attribute__((visibility("default"))) LLVMBool LLVMGetInlineAsmHasSideEffects(LLVMValueRef InlineAsmVal);
__attribute__((visibility("default"))) LLVMBool
LLVMGetInlineAsmNeedsAlignedStack(LLVMValueRef InlineAsmVal);
__attribute__((visibility("default"))) LLVMBool LLVMGetInlineAsmCanUnwind(LLVMValueRef InlineAsmVal);
__attribute__((visibility("default"))) LLVMContextRef LLVMGetModuleContext(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetTypeByName(LLVMModuleRef M, const char *Name);
__attribute__((visibility("default"))) LLVMNamedMDNodeRef LLVMGetFirstNamedMetadata(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMNamedMDNodeRef LLVMGetLastNamedMetadata(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMNamedMDNodeRef
LLVMGetNextNamedMetadata(LLVMNamedMDNodeRef NamedMDNode);
__attribute__((visibility("default"))) LLVMNamedMDNodeRef
LLVMGetPreviousNamedMetadata(LLVMNamedMDNodeRef NamedMDNode);
__attribute__((visibility("default"))) LLVMNamedMDNodeRef LLVMGetNamedMetadata(LLVMModuleRef M,
                                                   const char *Name,
                                                   size_t NameLen);
__attribute__((visibility("default"))) LLVMNamedMDNodeRef LLVMGetOrInsertNamedMetadata(LLVMModuleRef M,
                                                           const char *Name,
                                                           size_t NameLen);
__attribute__((visibility("default"))) const char *LLVMGetNamedMetadataName(LLVMNamedMDNodeRef NamedMD,
                                                size_t *NameLen);
__attribute__((visibility("default"))) unsigned LLVMGetNamedMetadataNumOperands(LLVMModuleRef M,
                                                    const char *Name);
__attribute__((visibility("default"))) void LLVMGetNamedMetadataOperands(LLVMModuleRef M, const char *Name,
                                             LLVMValueRef *Dest);
__attribute__((visibility("default"))) void LLVMAddNamedMetadataOperand(LLVMModuleRef M, const char *Name,
                                            LLVMValueRef Val);
__attribute__((visibility("default"))) const char *LLVMGetDebugLocDirectory(LLVMValueRef Val,
                                                unsigned *Length);
__attribute__((visibility("default"))) const char *LLVMGetDebugLocFilename(LLVMValueRef Val,
                                               unsigned *Length);
__attribute__((visibility("default"))) unsigned LLVMGetDebugLocLine(LLVMValueRef Val);
__attribute__((visibility("default"))) unsigned LLVMGetDebugLocColumn(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMValueRef LLVMAddFunction(LLVMModuleRef M, const char *Name,
                                        LLVMTypeRef FunctionTy);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNamedFunction(LLVMModuleRef M, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNamedFunctionWithLength(LLVMModuleRef M,
                                                       const char *Name,
                                                       size_t Length);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetFirstFunction(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetLastFunction(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNextFunction(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPreviousFunction(LLVMValueRef Fn);
__attribute__((visibility("default"))) void LLVMSetModuleInlineAsm(LLVMModuleRef M, const char *Asm);
__attribute__((visibility("default"))) LLVMTypeKind LLVMGetTypeKind(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMBool LLVMTypeIsSized(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMContextRef LLVMGetTypeContext(LLVMTypeRef Ty);
__attribute__((visibility("default"))) void LLVMDumpType(LLVMTypeRef Val);
__attribute__((visibility("default"))) char *LLVMPrintTypeToString(LLVMTypeRef Val);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt1TypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt8TypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt16TypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt32TypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt64TypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt128TypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMIntTypeInContext(LLVMContextRef C, unsigned NumBits);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt1Type(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt8Type(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt16Type(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt32Type(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt64Type(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMInt128Type(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMIntType(unsigned NumBits);
__attribute__((visibility("default"))) unsigned LLVMGetIntTypeWidth(LLVMTypeRef IntegerTy);
__attribute__((visibility("default"))) LLVMTypeRef LLVMHalfTypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMBFloatTypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMFloatTypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMDoubleTypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMX86FP80TypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMFP128TypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMPPCFP128TypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMHalfType(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMBFloatType(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMFloatType(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMDoubleType(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMX86FP80Type(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMFP128Type(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMPPCFP128Type(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMFunctionType(LLVMTypeRef ReturnType,
                                        LLVMTypeRef *ParamTypes,
                                        unsigned ParamCount, LLVMBool IsVarArg);
__attribute__((visibility("default"))) LLVMBool LLVMIsFunctionVarArg(LLVMTypeRef FunctionTy);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetReturnType(LLVMTypeRef FunctionTy);
__attribute__((visibility("default"))) unsigned LLVMCountParamTypes(LLVMTypeRef FunctionTy);
__attribute__((visibility("default"))) void LLVMGetParamTypes(LLVMTypeRef FunctionTy, LLVMTypeRef *Dest);
__attribute__((visibility("default"))) LLVMTypeRef LLVMStructTypeInContext(LLVMContextRef C,
                                               LLVMTypeRef *ElementTypes,
                                               unsigned ElementCount,
                                               LLVMBool Packed);
__attribute__((visibility("default"))) LLVMTypeRef LLVMStructType(LLVMTypeRef *ElementTypes,
                                      unsigned ElementCount, LLVMBool Packed);
__attribute__((visibility("default"))) LLVMTypeRef LLVMStructCreateNamed(LLVMContextRef C,
                                             const char *Name);
__attribute__((visibility("default"))) const char *LLVMGetStructName(LLVMTypeRef Ty);
__attribute__((visibility("default"))) void LLVMStructSetBody(LLVMTypeRef StructTy,
                                  LLVMTypeRef *ElementTypes,
                                  unsigned ElementCount, LLVMBool Packed);
__attribute__((visibility("default"))) unsigned LLVMCountStructElementTypes(LLVMTypeRef StructTy);
__attribute__((visibility("default"))) void LLVMGetStructElementTypes(LLVMTypeRef StructTy,
                                          LLVMTypeRef *Dest);
__attribute__((visibility("default"))) LLVMTypeRef LLVMStructGetTypeAtIndex(LLVMTypeRef StructTy,
                                                unsigned i);
__attribute__((visibility("default"))) LLVMBool LLVMIsPackedStruct(LLVMTypeRef StructTy);
__attribute__((visibility("default"))) LLVMBool LLVMIsOpaqueStruct(LLVMTypeRef StructTy);
__attribute__((visibility("default"))) LLVMBool LLVMIsLiteralStruct(LLVMTypeRef StructTy);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetElementType(LLVMTypeRef Ty);
__attribute__((visibility("default"))) void LLVMGetSubtypes(LLVMTypeRef Tp, LLVMTypeRef *Arr);
__attribute__((visibility("default"))) unsigned LLVMGetNumContainedTypes(LLVMTypeRef Tp);
__attribute__((visibility("default"))) LLVMTypeRef LLVMArrayType(LLVMTypeRef ElementType,
                                     unsigned ElementCount);
__attribute__((visibility("default"))) LLVMTypeRef LLVMArrayType2(LLVMTypeRef ElementType,
                                      uint64_t ElementCount);
__attribute__((visibility("default"))) unsigned LLVMGetArrayLength(LLVMTypeRef ArrayTy);
__attribute__((visibility("default"))) uint64_t LLVMGetArrayLength2(LLVMTypeRef ArrayTy);
__attribute__((visibility("default"))) LLVMTypeRef LLVMPointerType(LLVMTypeRef ElementType,
                                       unsigned AddressSpace);
__attribute__((visibility("default"))) LLVMBool LLVMPointerTypeIsOpaque(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMTypeRef LLVMPointerTypeInContext(LLVMContextRef C,
                                                unsigned AddressSpace);
__attribute__((visibility("default"))) unsigned LLVMGetPointerAddressSpace(LLVMTypeRef PointerTy);
__attribute__((visibility("default"))) LLVMTypeRef LLVMVectorType(LLVMTypeRef ElementType,
                                      unsigned ElementCount);
__attribute__((visibility("default"))) LLVMTypeRef LLVMScalableVectorType(LLVMTypeRef ElementType,
                                              unsigned ElementCount);
__attribute__((visibility("default"))) unsigned LLVMGetVectorSize(LLVMTypeRef VectorTy);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetConstantPtrAuthPointer(LLVMValueRef PtrAuth);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetConstantPtrAuthKey(LLVMValueRef PtrAuth);
__attribute__((visibility("default"))) LLVMValueRef
LLVMGetConstantPtrAuthDiscriminator(LLVMValueRef PtrAuth);
__attribute__((visibility("default"))) LLVMValueRef
LLVMGetConstantPtrAuthAddrDiscriminator(LLVMValueRef PtrAuth);
__attribute__((visibility("default"))) LLVMTypeRef LLVMVoidTypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMLabelTypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMX86AMXTypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMTokenTypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMMetadataTypeInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMTypeRef LLVMVoidType(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMLabelType(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMX86AMXType(void);
__attribute__((visibility("default"))) LLVMTypeRef LLVMTargetExtTypeInContext(
    LLVMContextRef C, const char *Name, LLVMTypeRef *TypeParams,
    unsigned TypeParamCount, unsigned *IntParams, unsigned IntParamCount);
__attribute__((visibility("default"))) const char *LLVMGetTargetExtTypeName(LLVMTypeRef TargetExtTy);
__attribute__((visibility("default"))) unsigned LLVMGetTargetExtTypeNumTypeParams(LLVMTypeRef TargetExtTy);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetTargetExtTypeTypeParam(LLVMTypeRef TargetExtTy,
                                                     unsigned Idx);
__attribute__((visibility("default"))) unsigned LLVMGetTargetExtTypeNumIntParams(LLVMTypeRef TargetExtTy);
__attribute__((visibility("default"))) unsigned LLVMGetTargetExtTypeIntParam(LLVMTypeRef TargetExtTy,
                                                 unsigned Idx);
__attribute__((visibility("default"))) LLVMTypeRef LLVMTypeOf(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMValueKind LLVMGetValueKind(LLVMValueRef Val);
__attribute__((visibility("default"))) const char *LLVMGetValueName2(LLVMValueRef Val, size_t *Length);
__attribute__((visibility("default"))) void LLVMSetValueName2(LLVMValueRef Val, const char *Name,
                                  size_t NameLen);
__attribute__((visibility("default"))) void LLVMDumpValue(LLVMValueRef Val);
__attribute__((visibility("default"))) char *LLVMPrintValueToString(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMContextRef LLVMGetValueContext(LLVMValueRef Val);
__attribute__((visibility("default"))) char *LLVMPrintDbgRecordToString(LLVMDbgRecordRef Record);
__attribute__((visibility("default"))) void LLVMReplaceAllUsesWith(LLVMValueRef OldVal,
                                       LLVMValueRef NewVal);
__attribute__((visibility("default"))) LLVMBool LLVMIsConstant(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMBool LLVMIsUndef(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMBool LLVMIsPoison(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMValueRef LLVMIsAArgument(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsABasicBlock(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAInlineAsm(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAUser(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstant(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsABlockAddress(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantAggregateZero(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantArray(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantDataSequential(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantDataArray(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantDataVector(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantExpr(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantFP(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantInt(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantPointerNull(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantStruct(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantTokenNone(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantVector(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAConstantPtrAuth(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAGlobalValue(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAGlobalAlias(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAGlobalObject(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAFunction(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAGlobalVariable(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAGlobalIFunc(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAUndefValue(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAPoisonValue(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAInstruction(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAUnaryOperator(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsABinaryOperator(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsACallInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAIntrinsicInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsADbgInfoIntrinsic(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsADbgVariableIntrinsic(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsADbgDeclareInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsADbgLabelInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAMemIntrinsic(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAMemCpyInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAMemMoveInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAMemSetInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsACmpInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAFCmpInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAICmpInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAExtractElementInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAGetElementPtrInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAInsertElementInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAInsertValueInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsALandingPadInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAPHINode(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsASelectInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAShuffleVectorInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAStoreInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsABranchInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAIndirectBrInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAInvokeInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAReturnInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsASwitchInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAUnreachableInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAResumeInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsACleanupReturnInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsACatchReturnInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsACatchSwitchInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsACallBrInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAFuncletPadInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsACatchPadInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsACleanupPadInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAUnaryInstruction(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAAllocaInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsACastInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAAddrSpaceCastInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsABitCastInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAFPExtInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAFPToSIInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAFPToUIInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAFPTruncInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAIntToPtrInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAPtrToIntInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsASExtInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsASIToFPInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsATruncInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAUIToFPInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAZExtInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAExtractValueInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsALoadInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAVAArgInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAFreezeInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAAtomicCmpXchgInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAAtomicRMWInst(LLVMValueRef Val); __attribute__((visibility("default"))) LLVMValueRef LLVMIsAFenceInst(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMValueRef LLVMIsAMDNode(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMValueRef LLVMIsAValueAsMetadata(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMValueRef LLVMIsAMDString(LLVMValueRef Val);
__attribute__((visibility("default"))) const char *LLVMGetValueName(LLVMValueRef Val);
__attribute__((visibility("default"))) void LLVMSetValueName(LLVMValueRef Val, const char *Name);
__attribute__((visibility("default"))) LLVMUseRef LLVMGetFirstUse(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMUseRef LLVMGetNextUse(LLVMUseRef U);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetUser(LLVMUseRef U);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetUsedValue(LLVMUseRef U);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetOperand(LLVMValueRef Val, unsigned Index);
__attribute__((visibility("default"))) LLVMUseRef LLVMGetOperandUse(LLVMValueRef Val, unsigned Index);
__attribute__((visibility("default"))) void LLVMSetOperand(LLVMValueRef User, unsigned Index,
                               LLVMValueRef Val);
__attribute__((visibility("default"))) int LLVMGetNumOperands(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNull(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstAllOnes(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetUndef(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPoison(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMBool LLVMIsNull(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstPointerNull(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstInt(LLVMTypeRef IntTy, unsigned long long N,
                                     LLVMBool SignExtend);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstIntOfArbitraryPrecision(
    LLVMTypeRef IntTy, unsigned NumWords, const uint64_t Words[]);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstIntOfString(LLVMTypeRef IntTy,
                                             const char *Text, uint8_t Radix);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstIntOfStringAndSize(LLVMTypeRef IntTy,
                                                    const char *Text,
                                                    unsigned SLen,
                                                    uint8_t Radix);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstReal(LLVMTypeRef RealTy, double N);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstRealOfString(LLVMTypeRef RealTy,
                                              const char *Text);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstRealOfStringAndSize(LLVMTypeRef RealTy,
                                                     const char *Text,
                                                     unsigned SLen);
__attribute__((visibility("default"))) unsigned long long
LLVMConstIntGetZExtValue(LLVMValueRef ConstantVal);
__attribute__((visibility("default"))) long long LLVMConstIntGetSExtValue(LLVMValueRef ConstantVal);
__attribute__((visibility("default"))) double LLVMConstRealGetDouble(LLVMValueRef ConstantVal,
                                         LLVMBool *losesInfo);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstStringInContext(LLVMContextRef C,
                                                 const char *Str,
                                                 unsigned Length,
                                                 LLVMBool DontNullTerminate);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstStringInContext2(LLVMContextRef C,
                                                  const char *Str,
                                                  size_t Length,
                                                  LLVMBool DontNullTerminate);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstString(const char *Str, unsigned Length,
                                        LLVMBool DontNullTerminate);
__attribute__((visibility("default"))) LLVMBool LLVMIsConstantString(LLVMValueRef c);
__attribute__((visibility("default"))) const char *LLVMGetAsString(LLVMValueRef c, size_t *Length);
__attribute__((visibility("default"))) const char *LLVMGetRawDataValues(LLVMValueRef c,
                                            size_t *SizeInBytes);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstStructInContext(LLVMContextRef C,
                                                 LLVMValueRef *ConstantVals,
                                                 unsigned Count,
                                                 LLVMBool Packed);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstStruct(LLVMValueRef *ConstantVals,
                                        unsigned Count, LLVMBool Packed);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstArray(LLVMTypeRef ElementTy,
                                       LLVMValueRef *ConstantVals,
                                       unsigned Length);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstArray2(LLVMTypeRef ElementTy,
                                        LLVMValueRef *ConstantVals,
                                        uint64_t Length);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstDataArray(LLVMTypeRef ElementTy,
                                           const char *Data,
                                           size_t SizeInBytes);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNamedStruct(LLVMTypeRef StructTy,
                                             LLVMValueRef *ConstantVals,
                                             unsigned Count);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetAggregateElement(LLVMValueRef C, unsigned Idx);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetElementAsConstant(LLVMValueRef C, unsigned idx) __attribute__((deprecated("Use LLVMGetAggregateElement instead")));
__attribute__((visibility("default"))) LLVMValueRef LLVMConstVector(LLVMValueRef *ScalarConstantVals,
                                        unsigned Size);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstantPtrAuth(LLVMValueRef Ptr, LLVMValueRef Key,
                                            LLVMValueRef Disc,
                                            LLVMValueRef AddrDisc);
__attribute__((visibility("default"))) LLVMOpcode LLVMGetConstOpcode(LLVMValueRef ConstantVal);
__attribute__((visibility("default"))) LLVMValueRef LLVMAlignOf(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMValueRef LLVMSizeOf(LLVMTypeRef Ty);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNeg(LLVMValueRef ConstantVal);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNSWNeg(LLVMValueRef ConstantVal);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNUWNeg(LLVMValueRef ConstantVal) __attribute__((deprecated("Use LLVMConstNull instead.")));
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNot(LLVMValueRef ConstantVal);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstAdd(LLVMValueRef LHSConstant,
                                     LLVMValueRef RHSConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNSWAdd(LLVMValueRef LHSConstant,
                                        LLVMValueRef RHSConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNUWAdd(LLVMValueRef LHSConstant,
                                        LLVMValueRef RHSConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstSub(LLVMValueRef LHSConstant,
                                     LLVMValueRef RHSConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNSWSub(LLVMValueRef LHSConstant,
                                        LLVMValueRef RHSConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstNUWSub(LLVMValueRef LHSConstant,
                                        LLVMValueRef RHSConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstXor(LLVMValueRef LHSConstant,
                                     LLVMValueRef RHSConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstGEP2(LLVMTypeRef Ty, LLVMValueRef ConstantVal,
                                      LLVMValueRef *ConstantIndices,
                                      unsigned NumIndices);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstInBoundsGEP2(LLVMTypeRef Ty,
                                              LLVMValueRef ConstantVal,
                                              LLVMValueRef *ConstantIndices,
                                              unsigned NumIndices);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstGEPWithNoWrapFlags(
    LLVMTypeRef Ty, LLVMValueRef ConstantVal, LLVMValueRef *ConstantIndices,
    unsigned NumIndices, LLVMGEPNoWrapFlags NoWrapFlags);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstTrunc(LLVMValueRef ConstantVal,
                                       LLVMTypeRef ToType);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstPtrToInt(LLVMValueRef ConstantVal,
                                          LLVMTypeRef ToType);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstIntToPtr(LLVMValueRef ConstantVal,
                                          LLVMTypeRef ToType);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstBitCast(LLVMValueRef ConstantVal,
                                         LLVMTypeRef ToType);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstAddrSpaceCast(LLVMValueRef ConstantVal,
                                               LLVMTypeRef ToType);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstTruncOrBitCast(LLVMValueRef ConstantVal,
                                                LLVMTypeRef ToType);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstPointerCast(LLVMValueRef ConstantVal,
                                             LLVMTypeRef ToType);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstExtractElement(LLVMValueRef VectorConstant,
                                                LLVMValueRef IndexConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstInsertElement(
    LLVMValueRef VectorConstant, LLVMValueRef ElementValueConstant,
    LLVMValueRef IndexConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstShuffleVector(LLVMValueRef VectorAConstant,
                                               LLVMValueRef VectorBConstant,
                                               LLVMValueRef MaskConstant);
__attribute__((visibility("default"))) LLVMValueRef LLVMBlockAddress(LLVMValueRef F, LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetBlockAddressFunction(LLVMValueRef BlockAddr);
__attribute__((visibility("default"))) LLVMBasicBlockRef
LLVMGetBlockAddressBasicBlock(LLVMValueRef BlockAddr);
__attribute__((visibility("default"))) LLVMValueRef LLVMConstInlineAsm(LLVMTypeRef Ty,
                                           const char *AsmString,
                                           const char *Constraints,
                                           LLVMBool HasSideEffects,
                                           LLVMBool IsAlignStack);
__attribute__((visibility("default"))) LLVMModuleRef LLVMGetGlobalParent(LLVMValueRef Global);
__attribute__((visibility("default"))) LLVMBool LLVMIsDeclaration(LLVMValueRef Global);
__attribute__((visibility("default"))) LLVMLinkage LLVMGetLinkage(LLVMValueRef Global);
__attribute__((visibility("default"))) void LLVMSetLinkage(LLVMValueRef Global, LLVMLinkage Linkage);
__attribute__((visibility("default"))) const char *LLVMGetSection(LLVMValueRef Global);
__attribute__((visibility("default"))) void LLVMSetSection(LLVMValueRef Global, const char *Section);
__attribute__((visibility("default"))) LLVMVisibility LLVMGetVisibility(LLVMValueRef Global);
__attribute__((visibility("default"))) void LLVMSetVisibility(LLVMValueRef Global, LLVMVisibility Viz);
__attribute__((visibility("default"))) LLVMDLLStorageClass LLVMGetDLLStorageClass(LLVMValueRef Global);
__attribute__((visibility("default"))) void LLVMSetDLLStorageClass(LLVMValueRef Global,
                                       LLVMDLLStorageClass Class);
__attribute__((visibility("default"))) LLVMUnnamedAddr LLVMGetUnnamedAddress(LLVMValueRef Global);
__attribute__((visibility("default"))) void LLVMSetUnnamedAddress(LLVMValueRef Global,
                                      LLVMUnnamedAddr UnnamedAddr);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGlobalGetValueType(LLVMValueRef Global);
__attribute__((visibility("default"))) LLVMBool LLVMHasUnnamedAddr(LLVMValueRef Global);
__attribute__((visibility("default"))) void LLVMSetUnnamedAddr(LLVMValueRef Global,
                                   LLVMBool HasUnnamedAddr);
__attribute__((visibility("default"))) unsigned LLVMGetAlignment(LLVMValueRef V);
__attribute__((visibility("default"))) void LLVMSetAlignment(LLVMValueRef V, unsigned Bytes);
__attribute__((visibility("default"))) void LLVMGlobalSetMetadata(LLVMValueRef Global, unsigned Kind,
                                      LLVMMetadataRef MD);
__attribute__((visibility("default"))) void LLVMGlobalEraseMetadata(LLVMValueRef Global, unsigned Kind);
__attribute__((visibility("default"))) void LLVMGlobalClearMetadata(LLVMValueRef Global);
__attribute__((visibility("default"))) LLVMValueMetadataEntry *
LLVMGlobalCopyAllMetadata(LLVMValueRef Value, size_t *NumEntries);
__attribute__((visibility("default"))) void
LLVMDisposeValueMetadataEntries(LLVMValueMetadataEntry *Entries);
__attribute__((visibility("default"))) unsigned
LLVMValueMetadataEntriesGetKind(LLVMValueMetadataEntry *Entries,
                                unsigned Index);
__attribute__((visibility("default"))) LLVMMetadataRef LLVMValueMetadataEntriesGetMetadata(
    LLVMValueMetadataEntry *Entries, unsigned Index);
__attribute__((visibility("default"))) LLVMValueRef LLVMAddGlobal(LLVMModuleRef M, LLVMTypeRef Ty,
                                      const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMAddGlobalInAddressSpace(LLVMModuleRef M,
                                                    LLVMTypeRef Ty,
                                                    const char *Name,
                                                    unsigned AddressSpace);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNamedGlobal(LLVMModuleRef M, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNamedGlobalWithLength(LLVMModuleRef M,
                                                     const char *Name,
                                                     size_t Length);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetFirstGlobal(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetLastGlobal(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNextGlobal(LLVMValueRef GlobalVar);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPreviousGlobal(LLVMValueRef GlobalVar);
__attribute__((visibility("default"))) void LLVMDeleteGlobal(LLVMValueRef GlobalVar);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetInitializer(LLVMValueRef GlobalVar);
__attribute__((visibility("default"))) void LLVMSetInitializer(LLVMValueRef GlobalVar,
                                   LLVMValueRef ConstantVal);
__attribute__((visibility("default"))) LLVMBool LLVMIsThreadLocal(LLVMValueRef GlobalVar);
__attribute__((visibility("default"))) void LLVMSetThreadLocal(LLVMValueRef GlobalVar,
                                   LLVMBool IsThreadLocal);
__attribute__((visibility("default"))) LLVMBool LLVMIsGlobalConstant(LLVMValueRef GlobalVar);
__attribute__((visibility("default"))) void LLVMSetGlobalConstant(LLVMValueRef GlobalVar,
                                      LLVMBool IsConstant);
__attribute__((visibility("default"))) LLVMThreadLocalMode LLVMGetThreadLocalMode(LLVMValueRef GlobalVar);
__attribute__((visibility("default"))) void LLVMSetThreadLocalMode(LLVMValueRef GlobalVar,
                                       LLVMThreadLocalMode Mode);
__attribute__((visibility("default"))) LLVMBool LLVMIsExternallyInitialized(LLVMValueRef GlobalVar);
__attribute__((visibility("default"))) void LLVMSetExternallyInitialized(LLVMValueRef GlobalVar,
                                             LLVMBool IsExtInit);
__attribute__((visibility("default"))) LLVMValueRef LLVMAddAlias2(LLVMModuleRef M, LLVMTypeRef ValueTy,
                                      unsigned AddrSpace, LLVMValueRef Aliasee,
                                      const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNamedGlobalAlias(LLVMModuleRef M,
                                                const char *Name,
                                                size_t NameLen);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetFirstGlobalAlias(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetLastGlobalAlias(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNextGlobalAlias(LLVMValueRef GA);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPreviousGlobalAlias(LLVMValueRef GA);
__attribute__((visibility("default"))) LLVMValueRef LLVMAliasGetAliasee(LLVMValueRef Alias);
__attribute__((visibility("default"))) void LLVMAliasSetAliasee(LLVMValueRef Alias, LLVMValueRef Aliasee);
__attribute__((visibility("default"))) void LLVMDeleteFunction(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMBool LLVMHasPersonalityFn(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPersonalityFn(LLVMValueRef Fn);
__attribute__((visibility("default"))) void LLVMSetPersonalityFn(LLVMValueRef Fn,
                                     LLVMValueRef PersonalityFn);
__attribute__((visibility("default"))) unsigned LLVMLookupIntrinsicID(const char *Name, size_t NameLen);
__attribute__((visibility("default"))) unsigned LLVMGetIntrinsicID(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetIntrinsicDeclaration(LLVMModuleRef Mod,
                                                    unsigned ID,
                                                    LLVMTypeRef *ParamTypes,
                                                    size_t ParamCount);
__attribute__((visibility("default"))) LLVMTypeRef LLVMIntrinsicGetType(LLVMContextRef Ctx, unsigned ID,
                                            LLVMTypeRef *ParamTypes,
                                            size_t ParamCount);
__attribute__((visibility("default"))) const char *LLVMIntrinsicGetName(unsigned ID, size_t *NameLength);
__attribute__((visibility("default"))) char *LLVMIntrinsicCopyOverloadedName(unsigned ID,
                                                 LLVMTypeRef *ParamTypes,
                                                 size_t ParamCount,
                                                 size_t *NameLength);
__attribute__((visibility("default"))) char *LLVMIntrinsicCopyOverloadedName2(LLVMModuleRef Mod,
                                                  unsigned ID,
                                                  LLVMTypeRef *ParamTypes,
                                                  size_t ParamCount,
                                                  size_t *NameLength);
__attribute__((visibility("default"))) LLVMBool LLVMIntrinsicIsOverloaded(unsigned ID);
__attribute__((visibility("default"))) unsigned LLVMGetFunctionCallConv(LLVMValueRef Fn);
__attribute__((visibility("default"))) void LLVMSetFunctionCallConv(LLVMValueRef Fn, unsigned CC);
__attribute__((visibility("default"))) const char *LLVMGetGC(LLVMValueRef Fn);
__attribute__((visibility("default"))) void LLVMSetGC(LLVMValueRef Fn, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPrefixData(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMBool LLVMHasPrefixData(LLVMValueRef Fn);
__attribute__((visibility("default"))) void LLVMSetPrefixData(LLVMValueRef Fn, LLVMValueRef prefixData);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPrologueData(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMBool LLVMHasPrologueData(LLVMValueRef Fn);
__attribute__((visibility("default"))) void LLVMSetPrologueData(LLVMValueRef Fn, LLVMValueRef prologueData);
__attribute__((visibility("default"))) void LLVMAddAttributeAtIndex(LLVMValueRef F, LLVMAttributeIndex Idx,
                                        LLVMAttributeRef A);
__attribute__((visibility("default"))) unsigned LLVMGetAttributeCountAtIndex(LLVMValueRef F,
                                                 LLVMAttributeIndex Idx);
__attribute__((visibility("default"))) void LLVMGetAttributesAtIndex(LLVMValueRef F, LLVMAttributeIndex Idx,
                                         LLVMAttributeRef *Attrs);
__attribute__((visibility("default"))) LLVMAttributeRef LLVMGetEnumAttributeAtIndex(LLVMValueRef F,
                                                        LLVMAttributeIndex Idx,
                                                        unsigned KindID);
__attribute__((visibility("default"))) LLVMAttributeRef LLVMGetStringAttributeAtIndex(
    LLVMValueRef F, LLVMAttributeIndex Idx, const char *K, unsigned KLen);
__attribute__((visibility("default"))) void LLVMRemoveEnumAttributeAtIndex(LLVMValueRef F,
                                               LLVMAttributeIndex Idx,
                                               unsigned KindID);
__attribute__((visibility("default"))) void LLVMRemoveStringAttributeAtIndex(LLVMValueRef F,
                                                 LLVMAttributeIndex Idx,
                                                 const char *K, unsigned KLen);
__attribute__((visibility("default"))) void LLVMAddTargetDependentFunctionAttr(LLVMValueRef Fn,
                                                   const char *A,
                                                   const char *V);
__attribute__((visibility("default"))) unsigned LLVMCountParams(LLVMValueRef Fn);
__attribute__((visibility("default"))) void LLVMGetParams(LLVMValueRef Fn, LLVMValueRef *Params);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetParam(LLVMValueRef Fn, unsigned Index);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetParamParent(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetFirstParam(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetLastParam(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNextParam(LLVMValueRef Arg);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPreviousParam(LLVMValueRef Arg);
__attribute__((visibility("default"))) void LLVMSetParamAlignment(LLVMValueRef Arg, unsigned Align);
__attribute__((visibility("default"))) LLVMValueRef LLVMAddGlobalIFunc(LLVMModuleRef M, const char *Name,
                                           size_t NameLen, LLVMTypeRef Ty,
                                           unsigned AddrSpace,
                                           LLVMValueRef Resolver);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNamedGlobalIFunc(LLVMModuleRef M,
                                                const char *Name,
                                                size_t NameLen);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetFirstGlobalIFunc(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetLastGlobalIFunc(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNextGlobalIFunc(LLVMValueRef IFunc);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPreviousGlobalIFunc(LLVMValueRef IFunc);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetGlobalIFuncResolver(LLVMValueRef IFunc);
__attribute__((visibility("default"))) void LLVMSetGlobalIFuncResolver(LLVMValueRef IFunc,
                                           LLVMValueRef Resolver);
__attribute__((visibility("default"))) void LLVMEraseGlobalIFunc(LLVMValueRef IFunc);
__attribute__((visibility("default"))) void LLVMRemoveGlobalIFunc(LLVMValueRef IFunc);
__attribute__((visibility("default"))) LLVMMetadataRef LLVMMDStringInContext2(LLVMContextRef C,
                                                  const char *Str, size_t SLen);
__attribute__((visibility("default"))) LLVMMetadataRef LLVMMDNodeInContext2(LLVMContextRef C,
                                                LLVMMetadataRef *MDs,
                                                size_t Count);
__attribute__((visibility("default"))) LLVMValueRef LLVMMetadataAsValue(LLVMContextRef C,
                                            LLVMMetadataRef MD);
__attribute__((visibility("default"))) LLVMMetadataRef LLVMValueAsMetadata(LLVMValueRef Val);
__attribute__((visibility("default"))) const char *LLVMGetMDString(LLVMValueRef V, unsigned *Length);
__attribute__((visibility("default"))) unsigned LLVMGetMDNodeNumOperands(LLVMValueRef V);
__attribute__((visibility("default"))) void LLVMGetMDNodeOperands(LLVMValueRef V, LLVMValueRef *Dest);
__attribute__((visibility("default"))) void LLVMReplaceMDNodeOperandWith(LLVMValueRef V, unsigned Index,
                                             LLVMMetadataRef Replacement);
__attribute__((visibility("default"))) LLVMValueRef LLVMMDStringInContext(LLVMContextRef C, const char *Str,
                                              unsigned SLen);
__attribute__((visibility("default"))) LLVMValueRef LLVMMDString(const char *Str, unsigned SLen);
__attribute__((visibility("default"))) LLVMValueRef LLVMMDNodeInContext(LLVMContextRef C,
                                            LLVMValueRef *Vals, unsigned Count);
__attribute__((visibility("default"))) LLVMValueRef LLVMMDNode(LLVMValueRef *Vals, unsigned Count);
__attribute__((visibility("default"))) LLVMOperandBundleRef LLVMCreateOperandBundle(const char *Tag,
                                                        size_t TagLen,
                                                        LLVMValueRef *Args,
                                                        unsigned NumArgs);
__attribute__((visibility("default"))) void LLVMDisposeOperandBundle(LLVMOperandBundleRef Bundle);
__attribute__((visibility("default"))) const char *LLVMGetOperandBundleTag(LLVMOperandBundleRef Bundle,
                                               size_t *Len);
__attribute__((visibility("default"))) unsigned LLVMGetNumOperandBundleArgs(LLVMOperandBundleRef Bundle);
__attribute__((visibility("default"))) LLVMValueRef
LLVMGetOperandBundleArgAtIndex(LLVMOperandBundleRef Bundle, unsigned Index);
__attribute__((visibility("default"))) LLVMValueRef LLVMBasicBlockAsValue(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMBool LLVMValueIsBasicBlock(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMValueAsBasicBlock(LLVMValueRef Val);
__attribute__((visibility("default"))) const char *LLVMGetBasicBlockName(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetBasicBlockParent(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetBasicBlockTerminator(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) unsigned LLVMCountBasicBlocks(LLVMValueRef Fn);
__attribute__((visibility("default"))) void LLVMGetBasicBlocks(LLVMValueRef Fn,
                                   LLVMBasicBlockRef *BasicBlocks);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetFirstBasicBlock(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetLastBasicBlock(LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetNextBasicBlock(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetPreviousBasicBlock(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetEntryBasicBlock(LLVMValueRef Fn);
__attribute__((visibility("default"))) void
LLVMInsertExistingBasicBlockAfterInsertBlock(LLVMBuilderRef Builder,
                                             LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) void LLVMAppendExistingBasicBlock(LLVMValueRef Fn,
                                             LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMCreateBasicBlockInContext(LLVMContextRef C,
                                                           const char *Name);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMAppendBasicBlockInContext(LLVMContextRef C,
                                                           LLVMValueRef Fn,
                                                           const char *Name);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMAppendBasicBlock(LLVMValueRef Fn,
                                                  const char *Name);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMInsertBasicBlockInContext(LLVMContextRef C,
                                                           LLVMBasicBlockRef BB,
                                                           const char *Name);
__attribute__((visibility("default"))) LLVMBasicBlockRef
LLVMInsertBasicBlock(LLVMBasicBlockRef InsertBeforeBB, const char *Name);
__attribute__((visibility("default"))) void LLVMDeleteBasicBlock(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) void LLVMRemoveBasicBlockFromParent(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) void LLVMMoveBasicBlockBefore(LLVMBasicBlockRef BB,
                                         LLVMBasicBlockRef MovePos);
__attribute__((visibility("default"))) void LLVMMoveBasicBlockAfter(LLVMBasicBlockRef BB,
                                        LLVMBasicBlockRef MovePos);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetFirstInstruction(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetLastInstruction(LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) int LLVMHasMetadata(LLVMValueRef Val);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetMetadata(LLVMValueRef Val, unsigned KindID);
__attribute__((visibility("default"))) void LLVMSetMetadata(LLVMValueRef Val, unsigned KindID,
                                LLVMValueRef Node);
__attribute__((visibility("default"))) LLVMValueMetadataEntry *
LLVMInstructionGetAllMetadataOtherThanDebugLoc(LLVMValueRef Instr,
                                               size_t *NumEntries);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetInstructionParent(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetNextInstruction(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetPreviousInstruction(LLVMValueRef Inst);
__attribute__((visibility("default"))) void LLVMInstructionRemoveFromParent(LLVMValueRef Inst);
__attribute__((visibility("default"))) void LLVMInstructionEraseFromParent(LLVMValueRef Inst);
__attribute__((visibility("default"))) void LLVMDeleteInstruction(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMOpcode LLVMGetInstructionOpcode(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMIntPredicate LLVMGetICmpPredicate(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMBool LLVMGetICmpSameSign(LLVMValueRef Inst);
__attribute__((visibility("default"))) void LLVMSetICmpSameSign(LLVMValueRef Inst, LLVMBool SameSign);
__attribute__((visibility("default"))) LLVMRealPredicate LLVMGetFCmpPredicate(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMValueRef LLVMInstructionClone(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMValueRef LLVMIsATerminatorInst(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMDbgRecordRef LLVMGetFirstDbgRecord(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMDbgRecordRef LLVMGetLastDbgRecord(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMDbgRecordRef LLVMGetNextDbgRecord(LLVMDbgRecordRef DbgRecord);
__attribute__((visibility("default"))) LLVMDbgRecordRef
LLVMGetPreviousDbgRecord(LLVMDbgRecordRef DbgRecord);
__attribute__((visibility("default"))) unsigned LLVMGetNumArgOperands(LLVMValueRef Instr);
__attribute__((visibility("default"))) void LLVMSetInstructionCallConv(LLVMValueRef Instr, unsigned CC);
__attribute__((visibility("default"))) unsigned LLVMGetInstructionCallConv(LLVMValueRef Instr);
__attribute__((visibility("default"))) void LLVMSetInstrParamAlignment(LLVMValueRef Instr,
                                           LLVMAttributeIndex Idx,
                                           unsigned Align);
__attribute__((visibility("default"))) void LLVMAddCallSiteAttribute(LLVMValueRef C, LLVMAttributeIndex Idx,
                                         LLVMAttributeRef A);
__attribute__((visibility("default"))) unsigned LLVMGetCallSiteAttributeCount(LLVMValueRef C,
                                                  LLVMAttributeIndex Idx);
__attribute__((visibility("default"))) void LLVMGetCallSiteAttributes(LLVMValueRef C,
                                          LLVMAttributeIndex Idx,
                                          LLVMAttributeRef *Attrs);
__attribute__((visibility("default"))) LLVMAttributeRef LLVMGetCallSiteEnumAttribute(LLVMValueRef C,
                                                         LLVMAttributeIndex Idx,
                                                         unsigned KindID);
__attribute__((visibility("default"))) LLVMAttributeRef LLVMGetCallSiteStringAttribute(
    LLVMValueRef C, LLVMAttributeIndex Idx, const char *K, unsigned KLen);
__attribute__((visibility("default"))) void LLVMRemoveCallSiteEnumAttribute(LLVMValueRef C,
                                                LLVMAttributeIndex Idx,
                                                unsigned KindID);
__attribute__((visibility("default"))) void LLVMRemoveCallSiteStringAttribute(LLVMValueRef C,
                                                  LLVMAttributeIndex Idx,
                                                  const char *K, unsigned KLen);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetCalledFunctionType(LLVMValueRef C);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetCalledValue(LLVMValueRef Instr);
__attribute__((visibility("default"))) unsigned LLVMGetNumOperandBundles(LLVMValueRef C);
__attribute__((visibility("default"))) LLVMOperandBundleRef LLVMGetOperandBundleAtIndex(LLVMValueRef C,
                                                            unsigned Index);
__attribute__((visibility("default"))) LLVMBool LLVMIsTailCall(LLVMValueRef CallInst);
__attribute__((visibility("default"))) void LLVMSetTailCall(LLVMValueRef CallInst, LLVMBool IsTailCall);
__attribute__((visibility("default"))) LLVMTailCallKind LLVMGetTailCallKind(LLVMValueRef CallInst);
__attribute__((visibility("default"))) void LLVMSetTailCallKind(LLVMValueRef CallInst,
                                    LLVMTailCallKind kind);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetNormalDest(LLVMValueRef InvokeInst);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetUnwindDest(LLVMValueRef InvokeInst);
__attribute__((visibility("default"))) void LLVMSetNormalDest(LLVMValueRef InvokeInst, LLVMBasicBlockRef B);
__attribute__((visibility("default"))) void LLVMSetUnwindDest(LLVMValueRef InvokeInst, LLVMBasicBlockRef B);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetCallBrDefaultDest(LLVMValueRef CallBr);
__attribute__((visibility("default"))) unsigned LLVMGetCallBrNumIndirectDests(LLVMValueRef CallBr);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetCallBrIndirectDest(LLVMValueRef CallBr,
                                                       unsigned Idx);
__attribute__((visibility("default"))) unsigned LLVMGetNumSuccessors(LLVMValueRef Term);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetSuccessor(LLVMValueRef Term, unsigned i);
__attribute__((visibility("default"))) void LLVMSetSuccessor(LLVMValueRef Term, unsigned i,
                                 LLVMBasicBlockRef block);
__attribute__((visibility("default"))) LLVMBool LLVMIsConditional(LLVMValueRef Branch);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetCondition(LLVMValueRef Branch);
__attribute__((visibility("default"))) void LLVMSetCondition(LLVMValueRef Branch, LLVMValueRef Cond);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetSwitchDefaultDest(LLVMValueRef SwitchInstr);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetAllocatedType(LLVMValueRef Alloca);
__attribute__((visibility("default"))) LLVMBool LLVMIsInBounds(LLVMValueRef GEP);
__attribute__((visibility("default"))) void LLVMSetIsInBounds(LLVMValueRef GEP, LLVMBool InBounds);
__attribute__((visibility("default"))) LLVMTypeRef LLVMGetGEPSourceElementType(LLVMValueRef GEP);
__attribute__((visibility("default"))) LLVMGEPNoWrapFlags LLVMGEPGetNoWrapFlags(LLVMValueRef GEP);
__attribute__((visibility("default"))) void LLVMGEPSetNoWrapFlags(LLVMValueRef GEP,
                                      LLVMGEPNoWrapFlags NoWrapFlags);
__attribute__((visibility("default"))) void LLVMAddIncoming(LLVMValueRef PhiNode,
                                LLVMValueRef *IncomingValues,
                                LLVMBasicBlockRef *IncomingBlocks,
                                unsigned Count);
__attribute__((visibility("default"))) unsigned LLVMCountIncoming(LLVMValueRef PhiNode);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetIncomingValue(LLVMValueRef PhiNode,
                                             unsigned Index);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetIncomingBlock(LLVMValueRef PhiNode,
                                                  unsigned Index);
__attribute__((visibility("default"))) unsigned LLVMGetNumIndices(LLVMValueRef Inst);
__attribute__((visibility("default"))) const unsigned *LLVMGetIndices(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMBuilderRef LLVMCreateBuilderInContext(LLVMContextRef C);
__attribute__((visibility("default"))) LLVMBuilderRef LLVMCreateBuilder(void);
__attribute__((visibility("default"))) void LLVMPositionBuilder(LLVMBuilderRef Builder,
                                    LLVMBasicBlockRef Block,
                                    LLVMValueRef Instr);
__attribute__((visibility("default"))) void LLVMPositionBuilderBeforeDbgRecords(LLVMBuilderRef Builder,
                                                    LLVMBasicBlockRef Block,
                                                    LLVMValueRef Inst);
__attribute__((visibility("default"))) void LLVMPositionBuilderBefore(LLVMBuilderRef Builder,
                                          LLVMValueRef Instr);
__attribute__((visibility("default"))) void
LLVMPositionBuilderBeforeInstrAndDbgRecords(LLVMBuilderRef Builder,
                                            LLVMValueRef Instr);
__attribute__((visibility("default"))) void LLVMPositionBuilderAtEnd(LLVMBuilderRef Builder,
                                         LLVMBasicBlockRef Block);
__attribute__((visibility("default"))) LLVMBasicBlockRef LLVMGetInsertBlock(LLVMBuilderRef Builder);
__attribute__((visibility("default"))) void LLVMClearInsertionPosition(LLVMBuilderRef Builder);
__attribute__((visibility("default"))) void LLVMInsertIntoBuilder(LLVMBuilderRef Builder,
                                      LLVMValueRef Instr);
__attribute__((visibility("default"))) void LLVMInsertIntoBuilderWithName(LLVMBuilderRef Builder,
                                              LLVMValueRef Instr,
                                              const char *Name);
__attribute__((visibility("default"))) void LLVMDisposeBuilder(LLVMBuilderRef Builder);
__attribute__((visibility("default"))) LLVMMetadataRef LLVMGetCurrentDebugLocation2(LLVMBuilderRef Builder);
__attribute__((visibility("default"))) void LLVMSetCurrentDebugLocation2(LLVMBuilderRef Builder,
                                             LLVMMetadataRef Loc);
__attribute__((visibility("default"))) void LLVMSetInstDebugLocation(LLVMBuilderRef Builder,
                                         LLVMValueRef Inst);
__attribute__((visibility("default"))) void LLVMAddMetadataToInst(LLVMBuilderRef Builder,
                                      LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMMetadataRef
LLVMBuilderGetDefaultFPMathTag(LLVMBuilderRef Builder);
__attribute__((visibility("default"))) void LLVMBuilderSetDefaultFPMathTag(LLVMBuilderRef Builder,
                                               LLVMMetadataRef FPMathTag);
__attribute__((visibility("default"))) LLVMContextRef LLVMGetBuilderContext(LLVMBuilderRef Builder);
__attribute__((visibility("default"))) void LLVMSetCurrentDebugLocation(LLVMBuilderRef Builder,
                                            LLVMValueRef L);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetCurrentDebugLocation(LLVMBuilderRef Builder);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildRetVoid(LLVMBuilderRef);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildRet(LLVMBuilderRef, LLVMValueRef V);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAggregateRet(LLVMBuilderRef,
                                              LLVMValueRef *RetVals,
                                              unsigned N);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildBr(LLVMBuilderRef, LLVMBasicBlockRef Dest);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCondBr(LLVMBuilderRef, LLVMValueRef If,
                                        LLVMBasicBlockRef Then,
                                        LLVMBasicBlockRef Else);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildSwitch(LLVMBuilderRef, LLVMValueRef V,
                                        LLVMBasicBlockRef Else,
                                        unsigned NumCases);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildIndirectBr(LLVMBuilderRef B, LLVMValueRef Addr,
                                            unsigned NumDests);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCallBr(
    LLVMBuilderRef B, LLVMTypeRef Ty, LLVMValueRef Fn,
    LLVMBasicBlockRef DefaultDest, LLVMBasicBlockRef *IndirectDests,
    unsigned NumIndirectDests, LLVMValueRef *Args, unsigned NumArgs,
    LLVMOperandBundleRef *Bundles, unsigned NumBundles, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildInvoke2(LLVMBuilderRef, LLVMTypeRef Ty,
                                         LLVMValueRef Fn, LLVMValueRef *Args,
                                         unsigned NumArgs,
                                         LLVMBasicBlockRef Then,
                                         LLVMBasicBlockRef Catch,
                                         const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildInvokeWithOperandBundles(
    LLVMBuilderRef, LLVMTypeRef Ty, LLVMValueRef Fn, LLVMValueRef *Args,
    unsigned NumArgs, LLVMBasicBlockRef Then, LLVMBasicBlockRef Catch,
    LLVMOperandBundleRef *Bundles, unsigned NumBundles, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildUnreachable(LLVMBuilderRef);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildResume(LLVMBuilderRef B, LLVMValueRef Exn);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildLandingPad(LLVMBuilderRef B, LLVMTypeRef Ty,
                                            LLVMValueRef PersFn,
                                            unsigned NumClauses,
                                            const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCleanupRet(LLVMBuilderRef B,
                                            LLVMValueRef CatchPad,
                                            LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCatchRet(LLVMBuilderRef B,
                                          LLVMValueRef CatchPad,
                                          LLVMBasicBlockRef BB);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCatchPad(LLVMBuilderRef B,
                                          LLVMValueRef ParentPad,
                                          LLVMValueRef *Args, unsigned NumArgs,
                                          const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCleanupPad(LLVMBuilderRef B,
                                            LLVMValueRef ParentPad,
                                            LLVMValueRef *Args,
                                            unsigned NumArgs, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCatchSwitch(LLVMBuilderRef B,
                                             LLVMValueRef ParentPad,
                                             LLVMBasicBlockRef UnwindBB,
                                             unsigned NumHandlers,
                                             const char *Name);
__attribute__((visibility("default"))) void LLVMAddCase(LLVMValueRef Switch, LLVMValueRef OnVal,
                            LLVMBasicBlockRef Dest);
__attribute__((visibility("default"))) void LLVMAddDestination(LLVMValueRef IndirectBr,
                                   LLVMBasicBlockRef Dest);
__attribute__((visibility("default"))) unsigned LLVMGetNumClauses(LLVMValueRef LandingPad);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetClause(LLVMValueRef LandingPad, unsigned Idx);
__attribute__((visibility("default"))) void LLVMAddClause(LLVMValueRef LandingPad, LLVMValueRef ClauseVal);
__attribute__((visibility("default"))) LLVMBool LLVMIsCleanup(LLVMValueRef LandingPad);
__attribute__((visibility("default"))) void LLVMSetCleanup(LLVMValueRef LandingPad, LLVMBool Val);
__attribute__((visibility("default"))) void LLVMAddHandler(LLVMValueRef CatchSwitch,
                               LLVMBasicBlockRef Dest);
__attribute__((visibility("default"))) unsigned LLVMGetNumHandlers(LLVMValueRef CatchSwitch);
__attribute__((visibility("default"))) void LLVMGetHandlers(LLVMValueRef CatchSwitch,
                                LLVMBasicBlockRef *Handlers);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetArgOperand(LLVMValueRef Funclet, unsigned i);
__attribute__((visibility("default"))) void LLVMSetArgOperand(LLVMValueRef Funclet, unsigned i,
                                  LLVMValueRef value);
__attribute__((visibility("default"))) LLVMValueRef LLVMGetParentCatchSwitch(LLVMValueRef CatchPad);
__attribute__((visibility("default"))) void LLVMSetParentCatchSwitch(LLVMValueRef CatchPad,
                                         LLVMValueRef CatchSwitch);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAdd(LLVMBuilderRef, LLVMValueRef LHS,
                                     LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNSWAdd(LLVMBuilderRef, LLVMValueRef LHS,
                                        LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNUWAdd(LLVMBuilderRef, LLVMValueRef LHS,
                                        LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFAdd(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildSub(LLVMBuilderRef, LLVMValueRef LHS,
                                     LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNSWSub(LLVMBuilderRef, LLVMValueRef LHS,
                                        LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNUWSub(LLVMBuilderRef, LLVMValueRef LHS,
                                        LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFSub(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildMul(LLVMBuilderRef, LLVMValueRef LHS,
                                     LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNSWMul(LLVMBuilderRef, LLVMValueRef LHS,
                                        LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNUWMul(LLVMBuilderRef, LLVMValueRef LHS,
                                        LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFMul(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildUDiv(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildExactUDiv(LLVMBuilderRef, LLVMValueRef LHS,
                                           LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildSDiv(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildExactSDiv(LLVMBuilderRef, LLVMValueRef LHS,
                                           LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFDiv(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildURem(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildSRem(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFRem(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildShl(LLVMBuilderRef, LLVMValueRef LHS,
                                     LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildLShr(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAShr(LLVMBuilderRef, LLVMValueRef LHS,
                                      LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAnd(LLVMBuilderRef, LLVMValueRef LHS,
                                     LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildOr(LLVMBuilderRef, LLVMValueRef LHS,
                                    LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildXor(LLVMBuilderRef, LLVMValueRef LHS,
                                     LLVMValueRef RHS, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildBinOp(LLVMBuilderRef B, LLVMOpcode Op,
                                       LLVMValueRef LHS, LLVMValueRef RHS,
                                       const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNeg(LLVMBuilderRef, LLVMValueRef V,
                                     const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNSWNeg(LLVMBuilderRef B, LLVMValueRef V,
                                        const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNUWNeg(LLVMBuilderRef B, LLVMValueRef V, const char *Name) __attribute__((deprecated("Use LLVMBuildNeg + LLVMSetNUW instead.")));
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFNeg(LLVMBuilderRef, LLVMValueRef V,
                                      const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildNot(LLVMBuilderRef, LLVMValueRef V,
                                     const char *Name);
__attribute__((visibility("default"))) LLVMBool LLVMGetNUW(LLVMValueRef ArithInst);
__attribute__((visibility("default"))) void LLVMSetNUW(LLVMValueRef ArithInst, LLVMBool HasNUW);
__attribute__((visibility("default"))) LLVMBool LLVMGetNSW(LLVMValueRef ArithInst);
__attribute__((visibility("default"))) void LLVMSetNSW(LLVMValueRef ArithInst, LLVMBool HasNSW);
__attribute__((visibility("default"))) LLVMBool LLVMGetExact(LLVMValueRef DivOrShrInst);
__attribute__((visibility("default"))) void LLVMSetExact(LLVMValueRef DivOrShrInst, LLVMBool IsExact);
__attribute__((visibility("default"))) LLVMBool LLVMGetNNeg(LLVMValueRef NonNegInst);
__attribute__((visibility("default"))) void LLVMSetNNeg(LLVMValueRef NonNegInst, LLVMBool IsNonNeg);
__attribute__((visibility("default"))) LLVMFastMathFlags LLVMGetFastMathFlags(LLVMValueRef FPMathInst);
__attribute__((visibility("default"))) void LLVMSetFastMathFlags(LLVMValueRef FPMathInst,
                                     LLVMFastMathFlags FMF);
__attribute__((visibility("default"))) LLVMBool LLVMCanValueUseFastMathFlags(LLVMValueRef Inst);
__attribute__((visibility("default"))) LLVMBool LLVMGetIsDisjoint(LLVMValueRef Inst);
__attribute__((visibility("default"))) void LLVMSetIsDisjoint(LLVMValueRef Inst, LLVMBool IsDisjoint);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildMalloc(LLVMBuilderRef, LLVMTypeRef Ty,
                                        const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildArrayMalloc(LLVMBuilderRef, LLVMTypeRef Ty,
                                             LLVMValueRef Val,
                                             const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildMemSet(LLVMBuilderRef B, LLVMValueRef Ptr,
                                        LLVMValueRef Val, LLVMValueRef Len,
                                        unsigned Align);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildMemCpy(LLVMBuilderRef B, LLVMValueRef Dst,
                                        unsigned DstAlign, LLVMValueRef Src,
                                        unsigned SrcAlign, LLVMValueRef Size);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildMemMove(LLVMBuilderRef B, LLVMValueRef Dst,
                                         unsigned DstAlign, LLVMValueRef Src,
                                         unsigned SrcAlign, LLVMValueRef Size);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAlloca(LLVMBuilderRef, LLVMTypeRef Ty,
                                        const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildArrayAlloca(LLVMBuilderRef, LLVMTypeRef Ty,
                                             LLVMValueRef Val,
                                             const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFree(LLVMBuilderRef, LLVMValueRef PointerVal);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildLoad2(LLVMBuilderRef, LLVMTypeRef Ty,
                                       LLVMValueRef PointerVal,
                                       const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildStore(LLVMBuilderRef, LLVMValueRef Val,
                                       LLVMValueRef Ptr);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildGEP2(LLVMBuilderRef B, LLVMTypeRef Ty,
                                      LLVMValueRef Pointer,
                                      LLVMValueRef *Indices,
                                      unsigned NumIndices, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildInBoundsGEP2(LLVMBuilderRef B, LLVMTypeRef Ty,
                                              LLVMValueRef Pointer,
                                              LLVMValueRef *Indices,
                                              unsigned NumIndices,
                                              const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildGEPWithNoWrapFlags(
    LLVMBuilderRef B, LLVMTypeRef Ty, LLVMValueRef Pointer,
    LLVMValueRef *Indices, unsigned NumIndices, const char *Name,
    LLVMGEPNoWrapFlags NoWrapFlags);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildStructGEP2(LLVMBuilderRef B, LLVMTypeRef Ty,
                                            LLVMValueRef Pointer, unsigned Idx,
                                            const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildGlobalString(LLVMBuilderRef B, const char *Str,
                                              const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildGlobalStringPtr(LLVMBuilderRef B,
                                                 const char *Str,
                                                 const char *Name);
__attribute__((visibility("default"))) LLVMBool LLVMGetVolatile(LLVMValueRef MemoryAccessInst);
__attribute__((visibility("default"))) void LLVMSetVolatile(LLVMValueRef MemoryAccessInst,
                                LLVMBool IsVolatile);
__attribute__((visibility("default"))) LLVMBool LLVMGetWeak(LLVMValueRef CmpXchgInst);
__attribute__((visibility("default"))) void LLVMSetWeak(LLVMValueRef CmpXchgInst, LLVMBool IsWeak);
__attribute__((visibility("default"))) LLVMAtomicOrdering LLVMGetOrdering(LLVMValueRef MemoryAccessInst);
__attribute__((visibility("default"))) void LLVMSetOrdering(LLVMValueRef MemoryAccessInst,
                                LLVMAtomicOrdering Ordering);
__attribute__((visibility("default"))) LLVMAtomicRMWBinOp LLVMGetAtomicRMWBinOp(LLVMValueRef AtomicRMWInst);
__attribute__((visibility("default"))) void LLVMSetAtomicRMWBinOp(LLVMValueRef AtomicRMWInst,
                                      LLVMAtomicRMWBinOp BinOp);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildTrunc(LLVMBuilderRef, LLVMValueRef Val,
                                       LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildZExt(LLVMBuilderRef, LLVMValueRef Val,
                                      LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildSExt(LLVMBuilderRef, LLVMValueRef Val,
                                      LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFPToUI(LLVMBuilderRef, LLVMValueRef Val,
                                        LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFPToSI(LLVMBuilderRef, LLVMValueRef Val,
                                        LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildUIToFP(LLVMBuilderRef, LLVMValueRef Val,
                                        LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildSIToFP(LLVMBuilderRef, LLVMValueRef Val,
                                        LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFPTrunc(LLVMBuilderRef, LLVMValueRef Val,
                                         LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFPExt(LLVMBuilderRef, LLVMValueRef Val,
                                       LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildPtrToInt(LLVMBuilderRef, LLVMValueRef Val,
                                          LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildIntToPtr(LLVMBuilderRef, LLVMValueRef Val,
                                          LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildBitCast(LLVMBuilderRef, LLVMValueRef Val,
                                         LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAddrSpaceCast(LLVMBuilderRef, LLVMValueRef Val,
                                               LLVMTypeRef DestTy,
                                               const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildZExtOrBitCast(LLVMBuilderRef, LLVMValueRef Val,
                                               LLVMTypeRef DestTy,
                                               const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildSExtOrBitCast(LLVMBuilderRef, LLVMValueRef Val,
                                               LLVMTypeRef DestTy,
                                               const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildTruncOrBitCast(LLVMBuilderRef,
                                                LLVMValueRef Val,
                                                LLVMTypeRef DestTy,
                                                const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCast(LLVMBuilderRef B, LLVMOpcode Op,
                                      LLVMValueRef Val, LLVMTypeRef DestTy,
                                      const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildPointerCast(LLVMBuilderRef, LLVMValueRef Val,
                                             LLVMTypeRef DestTy,
                                             const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildIntCast2(LLVMBuilderRef, LLVMValueRef Val,
                                          LLVMTypeRef DestTy, LLVMBool IsSigned,
                                          const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFPCast(LLVMBuilderRef, LLVMValueRef Val,
                                        LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildIntCast(LLVMBuilderRef,
                                         LLVMValueRef Val,
                                         LLVMTypeRef DestTy, const char *Name);
__attribute__((visibility("default"))) LLVMOpcode LLVMGetCastOpcode(LLVMValueRef Src, LLVMBool SrcIsSigned,
                                        LLVMTypeRef DestTy,
                                        LLVMBool DestIsSigned);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildICmp(LLVMBuilderRef, LLVMIntPredicate Op,
                                      LLVMValueRef LHS, LLVMValueRef RHS,
                                      const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFCmp(LLVMBuilderRef, LLVMRealPredicate Op,
                                      LLVMValueRef LHS, LLVMValueRef RHS,
                                      const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildPhi(LLVMBuilderRef, LLVMTypeRef Ty,
                                     const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCall2(LLVMBuilderRef, LLVMTypeRef,
                                       LLVMValueRef Fn, LLVMValueRef *Args,
                                       unsigned NumArgs, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildCallWithOperandBundles(
    LLVMBuilderRef, LLVMTypeRef, LLVMValueRef Fn, LLVMValueRef *Args,
    unsigned NumArgs, LLVMOperandBundleRef *Bundles, unsigned NumBundles,
    const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildSelect(LLVMBuilderRef, LLVMValueRef If,
                                        LLVMValueRef Then, LLVMValueRef Else,
                                        const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildVAArg(LLVMBuilderRef, LLVMValueRef List,
                                       LLVMTypeRef Ty, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildExtractElement(LLVMBuilderRef,
                                                LLVMValueRef VecVal,
                                                LLVMValueRef Index,
                                                const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildInsertElement(LLVMBuilderRef,
                                               LLVMValueRef VecVal,
                                               LLVMValueRef EltVal,
                                               LLVMValueRef Index,
                                               const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildShuffleVector(LLVMBuilderRef, LLVMValueRef V1,
                                               LLVMValueRef V2,
                                               LLVMValueRef Mask,
                                               const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildExtractValue(LLVMBuilderRef,
                                              LLVMValueRef AggVal,
                                              unsigned Index, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildInsertValue(LLVMBuilderRef,
                                             LLVMValueRef AggVal,
                                             LLVMValueRef EltVal,
                                             unsigned Index, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFreeze(LLVMBuilderRef, LLVMValueRef Val,
                                        const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildIsNull(LLVMBuilderRef, LLVMValueRef Val,
                                        const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildIsNotNull(LLVMBuilderRef, LLVMValueRef Val,
                                           const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildPtrDiff2(LLVMBuilderRef, LLVMTypeRef ElemTy,
                                          LLVMValueRef LHS, LLVMValueRef RHS,
                                          const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFence(LLVMBuilderRef B,
                                       LLVMAtomicOrdering ordering,
                                       LLVMBool singleThread, const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildFenceSyncScope(LLVMBuilderRef B,
                                                LLVMAtomicOrdering ordering,
                                                unsigned SSID,
                                                const char *Name);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAtomicRMW(LLVMBuilderRef B,
                                           LLVMAtomicRMWBinOp op,
                                           LLVMValueRef PTR, LLVMValueRef Val,
                                           LLVMAtomicOrdering ordering,
                                           LLVMBool singleThread);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAtomicRMWSyncScope(
    LLVMBuilderRef B, LLVMAtomicRMWBinOp op, LLVMValueRef PTR, LLVMValueRef Val,
    LLVMAtomicOrdering ordering, unsigned SSID);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAtomicCmpXchg(
    LLVMBuilderRef B, LLVMValueRef Ptr, LLVMValueRef Cmp, LLVMValueRef New,
    LLVMAtomicOrdering SuccessOrdering, LLVMAtomicOrdering FailureOrdering,
    LLVMBool SingleThread);
__attribute__((visibility("default"))) LLVMValueRef LLVMBuildAtomicCmpXchgSyncScope(
    LLVMBuilderRef B, LLVMValueRef Ptr, LLVMValueRef Cmp, LLVMValueRef New,
    LLVMAtomicOrdering SuccessOrdering, LLVMAtomicOrdering FailureOrdering,
    unsigned SSID);
__attribute__((visibility("default"))) unsigned LLVMGetNumMaskElements(LLVMValueRef ShuffleVectorInst);
__attribute__((visibility("default"))) int LLVMGetUndefMaskElem(void);
__attribute__((visibility("default"))) int LLVMGetMaskValue(LLVMValueRef ShuffleVectorInst, unsigned Elt);
__attribute__((visibility("default"))) LLVMBool LLVMIsAtomicSingleThread(LLVMValueRef AtomicInst);
__attribute__((visibility("default"))) void LLVMSetAtomicSingleThread(LLVMValueRef AtomicInst,
                                          LLVMBool SingleThread);
__attribute__((visibility("default"))) LLVMBool LLVMIsAtomic(LLVMValueRef Inst);
__attribute__((visibility("default"))) unsigned LLVMGetAtomicSyncScopeID(LLVMValueRef AtomicInst);
__attribute__((visibility("default"))) void LLVMSetAtomicSyncScopeID(LLVMValueRef AtomicInst,
                                         unsigned SSID);
__attribute__((visibility("default"))) LLVMAtomicOrdering
LLVMGetCmpXchgSuccessOrdering(LLVMValueRef CmpXchgInst);
__attribute__((visibility("default"))) void LLVMSetCmpXchgSuccessOrdering(LLVMValueRef CmpXchgInst,
                                              LLVMAtomicOrdering Ordering);
__attribute__((visibility("default"))) LLVMAtomicOrdering
LLVMGetCmpXchgFailureOrdering(LLVMValueRef CmpXchgInst);
__attribute__((visibility("default"))) void LLVMSetCmpXchgFailureOrdering(LLVMValueRef CmpXchgInst,
                                              LLVMAtomicOrdering Ordering);
__attribute__((visibility("default"))) LLVMModuleProviderRef
LLVMCreateModuleProviderForExistingModule(LLVMModuleRef M);
__attribute__((visibility("default"))) void LLVMDisposeModuleProvider(LLVMModuleProviderRef M);
__attribute__((visibility("default"))) LLVMBool LLVMCreateMemoryBufferWithContentsOfFile(
    const char *Path, LLVMMemoryBufferRef *OutMemBuf, char **OutMessage);
__attribute__((visibility("default"))) LLVMBool LLVMCreateMemoryBufferWithSTDIN(
    LLVMMemoryBufferRef *OutMemBuf, char **OutMessage);
__attribute__((visibility("default"))) LLVMMemoryBufferRef LLVMCreateMemoryBufferWithMemoryRange(
    const char *InputData, size_t InputDataLength, const char *BufferName,
    LLVMBool RequiresNullTerminator);
__attribute__((visibility("default"))) LLVMMemoryBufferRef LLVMCreateMemoryBufferWithMemoryRangeCopy(
    const char *InputData, size_t InputDataLength, const char *BufferName);
__attribute__((visibility("default"))) const char *LLVMGetBufferStart(LLVMMemoryBufferRef MemBuf);
__attribute__((visibility("default"))) size_t LLVMGetBufferSize(LLVMMemoryBufferRef MemBuf);
__attribute__((visibility("default"))) void LLVMDisposeMemoryBuffer(LLVMMemoryBufferRef MemBuf);
__attribute__((visibility("default"))) LLVMPassManagerRef LLVMCreatePassManager(void);
__attribute__((visibility("default"))) LLVMPassManagerRef
LLVMCreateFunctionPassManagerForModule(LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMPassManagerRef
LLVMCreateFunctionPassManager(LLVMModuleProviderRef MP);
__attribute__((visibility("default"))) LLVMBool LLVMRunPassManager(LLVMPassManagerRef PM, LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMBool LLVMInitializeFunctionPassManager(LLVMPassManagerRef FPM);
__attribute__((visibility("default"))) LLVMBool LLVMRunFunctionPassManager(LLVMPassManagerRef FPM,
                                               LLVMValueRef F);
__attribute__((visibility("default"))) LLVMBool LLVMFinalizeFunctionPassManager(LLVMPassManagerRef FPM);
__attribute__((visibility("default"))) void LLVMDisposePassManager(LLVMPassManagerRef PM);
__attribute__((visibility("default"))) LLVMBool LLVMStartMultithreaded(void);
__attribute__((visibility("default"))) void LLVMStopMultithreaded(void);
__attribute__((visibility("default"))) LLVMBool LLVMIsMultithreaded(void);
#pragma clang diagnostic pop
#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
enum LLVMByteOrdering { LLVMBigEndian, LLVMLittleEndian };
typedef struct LLVMOpaqueTargetData *LLVMTargetDataRef;
typedef struct LLVMOpaqueTargetLibraryInfotData *LLVMTargetLibraryInfoRef;
__attribute__((visibility("default"))) void LLVMInitializeAArch64TargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeAMDGPUTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeARMTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeAVRTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeBPFTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeHexagonTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeLanaiTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeLoongArchTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeMipsTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeMSP430TargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeNVPTXTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializePowerPCTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeRISCVTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeSparcTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeSPIRVTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeSystemZTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeVETargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeWebAssemblyTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeX86TargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeXCoreTargetInfo(void);
__attribute__((visibility("default"))) void LLVMInitializeAArch64Target(void);
__attribute__((visibility("default"))) void LLVMInitializeAMDGPUTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeARMTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeAVRTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeBPFTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeHexagonTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeLanaiTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeLoongArchTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeMipsTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeMSP430Target(void);
__attribute__((visibility("default"))) void LLVMInitializeNVPTXTarget(void);
__attribute__((visibility("default"))) void LLVMInitializePowerPCTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeRISCVTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeSparcTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeSPIRVTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeSystemZTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeVETarget(void);
__attribute__((visibility("default"))) void LLVMInitializeWebAssemblyTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeX86Target(void);
__attribute__((visibility("default"))) void LLVMInitializeXCoreTarget(void);
__attribute__((visibility("default"))) void LLVMInitializeAArch64TargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeAMDGPUTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeARMTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeAVRTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeBPFTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeHexagonTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeLanaiTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeLoongArchTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeMipsTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeMSP430TargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeNVPTXTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializePowerPCTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeRISCVTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeSparcTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeSPIRVTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeSystemZTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeVETargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeWebAssemblyTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeX86TargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeXCoreTargetMC(void);
__attribute__((visibility("default"))) void LLVMInitializeAArch64AsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeAMDGPUAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeARMAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeAVRAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeBPFAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeHexagonAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeLanaiAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeLoongArchAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeMipsAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeMSP430AsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeNVPTXAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializePowerPCAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeRISCVAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeSparcAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeSPIRVAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeSystemZAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeVEAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeWebAssemblyAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeX86AsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeXCoreAsmPrinter(void);
__attribute__((visibility("default"))) void LLVMInitializeAArch64AsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeAMDGPUAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeARMAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeAVRAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeBPFAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeHexagonAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeLanaiAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeLoongArchAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeMipsAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeMSP430AsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializePowerPCAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeRISCVAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeSparcAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeSystemZAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeVEAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeWebAssemblyAsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeX86AsmParser(void);
__attribute__((visibility("default"))) void LLVMInitializeAArch64Disassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeAMDGPUDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeARMDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeAVRDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeBPFDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeHexagonDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeLanaiDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeLoongArchDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeMipsDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeMSP430Disassembler(void);
__attribute__((visibility("default"))) void LLVMInitializePowerPCDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeRISCVDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeSparcDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeSystemZDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeVEDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeWebAssemblyDisassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeX86Disassembler(void);
__attribute__((visibility("default"))) void LLVMInitializeXCoreDisassembler(void);
static inline void LLVMInitializeAllTargetInfos(void) {
LLVMInitializeAArch64TargetInfo();
LLVMInitializeAMDGPUTargetInfo();
LLVMInitializeARMTargetInfo();
LLVMInitializeAVRTargetInfo();
LLVMInitializeBPFTargetInfo();
LLVMInitializeHexagonTargetInfo();
LLVMInitializeLanaiTargetInfo();
LLVMInitializeLoongArchTargetInfo();
LLVMInitializeMipsTargetInfo();
LLVMInitializeMSP430TargetInfo();
LLVMInitializeNVPTXTargetInfo();
LLVMInitializePowerPCTargetInfo();
LLVMInitializeRISCVTargetInfo();
LLVMInitializeSparcTargetInfo();
LLVMInitializeSPIRVTargetInfo();
LLVMInitializeSystemZTargetInfo();
LLVMInitializeVETargetInfo();
LLVMInitializeWebAssemblyTargetInfo();
LLVMInitializeX86TargetInfo();
LLVMInitializeXCoreTargetInfo();

}
static inline void LLVMInitializeAllTargets(void) {
LLVMInitializeAArch64Target();
LLVMInitializeAMDGPUTarget();
LLVMInitializeARMTarget();
LLVMInitializeAVRTarget();
LLVMInitializeBPFTarget();
LLVMInitializeHexagonTarget();
LLVMInitializeLanaiTarget();
LLVMInitializeLoongArchTarget();
LLVMInitializeMipsTarget();
LLVMInitializeMSP430Target();
LLVMInitializeNVPTXTarget();
LLVMInitializePowerPCTarget();
LLVMInitializeRISCVTarget();
LLVMInitializeSparcTarget();
LLVMInitializeSPIRVTarget();
LLVMInitializeSystemZTarget();
LLVMInitializeVETarget();
LLVMInitializeWebAssemblyTarget();
LLVMInitializeX86Target();
LLVMInitializeXCoreTarget();

}
static inline void LLVMInitializeAllTargetMCs(void) {
LLVMInitializeAArch64TargetMC();
LLVMInitializeAMDGPUTargetMC();
LLVMInitializeARMTargetMC();
LLVMInitializeAVRTargetMC();
LLVMInitializeBPFTargetMC();
LLVMInitializeHexagonTargetMC();
LLVMInitializeLanaiTargetMC();
LLVMInitializeLoongArchTargetMC();
LLVMInitializeMipsTargetMC();
LLVMInitializeMSP430TargetMC();
LLVMInitializeNVPTXTargetMC();
LLVMInitializePowerPCTargetMC();
LLVMInitializeRISCVTargetMC();
LLVMInitializeSparcTargetMC();
LLVMInitializeSPIRVTargetMC();
LLVMInitializeSystemZTargetMC();
LLVMInitializeVETargetMC();
LLVMInitializeWebAssemblyTargetMC();
LLVMInitializeX86TargetMC();
LLVMInitializeXCoreTargetMC();

}
static inline void LLVMInitializeAllAsmPrinters(void) {
LLVMInitializeAArch64AsmPrinter();
LLVMInitializeAMDGPUAsmPrinter();
LLVMInitializeARMAsmPrinter();
LLVMInitializeAVRAsmPrinter();
LLVMInitializeBPFAsmPrinter();
LLVMInitializeHexagonAsmPrinter();
LLVMInitializeLanaiAsmPrinter();
LLVMInitializeLoongArchAsmPrinter();
LLVMInitializeMipsAsmPrinter();
LLVMInitializeMSP430AsmPrinter();
LLVMInitializeNVPTXAsmPrinter();
LLVMInitializePowerPCAsmPrinter();
LLVMInitializeRISCVAsmPrinter();
LLVMInitializeSparcAsmPrinter();
LLVMInitializeSPIRVAsmPrinter();
LLVMInitializeSystemZAsmPrinter();
LLVMInitializeVEAsmPrinter();
LLVMInitializeWebAssemblyAsmPrinter();
LLVMInitializeX86AsmPrinter();
LLVMInitializeXCoreAsmPrinter();

}
static inline void LLVMInitializeAllAsmParsers(void) {
LLVMInitializeAArch64AsmParser();
LLVMInitializeAMDGPUAsmParser();
LLVMInitializeARMAsmParser();
LLVMInitializeAVRAsmParser();
LLVMInitializeBPFAsmParser();
LLVMInitializeHexagonAsmParser();
LLVMInitializeLanaiAsmParser();
LLVMInitializeLoongArchAsmParser();
LLVMInitializeMipsAsmParser();
LLVMInitializeMSP430AsmParser();
LLVMInitializePowerPCAsmParser();
LLVMInitializeRISCVAsmParser();
LLVMInitializeSparcAsmParser();
LLVMInitializeSystemZAsmParser();
LLVMInitializeVEAsmParser();
LLVMInitializeWebAssemblyAsmParser();
LLVMInitializeX86AsmParser();

}
static inline void LLVMInitializeAllDisassemblers(void) {
LLVMInitializeAArch64Disassembler();
LLVMInitializeAMDGPUDisassembler();
LLVMInitializeARMDisassembler();
LLVMInitializeAVRDisassembler();
LLVMInitializeBPFDisassembler();
LLVMInitializeHexagonDisassembler();
LLVMInitializeLanaiDisassembler();
LLVMInitializeLoongArchDisassembler();
LLVMInitializeMipsDisassembler();
LLVMInitializeMSP430Disassembler();
LLVMInitializePowerPCDisassembler();
LLVMInitializeRISCVDisassembler();
LLVMInitializeSparcDisassembler();
LLVMInitializeSystemZDisassembler();
LLVMInitializeVEDisassembler();
LLVMInitializeWebAssemblyDisassembler();
LLVMInitializeX86Disassembler();
LLVMInitializeXCoreDisassembler();

}
static inline LLVMBool LLVMInitializeNativeTarget(void) {
  LLVMInitializeAArch64TargetInfo();
  LLVMInitializeAArch64Target();
  LLVMInitializeAArch64TargetMC();
  return 0;
}
static inline LLVMBool LLVMInitializeNativeAsmParser(void) {
  LLVMInitializeAArch64AsmParser();
  return 0;
}
static inline LLVMBool LLVMInitializeNativeAsmPrinter(void) {
  LLVMInitializeAArch64AsmPrinter();
  return 0;
}
static inline LLVMBool LLVMInitializeNativeDisassembler(void) {
  LLVMInitializeAArch64Disassembler();
  return 0;
}
__attribute__((visibility("default"))) LLVMTargetDataRef LLVMGetModuleDataLayout(LLVMModuleRef M);
__attribute__((visibility("default"))) void LLVMSetModuleDataLayout(LLVMModuleRef M, LLVMTargetDataRef DL);
__attribute__((visibility("default"))) LLVMTargetDataRef LLVMCreateTargetData(const char *StringRep);
__attribute__((visibility("default"))) void LLVMDisposeTargetData(LLVMTargetDataRef TD);
__attribute__((visibility("default"))) void LLVMAddTargetLibraryInfo(LLVMTargetLibraryInfoRef TLI,
                                         LLVMPassManagerRef PM);
__attribute__((visibility("default"))) char *LLVMCopyStringRepOfTargetData(LLVMTargetDataRef TD);
__attribute__((visibility("default"))) enum LLVMByteOrdering LLVMByteOrder(LLVMTargetDataRef TD);
__attribute__((visibility("default"))) unsigned LLVMPointerSize(LLVMTargetDataRef TD);
__attribute__((visibility("default"))) unsigned LLVMPointerSizeForAS(LLVMTargetDataRef TD, unsigned AS);
__attribute__((visibility("default"))) LLVMTypeRef LLVMIntPtrType(LLVMTargetDataRef TD);
__attribute__((visibility("default"))) LLVMTypeRef LLVMIntPtrTypeForAS(LLVMTargetDataRef TD, unsigned AS);
__attribute__((visibility("default"))) LLVMTypeRef LLVMIntPtrTypeInContext(LLVMContextRef C,
                                               LLVMTargetDataRef TD);
__attribute__((visibility("default"))) LLVMTypeRef LLVMIntPtrTypeForASInContext(LLVMContextRef C,
                                                    LLVMTargetDataRef TD,
                                                    unsigned AS);
__attribute__((visibility("default"))) unsigned long long LLVMSizeOfTypeInBits(LLVMTargetDataRef TD,
                                                   LLVMTypeRef Ty);
__attribute__((visibility("default"))) unsigned long long LLVMStoreSizeOfType(LLVMTargetDataRef TD,
                                                  LLVMTypeRef Ty);
__attribute__((visibility("default"))) unsigned long long LLVMABISizeOfType(LLVMTargetDataRef TD,
                                                LLVMTypeRef Ty);
__attribute__((visibility("default"))) unsigned LLVMABIAlignmentOfType(LLVMTargetDataRef TD,
                                           LLVMTypeRef Ty);
__attribute__((visibility("default"))) unsigned LLVMCallFrameAlignmentOfType(LLVMTargetDataRef TD,
                                                 LLVMTypeRef Ty);
__attribute__((visibility("default"))) unsigned LLVMPreferredAlignmentOfType(LLVMTargetDataRef TD,
                                                 LLVMTypeRef Ty);
__attribute__((visibility("default"))) unsigned LLVMPreferredAlignmentOfGlobal(LLVMTargetDataRef TD,
                                                   LLVMValueRef GlobalVar);
__attribute__((visibility("default"))) unsigned LLVMElementAtOffset(LLVMTargetDataRef TD,
                                        LLVMTypeRef StructTy,
                                        unsigned long long Offset);
__attribute__((visibility("default"))) unsigned long long LLVMOffsetOfElement(LLVMTargetDataRef TD,
                                                  LLVMTypeRef StructTy,
                                                  unsigned Element);
#pragma clang diagnostic pop
#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
typedef struct LLVMOpaqueTargetMachineOptions *LLVMTargetMachineOptionsRef;
typedef struct LLVMOpaqueTargetMachine *LLVMTargetMachineRef;
typedef struct LLVMTarget *LLVMTargetRef;
typedef enum {
    LLVMCodeGenLevelNone,
    LLVMCodeGenLevelLess,
    LLVMCodeGenLevelDefault,
    LLVMCodeGenLevelAggressive
} LLVMCodeGenOptLevel;
typedef enum {
    LLVMRelocDefault,
    LLVMRelocStatic,
    LLVMRelocPIC,
    LLVMRelocDynamicNoPic,
    LLVMRelocROPI,
    LLVMRelocRWPI,
    LLVMRelocROPI_RWPI
} LLVMRelocMode;
typedef enum {
    LLVMCodeModelDefault,
    LLVMCodeModelJITDefault,
    LLVMCodeModelTiny,
    LLVMCodeModelSmall,
    LLVMCodeModelKernel,
    LLVMCodeModelMedium,
    LLVMCodeModelLarge
} LLVMCodeModel;
typedef enum {
    LLVMAssemblyFile,
    LLVMObjectFile
} LLVMCodeGenFileType;
typedef enum {
  LLVMGlobalISelAbortEnable,
  LLVMGlobalISelAbortDisable,
  LLVMGlobalISelAbortDisableWithDiag,
} LLVMGlobalISelAbortMode;
__attribute__((visibility("default"))) LLVMTargetRef LLVMGetFirstTarget(void);
__attribute__((visibility("default"))) LLVMTargetRef LLVMGetNextTarget(LLVMTargetRef T);
__attribute__((visibility("default"))) LLVMTargetRef LLVMGetTargetFromName(const char *Name);
__attribute__((visibility("default"))) LLVMBool LLVMGetTargetFromTriple(const char *Triple,
                                            LLVMTargetRef *T,
                                            char **ErrorMessage);
__attribute__((visibility("default"))) const char *LLVMGetTargetName(LLVMTargetRef T);
__attribute__((visibility("default"))) const char *LLVMGetTargetDescription(LLVMTargetRef T);
__attribute__((visibility("default"))) LLVMBool LLVMTargetHasJIT(LLVMTargetRef T);
__attribute__((visibility("default"))) LLVMBool LLVMTargetHasTargetMachine(LLVMTargetRef T);
__attribute__((visibility("default"))) LLVMBool LLVMTargetHasAsmBackend(LLVMTargetRef T);
__attribute__((visibility("default"))) LLVMTargetMachineOptionsRef LLVMCreateTargetMachineOptions(void);
__attribute__((visibility("default"))) void
LLVMDisposeTargetMachineOptions(LLVMTargetMachineOptionsRef Options);
__attribute__((visibility("default"))) void
LLVMTargetMachineOptionsSetCPU(LLVMTargetMachineOptionsRef Options,
                               const char *CPU);
__attribute__((visibility("default"))) void
LLVMTargetMachineOptionsSetFeatures(LLVMTargetMachineOptionsRef Options,
                                    const char *Features);
__attribute__((visibility("default"))) void
LLVMTargetMachineOptionsSetABI(LLVMTargetMachineOptionsRef Options,
                               const char *ABI);
__attribute__((visibility("default"))) void
LLVMTargetMachineOptionsSetCodeGenOptLevel(LLVMTargetMachineOptionsRef Options,
                                           LLVMCodeGenOptLevel Level);
__attribute__((visibility("default"))) void
LLVMTargetMachineOptionsSetRelocMode(LLVMTargetMachineOptionsRef Options,
                                     LLVMRelocMode Reloc);
__attribute__((visibility("default"))) void
LLVMTargetMachineOptionsSetCodeModel(LLVMTargetMachineOptionsRef Options,
                                     LLVMCodeModel CodeModel);
__attribute__((visibility("default"))) LLVMTargetMachineRef LLVMCreateTargetMachineWithOptions(
    LLVMTargetRef T, const char *Triple, LLVMTargetMachineOptionsRef Options);
__attribute__((visibility("default"))) LLVMTargetMachineRef LLVMCreateTargetMachine(
    LLVMTargetRef T, const char *Triple, const char *CPU, const char *Features,
    LLVMCodeGenOptLevel Level, LLVMRelocMode Reloc, LLVMCodeModel CodeModel);
__attribute__((visibility("default"))) void LLVMDisposeTargetMachine(LLVMTargetMachineRef T);
__attribute__((visibility("default"))) LLVMTargetRef LLVMGetTargetMachineTarget(LLVMTargetMachineRef T);
__attribute__((visibility("default"))) char *LLVMGetTargetMachineTriple(LLVMTargetMachineRef T);
__attribute__((visibility("default"))) char *LLVMGetTargetMachineCPU(LLVMTargetMachineRef T);
__attribute__((visibility("default"))) char *LLVMGetTargetMachineFeatureString(LLVMTargetMachineRef T);
__attribute__((visibility("default"))) LLVMTargetDataRef LLVMCreateTargetDataLayout(LLVMTargetMachineRef T);
__attribute__((visibility("default"))) void LLVMSetTargetMachineAsmVerbosity(LLVMTargetMachineRef T,
                                                 LLVMBool VerboseAsm);
__attribute__((visibility("default"))) void LLVMSetTargetMachineFastISel(LLVMTargetMachineRef T,
                                             LLVMBool Enable);
__attribute__((visibility("default"))) void LLVMSetTargetMachineGlobalISel(LLVMTargetMachineRef T,
                                               LLVMBool Enable);
__attribute__((visibility("default"))) void
LLVMSetTargetMachineGlobalISelAbort(LLVMTargetMachineRef T,
                                    LLVMGlobalISelAbortMode Mode);
__attribute__((visibility("default"))) void LLVMSetTargetMachineMachineOutliner(LLVMTargetMachineRef T,
                                                    LLVMBool Enable);
__attribute__((visibility("default"))) LLVMBool LLVMTargetMachineEmitToFile(LLVMTargetMachineRef T,
                                                LLVMModuleRef M,
                                                const char *Filename,
                                                LLVMCodeGenFileType codegen,
                                                char **ErrorMessage);
__attribute__((visibility("default"))) LLVMBool LLVMTargetMachineEmitToMemoryBuffer(
    LLVMTargetMachineRef T, LLVMModuleRef M, LLVMCodeGenFileType codegen,
    char **ErrorMessage, LLVMMemoryBufferRef *OutMemBuf);
__attribute__((visibility("default"))) char *LLVMGetDefaultTargetTriple(void);
__attribute__((visibility("default"))) char *LLVMNormalizeTargetTriple(const char *triple);
__attribute__((visibility("default"))) char *LLVMGetHostCPUName(void);
__attribute__((visibility("default"))) char *LLVMGetHostCPUFeatures(void);
__attribute__((visibility("default"))) void LLVMAddAnalysisPasses(LLVMTargetMachineRef T,
                                      LLVMPassManagerRef PM);
#pragma clang diagnostic pop
typedef struct CodegenMap {
    HashMap *map;
    struct CodegenMap *parent;
} CodegenMap;
struct CodegenContext {
    TypeStore *store;
    LLVMContextRef context;
    LLVMModuleRef module;
    LLVMBuilderRef builder;
    LLVMTargetRef target;
    LLVMTargetMachineRef machine;
    LLVMTargetDataRef target_data;
    HashMap *globals;
    HashMap *type_cache;
    CodegenMap *locals;
    LLVMBasicBlockRef loop_cond_bb;
    LLVMBasicBlockRef loop_end_bb;
    int opt_level;
    ModuleLoader *loader;
    Type *current_func_type;
    LLVMValueRef sret_ptr;
    DynArray *deferred_actions;
    size_t loop_defer_count;
};
CodegenMap *codegen_map_create(CodegenContext *ctx, CodegenMap *parent);
void codegen_map_destroy(CodegenMap *m);
void codegen_map_put(CodegenMap *m, void *key, LLVMValueRef val);
LLVMValueRef codegen_map_get(CodegenMap *m, void *key);
LLVMTypeRef get_llvm_type(CodegenContext *ctx, Type *t);
LLVMTypeRef get_llvm_function_type(CodegenContext *ctx, Type *t);
_Bool type_is_address_only(Type *t);
_Bool type_is_indirect(CodegenContext *ctx, Type *t);
LLVMValueRef codegen_load_value(CodegenContext *ctx, LLVMValueRef ptr, Type *type);
LLVMValueRef codegen_materialize_slice(CodegenContext *ctx, LLVMValueRef val, Type *src_type, Type *dst_type);
LLVMValueRef create_entry_block_alloca(CodegenContext *ctx, LLVMTypeRef ty, const char *name);
char* mangle_name(CodegenContext *ctx, CompilationUnit *unit, InternResult *symbol_name);
size_t struct_field_index(Type *struct_type, const char *field_name);
LLVMValueRef codegen_expr(CodegenContext *ctx, AstNode *expr);
LLVMValueRef codegen_lvalue(CodegenContext *ctx, AstNode *expr);
void codegen_statement(CodegenContext *ctx, AstNode *stmt);
LLVMValueRef codegen_expr_literal(CodegenContext *ctx, AstNode *expr);
LLVMValueRef codegen_expr_ident(CodegenContext *ctx, AstNode *expr);
LLVMValueRef codegen_expr_ops(CodegenContext *ctx, AstNode *expr);
LLVMValueRef codegen_expr_call(CodegenContext *ctx, AstNode *expr);
void codegen_decl_proto(CodegenContext *ctx, AstNode *decl);
void codegen_decl_body(CodegenContext *ctx, AstNode *decl);

static void codegen_intrinsic_print_value(CodegenContext *ctx, LLVMValueRef val, Type *t);
static void codegen_intrinsic_print_str_lit(CodegenContext *ctx, const char *s) {
    LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8TypeInContext(ctx->context), 0);
    LLVMTypeRef fn_ty = LLVMFunctionType(LLVMVoidTypeInContext(ctx->context), &i8ptr, 1, 0);
    LLVMValueRef fn = LLVMGetNamedFunction(ctx->module, "print_str");
    if (!fn) fn = LLVMAddFunction(ctx->module, "print_str", fn_ty);
    LLVMValueRef str = LLVMBuildGlobalStringPtr(ctx->builder, s, "print_tmp");
    LLVMBuildCall2(ctx->builder, fn_ty, fn, &str, 1, "");
}
static void codegen_intrinsic_print_value(CodegenContext *ctx, LLVMValueRef val, Type *t) {
    if (!t) return;
    if (t->kind == TYPE_PRIMITIVE) {
        const char *fn_name = ((void*)0);
        LLVMTypeRef param_ty = ((void*)0);
        switch (t->as.primitive) {
            case PRIM_I32: fn_name = "print_i32"; param_ty = LLVMInt32TypeInContext(ctx->context); break;
            case PRIM_I64: fn_name = "print_i64"; param_ty = LLVMInt64TypeInContext(ctx->context); break;
            case PRIM_F32: fn_name = "print_f32"; param_ty = LLVMFloatTypeInContext(ctx->context); break;
            case PRIM_F64: fn_name = "print_f64"; param_ty = LLVMDoubleTypeInContext(ctx->context); break;
            case PRIM_BOOL: fn_name = "print_bool"; param_ty = LLVMInt32TypeInContext(ctx->context); break;
            case PRIM_CHAR: fn_name = "print_char"; param_ty = LLVMInt8TypeInContext(ctx->context); break;
            default: break;
        }
        if (fn_name) {
            LLVMTypeRef fn_ty = LLVMFunctionType(LLVMVoidTypeInContext(ctx->context), &param_ty, 1, 0);
            LLVMValueRef fn = LLVMGetNamedFunction(ctx->module, fn_name);
            if (!fn) fn = LLVMAddFunction(ctx->module, fn_name, fn_ty);
            LLVMValueRef arg = val;
            if (t->as.primitive == PRIM_BOOL) {
                arg = LLVMBuildZExt(ctx->builder, val, param_ty, "bool_to_i32");
            }
            LLVMBuildCall2(ctx->builder, fn_ty, fn, &arg, 1, "");
        }
    }
    else if (t->kind == TYPE_POINTER) {
        if (t == ctx->store->t_str || (t->as.ptr.base->kind == TYPE_PRIMITIVE && t->as.ptr.base->as.primitive == PRIM_CHAR)) {
            LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8TypeInContext(ctx->context), 0);
            LLVMTypeRef fn_ty = LLVMFunctionType(LLVMVoidTypeInContext(ctx->context), &i8ptr, 1, 0);
            LLVMValueRef fn = LLVMGetNamedFunction(ctx->module, "print_str");
            if (!fn) fn = LLVMAddFunction(ctx->module, "print_str", fn_ty);
            LLVMValueRef arg = LLVMBuildBitCast(ctx->builder, val, i8ptr, "str_cast");
            LLVMBuildCall2(ctx->builder, fn_ty, fn, &arg, 1, "");
            return;
        }
        LLVMBasicBlockRef current_bb = LLVMGetInsertBlock(ctx->builder);
        LLVMValueRef current_func = LLVMGetBasicBlockParent(current_bb);
        LLVMBasicBlockRef null_bb = LLVMAppendBasicBlockInContext(ctx->context, current_func, "print_null");
        LLVMBasicBlockRef ptr_bb = LLVMAppendBasicBlockInContext(ctx->context, current_func, "print_ptr_val");
        LLVMBasicBlockRef end_bb = LLVMAppendBasicBlockInContext(ctx->context, current_func, "print_ptr_end");
        LLVMValueRef is_null = LLVMBuildICmp(ctx->builder, LLVMIntEQ, val, LLVMConstNull(LLVMTypeOf(val)), "is_null");
        LLVMBuildCondBr(ctx->builder, is_null, null_bb, ptr_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, null_bb);
        codegen_intrinsic_print_str_lit(ctx, "null");
        LLVMBuildBr(ctx->builder, end_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, ptr_bb);
        LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8TypeInContext(ctx->context), 0);
        LLVMTypeRef fn_ty = LLVMFunctionType(LLVMVoidTypeInContext(ctx->context), &i8ptr, 1, 0);
        LLVMValueRef fn = LLVMGetNamedFunction(ctx->module, "print_ptr");
        if (!fn) fn = LLVMAddFunction(ctx->module, "print_ptr", fn_ty);
        LLVMValueRef arg = LLVMBuildBitCast(ctx->builder, val, i8ptr, "ptr_cast");
        LLVMBuildCall2(ctx->builder, fn_ty, fn, &arg, 1, "");
        LLVMBuildBr(ctx->builder, end_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, end_bb);
    }
    else if (t->kind == TYPE_STRUCT) {
        codegen_intrinsic_print_str_lit(ctx, "{ ");
        for (size_t i = 0; i < t->as.struct_type.field_count; i++) {
            if (i > 0) codegen_intrinsic_print_str_lit(ctx, ", ");
            Slice *fname = (Slice*)t->as.struct_type.fields[i].name->key;
            char field_prefix[256];
            __builtin___snprintf_chk (field_prefix, sizeof(field_prefix), 0, __builtin_object_size (field_prefix, 2 > 1 ? 1 : 0), "%.*s: ", (int)fname->len, fname->ptr);
            codegen_intrinsic_print_str_lit(ctx, field_prefix);
            LLVMValueRef field_val;
            LLVMTypeRef struct_ty = get_llvm_type(ctx, t);
            if (LLVMGetTypeKind(LLVMTypeOf(val)) == LLVMPointerTypeKind) {
                field_val = LLVMBuildStructGEP2(ctx->builder, struct_ty, val, (unsigned)i, "field_ptr");
                field_val = codegen_load_value(ctx, field_val, t->as.struct_type.fields[i].type);
            } else {
                field_val = LLVMBuildExtractValue(ctx->builder, val, (unsigned)i, "field_val");
            }
            codegen_intrinsic_print_value(ctx, field_val, t->as.struct_type.fields[i].type);
        }
        codegen_intrinsic_print_str_lit(ctx, " }");
    }
    else if (t->kind == TYPE_ARRAY || t->kind == TYPE_SLICE) {
        codegen_intrinsic_print_str_lit(ctx, "[");
        LLVMValueRef ptr = ((void*)0);
        LLVMValueRef len = ((void*)0);
        Type *base_type = (t->kind == TYPE_ARRAY) ? t->as.array.base : t->as.slice.base;
        LLVMTypeRef elem_ty = get_llvm_type(ctx, base_type);
        if (t->kind == TYPE_ARRAY) {
            ptr = LLVMBuildBitCast(ctx->builder, val, LLVMPointerType(elem_ty, 0), "arr_ptr");
            len = LLVMConstInt(LLVMInt64TypeInContext(ctx->context), (unsigned long long)t->as.array.size, 0);
        } else {
            LLVMValueRef slice_struct = val;
            if (LLVMGetTypeKind(LLVMTypeOf(val)) == LLVMPointerTypeKind) {
                slice_struct = LLVMBuildLoad2(ctx->builder, get_llvm_type(ctx, t), val, "slice_load");
            }
            ptr = LLVMBuildExtractValue(ctx->builder, slice_struct, 0, "slice_ptr");
            ptr = LLVMBuildBitCast(ctx->builder, ptr, LLVMPointerType(elem_ty, 0), "slice_ptr_cast");
            len = LLVMBuildExtractValue(ctx->builder, slice_struct, 1, "slice_len");
        }
        LLVMValueRef current_func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));
        LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(ctx->context, current_func, "print_loop_cond");
        LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(ctx->context, current_func, "print_loop_body");
        LLVMBasicBlockRef end_bb = LLVMAppendBasicBlockInContext(ctx->context, current_func, "print_loop_end");
        LLVMValueRef index_ptr = create_entry_block_alloca(ctx, LLVMInt64TypeInContext(ctx->context), "print_idx");
        LLVMBuildStore(ctx->builder, LLVMConstInt(LLVMInt64TypeInContext(ctx->context), 0, 0), index_ptr);
        LLVMBuildBr(ctx->builder, cond_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, cond_bb);
        LLVMValueRef curr_idx = LLVMBuildLoad2(ctx->builder, LLVMInt64TypeInContext(ctx->context), index_ptr, "curr_idx");
        LLVMValueRef cond = LLVMBuildICmp(ctx->builder, LLVMIntULT, curr_idx, len, "loop_cond");
        LLVMBuildCondBr(ctx->builder, cond, body_bb, end_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, body_bb);
        LLVMBasicBlockRef comma_bb = LLVMAppendBasicBlockInContext(ctx->context, current_func, "print_comma");
        LLVMBasicBlockRef no_comma_bb = LLVMAppendBasicBlockInContext(ctx->context, current_func, "print_no_comma");
        LLVMValueRef is_not_first = LLVMBuildICmp(ctx->builder, LLVMIntUGT, curr_idx, LLVMConstInt(LLVMInt64TypeInContext(ctx->context), 0, 0), "is_not_first");
        LLVMBuildCondBr(ctx->builder, is_not_first, comma_bb, no_comma_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, comma_bb);
        codegen_intrinsic_print_str_lit(ctx, ", ");
        LLVMBuildBr(ctx->builder, no_comma_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, no_comma_bb);
        LLVMValueRef elem_ptr = LLVMBuildGEP2(ctx->builder, elem_ty, ptr, &curr_idx, 1, "elem_ptr");
        LLVMValueRef elem_val = codegen_load_value(ctx, elem_ptr, base_type);
        codegen_intrinsic_print_value(ctx, elem_val, base_type);
        LLVMValueRef next_idx = LLVMBuildAdd(ctx->builder, curr_idx, LLVMConstInt(LLVMInt64TypeInContext(ctx->context), 1, 0), "next_idx");
        LLVMBuildStore(ctx->builder, next_idx, index_ptr);
        LLVMBuildBr(ctx->builder, cond_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, end_bb);
        codegen_intrinsic_print_str_lit(ctx, "]");
    }
}
LLVMValueRef codegen_expr_call(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) {
        AstCallExpr *c = &expr->data.call_expr;
        const char *callee_name = "<complex>";
        if (c->callee->node_type == AST_IDENTIFIER) {
            callee_name = ((Slice*)c->callee->data.identifier.intern_result->key)->ptr;
        }
        ice_impl_at("./src/codegen/codegen_call.c", 237, (expr)->filename, (expr)->span, "Call to '%s' missing type. (Sema failure?)", callee_name);
    }
    AstCallExpr *call = &expr->data.call_expr;
    if (call->callee->node_type == AST_IDENTIFIER) {
        Symbol *sym = call->callee->data.identifier.symbol;
        if (sym && sym->kind == SYMBOL_VALUE_INTRINSIC) {
            if (sym->intrinsic_kind == INTRINSIC_PRINT || sym->intrinsic_kind == INTRINSIC_PRINT_NEWLINE) {
                _Bool newline = (sym->intrinsic_kind == INTRINSIC_PRINT_NEWLINE);
                size_t arg_count = call->args ? call->args->count : 0;
                for (size_t i = 0; i < arg_count; i++) {
                    AstNode *arg = *(AstNode**)dynarray_get(call->args, i);
                    LLVMValueRef val = codegen_expr(ctx, arg);
                    codegen_intrinsic_print_value(ctx, val, arg->type);
                }
                if (newline) {
                    LLVMTypeRef fn_ty = LLVMFunctionType(LLVMVoidTypeInContext(ctx->context), ((void*)0), 0, 0);
                    LLVMValueRef fn = LLVMGetNamedFunction(ctx->module, "print_newline");
                    if (!fn) fn = LLVMAddFunction(ctx->module, "print_newline", fn_ty);
                    LLVMBuildCall2(ctx->builder, fn_ty, fn, ((void*)0), 0, "");
                }
                return ((void*)0);
            }
        }
    }
    LLVMValueRef callee = codegen_expr(ctx, call->callee);
    Type *fn_type = call->callee->type;
    if (fn_type->kind == TYPE_POINTER) fn_type = fn_type->as.ptr.base;
    if (!fn_type || fn_type->kind != TYPE_FUNCTION) ice_impl("./src/codegen/codegen_call.c", 279, "Callee must be a function type");
    _Bool sret = type_is_indirect(ctx, fn_type->as.func.return_type);
    size_t param_count = fn_type->as.func.param_count;
    size_t llvm_arg_count = param_count + (sret ? 1 : 0);
    LLVMValueRef *args = ((void*)0);
    if (llvm_arg_count > 0) args = xmalloc(sizeof(LLVMValueRef) * llvm_arg_count);
    size_t idx = 0;
    LLVMValueRef sret_alloca = ((void*)0);
    if (sret) {
        LLVMTypeRef ret_ty = get_llvm_type(ctx, fn_type->as.func.return_type);
        sret_alloca = create_entry_block_alloca(ctx, ret_ty, "sret_tmp");
        args[idx++] = sret_alloca;
    }
    for (size_t i = 0; i < param_count; i++) {
        AstNode *arg_node = *(AstNode**)dynarray_get(call->args, i);
        Type *param_ty = fn_type->as.func.params[i];
        if (type_is_indirect(ctx, param_ty)) {
            args[idx++] = codegen_lvalue(ctx, arg_node);
        } else {
            args[idx++] = codegen_expr(ctx, arg_node);
        }
    }
    LLVMTypeRef fn_ty = get_llvm_function_type(ctx, fn_type);
    LLVMValueRef call_instr = LLVMBuildCall2(
        ctx->builder,
        fn_ty,
        callee,
        args,
        (unsigned)llvm_arg_count,
        (type_is_void(expr->type) || sret) ? "" : "calltmp"
    );
    if (sret) {
        LLVMTypeRef ret_ty = get_llvm_type(ctx, fn_type->as.func.return_type);
        LLVMAddCallSiteAttribute(call_instr, 1, LLVMCreateTypeAttribute(ctx->context,
            LLVMGetEnumAttributeKindForName("sret", 4), ret_ty));
    }
    size_t attr_idx = sret ? 2 : 1;
    for (size_t i = 0; i < param_count; i++) {
        if (type_is_indirect(ctx, fn_type->as.func.params[i])) {
            LLVMTypeRef param_ty = get_llvm_type(ctx, fn_type->as.func.params[i]);
            LLVMAddCallSiteAttribute(call_instr, (unsigned)(attr_idx + i), LLVMCreateTypeAttribute(ctx->context,
                LLVMGetEnumAttributeKindForName("byval", 5), param_ty));
        }
    }
    if (args) free(args);
    if (sret) {
        return codegen_load_value(ctx, sret_alloca, fn_type->as.func.return_type);
    }
    return call_instr;
}
CodegenMap* codegen_map_create(CodegenContext *ctx, CodegenMap *parent) {
    CodegenMap *m = xmalloc(sizeof(CodegenMap));
    m->map = hashmap_create(8);
    m->parent = parent;
    return m;
}
void codegen_map_destroy(CodegenMap *m) {
    if (!m) return;
    hashmap_destroy(m->map, ((void*)0), ((void*)0));
    free(m);
}
void codegen_map_put(CodegenMap *m, void *key, LLVMValueRef val) {
    hashmap_put(m->map, key, val, ptr_hash, ptr_cmp);
}
LLVMValueRef codegen_map_get(CodegenMap *m, void *key) {
    while (m) {
        LLVMValueRef val = hashmap_get(m->map, key, ptr_hash, ptr_cmp);
        if (val) return val;
        m = m->parent;
    }
    return ((void*)0);
}
CodegenContext* codegen_context_create(TypeStore *store, const char *module_name, int opt_level, ModuleLoader *loader) {
    CodegenContext *ctx = xmalloc(sizeof(CodegenContext));
    ctx->store = store;
    ctx->context = LLVMContextCreate();
    ctx->module = LLVMModuleCreateWithNameInContext(module_name, ctx->context);
    ctx->builder = LLVMCreateBuilderInContext(ctx->context);
    ctx->loader = loader;
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    char *target_triple = LLVMGetDefaultTargetTriple();
    LLVMSetTarget(ctx->module, target_triple);
    char *error = ((void*)0);
    if (LLVMGetTargetFromTriple(target_triple, &ctx->target, &error) != 0) {
        char err_msg[256];
        __builtin___snprintf_chk (err_msg, sizeof(err_msg), 0, __builtin_object_size (err_msg, 2 > 1 ? 1 : 0), "%s", error);
        LLVMDisposeMessage(error);
        ice_impl("./src/codegen/codegen_context.c", 49, "LLVMGetTargetFromTriple failed: %s", err_msg);
    }
    char *cpu = LLVMGetHostCPUName();
    char *features = LLVMGetHostCPUFeatures();
    ctx->machine = LLVMCreateTargetMachine(
        ctx->target, target_triple, cpu, features,
        LLVMCodeGenLevelAggressive, LLVMRelocDefault, LLVMCodeModelDefault
    );
    LLVMDisposeMessage(target_triple);
    LLVMDisposeMessage(cpu);
    LLVMDisposeMessage(features);
    if (!ctx->machine) {
        ice_impl("./src/codegen/codegen_context.c", 66, "Failed to create LLVMTargetMachine");
    }
    ctx->target_data = LLVMCreateTargetDataLayout(ctx->machine);
    LLVMSetModuleDataLayout(ctx->module, ctx->target_data);
    ctx->globals = hashmap_create(1024);
    ctx->type_cache = hashmap_create(256);
    ctx->locals = codegen_map_create(ctx, ((void*)0));
    ctx->loop_cond_bb = ((void*)0);
    ctx->loop_end_bb = ((void*)0);
    ctx->opt_level = opt_level;
    ctx->current_func_type = ((void*)0);
    ctx->sret_ptr = ((void*)0);
    ctx->deferred_actions = xmalloc(sizeof(DynArray));
    dynarray_init(ctx->deferred_actions, sizeof(AstNode*));
    ctx->loop_defer_count = 0;
    return ctx;
}
void codegen_context_destroy(CodegenContext *ctx) {
    hashmap_destroy(ctx->globals, ((void*)0), ((void*)0));
    hashmap_destroy(ctx->type_cache, ((void*)0), ((void*)0));
    dynarray_free(ctx->deferred_actions);
    free(ctx->deferred_actions);
    LLVMDisposeTargetData(ctx->target_data);
    LLVMDisposeTargetMachine(ctx->machine);
    while (ctx->locals) {
        CodegenMap *parent = ctx->locals->parent;
        codegen_map_destroy(ctx->locals);
        ctx->locals = parent;
    }
    LLVMDisposeBuilder(ctx->builder);
    LLVMDisposeModule(ctx->module);
    LLVMContextDispose(ctx->context);
    free(ctx);
}
void codegen_decl_proto(CodegenContext *ctx, AstNode *decl) {
    if (decl->node_type == AST_FUNCTION_DECLARATION) {
        AstFunctionDeclaration *fdecl = &decl->data.function_declaration;
        Type *fn_type_sema = decl->type;
        if (!fn_type_sema || fn_type_sema->kind != TYPE_FUNCTION) {
            ice_impl("./src/codegen/codegen_decl.c", 10, "Function declaration missing type or has incorrect type kind: %d", fn_type_sema ? fn_type_sema->kind : -1);
        }
        _Bool sret = type_is_indirect(ctx, fn_type_sema->as.func.return_type);
        LLVMTypeRef ret_type = sret ? LLVMVoidTypeInContext(ctx->context) : get_llvm_type(ctx, fn_type_sema->as.func.return_type);
        size_t param_count = fn_type_sema->as.func.param_count;
        size_t llvm_param_count = param_count + (sret ? 1 : 0);
        LLVMTypeRef *llvm_params = xmalloc(sizeof(LLVMTypeRef) * llvm_param_count);
        size_t idx = 0;
        if (sret) {
            llvm_params[idx++] = LLVMPointerType(get_llvm_type(ctx, fn_type_sema->as.func.return_type), 0);
        }
        for (size_t i = 0; i < param_count; i++) {
            Type *param_ty = fn_type_sema->as.func.params[i];
            if (type_is_indirect(ctx, param_ty)) {
                llvm_params[idx++] = LLVMPointerType(get_llvm_type(ctx, param_ty), 0);
            } else {
                llvm_params[idx++] = get_llvm_type(ctx, param_ty);
            }
        }
        const char *name = "anon_func";
        char *allocated_name = ((void*)0);
        if (fdecl->intern_result && fdecl->intern_result->key) {
            CompilationUnit *u = module_loader_get_unit(ctx->loader, decl->filename);
            allocated_name = mangle_name(ctx, u, fdecl->intern_result);
            name = allocated_name;
        }
        LLVMTypeRef func_type = LLVMFunctionType(ret_type, llvm_params, (unsigned)llvm_param_count, 0);
        LLVMValueRef func = LLVMAddFunction(ctx->module, name, func_type);
        if (sret) {
            LLVMAddAttributeAtIndex(func, 1, LLVMCreateTypeAttribute(ctx->context,
                LLVMGetEnumAttributeKindForName("sret", 4), get_llvm_type(ctx, fn_type_sema->as.func.return_type)));
        }
        idx = sret ? 1 : 0;
        for (size_t i = 0; i < param_count; i++) {
            if (type_is_indirect(ctx, fn_type_sema->as.func.params[i])) {
                LLVMTypeRef param_ty = get_llvm_type(ctx, fn_type_sema->as.func.params[i]);
                LLVMAddAttributeAtIndex(func, (unsigned)(idx + i + 1), LLVMCreateTypeAttribute(ctx->context,
                    LLVMGetEnumAttributeKindForName("byval", 5), param_ty));
            }
        }
        if (allocated_name) free(allocated_name);
        if (llvm_params) free(llvm_params);
    } else if (decl->node_type == AST_VARIABLE_DECLARATION) {
        AstVariableDeclaration *vdecl = &decl->data.variable_declaration;
        if (!decl->type) ice_impl("./src/codegen/codegen_decl.c", 66, "Variable declaration missing type.");
        LLVMTypeRef ty = get_llvm_type(ctx, decl->type);
        const char *name = "global_var";
        char *allocated_name = ((void*)0);
        if (vdecl->intern_result && vdecl->intern_result->key) {
            CompilationUnit *u = module_loader_get_unit(ctx->loader, decl->filename);
            allocated_name = mangle_name(ctx, u, vdecl->intern_result);
            name = allocated_name;
        }
        LLVMValueRef gvar = LLVMAddGlobal(ctx->module, ty, name);
        if (LLVMGetTypeKind(ty) != LLVMVoidTypeKind)
            LLVMSetInitializer(gvar, LLVMConstNull(ty));
        if (vdecl->intern_result) {
            hashmap_put(ctx->globals,
                        (void*)(intptr_t)vdecl->intern_result->entry->dense_index,
                        gvar, ptr_hash, ptr_cmp);
        }
        if (allocated_name) free(allocated_name);
    }
}
void codegen_decl_body(CodegenContext *ctx, AstNode *decl) {
    if (decl->node_type == AST_FUNCTION_DECLARATION) {
        AstFunctionDeclaration *fdecl = &decl->data.function_declaration;
        Type *fn_type_sema = decl->type;
        const char *name = "anon_func";
        char *allocated_name = ((void*)0);
        if (fdecl->intern_result && fdecl->intern_result->key) {
            CompilationUnit *u = module_loader_get_unit(ctx->loader, decl->filename);
            allocated_name = mangle_name(ctx, u, fdecl->intern_result);
            name = allocated_name;
        }
        LLVMValueRef func = LLVMGetNamedFunction(ctx->module, name);
        if (!func) ice_impl("./src/codegen/codegen_decl.c", 103, "codegen_decl_body: function '%s' not declared in proto pass", name);
        if (fdecl->body) {
            LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(ctx->context, func, "entry");
            LLVMPositionBuilderAtEnd(ctx->builder, entry);
            ctx->locals = codegen_map_create(ctx, ctx->locals);
            ctx->current_func_type = fn_type_sema;
            ctx->deferred_actions->count = 0;
            _Bool sret = type_is_indirect(ctx, fn_type_sema->as.func.return_type);
            if (sret) {
                ctx->sret_ptr = LLVMGetParam(func, 0);
            } else {
                ctx->sret_ptr = ((void*)0);
            }
            size_t param_count = fdecl->params ? fdecl->params->count : 0;
            size_t idx = 0;
            if (sret) idx++;
            for (size_t i = 0; i < param_count; i++) {
                AstNode *param_node = *(AstNode**)dynarray_get(fdecl->params, i);
                AstParam *param = &param_node->data.param;
                LLVMValueRef val = LLVMGetParam(func, (unsigned int)idx++);
                Type *param_ty = fn_type_sema->as.func.params[i];
                LLVMValueRef storage;
                if (type_is_indirect(ctx, param_ty)) {
                    storage = val;
                } else {
                    LLVMTypeRef ty = get_llvm_type(ctx, param_node->type);
                    storage = LLVMBuildAlloca(ctx->builder, ty, "param");
                    LLVMBuildStore(ctx->builder, val, storage);
                }
                if (param->name_idx != -1) {
                    codegen_map_put(ctx->locals, (void*)(intptr_t)param->name_idx, storage);
                }
            }
            if (fdecl->body->node_type == AST_BLOCK) {
                DynArray *stmts = fdecl->body->data.block.statements;
                for (size_t i = 0; i < stmts->count; i++) {
                    AstNode *stmt = *(AstNode**)dynarray_get(stmts, i);
                    codegen_statement(ctx, stmt);
                }
            } else {
                codegen_statement(ctx, fdecl->body);
            }
            LLVMBasicBlockRef current_block = LLVMGetInsertBlock(ctx->builder);
            if (current_block && !LLVMGetBasicBlockTerminator(current_block)) {
                for (int i = (int)ctx->deferred_actions->count - 1; i >= 0; i--) {
                    AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, i);
                    codegen_statement(ctx, body);
                }
                current_block = LLVMGetInsertBlock(ctx->builder);
                if (current_block && !LLVMGetBasicBlockTerminator(current_block)) {
                    _Bool sret_implicit = type_is_indirect(ctx, fn_type_sema->as.func.return_type);
                    LLVMTypeRef ret_ty = sret_implicit ? LLVMVoidTypeInContext(ctx->context) : get_llvm_type(ctx, fn_type_sema->as.func.return_type);
                    if (LLVMGetTypeKind(ret_ty) == LLVMVoidTypeKind) {
                        LLVMBuildRetVoid(ctx->builder);
                    } else {
                        LLVMBuildRet(ctx->builder, LLVMConstNull(ret_ty));
                    }
                }
            }
            CodegenMap *old = ctx->locals;
            ctx->locals = old->parent;
            codegen_map_destroy(old);
            ctx->current_func_type = ((void*)0);
            ctx->sret_ptr = ((void*)0);
        } else if (fdecl->link_name) {
            Slice *s = (Slice*)fdecl->link_name->key;
            char *ext_name = xmalloc(s->len + 1);
            __builtin___memcpy_chk (ext_name, s->ptr, s->len, __builtin_object_size (ext_name, 0));
            ext_name[s->len] = '\0';
            LLVMSetLinkage(func, LLVMInternalLinkage);
            LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(ctx->context, func, "entry");
            LLVMPositionBuilderAtEnd(ctx->builder, entry);
            LLVMValueRef ext_func = LLVMGetNamedFunction(ctx->module, ext_name);
            if (!ext_func) {
                ext_func = LLVMAddFunction(ctx->module, ext_name, LLVMGlobalGetValueType(func));
            }
            size_t param_count = LLVMCountParams(func);
            LLVMValueRef *args = ((void*)0);
            if (param_count > 0) {
                args = xmalloc(sizeof(LLVMValueRef) * param_count);
                for (size_t i = 0; i < param_count; i++) {
                    args[i] = LLVMGetParam(func, (unsigned int)i);
                }
            }
            LLVMTypeRef ret_ty = LLVMGetReturnType(LLVMGlobalGetValueType(func));
            if (LLVMGetTypeKind(ret_ty) == LLVMVoidTypeKind) {
                LLVMBuildCall2(ctx->builder, LLVMGlobalGetValueType(ext_func), ext_func, args, (unsigned int)param_count, "");
                LLVMBuildRetVoid(ctx->builder);
            } else {
                LLVMValueRef call_res = LLVMBuildCall2(ctx->builder, LLVMGlobalGetValueType(ext_func), ext_func, args, (unsigned int)param_count, "ffi_call");
                LLVMBuildRet(ctx->builder, call_res);
            }
            if (args) free(args);
            free(ext_name);
        }
        if (allocated_name) free(allocated_name);
    } else if (decl->node_type == AST_VARIABLE_DECLARATION) {
        AstVariableDeclaration *vdecl = &decl->data.variable_declaration;
        if (vdecl->initializer) {
            const char *name = "global_var";
            char *allocated_name = ((void*)0);
            if (vdecl->intern_result && vdecl->intern_result->key) {
                CompilationUnit *u = module_loader_get_unit(ctx->loader, decl->filename);
                allocated_name = mangle_name(ctx, u, vdecl->intern_result);
                name = allocated_name;
            }
            LLVMValueRef gvar = LLVMGetNamedGlobal(ctx->module, name);
            if (gvar) {
                LLVMValueRef init_val = codegen_expr(ctx, vdecl->initializer);
                if (init_val && LLVMIsConstant(init_val))
                    LLVMSetInitializer(gvar, init_val);
            }
            if (allocated_name) free(allocated_name);
        }
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
typedef enum {
  LLVMAbortProcessAction,
  LLVMPrintMessageAction,
  LLVMReturnStatusAction
} LLVMVerifierFailureAction;
__attribute__((visibility("default"))) LLVMBool LLVMVerifyModule(LLVMModuleRef M,
                                     LLVMVerifierFailureAction Action,
                                     char **OutMessage);
__attribute__((visibility("default"))) LLVMBool LLVMVerifyFunction(LLVMValueRef Fn,
                                       LLVMVerifierFailureAction Action);
__attribute__((visibility("default"))) void LLVMViewFunctionCFG(LLVMValueRef Fn);
__attribute__((visibility("default"))) void LLVMViewFunctionCFGOnly(LLVMValueRef Fn);
#pragma clang diagnostic pop
#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
typedef struct LLVMOpaqueError *LLVMErrorRef;
typedef const void *LLVMErrorTypeId;
__attribute__((visibility("default"))) LLVMErrorTypeId LLVMGetErrorTypeId(LLVMErrorRef Err);
__attribute__((visibility("default"))) void LLVMConsumeError(LLVMErrorRef Err);
__attribute__((visibility("default"))) void LLVMCantFail(LLVMErrorRef Err);
__attribute__((visibility("default"))) char *LLVMGetErrorMessage(LLVMErrorRef Err);
__attribute__((visibility("default"))) void LLVMDisposeErrorMessage(char *ErrMsg);
__attribute__((visibility("default"))) LLVMErrorTypeId LLVMGetStringErrorTypeId(void);
__attribute__((visibility("default"))) LLVMErrorRef LLVMCreateStringError(const char *ErrMsg);
#pragma clang diagnostic pop
#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
typedef struct LLVMOpaquePassBuilderOptions *LLVMPassBuilderOptionsRef;
__attribute__((visibility("default"))) LLVMErrorRef LLVMRunPasses(LLVMModuleRef M, const char *Passes,
                                      LLVMTargetMachineRef TM,
                                      LLVMPassBuilderOptionsRef Options);
__attribute__((visibility("default"))) LLVMErrorRef LLVMRunPassesOnFunction(
    LLVMValueRef F, const char *Passes, LLVMTargetMachineRef TM,
    LLVMPassBuilderOptionsRef Options);
__attribute__((visibility("default"))) LLVMPassBuilderOptionsRef LLVMCreatePassBuilderOptions(void);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetVerifyEach(LLVMPassBuilderOptionsRef Options,
                                    LLVMBool VerifyEach);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetDebugLogging(LLVMPassBuilderOptionsRef Options,
                                      LLVMBool DebugLogging);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetAAPipeline(LLVMPassBuilderOptionsRef Options,
                                    const char *AAPipeline);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetLoopInterleaving(LLVMPassBuilderOptionsRef Options,
                                          LLVMBool LoopInterleaving);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetLoopVectorization(LLVMPassBuilderOptionsRef Options,
                                           LLVMBool LoopVectorization);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetSLPVectorization(LLVMPassBuilderOptionsRef Options,
                                          LLVMBool SLPVectorization);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetLoopUnrolling(LLVMPassBuilderOptionsRef Options,
                                       LLVMBool LoopUnrolling);
__attribute__((visibility("default"))) void LLVMPassBuilderOptionsSetForgetAllSCEVInLoopUnroll(
    LLVMPassBuilderOptionsRef Options, LLVMBool ForgetAllSCEVInLoopUnroll);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetLicmMssaOptCap(LLVMPassBuilderOptionsRef Options,
                                        unsigned LicmMssaOptCap);
__attribute__((visibility("default"))) void LLVMPassBuilderOptionsSetLicmMssaNoAccForPromotionCap(
    LLVMPassBuilderOptionsRef Options, unsigned LicmMssaNoAccForPromotionCap);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetCallGraphProfile(LLVMPassBuilderOptionsRef Options,
                                          LLVMBool CallGraphProfile);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetMergeFunctions(LLVMPassBuilderOptionsRef Options,
                                        LLVMBool MergeFunctions);
__attribute__((visibility("default"))) void
LLVMPassBuilderOptionsSetInlinerThreshold(LLVMPassBuilderOptionsRef Options,
                                          int Threshold);
__attribute__((visibility("default"))) void
LLVMDisposePassBuilderOptions(LLVMPassBuilderOptionsRef Options);
#pragma clang diagnostic pop
#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
__attribute__((visibility("default"))) void LLVMLinkInMCJIT(void);
__attribute__((visibility("default"))) void LLVMLinkInInterpreter(void);
typedef struct LLVMOpaqueGenericValue *LLVMGenericValueRef;
typedef struct LLVMOpaqueExecutionEngine *LLVMExecutionEngineRef;
typedef struct LLVMOpaqueMCJITMemoryManager *LLVMMCJITMemoryManagerRef;
struct LLVMMCJITCompilerOptions {
  unsigned OptLevel;
  LLVMCodeModel CodeModel;
  LLVMBool NoFramePointerElim;
  LLVMBool EnableFastISel;
  LLVMMCJITMemoryManagerRef MCJMM;
};
__attribute__((visibility("default"))) LLVMGenericValueRef LLVMCreateGenericValueOfInt(LLVMTypeRef Ty,
                                                           unsigned long long N,
                                                           LLVMBool IsSigned);
__attribute__((visibility("default"))) LLVMGenericValueRef LLVMCreateGenericValueOfPointer(void *P);
__attribute__((visibility("default"))) LLVMGenericValueRef LLVMCreateGenericValueOfFloat(LLVMTypeRef Ty,
                                                             double N);
__attribute__((visibility("default"))) unsigned LLVMGenericValueIntWidth(LLVMGenericValueRef GenValRef);
__attribute__((visibility("default"))) unsigned long long LLVMGenericValueToInt(LLVMGenericValueRef GenVal,
                                                    LLVMBool IsSigned);
__attribute__((visibility("default"))) void *LLVMGenericValueToPointer(LLVMGenericValueRef GenVal);
__attribute__((visibility("default"))) double LLVMGenericValueToFloat(LLVMTypeRef TyRef,
                                          LLVMGenericValueRef GenVal);
__attribute__((visibility("default"))) void LLVMDisposeGenericValue(LLVMGenericValueRef GenVal);
__attribute__((visibility("default"))) LLVMBool LLVMCreateExecutionEngineForModule(
    LLVMExecutionEngineRef *OutEE, LLVMModuleRef M, char **OutError);
__attribute__((visibility("default"))) LLVMBool LLVMCreateInterpreterForModule(
    LLVMExecutionEngineRef *OutInterp, LLVMModuleRef M, char **OutError);
__attribute__((visibility("default"))) LLVMBool
LLVMCreateJITCompilerForModule(LLVMExecutionEngineRef *OutJIT, LLVMModuleRef M,
                               unsigned OptLevel, char **OutError);
__attribute__((visibility("default"))) void
LLVMInitializeMCJITCompilerOptions(struct LLVMMCJITCompilerOptions *Options,
                                   size_t SizeOfOptions);
__attribute__((visibility("default"))) LLVMBool LLVMCreateMCJITCompilerForModule(
    LLVMExecutionEngineRef *OutJIT, LLVMModuleRef M,
    struct LLVMMCJITCompilerOptions *Options, size_t SizeOfOptions,
    char **OutError);
__attribute__((visibility("default"))) void LLVMDisposeExecutionEngine(LLVMExecutionEngineRef EE);
__attribute__((visibility("default"))) void LLVMRunStaticConstructors(LLVMExecutionEngineRef EE);
__attribute__((visibility("default"))) void LLVMRunStaticDestructors(LLVMExecutionEngineRef EE);
__attribute__((visibility("default"))) int LLVMRunFunctionAsMain(LLVMExecutionEngineRef EE, LLVMValueRef F,
                                     unsigned ArgC, const char *const *ArgV,
                                     const char *const *EnvP);
__attribute__((visibility("default"))) LLVMGenericValueRef LLVMRunFunction(LLVMExecutionEngineRef EE,
                                               LLVMValueRef F, unsigned NumArgs,
                                               LLVMGenericValueRef *Args);
__attribute__((visibility("default"))) void LLVMFreeMachineCodeForFunction(LLVMExecutionEngineRef EE,
                                               LLVMValueRef F);
__attribute__((visibility("default"))) void LLVMAddModule(LLVMExecutionEngineRef EE, LLVMModuleRef M);
__attribute__((visibility("default"))) LLVMBool LLVMRemoveModule(LLVMExecutionEngineRef EE, LLVMModuleRef M,
                                     LLVMModuleRef *OutMod, char **OutError);
__attribute__((visibility("default"))) LLVMBool LLVMFindFunction(LLVMExecutionEngineRef EE,
                                     const char *Name, LLVMValueRef *OutFn);
__attribute__((visibility("default"))) void *LLVMRecompileAndRelinkFunction(LLVMExecutionEngineRef EE,
                                                LLVMValueRef Fn);
__attribute__((visibility("default"))) LLVMTargetDataRef
LLVMGetExecutionEngineTargetData(LLVMExecutionEngineRef EE);
__attribute__((visibility("default"))) LLVMTargetMachineRef
LLVMGetExecutionEngineTargetMachine(LLVMExecutionEngineRef EE);
__attribute__((visibility("default"))) void LLVMAddGlobalMapping(LLVMExecutionEngineRef EE,
                                     LLVMValueRef Global, void *Addr);
__attribute__((visibility("default"))) void *LLVMGetPointerToGlobal(LLVMExecutionEngineRef EE,
                                        LLVMValueRef Global);
__attribute__((visibility("default"))) uint64_t LLVMGetGlobalValueAddress(LLVMExecutionEngineRef EE,
                                              const char *Name);
__attribute__((visibility("default"))) uint64_t LLVMGetFunctionAddress(LLVMExecutionEngineRef EE,
                                           const char *Name);
__attribute__((visibility("default"))) LLVMBool LLVMExecutionEngineGetErrMsg(LLVMExecutionEngineRef EE,
                                                 char **OutError);
typedef uint8_t *(*LLVMMemoryManagerAllocateCodeSectionCallback)(
  void *Opaque, uintptr_t Size, unsigned Alignment, unsigned SectionID,
  const char *SectionName);
typedef uint8_t *(*LLVMMemoryManagerAllocateDataSectionCallback)(
  void *Opaque, uintptr_t Size, unsigned Alignment, unsigned SectionID,
  const char *SectionName, LLVMBool IsReadOnly);
typedef LLVMBool (*LLVMMemoryManagerFinalizeMemoryCallback)(
  void *Opaque, char **ErrMsg);
typedef void (*LLVMMemoryManagerDestroyCallback)(void *Opaque);
__attribute__((visibility("default"))) LLVMMCJITMemoryManagerRef LLVMCreateSimpleMCJITMemoryManager(
    void *Opaque,
    LLVMMemoryManagerAllocateCodeSectionCallback AllocateCodeSection,
    LLVMMemoryManagerAllocateDataSectionCallback AllocateDataSection,
    LLVMMemoryManagerFinalizeMemoryCallback FinalizeMemory,
    LLVMMemoryManagerDestroyCallback Destroy);
__attribute__((visibility("default"))) void LLVMDisposeMCJITMemoryManager(LLVMMCJITMemoryManagerRef MM);
__attribute__((visibility("default"))) LLVMJITEventListenerRef LLVMCreateGDBRegistrationListener(void);
__attribute__((visibility("default"))) LLVMJITEventListenerRef LLVMCreateIntelJITEventListener(void);
__attribute__((visibility("default"))) LLVMJITEventListenerRef LLVMCreateOProfileJITEventListener(void);
__attribute__((visibility("default"))) LLVMJITEventListenerRef LLVMCreatePerfJITEventListener(void);
#pragma clang diagnostic pop
#pragma clang diagnostic push
#pragma clang diagnostic error "-Wstrict-prototypes"
__attribute__((visibility("default"))) LLVMBool LLVMLoadLibraryPermanently(const char *Filename);
__attribute__((visibility("default"))) void LLVMParseCommandLineOptions(int argc, const char *const *argv,
                                            const char *Overview);
__attribute__((visibility("default"))) void *LLVMSearchForAddressOfSymbol(const char *symbolName);
__attribute__((visibility("default"))) void LLVMAddSymbol(const char *symbolName, void *symbolValue);
#pragma clang diagnostic pop

void codegen_initialize(void) {
    LLVMInitializeAllTargetInfos();
    LLVMInitializeAllTargets();
    LLVMInitializeAllTargetMCs();
    LLVMInitializeAllAsmParsers();
    LLVMInitializeAllAsmPrinters();
    LLVMLinkInMCJIT();
    LLVMLoadLibraryPermanently(((void*)0));
}
static void run_optimizations(CodegenContext *ctx) {
    if (ctx->opt_level <= 0) return;
    char passes[32];
    __builtin___snprintf_chk (passes, sizeof(passes), 0, __builtin_object_size (passes, 2 > 1 ? 1 : 0), "default<O%d>", ctx->opt_level);
    LLVMPassBuilderOptionsRef opts = LLVMCreatePassBuilderOptions();
    LLVMRunPasses(ctx->module, passes, ctx->machine, opts);
    LLVMDisposePassBuilderOptions(opts);
}
int codegen_program(CodegenContext *ctx) {
    if (!ctx || !ctx->loader || !ctx->loader->units_ordered) return -1;
    for (size_t i = 0; i < ctx->loader->units_ordered->count; i++) {
        CompilationUnit *unit = *(CompilationUnit**)dynarray_get(ctx->loader->units_ordered, i);
        if (!unit->ast_root) continue;
        AstProgram *prog = &unit->ast_root->data.program;
        if (!prog->decls) continue;
        for (size_t j = 0; j < prog->decls->count; j++) {
            AstNode *decl = *(AstNode**)dynarray_get(prog->decls, j);
            if (decl->node_type != AST_IMPORT_DECLARATION) {
                codegen_decl_proto(ctx, decl);
            }
        }
    }
    for (size_t i = 0; i < ctx->loader->units_ordered->count; i++) {
        CompilationUnit *unit = *(CompilationUnit**)dynarray_get(ctx->loader->units_ordered, i);
        if (!unit->ast_root) continue;
        AstProgram *prog = &unit->ast_root->data.program;
        if (!prog->decls) continue;
        for (size_t j = 0; j < prog->decls->count; j++) {
            AstNode *decl = *(AstNode**)dynarray_get(prog->decls, j);
            if (decl->node_type != AST_IMPORT_DECLARATION) {
                codegen_decl_body(ctx, decl);
            }
        }
    }
    run_optimizations(ctx);
    char *v_error = ((void*)0);
    if (LLVMVerifyModule(ctx->module, LLVMPrintMessageAction, &v_error) == 1) {
        fprintf(__stderrp, "LLVM Verification Error: %s\n", v_error ? v_error : "Unknown");
        if (v_error) LLVMDisposeMessage(v_error);
        return -1;
    }
    if (v_error) LLVMDisposeMessage(v_error);
    return 0;
}
void codegen_dump_module(CodegenContext *ctx) {
    LLVMDumpModule(ctx->module);
}
void codegen_emit_object(CodegenContext *ctx, const char *filename) {
    char *error = ((void*)0);
    if (LLVMTargetMachineEmitToFile(ctx->machine, ctx->module, (char *)filename,
                                    LLVMObjectFile, &error)) {
        fprintf(__stderrp, "Error emitting object file: %s\n", error);
        LLVMDisposeMessage(error);
    }
}
int codegen_run_jit(CodegenContext *ctx) {
    LLVMExecutionEngineRef engine;
    char *error = ((void*)0);
    if (LLVMCreateExecutionEngineForModule(&engine, ctx->module, &error) != 0) {
        fprintf(__stderrp, "Failed to create execution engine: %s\n", error);
        LLVMDisposeMessage(error);
        return -1;
    }
    LLVMValueRef main_func = LLVMGetNamedFunction(engine ? ctx->module : ((void*)0), "main");
    if (!main_func) {
        fprintf(__stderrp, "Could not find main function\n");
        LLVMRemoveModule(engine, ctx->module, &ctx->module, &error);
        LLVMDisposeExecutionEngine(engine);
        return -1;
    }
    uint64_t addr = LLVMGetFunctionAddress(engine, "main");
    int (*main_ptr)(void) = (int (*)(void))addr;
    int result = main_ptr();
    LLVMModuleRef removed_module;
    if (LLVMRemoveModule(engine, ctx->module, &removed_module, &error) != 0) {
        fprintf(__stderrp, "Failed to remove module from JIT: %s\n", error);
        LLVMDisposeMessage(error);
    }
    LLVMDisposeExecutionEngine(engine);
    return result;
}
LLVMValueRef codegen_expr(CodegenContext *ctx, AstNode *expr);
static LLVMValueRef codegen_expr_intrinsic(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ice_impl("./src/codegen/codegen_expr.c", 20, "Intrinsic node (kind %d) missing type.", expr->data.intrinsic.kind);
    IntrinsicKind kind = expr->data.intrinsic.kind;
    DynArray *args = expr->data.intrinsic.args;
    LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8TypeInContext(ctx->context), 0);
    LLVMTypeRef i64ty = LLVMInt64TypeInContext(ctx->context);
    if (kind == INTRINSIC_ALLOC) {
        AstNode *allocator_arg = *(AstNode**)dynarray_get(args, 1);
        AstNode *count_arg = args->count == 3 ? *(AstNode**)dynarray_get(args, 2) : ((void*)0);
        Type *target_type = expr->type;
        if (target_type->kind == TYPE_POINTER) target_type = target_type->as.ptr.base;
        LLVMTypeRef llvm_target_type = get_llvm_type(ctx, target_type);
        LLVMValueRef allocator_val = codegen_expr(ctx, allocator_arg);
        LLVMValueRef count_val = count_arg ? codegen_expr(ctx, count_arg) : LLVMConstInt(i64ty, 1, 0);
        LLVMValueRef total_bytes = LLVMBuildMul(ctx->builder,
            LLVMBuildIntCast(ctx->builder, count_val, i64ty, "count_i64"),
            LLVMSizeOf(llvm_target_type), "alloc_bytes");
        size_t ctx_idx = struct_field_index(allocator_arg->type, "ctx");
        size_t alloc_idx = struct_field_index(allocator_arg->type, "alloc");
        if (ctx_idx == (size_t)-1 || alloc_idx == (size_t)-1) ice_impl("./src/codegen/codegen_expr.c", 48, "@alloc allocator missing required fields");
        LLVMValueRef ctx_val = LLVMBuildExtractValue(ctx->builder, allocator_val, (unsigned)ctx_idx, "ctx_val");
        LLVMValueRef alloc_fn = LLVMBuildExtractValue(ctx->builder, allocator_val, (unsigned)alloc_idx, "alloc_fn_val");
        LLVMTypeRef alloc_fn_ty = LLVMFunctionType(i8ptr, (LLVMTypeRef[]){i8ptr, i64ty}, 2, 0);
        LLVMValueRef call_args[] = { ctx_val, total_bytes };
        LLVMValueRef raw_mem = LLVMBuildCall2(ctx->builder, alloc_fn_ty, alloc_fn, call_args, 2, "raw_mem");
        return LLVMBuildBitCast(ctx->builder, raw_mem, LLVMPointerType(llvm_target_type, 0), "typed_mem");
    }
    else if (kind == INTRINSIC_FREE) {
        AstNode *allocator_arg = *(AstNode**)dynarray_get(args, args->count == 3 ? 1 : 0);
        AstNode *ptr_arg = *(AstNode**)dynarray_get(args, args->count == 3 ? 2 : 1);
        LLVMValueRef allocator_val = codegen_expr(ctx, allocator_arg);
        LLVMValueRef ptr_val = codegen_expr(ctx, ptr_arg);
        size_t ctx_idx = struct_field_index(allocator_arg->type, "ctx");
        size_t free_idx = struct_field_index(allocator_arg->type, "free");
        if (ctx_idx == (size_t)-1 || free_idx == (size_t)-1) ice_impl("./src/codegen/codegen_expr.c", 70, "@free allocator missing required fields");
        LLVMValueRef ctx_val = LLVMBuildExtractValue(ctx->builder, allocator_val, (unsigned)ctx_idx, "ctx_val");
        LLVMValueRef free_fn = LLVMBuildExtractValue(ctx->builder, allocator_val, (unsigned)free_idx, "free_fn_val");
        LLVMTypeRef void_ty = LLVMVoidTypeInContext(ctx->context);
        LLVMTypeRef free_fn_ty = LLVMFunctionType(void_ty, (LLVMTypeRef[]){i8ptr, i8ptr}, 2, 0);
        LLVMValueRef call_args[] = { ctx_val, LLVMBuildBitCast(ctx->builder, ptr_val, i8ptr, "ptr_to_free") };
        return LLVMBuildCall2(ctx->builder, free_fn_ty, free_fn, call_args, 2, "");
    }
    return ((void*)0);
}
LLVMValueRef codegen_expr_ident(CodegenContext *ctx, AstNode *expr) {
    Symbol *sym = expr->data.identifier.symbol;
    if (!sym) ice_impl("./src/codegen/codegen_expr.c", 92, "Identifier '%s' missing symbol in Codegen.", ((Slice*)expr->data.identifier.intern_result->key)->ptr);
    LLVMValueRef val = codegen_lvalue(ctx, expr);
    if (sym->kind == SYMBOL_VARIABLE) {
        if (expr->type->kind == TYPE_ARRAY) {
             return val;
        }
        return codegen_load_value(ctx, val, expr->type);
    }
    return val;
}
static LLVMValueRef codegen_expr_member(CodegenContext *ctx, AstNode *expr) {
    AstMemberExpr *member = &expr->data.member_expr;
    LLVMValueRef lval = codegen_lvalue(ctx, expr);
    if (member->symbol && member->symbol->kind == SYMBOL_VALUE_FUNCTION) {
         return lval;
    }
    if (expr->type->kind == TYPE_ARRAY) {
        return lval;
    }
    return codegen_load_value(ctx, lval, expr->type);
}
static LLVMValueRef codegen_expr_struct_literal(CodegenContext *ctx, AstNode *expr) {
    AstStructLiteral *lit = &expr->data.struct_literal;
    LLVMTypeRef struct_ty = get_llvm_type(ctx, expr->type);
    if (expr->is_llvm_const_safe) {
        LLVMValueRef *fields = xmalloc(sizeof(LLVMValueRef) * lit->fields->count);
        for (size_t i = 0; i < lit->fields->count; i++) {
            AstFieldInit *init = (AstFieldInit*)dynarray_get(lit->fields, i);
            size_t idx = get_struct_field_index(expr->type, init->name);
            if (idx == (size_t)-1) ice_impl_at("./src/codegen/codegen_expr.c", 142, (expr)->filename, (expr)->span, "Field index not found in codegen");
            fields[idx] = codegen_expr(ctx, init->expr);
        }
        LLVMValueRef val = LLVMConstNamedStruct(struct_ty, fields, (unsigned)lit->fields->count);
        free(fields);
        return val;
    }
    LLVMValueRef val = LLVMGetUndef(struct_ty);
    for (size_t i = 0; i < lit->fields->count; i++) {
        AstFieldInit *init = (AstFieldInit*)dynarray_get(lit->fields, i);
        LLVMValueRef field_val = codegen_expr(ctx, init->expr);
        size_t idx = get_struct_field_index(expr->type, init->name);
        if (idx == (size_t)-1) ice_impl_at("./src/codegen/codegen_expr.c", 160, (expr)->filename, (expr)->span, "Field index not found in codegen");
        val = LLVMBuildInsertValue(ctx->builder, val, field_val, (unsigned)idx, "struct_init");
    }
    return val;
}
static LLVMValueRef codegen_expr_initializer_list(CodegenContext *ctx, AstNode *expr) {
    AstInitializeList *list = &expr->data.initializer_list;
    Type *t = expr->type;
    if (t->kind != TYPE_ARRAY) ice_impl("./src/codegen/codegen_expr.c", 171, "Initializer list must have array type in Codegen");
    LLVMTypeRef arr_ty = get_llvm_type(ctx, t);
    LLVMTypeRef elem_ty = get_llvm_type(ctx, t->as.array.base);
    if (expr->is_llvm_const_safe) {
        LLVMValueRef *elems = xmalloc(sizeof(LLVMValueRef) * list->elements->count);
        for (size_t i = 0; i < list->elements->count; i++) {
            AstNode *elem = *(AstNode**)dynarray_get(list->elements, i);
            elems[i] = codegen_expr(ctx, elem);
        }
        LLVMValueRef val = LLVMConstArray(elem_ty, elems, (unsigned)list->elements->count);
        free(elems);
        return val;
    }
    LLVMValueRef arr_val = LLVMGetUndef(arr_ty);
    for (size_t i = 0; i < list->elements->count; i++) {
        AstNode *elem = *(AstNode**)dynarray_get(list->elements, i);
        LLVMValueRef elem_val = codegen_expr(ctx, elem);
        arr_val = LLVMBuildInsertValue(ctx->builder, arr_val, elem_val, (unsigned)i, "arr_init");
    }
    return arr_val;
}
static LLVMValueRef codegen_expr_subscript(CodegenContext *ctx, AstNode *expr) {
    LLVMValueRef ptr = codegen_lvalue(ctx, expr);
    return codegen_load_value(ctx, ptr, expr->type);
}
static LLVMValueRef codegen_const_value(CodegenContext *ctx, Type *type, ConstValue *val) {
    if (val->type == STRING_LITERAL) {
         return LLVMBuildGlobalStringPtr(ctx->builder, ((Slice*)val->value.string_val->key)->ptr, "str_lit");
    }
    if (type_is_integer(type)) return LLVMConstInt(get_llvm_type(ctx, type), (unsigned long long)val->value.int_val, 0);
    if (type_is_float(type)) return LLVMConstReal(get_llvm_type(ctx, type), val->value.float_val);
    if (type_is_bool(type)) return LLVMConstInt(get_llvm_type(ctx, type), val->value.bool_val ? 1 : 0, 0);
    if (type_is_char(type)) return LLVMConstInt(get_llvm_type(ctx, type), (unsigned long long)val->value.char_val, 0);
    if (type->kind == TYPE_POINTER) {
        LLVMTypeRef ptr_ty = get_llvm_type(ctx, type);
        if (val->value.int_val == 0) return LLVMConstNull(ptr_ty);
        return LLVMConstIntToPtr(LLVMConstInt(LLVMInt64TypeInContext(ctx->context), (unsigned long long)val->value.int_val, 0), ptr_ty);
    }
    return ((void*)0);
}
LLVMValueRef codegen_expr(CodegenContext *ctx, AstNode *expr) {
    if (!expr) return ((void*)0);
    if (expr->is_foldable_const) {
        return codegen_const_value(ctx, expr->type, &expr->const_value);
    }
    switch (expr->node_type) {
        case AST_LITERAL: {
            if (expr->data.literal.type == STRING_LITERAL) {
                return LLVMBuildGlobalStringPtr(ctx->builder, ((Slice*)expr->data.literal.value.string_val->key)->ptr, "str_lit");
            }
            return codegen_const_value(ctx, expr->type, &expr->const_value);
        }
        case AST_IDENTIFIER: return codegen_expr_ident(ctx, expr);
        case AST_CALL_EXPR: return codegen_expr_call(ctx, expr);
        case AST_MEMBER_EXPR: return codegen_expr_member(ctx, expr);
        case AST_STRUCT_LITERAL: return codegen_expr_struct_literal(ctx, expr);
        case AST_INITIALIZER_LIST: return codegen_expr_initializer_list(ctx, expr);
        case AST_SUBSCRIPT_EXPR: return codegen_expr_subscript(ctx, expr);
        case AST_INTRINSIC: return codegen_expr_intrinsic(ctx, expr);
        case AST_BINARY_EXPR:
        case AST_UNARY_EXPR:
        case AST_ASSIGNMENT_EXPR:
        case AST_CAST:
            return codegen_expr_ops(ctx, expr);
        default:
            ice_impl("./src/codegen/codegen_expr.c", 255, "codegen_expr: unhandled node type %d", expr->node_type);
    }
    return ((void*)0);
}
LLVMValueRef codegen_lvalue(CodegenContext *ctx, AstNode *expr) {
    if (!expr) return ((void*)0);
    if (!expr->type) ice_impl_at("./src/codegen/codegen_lvalue.c", 14, (expr)->filename, (expr)->span, "LValue node missing type.");
    if (expr->node_type == AST_IDENTIFIER) {
        AstIdentifier *ident = &expr->data.identifier;
        if (ident->intern_result) {
            void *key = (void*)(intptr_t)ident->intern_result->entry->dense_index;
            LLVMValueRef val = codegen_map_get(ctx->locals, key);
            if (val) return val;
        }
        CompilationUnit *current_unit = module_loader_get_unit(ctx->loader, expr->filename);
        if (current_unit && current_unit->global_scope) {
            Symbol *sym = scope_lookup_symbol(current_unit->global_scope, ident->intern_result, expr->filename);
            if (sym) {
                while (sym && sym->kind == SYMBOL_VALUE_ALIAS) {
                    sym = sym->target_symbol;
                }
                if (!sym) ice_impl_at("./src/codegen/codegen_lvalue.c", 39, (expr)->filename, (expr)->span, "Alias '%s' resolved to NULL.", ((Slice*)ident->intern_result->key)->ptr);
                CompilationUnit *origin_unit = module_loader_get_unit(ctx->loader, sym->filename);
                char *mangled = mangle_name(ctx, origin_unit, sym->name_rec);
                LLVMValueRef val = LLVMGetNamedFunction(ctx->module, mangled);
                if (!val) val = LLVMGetNamedGlobal(ctx->module, mangled);
                free(mangled);
                if (val) return val;
            }
        }
        ice_impl_at("./src/codegen/codegen_lvalue.c", 53, (expr)->filename, (expr)->span, "Identifier '%s' could not be resolved to an lvalue.", ((Slice*)ident->intern_result->key)->ptr);
        return ((void*)0);
    }
    if (expr->node_type == AST_SUBSCRIPT_EXPR) {
        AstSubscriptExpr *sub = &expr->data.subscript_expr;
        Type *target_type = sub->target->type;
        if (!target_type) ice_impl_at("./src/codegen/codegen_lvalue.c", 63, (sub->target)->filename, (sub->target)->span, "Subscript target missing type.");
        LLVMValueRef idx = codegen_expr(ctx, sub->index);
        if (target_type->kind == TYPE_ARRAY) {
            LLVMValueRef target = codegen_lvalue(ctx, sub->target);
            LLVMTypeRef arr_ty = get_llvm_type(ctx, target_type);
            LLVMValueRef indices[] = {
                LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 0, 0),
                idx
            };
            return LLVMBuildInBoundsGEP2(ctx->builder, arr_ty, target, indices, 2, "arrayidx");
        }
        else if (target_type->kind == TYPE_SLICE) {
            LLVMValueRef struct_ptr = codegen_lvalue(ctx, sub->target);
            if (!struct_ptr) ice_impl_at("./src/codegen/codegen_lvalue.c", 84, (sub->target)->filename, (sub->target)->span, "Subscript target failed to resolve.");
            LLVMTypeRef struct_ty = get_llvm_type(ctx, target_type);
            LLVMValueRef data_ptr_ptr = LLVMBuildStructGEP2(ctx->builder, struct_ty, struct_ptr, 0, "data_ptr_ptr");
            LLVMTypeRef elem_ptr_ty = LLVMStructGetTypeAtIndex(struct_ty, 0);
            LLVMValueRef data_ptr = LLVMBuildLoad2(ctx->builder, elem_ptr_ty, data_ptr_ptr, "data_ptr");
            LLVMTypeRef elem_ty = get_llvm_type(ctx, target_type->as.slice.base);
            return LLVMBuildGEP2(ctx->builder, elem_ty, data_ptr, &idx, 1, "sliceidx");
        }
        else if (target_type->kind == TYPE_POINTER) {
            LLVMValueRef target = codegen_expr(ctx, sub->target);
            LLVMTypeRef elem_ty = get_llvm_type(ctx, target_type->as.ptr.base);
            return LLVMBuildGEP2(ctx->builder, elem_ty, target, &idx, 1, "ptr_idx");
        }
        else {
            ice_impl_at("./src/codegen/codegen_lvalue.c", 103, (sub->target)->filename, (sub->target)->span, "Subscript target must be array, slice, or pointer");
        }
    }
    if (expr->node_type == AST_MEMBER_EXPR) {
        AstMemberExpr *mem_expr = &expr->data.member_expr;
        if (mem_expr->symbol) {
            CompilationUnit *u = module_loader_get_unit(ctx->loader, mem_expr->symbol->filename);
            if (!u) ice_impl("./src/codegen/codegen_lvalue.c", 116, "Failed to find CompilationUnit for symbol in '%s'", mem_expr->symbol->filename ? mem_expr->symbol->filename : "unknown");
            char *mangled = mangle_name(ctx, u, mem_expr->member);
            LLVMValueRef val = LLVMGetNamedFunction(ctx->module, mangled);
            if (!val) val = LLVMGetNamedGlobal(ctx->module, mangled);
            if (!val) ice_impl("./src/codegen/codegen_lvalue.c", 122, "Failed to find LLVM value for mangled symbol '%s'", mangled);
            free(mangled);
            return val;
        }
        Type *target_type = mem_expr->target->type;
        if (!target_type) ice_impl_at("./src/codegen/codegen_lvalue.c", 130, (mem_expr->target)->filename, (mem_expr->target)->span, "Member expression target missing type.");
        Type *underlying = target_type;
        if (underlying->kind == TYPE_POINTER) {
            underlying = underlying->as.ptr.base;
        }
        LLVMValueRef target_lvalue = codegen_lvalue(ctx, mem_expr->target);
        if (!target_lvalue) ice_impl_at("./src/codegen/codegen_lvalue.c", 140, (mem_expr->target)->filename, (mem_expr->target)->span, "Member expression target failed to resolve.");
        if (target_type->kind == TYPE_POINTER) {
            LLVMTypeRef ptr_ty = get_llvm_type(ctx, target_type);
            target_lvalue = LLVMBuildLoad2(ctx->builder, ptr_ty, target_lvalue, "deref_ptr");
        }
        if (underlying->kind == TYPE_SLICE) {
            LLVMTypeRef struct_ty = get_llvm_type(ctx, underlying);
            unsigned idx = (mem_expr->member == ctx->store->kw_len) ? 1 : 0;
            return LLVMBuildStructGEP2(ctx->builder, struct_ty, target_lvalue, idx, "slice_gep");
        }
        else if (underlying->kind == TYPE_STRUCT) {
            LLVMTypeRef struct_ty = get_llvm_type(ctx, underlying);
            size_t idx = get_struct_field_index(underlying, mem_expr->member);
            if (idx == (size_t)-1) ice_impl_at("./src/codegen/codegen_lvalue.c", 159, (expr)->filename, (expr)->span, "Field index not found in codegen");
            return LLVMBuildStructGEP2(ctx->builder, struct_ty, target_lvalue, (unsigned)idx, "field_gep");
        }
        ice_impl_at("./src/codegen/codegen_lvalue.c", 163, (expr)->filename, (expr)->span, "Member access requires struct or slice");
    }
    if (expr->node_type == AST_UNARY_EXPR && expr->data.unary_expr.op == OP_DEREF) {
        return codegen_expr(ctx, expr->data.unary_expr.expr);
    }
    if (expr->node_type == AST_STRUCT_LITERAL || expr->node_type == AST_INITIALIZER_LIST) {
        LLVMTypeRef ty = get_llvm_type(ctx, expr->type);
        LLVMValueRef slot = LLVMBuildAlloca(ctx->builder, ty, "literal_mem");
        LLVMValueRef val = codegen_expr(ctx, expr);
        LLVMBuildStore(ctx->builder, val, slot);
        return slot;
    }
    ice_impl_at("./src/codegen/codegen_lvalue.c", 187, (expr)->filename, (expr)->span, "Unhandled lvalue node type %d", expr->node_type);
}
LLVMValueRef codegen_materialize_slice(CodegenContext *ctx, LLVMValueRef val, Type *src_type, Type *dst_type) {
    size_t n = src_type->as.array.size;
    Type *src_inner = src_type->as.array.base;
    Type *dst_inner = dst_type->as.slice.base;
    LLVMTypeRef dst_ty = get_llvm_type(ctx, dst_type);
    LLVMTypeRef i32_ty = LLVMInt32TypeInContext(ctx->context);
    LLVMTypeRef i64_ty = LLVMInt64TypeInContext(ctx->context);
    _Bool inner_needs_deep_cast =
        src_inner->kind == TYPE_ARRAY && dst_inner->kind == TYPE_SLICE;
    if (!inner_needs_deep_cast) {
        LLVMValueRef fat = LLVMGetUndef(dst_ty);
        LLVMTypeRef elem_ptr_ty = LLVMStructGetTypeAtIndex(dst_ty, 0);
        LLVMValueRef elem_ptr = LLVMBuildBitCast(ctx->builder, val, elem_ptr_ty, "array_ptr_decay");
        fat = LLVMBuildInsertValue(ctx->builder, fat, elem_ptr, 0, "fat_ptr_ptr");
        fat = LLVMBuildInsertValue(ctx->builder, fat, LLVMConstInt(i64_ty, n, 0), 1, "fat_ptr_len");
        return fat;
    }
    LLVMTypeRef elem_slice_ty = get_llvm_type(ctx, dst_inner);
    LLVMTypeRef hdrs_arr_ty = LLVMArrayType(elem_slice_ty, n);
    LLVMTypeRef outer_arr_ty = get_llvm_type(ctx, src_type);
    LLVMValueRef hdrs = LLVMBuildAlloca(ctx->builder, hdrs_arr_ty, "slice_hdrs");
    for (size_t i = 0; i < n; i++) {
        LLVMValueRef idx[] = { LLVMConstInt(i32_ty, 0, 0), LLVMConstInt(i32_ty, (unsigned)i, 0) };
        LLVMValueRef row_ptr = LLVMBuildGEP2(ctx->builder, outer_arr_ty, val, idx, 2, "row_ptr");
        LLVMValueRef row_fat = codegen_materialize_slice(ctx, row_ptr, src_inner, dst_inner);
        LLVMValueRef hdr_ptr = LLVMBuildGEP2(ctx->builder, hdrs_arr_ty, hdrs, idx, 2, "hdr_ptr");
        LLVMBuildStore(ctx->builder, row_fat, hdr_ptr);
    }
    LLVMValueRef outer = LLVMGetUndef(dst_ty);
    outer = LLVMBuildInsertValue(ctx->builder, outer, hdrs, 0, "outer_ptr");
    outer = LLVMBuildInsertValue(ctx->builder, outer, LLVMConstInt(i64_ty, n, 0), 1, "outer_len");
    return outer;
}
LLVMValueRef codegen_expr_ops(CodegenContext *ctx, AstNode *expr) {
    if (expr->node_type == AST_CAST) {
        AstCastExpr *cast_node = &expr->data.cast_expr;
        LLVMValueRef val = codegen_expr(ctx, cast_node->expr);
        LLVMTypeRef dst_ty = get_llvm_type(ctx, cast_node->target_type);
        if (!val || !dst_ty) return val;
        LLVMTypeRef src_ty = LLVMTypeOf(val);
        LLVMTypeKind src_k = LLVMGetTypeKind(src_ty);
        LLVMTypeKind dst_k = LLVMGetTypeKind(dst_ty);
        if (src_k == dst_k) {
            if (src_k == LLVMIntegerTypeKind) {
                unsigned src_w = LLVMGetIntTypeWidth(src_ty);
                unsigned dst_w = LLVMGetIntTypeWidth(dst_ty);
                if (src_w == dst_w) return val;
                if (src_w > dst_w) return LLVMBuildTrunc(ctx->builder, val, dst_ty, "trunc");
                return LLVMBuildSExt(ctx->builder, val, dst_ty, "sext");
            }
            if (src_k == LLVMPointerTypeKind &&
                cast_node->expr->type->kind == TYPE_POINTER &&
                cast_node->target_type->kind == TYPE_POINTER) {
                Type *src_base = cast_node->expr->type->as.ptr.base;
                Type *dst_base = cast_node->target_type->as.ptr.base;
                if (src_base->kind == TYPE_ARRAY && dst_base->kind == TYPE_SLICE) {
                    LLVMTypeRef slice_ty = get_llvm_type(ctx, dst_base);
                    LLVMValueRef slice_val = codegen_materialize_slice(ctx, val, src_base, dst_base);
                    LLVMValueRef slice_alloca = LLVMBuildAlloca(ctx->builder, slice_ty, "temp_slice_ptr_cast");
                    LLVMBuildStore(ctx->builder, slice_val, slice_alloca);
                    return slice_alloca;
                }
            }
        } else {
            if (cast_node->expr->type->kind == TYPE_ARRAY && cast_node->target_type->kind == TYPE_SLICE) {
                return codegen_materialize_slice(ctx, val, cast_node->expr->type, cast_node->target_type);
            }
            if (src_k == LLVMPointerTypeKind && dst_k == LLVMIntegerTypeKind)
                return LLVMBuildPtrToInt(ctx->builder, val, dst_ty, "ptrtoint");
            if (src_k == LLVMIntegerTypeKind && dst_k == LLVMPointerTypeKind)
                return LLVMBuildIntToPtr(ctx->builder, val, dst_ty, "inttoptr");
            if (src_k == LLVMIntegerTypeKind &&
                (dst_k == LLVMFloatTypeKind || dst_k == LLVMDoubleTypeKind))
                return LLVMBuildSIToFP(ctx->builder, val, dst_ty, "sitofp");
            if ((src_k == LLVMFloatTypeKind || src_k == LLVMDoubleTypeKind) &&
                dst_k == LLVMIntegerTypeKind)
                return LLVMBuildFPToSI(ctx->builder, val, dst_ty, "fptosi");
        }
        return LLVMBuildBitCast(ctx->builder, val, dst_ty, "bitcast");
    }
    if (expr->node_type == AST_BINARY_EXPR) {
        LLVMValueRef L = codegen_expr(ctx, expr->data.binary_expr.left);
        LLVMValueRef R = codegen_expr(ctx, expr->data.binary_expr.right);
        if (!L || !R) return ((void*)0);
        Type *ltype = expr->data.binary_expr.left->type;
        int is_float = (ltype && ltype->kind == TYPE_PRIMITIVE &&
                          (ltype->as.primitive == PRIM_F32 ||
                           ltype->as.primitive == PRIM_F64));
        switch (expr->data.binary_expr.op) {
            case OP_ADD: return is_float ? LLVMBuildFAdd(ctx->builder, L, R, "addtmp") : LLVMBuildAdd(ctx->builder, L, R, "addtmp");
            case OP_SUB: return is_float ? LLVMBuildFSub(ctx->builder, L, R, "subtmp") : LLVMBuildSub(ctx->builder, L, R, "subtmp");
            case OP_MUL: return is_float ? LLVMBuildFMul(ctx->builder, L, R, "multmp") : LLVMBuildMul(ctx->builder, L, R, "multmp");
            case OP_DIV: return is_float ? LLVMBuildFDiv(ctx->builder, L, R, "divtmp") : LLVMBuildSDiv(ctx->builder, L, R, "divtmp");
            case OP_MOD: return is_float ? LLVMBuildFRem(ctx->builder, L, R, "modtmp") : LLVMBuildSRem(ctx->builder, L, R, "modtmp");
            case OP_EQ: {
                LLVMValueRef res = is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOEQ, L, R, "eqtmp") : LLVMBuildICmp(ctx->builder, LLVMIntEQ, L, R, "eqtmp");
                return LLVMBuildZExt(ctx->builder, res, get_llvm_type(ctx, expr->type), "bool_zext");
            }
            case OP_NEQ: {
                LLVMValueRef res = is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealONE, L, R, "neqtmp") : LLVMBuildICmp(ctx->builder, LLVMIntNE, L, R, "neqtmp");
                return LLVMBuildZExt(ctx->builder, res, get_llvm_type(ctx, expr->type), "bool_zext");
            }
            case OP_LT: {
                LLVMValueRef res = is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOLT, L, R, "lttmp") : LLVMBuildICmp(ctx->builder, LLVMIntSLT, L, R, "lttmp");
                return LLVMBuildZExt(ctx->builder, res, get_llvm_type(ctx, expr->type), "bool_zext");
            }
            case OP_GT: {
                LLVMValueRef res = is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOGT, L, R, "gttmp") : LLVMBuildICmp(ctx->builder, LLVMIntSGT, L, R, "gttmp");
                return LLVMBuildZExt(ctx->builder, res, get_llvm_type(ctx, expr->type), "bool_zext");
            }
            case OP_LE: {
                LLVMValueRef res = is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOLE, L, R, "letmp") : LLVMBuildICmp(ctx->builder, LLVMIntSLE, L, R, "letmp");
                return LLVMBuildZExt(ctx->builder, res, get_llvm_type(ctx, expr->type), "bool_zext");
            }
            case OP_GE: {
                LLVMValueRef res = is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOGE, L, R, "getmp") : LLVMBuildICmp(ctx->builder, LLVMIntSGE, L, R, "getmp");
                return LLVMBuildZExt(ctx->builder, res, get_llvm_type(ctx, expr->type), "bool_zext");
            }
            case OP_AND: {
                LLVMValueRef res = LLVMBuildAnd(ctx->builder, L, R, "andtmp");
                return LLVMBuildZExt(ctx->builder, res, get_llvm_type(ctx, expr->type), "bool_zext");
            }
            case OP_OR: {
                LLVMValueRef res = LLVMBuildOr(ctx->builder, L, R, "ortmp");
                return LLVMBuildZExt(ctx->builder, res, get_llvm_type(ctx, expr->type), "bool_zext");
            }
            default: {
                ice_impl("./src/codegen/codegen_ops.c", 159, "codegen_expr_ops: unhandled binary operator %d", expr->data.binary_expr.op);
            }
        }
    }
    if (expr->node_type == AST_ASSIGNMENT_EXPR) {
        AstAssignmentExpr *assign = &expr->data.assignment_expr;
        LLVMValueRef ptr = codegen_lvalue(ctx, assign->lvalue);
        LLVMValueRef rval = codegen_expr(ctx, assign->rvalue);
        if (!ptr || !rval) return ((void*)0);
        if (assign->op == OP_ASSIGN) {
            LLVMBuildStore(ctx->builder, rval, ptr);
            return rval;
        }
        LLVMTypeRef ty = get_llvm_type(ctx, assign->lvalue->type);
        LLVMValueRef lval = LLVMBuildLoad2(ctx->builder, ty, ptr, "loadtmp");
        LLVMValueRef res = ((void*)0);
        Type *ltype = assign->lvalue->type;
        int is_float = (ltype && ltype->kind == TYPE_PRIMITIVE &&
                          (ltype->as.primitive == PRIM_F32 ||
                           ltype->as.primitive == PRIM_F64));
        switch (assign->op) {
            case OP_PLUS_EQ: res = is_float ? LLVMBuildFAdd(ctx->builder, lval, rval, "addtmp") : LLVMBuildAdd(ctx->builder, lval, rval, "addtmp"); break;
            case OP_MINUS_EQ: res = is_float ? LLVMBuildFSub(ctx->builder, lval, rval, "subtmp") : LLVMBuildSub(ctx->builder, lval, rval, "subtmp"); break;
            case OP_MUL_EQ: res = is_float ? LLVMBuildFMul(ctx->builder, lval, rval, "multmp") : LLVMBuildMul(ctx->builder, lval, rval, "multmp"); break;
            case OP_DIV_EQ: res = is_float ? LLVMBuildFDiv(ctx->builder, lval, rval, "divtmp") : LLVMBuildSDiv(ctx->builder, lval, rval, "divtmp"); break;
            case OP_MOD_EQ: res = is_float ? LLVMBuildFRem(ctx->builder, lval, rval, "modtmp") : LLVMBuildSRem(ctx->builder, lval, rval, "modtmp"); break;
            default: res = rval; break;
        }
        if (res) LLVMBuildStore(ctx->builder, res, ptr);
        return res;
    }
    if (expr->node_type == AST_UNARY_EXPR) {
        AstUnaryExpr *ue = &expr->data.unary_expr;
        if (ue->op == OP_ADRESS) {
            return codegen_lvalue(ctx, ue->expr);
        } else if (ue->op == OP_DEREF) {
            LLVMValueRef ptr = codegen_expr(ctx, ue->expr);
            return codegen_load_value(ctx, ptr, expr->type);
        } else if (ue->op == OP_SUB) {
            LLVMValueRef val = codegen_expr(ctx, ue->expr);
            LLVMTypeRef ty = LLVMTypeOf(val);
            if (LLVMGetTypeKind(ty) == LLVMIntegerTypeKind)
                return LLVMBuildNeg(ctx->builder, val, "negtmp");
            return LLVMBuildFNeg(ctx->builder, val, "fnegtmp");
        } else if (ue->op == OP_NOT) {
            LLVMValueRef val = codegen_expr(ctx, ue->expr);
            LLVMTypeRef ty = LLVMTypeOf(val);
            if (LLVMGetTypeKind(ty) == LLVMIntegerTypeKind) {
                LLVMValueRef res = LLVMBuildICmp(ctx->builder, LLVMIntEQ, val, LLVMConstInt(ty, 0, 0), "nottmp");
                return LLVMBuildZExt(ctx->builder, res, ty, "not_bool");
            }
            return LLVMBuildNot(ctx->builder, val, "nottmp");
        }
 else if (ue->op == OP_POST_INC || ue->op == OP_POST_DEC ||
                   ue->op == OP_PRE_INC || ue->op == OP_PRE_DEC) {
            LLVMValueRef ptr = codegen_lvalue(ctx, ue->expr);
            LLVMTypeRef ty = get_llvm_type(ctx, ue->expr->type);
            if (LLVMGetTypeKind(ty) == LLVMVoidTypeKind) return ((void*)0);
            LLVMValueRef val = LLVMBuildLoad2(ctx->builder, ty, ptr, "loadtmp");
            LLVMValueRef new_val = ((void*)0);
            int is_float = (LLVMGetTypeKind(ty) == LLVMFloatTypeKind ||
                            LLVMGetTypeKind(ty) == LLVMDoubleTypeKind);
            if (!is_float) {
                if (ue->op == OP_POST_INC || ue->op == OP_PRE_INC)
                    new_val = LLVMBuildAdd(ctx->builder, val, LLVMConstInt(ty, 1, 0), "inc");
                else
                    new_val = LLVMBuildSub(ctx->builder, val, LLVMConstInt(ty, 1, 0), "dec");
            } else {
                if (ue->op == OP_POST_INC || ue->op == OP_PRE_INC)
                    new_val = LLVMBuildFAdd(ctx->builder, val, LLVMConstReal(ty, 1.0), "inc");
                else
                    new_val = LLVMBuildFSub(ctx->builder, val, LLVMConstReal(ty, 1.0), "dec");
            }
            if (new_val) LLVMBuildStore(ctx->builder, new_val, ptr);
            return (ue->op == OP_POST_INC || ue->op == OP_POST_DEC) ? val : new_val;
        }
    }
    return ((void*)0);
}
static LLVMValueRef coerce_to_bool(CodegenContext *ctx, LLVMValueRef val) {
    LLVMTypeRef ty = LLVMTypeOf(val);
    LLVMTypeKind kind = LLVMGetTypeKind(ty);
    if (kind == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(ty) == 1) {
        return val;
    }
    if (kind == LLVMPointerTypeKind) {
        return LLVMBuildICmp(ctx->builder, LLVMIntNE, val, LLVMConstNull(ty), "cond");
    } else if (kind == LLVMIntegerTypeKind) {
        return LLVMBuildICmp(ctx->builder, LLVMIntNE, val, LLVMConstInt(ty, 0, 0), "cond");
    } else if (kind == LLVMFloatTypeKind || kind == LLVMDoubleTypeKind) {
        return LLVMBuildFCmp(ctx->builder, LLVMRealUNE, val, LLVMConstNull(ty), "cond");
    }
    return val;
}
void codegen_statement(CodegenContext *ctx, AstNode *stmt) {
    if (!stmt) return;
    LLVMBasicBlockRef current_block = LLVMGetInsertBlock(ctx->builder);
    if (current_block && LLVMGetBasicBlockTerminator(current_block)) {
        return;
    }
    if (!stmt->type) {
        switch (stmt->node_type) {
            case AST_BLOCK:
            case AST_IF_STATEMENT:
            case AST_WHILE_STATEMENT:
            case AST_FOR_STATEMENT:
            case AST_RETURN_STATEMENT:
            case AST_BREAK_STATEMENT:
            case AST_CONTINUE_STATEMENT:
            case AST_DEFER_STATEMENT:
            case AST_EXPR_STATEMENT:
                break;
            default:
                ice_impl_at("./src/codegen/codegen_stmt.c", 47, (stmt)->filename, (stmt)->span, "Statement node type %d missing type annotation.", stmt->node_type);
        }
    }
    switch (stmt->node_type) {
        case AST_BLOCK: {
            DynArray *stmts = stmt->data.block.statements;
            ctx->locals = codegen_map_create(ctx, ctx->locals);
            size_t previous_defer_count = ctx->deferred_actions->count;
            for (size_t i = 0; i < stmts->count; i++) {
                AstNode *s = *(AstNode**)dynarray_get(stmts, i);
                codegen_statement(ctx, s);
            }
            for (int i = (int)ctx->deferred_actions->count - 1; i >= (int)previous_defer_count; i--) {
                AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, i);
                codegen_statement(ctx, body);
            }
            ctx->deferred_actions->count = previous_defer_count;
            CodegenMap *old = ctx->locals;
            ctx->locals = old->parent;
            codegen_map_destroy(old);
            break;
        }
        case AST_IF_STATEMENT: {
            AstIfStatement *ifs = &stmt->data.if_statement;
            LLVMValueRef cond = coerce_to_bool(ctx, codegen_expr(ctx, ifs->condition));
            LLVMValueRef func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));
            LLVMBasicBlockRef then_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "then");
            LLVMBasicBlockRef else_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "else");
            LLVMBasicBlockRef merge_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "merge");
            LLVMBuildCondBr(ctx->builder, cond, then_bb, else_bb);
            LLVMPositionBuilderAtEnd(ctx->builder, then_bb);
            codegen_statement(ctx, ifs->then_branch);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, merge_bb);
            LLVMPositionBuilderAtEnd(ctx->builder, else_bb);
            if (ifs->else_branch) codegen_statement(ctx, ifs->else_branch);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, merge_bb);
            LLVMPositionBuilderAtEnd(ctx->builder, merge_bb);
            break;
        }
        case AST_WHILE_STATEMENT: {
            AstWhileStatement *whl = &stmt->data.while_statement;
            LLVMValueRef func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));
            LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "while.cond");
            LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "while.body");
            LLVMBasicBlockRef end_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "while.end");
            LLVMBuildBr(ctx->builder, cond_bb);
            LLVMPositionBuilderAtEnd(ctx->builder, cond_bb);
            LLVMValueRef cond = coerce_to_bool(ctx, codegen_expr(ctx, whl->condition));
            LLVMBuildCondBr(ctx->builder, cond, body_bb, end_bb);
            LLVMBasicBlockRef old_cond = ctx->loop_cond_bb;
            LLVMBasicBlockRef old_end = ctx->loop_end_bb;
            size_t old_loop_defer = ctx->loop_defer_count;
            ctx->loop_cond_bb = cond_bb;
            ctx->loop_end_bb = end_bb;
            ctx->loop_defer_count = ctx->deferred_actions->count;
            LLVMPositionBuilderAtEnd(ctx->builder, body_bb);
            codegen_statement(ctx, whl->body);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, cond_bb);
            ctx->loop_cond_bb = old_cond;
            ctx->loop_end_bb = old_end;
            ctx->loop_defer_count = old_loop_defer;
            LLVMPositionBuilderAtEnd(ctx->builder, end_bb);
            break;
        }
        case AST_FOR_STATEMENT: {
            AstForStatement *fst = &stmt->data.for_statement;
            LLVMValueRef func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));
            ctx->locals = codegen_map_create(ctx, ctx->locals);
            if (fst->init) codegen_statement(ctx, fst->init);
            LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.cond");
            LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.body");
            LLVMBasicBlockRef post_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.post");
            LLVMBasicBlockRef end_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.end");
            LLVMBuildBr(ctx->builder, cond_bb);
            LLVMPositionBuilderAtEnd(ctx->builder, cond_bb);
            if (fst->condition) {
                LLVMValueRef cond = coerce_to_bool(ctx, codegen_expr(ctx, fst->condition));
                LLVMBuildCondBr(ctx->builder, cond, body_bb, end_bb);
            } else {
                LLVMBuildBr(ctx->builder, body_bb);
            }
            LLVMBasicBlockRef old_cond = ctx->loop_cond_bb;
            LLVMBasicBlockRef old_end = ctx->loop_end_bb;
            size_t old_loop_defer = ctx->loop_defer_count;
            ctx->loop_cond_bb = post_bb;
            ctx->loop_end_bb = end_bb;
            ctx->loop_defer_count = ctx->deferred_actions->count;
            LLVMPositionBuilderAtEnd(ctx->builder, body_bb);
            codegen_statement(ctx, fst->body);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, post_bb);
            LLVMPositionBuilderAtEnd(ctx->builder, post_bb);
            if (fst->post) codegen_expr(ctx, fst->post);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, cond_bb);
            ctx->loop_cond_bb = old_cond;
            ctx->loop_end_bb = old_end;
            ctx->loop_defer_count = old_loop_defer;
            LLVMPositionBuilderAtEnd(ctx->builder, end_bb);
            CodegenMap *old = ctx->locals;
            ctx->locals = old->parent;
            codegen_map_destroy(old);
            break;
        }
        case AST_RETURN_STATEMENT: {
            Type *fn_type = ctx->current_func_type;
            if (!fn_type) ice_impl("./src/codegen/codegen_stmt.c", 188, "Return statement outside of function context.");
            LLVMValueRef retval = ((void*)0);
            if (stmt->data.return_statement.expression) {
                retval = codegen_expr(ctx, stmt->data.return_statement.expression);
                if (!retval) {
                    LLVMTypeRef ty = get_llvm_type(ctx, stmt->data.return_statement.expression->type);
                    if (LLVMGetTypeKind(ty) != LLVMVoidTypeKind)
                        retval = LLVMConstNull(ty);
                }
            }
            while (ctx->deferred_actions->count > 0) {
                AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, ctx->deferred_actions->count - 1);
                ctx->deferred_actions->count--;
                codegen_statement(ctx, body);
                current_block = LLVMGetInsertBlock(ctx->builder);
                if (current_block && LLVMGetBasicBlockTerminator(current_block)) {
                    return;
                }
            }
            _Bool sret = type_is_indirect(ctx, fn_type->as.func.return_type);
            if (sret) {
                if (retval) LLVMBuildStore(ctx->builder, retval, ctx->sret_ptr);
                LLVMBuildRetVoid(ctx->builder);
                return;
            } else if (retval) {
                LLVMBuildRet(ctx->builder, retval);
                return;
            }
            LLVMBuildRetVoid(ctx->builder);
            break;
        }
        case AST_BREAK_STATEMENT: {
            if (ctx->loop_end_bb) {
                size_t original_count = ctx->deferred_actions->count;
                while (ctx->deferred_actions->count > ctx->loop_defer_count) {
                    AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, ctx->deferred_actions->count - 1);
                    ctx->deferred_actions->count--;
                    codegen_statement(ctx, body);
                    LLVMBasicBlockRef stmt_block = LLVMGetInsertBlock(ctx->builder);
                    if (stmt_block && LLVMGetBasicBlockTerminator(stmt_block)) {
                        break;
                    }
                }
                ctx->deferred_actions->count = original_count;
                current_block = LLVMGetInsertBlock(ctx->builder);
                if (current_block && !LLVMGetBasicBlockTerminator(current_block)) {
                    LLVMBuildBr(ctx->builder, ctx->loop_end_bb);
                }
            }
            break;
        }
        case AST_CONTINUE_STATEMENT: {
            if (ctx->loop_cond_bb) {
                size_t original_count = ctx->deferred_actions->count;
                while (ctx->deferred_actions->count > ctx->loop_defer_count) {
                    AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, ctx->deferred_actions->count - 1);
                    ctx->deferred_actions->count--;
                    codegen_statement(ctx, body);
                    LLVMBasicBlockRef stmt_block = LLVMGetInsertBlock(ctx->builder);
                    if (stmt_block && LLVMGetBasicBlockTerminator(stmt_block)) {
                        break;
                    }
                }
                ctx->deferred_actions->count = original_count;
                current_block = LLVMGetInsertBlock(ctx->builder);
                if (current_block && !LLVMGetBasicBlockTerminator(current_block)) {
                    LLVMBuildBr(ctx->builder, ctx->loop_cond_bb);
                }
            }
            break;
        }
        case AST_VARIABLE_DECLARATION: {
            AstVariableDeclaration *vdecl = &stmt->data.variable_declaration;
            if (!stmt->type) ice_impl_at("./src/codegen/codegen_stmt.c", 280, (stmt)->filename, (stmt)->span, "Variable declaration missing type.");
            LLVMTypeRef ty = get_llvm_type(ctx, stmt->type);
            LLVMValueRef alloca = create_entry_block_alloca(ctx, ty, "var");
            if (vdecl->intern_result) {
                void *key = (void*)(intptr_t)vdecl->intern_result->entry->dense_index;
                codegen_map_put(ctx->locals, key, alloca);
            }
            if (vdecl->initializer) {
                LLVMValueRef init_val = codegen_expr(ctx, vdecl->initializer);
                if (init_val) LLVMBuildStore(ctx->builder, init_val, alloca);
            }
            break;
        }
        case AST_EXPR_STATEMENT: {
            codegen_expr(ctx, stmt->data.expr_statement.expression);
            break;
        }
        case AST_DEFER_STATEMENT: {
            dynarray_push_value(ctx->deferred_actions, &stmt->data.defer_statement.body);
            break;
        }
        default:
            ice_impl_at("./src/codegen/codegen_stmt.c", 307, (stmt)->filename, (stmt)->span, "Unhandled statement type %d in codegen.", stmt->node_type);
    }
}
LLVMTypeRef get_llvm_function_type(CodegenContext *ctx, Type *t) {
    if (!t || t->kind != TYPE_FUNCTION) return LLVMFunctionType(LLVMVoidTypeInContext(ctx->context), ((void*)0), 0, 0);
    _Bool sret = type_is_indirect(ctx, t->as.func.return_type);
    LLVMTypeRef ret_type = sret ? LLVMVoidTypeInContext(ctx->context) : get_llvm_type(ctx, t->as.func.return_type);
    size_t param_count = t->as.func.param_count;
    size_t llvm_arg_count = param_count + (sret ? 1 : 0);
    LLVMTypeRef *llvm_params = xmalloc(sizeof(LLVMTypeRef) * llvm_arg_count);
    size_t idx = 0;
    if (sret) {
        llvm_params[idx++] = LLVMPointerType(get_llvm_type(ctx, t->as.func.return_type), 0);
    }
    for (size_t i = 0; i < param_count; i++) {
        Type *param_ty = t->as.func.params[i];
        if (type_is_indirect(ctx, param_ty)) {
            llvm_params[idx++] = LLVMPointerType(get_llvm_type(ctx, param_ty), 0);
        } else {
            llvm_params[idx++] = get_llvm_type(ctx, param_ty);
        }
    }
    LLVMTypeRef fn_ty = LLVMFunctionType(ret_type, llvm_params, (unsigned)llvm_arg_count, 0);
    free(llvm_params);
    return fn_ty;
}
_Bool type_is_address_only(Type *t) {
    if (!t) ice_impl("./src/codegen/codegen_types.c", 33, "type_is_address_only: NULL type reached codegen");
    switch (t->kind) {
        case TYPE_FUNCTION: return 1;
        case TYPE_ARRAY: return 1;
        case TYPE_SLICE: return 0;
        case TYPE_VOID: return 1;
        default: return 0;
    }
}
_Bool type_is_indirect(CodegenContext *ctx, Type *t) {
    if (t->kind != TYPE_STRUCT) return 0;
    LLVMTypeRef llvm_ty = get_llvm_type(ctx, t);
    return LLVMABISizeOfType(ctx->target_data, llvm_ty) > 16;
}
LLVMValueRef codegen_load_value(CodegenContext *ctx, LLVMValueRef ptr, Type *type) {
    if (!ptr) ice_impl("./src/codegen/codegen_types.c", 51, "codegen_load_value: NULL lvalue for type kind %d", type ? type->kind : -1);
    if (type_is_address_only(type)) return ptr;
    return LLVMBuildLoad2(ctx->builder, get_llvm_type(ctx, type), ptr, "loadtmp");
}
LLVMTypeRef get_llvm_type(CodegenContext *ctx, Type *t) {
    if (!t) ice_impl("./src/codegen/codegen_types.c", 57, "get_llvm_type: received NULL type.");
    LLVMTypeRef cached = hashmap_get(ctx->type_cache, t, ptr_hash, ptr_cmp);
    if (cached) return cached;
    LLVMTypeRef res = ((void*)0);
    switch (t->kind) {
        case TYPE_VOID: res = LLVMVoidTypeInContext(ctx->context); break;
        case TYPE_PRIMITIVE:
            switch (t->as.primitive) {
                case PRIM_I32: res = LLVMInt32TypeInContext(ctx->context); break;
                case PRIM_I64: res = LLVMInt64TypeInContext(ctx->context); break;
                case PRIM_F32: res = LLVMFloatTypeInContext(ctx->context); break;
                case PRIM_F64: res = LLVMDoubleTypeInContext(ctx->context); break;
                case PRIM_BOOL: res = LLVMInt8TypeInContext(ctx->context); break;
                case PRIM_CHAR: res = LLVMInt8TypeInContext(ctx->context); break;
                default: ice_impl("./src/codegen/codegen_types.c", 75, "get_llvm_type: unrecognized primitive kind %d", t->as.primitive);
            }
            break;
        case TYPE_POINTER:
        case TYPE_FUNCTION:
            res = LLVMPointerType(LLVMInt8TypeInContext(ctx->context), 0);
            break;
        case TYPE_ARRAY:
            res = LLVMArrayType(get_llvm_type(ctx, t->as.array.base), (unsigned int)t->as.array.size);
            break;
        case TYPE_SLICE:
            {
                LLVMTypeRef elements[] = {
                    LLVMPointerType(LLVMInt8TypeInContext(ctx->context), 0),
                    LLVMInt64TypeInContext(ctx->context)
                };
                res = LLVMStructTypeInContext(ctx->context, elements, 2, 0);
            }
            break;
        case TYPE_STRUCT: {
            const char *struct_name = "anon_struct";
            if (t->as.struct_type.name && t->as.struct_type.name->key) {
                struct_name = ((Slice*)t->as.struct_type.name->key)->ptr;
            }
            LLVMTypeRef struct_ty = LLVMStructCreateNamed(ctx->context, struct_name);
            hashmap_put(ctx->type_cache, (void*)t, struct_ty, ptr_hash, ptr_cmp);
            size_t field_count = t->as.struct_type.field_count;
            if (field_count > 0) {
                LLVMTypeRef *field_types = xmalloc(sizeof(LLVMTypeRef) * field_count);
                for (size_t i = 0; i < field_count; i++) {
                    field_types[i] = get_llvm_type(ctx, t->as.struct_type.fields[i].type);
                }
                LLVMStructSetBody(struct_ty, field_types, (unsigned int)field_count, 0);
                free(field_types);
            } else {
                LLVMStructSetBody(struct_ty, ((void*)0), 0, 0);
            }
            return struct_ty;
        }
        default:
            ice_impl("./src/codegen/codegen_types.c", 122, "get_llvm_type: unrecognized type kind %d", t->kind);
    }
    if (res) {
        hashmap_put(ctx->type_cache, (void*)t, res, ptr_hash, ptr_cmp);
    }
    return res;
}
LLVMValueRef create_entry_block_alloca(CodegenContext *ctx, LLVMTypeRef ty, const char *name) {
    LLVMBasicBlockRef current_block = LLVMGetInsertBlock(ctx->builder);
    LLVMValueRef current_func = LLVMGetBasicBlockParent(current_block);
    LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(current_func);
    LLVMBuilderRef tmp_builder = LLVMCreateBuilderInContext(ctx->context);
    LLVMValueRef first_instr = LLVMGetFirstInstruction(entry_block);
    if (first_instr) {
        LLVMPositionBuilderBefore(tmp_builder, first_instr);
    } else {
        LLVMPositionBuilderAtEnd(tmp_builder, entry_block);
    }
    LLVMValueRef alloca = LLVMBuildAlloca(tmp_builder, ty, name);
    LLVMDisposeBuilder(tmp_builder);
    return alloca;
}
char* mangle_name(CodegenContext *ctx, CompilationUnit *unit, InternResult *symbol_name) {
    if (!unit || !unit->logical_path) {
        Slice *s = (Slice*)symbol_name->key;
        char *name = xmalloc(s->len + 1);
        __builtin___memcpy_chk (name, s->ptr, s->len, __builtin_object_size (name, 0));
        name[s->len] = '\0';
        return name;
    }
    Slice *s = (Slice*)symbol_name->key;
    size_t len = strlen(unit->logical_path) + s->len + 10;
    char *mangled = xmalloc(len);
    char *log_path_fixed = xstrdup(unit->logical_path);
    for (char *p = log_path_fixed; *p; p++) if (*p == '.') *p = '_';
    __builtin___snprintf_chk (mangled, len, 0, __builtin_object_size (mangled, 2 > 1 ? 1 : 0), "__mod_%s_%.*s", log_path_fixed, (int)s->len, s->ptr);
    free(log_path_fixed);
    return mangled;
}
size_t struct_field_index(Type *struct_type, const char *field_name) {
    for (size_t i = 0; i < struct_type->as.struct_type.field_count; i++) {
        Slice *name = (Slice*)struct_type->as.struct_type.fields[i].name->key;
        if (name->len == strlen(field_name) && memcmp(name->ptr, field_name, name->len) == 0) {
            return i;
        }
    }
    return (size_t)-1;
}
size_t get_struct_field_index(Type *struct_type, InternResult *field_name) {
    for (size_t i = 0; i < struct_type->as.struct_type.field_count; i++) {
        if (struct_type->as.struct_type.fields[i].name == field_name) {
            return i;
        }
    }
    return (size_t)-1;
}
int parse_options(int argc, char **argv, Options *opts, const char **in_path) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 0;
    }
    opts->print_tokens = 0;
    opts->print_ast = 0;
    opts->print_ir = 0;
    opts->print_types = 0;
    opts->print_time = 0;
    opts->verbose = 0;
    opts->run_executable = 0;
    opts->quiet = 0;
    opts->output_name = "output";
    opts->opt_level = 0;
    opts->stdlib_path = "lib";
    int pos_args = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--tokens") == 0 || strcmp(argv[i], "-t") == 0) {
            opts->print_tokens = 1;
        } else if (strcmp(argv[i], "--ast") == 0 || strcmp(argv[i], "-a") == 0) {
            opts->print_ast = 1;
        } else if (strcmp(argv[i], "--ir") == 0) {
            opts->print_ir = 1;
        } else if (strcmp(argv[i], "--types") == 0 || strcmp(argv[i], "-y") == 0) {
            opts->print_types = 1;
        } else if (strcmp(argv[i], "--time") == 0 || strcmp(argv[i], "-T") == 0) {
            opts->print_time = 1;
        } else if (strcmp(argv[i], "--run") == 0 || strcmp(argv[i], "-r") == 0) {
            opts->run_executable = 1;
        } else if (strcmp(argv[i], "--quiet") == 0 || strcmp(argv[i], "-q") == 0) {
            opts->quiet = 1;
        } else if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0) {
            opts->verbose = 1;
        } else if (strncmp(argv[i], "-O", 2) == 0) {
            if (strlen(argv[i]) == 3) {
                opts->opt_level = argv[i][2] - '0';
            } else if (i + 1 < argc) {
                opts->opt_level = atoi(argv[++i]);
            }
            if (opts->opt_level < 0 || opts->opt_level > 3) {
                fprintf(__stderrp, "Error: Invalid optimization level: %d (must be 0-3)\n", opts->opt_level);
                return 0;
            }
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                opts->output_name = argv[++i];
            } else {
                fprintf(__stderrp, "Error: -o requires an argument\n");
                return 0;
            }
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--version") == 0) {
            print_version();
            return 0;
        } else if (argv[i][0] == '-') {
            fprintf(__stderrp, "Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            return 0;
        } else {
            if (pos_args == 0) {
                *in_path = argv[i];
                pos_args++;
            } else {
                fprintf(__stderrp, "Error: Unexpected argument: %s\n", argv[i]);
                return 0;
            }
        }
    }
    if (pos_args == 0) {
        fprintf(__stderrp, "Error: No input file specified\n");
        return 0;
    }
    return 1;
}
void print_usage(const char *prog) {
    fprintf(__stderrp, "Usage: %s <file> [options]\n", prog);
    fprintf(__stderrp, "Options:\n");
    fprintf(__stderrp, "  -o <name>       Set output executable name (default: 'output')\n");
    fprintf(__stderrp, "  -O<level>       Optimization level (0-3)\n");
    fprintf(__stderrp, "  -r, --run       Compile and run the program immediately\n");
    fprintf(__stderrp, "  -v, --verbose   Show compilation progress\n");
    fprintf(__stderrp, "  -q, --quiet     Suppress all non-error output\n");
    fprintf(__stderrp, "  -T, --time      Show performance metrics\n");
    fprintf(__stderrp, "  -a, --ast       Dump the parsed AST\n");
    fprintf(__stderrp, "  --ir            Dump the generated LLVM IR\n");
    fprintf(__stderrp, "  -t, --tokens    Dump lexer tokens\n");
    fprintf(__stderrp, "  -y, --types     Dump type system state\n");
    fprintf(__stderrp, "  --version       Show version information\n");
    fprintf(__stderrp, "  -h, --help      Show this help message\n");
}
void print_version(void) {
    printf("Compiler v3.0 (Development Build)\n");
}

typedef struct {
    double time_tokenize_ms;
    double time_parse_ms;
    double time_sema_ms;
    double time_codegen_ms;
    size_t mem_lex_bytes;
    size_t mem_parse_bytes;
    size_t mem_sema_bytes;
    size_t rss_delta_bytes;
    size_t token_count;
    size_t file_size_bytes;
    const char *filename;
} CompilationStats;
size_t count_ast_nodes(AstNode *program);
void print_compilation_report(CompilationStats *stats, AstNode *program);

static void count_nodes_recursive(AstNode *node, size_t *count) {
    if (!node) return;
    (*count)++;
    switch (node->node_type) {
        case AST_PROGRAM: {
            AstProgram *p = &node->data.program;
            if (p->decls) {
                for (size_t i = 0; i < p->decls->count; i++) {
                    count_nodes_recursive(*(AstNode**)dynarray_get(p->decls, i), count);
                }
            }
            break;
        }
        case AST_FUNCTION_DECLARATION: {
            AstFunctionDeclaration *f = &node->data.function_declaration;
            if (f->params) {
                for (size_t i = 0; i < f->params->count; i++) {
                    count_nodes_recursive(*(AstNode**)dynarray_get(f->params, i), count);
                }
            }
            count_nodes_recursive(f->return_type, count);
            count_nodes_recursive(f->body, count);
            break;
        }
        case AST_VARIABLE_DECLARATION: {
            AstVariableDeclaration *v = &node->data.variable_declaration;
            count_nodes_recursive(v->type, count);
            count_nodes_recursive(v->initializer, count);
            break;
        }
        case AST_BLOCK: {
            AstBlock *b = &node->data.block;
            if (b->statements) {
                for (size_t i = 0; i < b->statements->count; i++) {
                    count_nodes_recursive(*(AstNode**)dynarray_get(b->statements, i), count);
                }
            }
            break;
        }
        case AST_RETURN_STATEMENT:
            count_nodes_recursive(node->data.return_statement.expression, count);
            break;
        case AST_IF_STATEMENT: {
            AstIfStatement *i = &node->data.if_statement;
            count_nodes_recursive(i->condition, count);
            count_nodes_recursive(i->then_branch, count);
            count_nodes_recursive(i->else_branch, count);
            break;
        }
        case AST_WHILE_STATEMENT: {
            AstWhileStatement *w = &node->data.while_statement;
            count_nodes_recursive(w->condition, count);
            count_nodes_recursive(w->body, count);
            break;
        }
        case AST_BINARY_EXPR:
            count_nodes_recursive(node->data.binary_expr.left, count);
            count_nodes_recursive(node->data.binary_expr.right, count);
            break;
        case AST_UNARY_EXPR:
            count_nodes_recursive(node->data.unary_expr.expr, count);
            break;
        case AST_ASSIGNMENT_EXPR:
            count_nodes_recursive(node->data.assignment_expr.lvalue, count);
            count_nodes_recursive(node->data.assignment_expr.rvalue, count);
            break;
        case AST_CALL_EXPR: {
            AstCallExpr *c = &node->data.call_expr;
            count_nodes_recursive(c->callee, count);
            if (c->args) {
                for (size_t i = 0; i < c->args->count; i++) {
                    count_nodes_recursive(*(AstNode**)dynarray_get(c->args, i), count);
                }
            }
            break;
        }
        case AST_SUBSCRIPT_EXPR:
            count_nodes_recursive(node->data.subscript_expr.target, count);
            count_nodes_recursive(node->data.subscript_expr.index, count);
            break;
        case AST_INITIALIZER_LIST: {
            AstInitializeList *l = &node->data.initializer_list;
            if (l->elements) {
                for (size_t i = 0; i < l->elements->count; i++) {
                    count_nodes_recursive(*(AstNode**)dynarray_get(l->elements, i), count);
                }
            }
            break;
        }
        case AST_CAST:
            count_nodes_recursive(node->data.cast_expr.expr, count);
            break;
        case AST_EXPR_STATEMENT:
            count_nodes_recursive(node->data.expr_statement.expression, count);
            break;
        case AST_TYPE:
            if (node->data.ast_type.kind == AST_TYPE_ARRAY) {
                count_nodes_recursive(node->data.ast_type.u.array.elem, count);
                count_nodes_recursive(node->data.ast_type.u.array.size_expr, count);
            } else if (node->data.ast_type.kind == AST_TYPE_PTR) {
                count_nodes_recursive(node->data.ast_type.u.ptr.target, count);
            } else if (node->data.ast_type.kind == AST_TYPE_FUNC) {
                count_nodes_recursive(node->data.ast_type.u.func.return_type, count);
            }
            break;
        default: break;
    }
}
size_t count_ast_nodes(AstNode *program) {
    size_t count = 0;
    count_nodes_recursive(program, &count);
    return count;
}
static void print_mem_unit(size_t bytes) {
    if (bytes < 1024) {
        printf("  %7zu B   ", bytes);
    } else if (bytes < 1024 * 1024) {
        printf("  %7.2f KB  ", bytes / 1024.0);
    } else {
        printf("  %7.2f MB  ", bytes / (1024.0 * 1024.0));
    }
}
void print_compilation_report(CompilationStats *stats, AstNode *program) {
    double total_time = stats->time_tokenize_ms + stats->time_parse_ms + stats->time_sema_ms + stats->time_codegen_ms;
    if (total_time <= 0) total_time = 0.001;
    size_t ast_nodes = count_ast_nodes(program);
    size_t total_mem = stats->mem_lex_bytes + stats->mem_parse_bytes + stats->mem_sema_bytes;
    double throughput = (stats->file_size_bytes / (1024.0 * 1024.0)) / (total_time / 1000.0);
    printf("\n%s[%sCompiling %s%s%s]%s\n", "\033[90m", "\033[0m", "\033[36m", stats->filename ? stats->filename : "<stdin>", "\033[0m", "\033[0m");
    printf("%s┌─────────────────┬─────────────┬──────────────┐%s\n", "\033[90m", "\033[0m");
    printf("%s│%s Phase           %s│%s  Time       %s│%s Memory       %s│%s\n", "\033[90m", "\033[1m", "\033[90m", "\033[1m", "\033[90m", "\033[1m", "\033[90m", "\033[0m");
    printf("%s├─────────────────┼─────────────┼──────────────┤%s\n", "\033[90m", "\033[0m");
    printf("%s│%s Lexical         %s│%s %8.2f ms %s│%s", "\033[90m", "\033[0m", "\033[90m", "\033[0m", stats->time_tokenize_ms, "\033[90m", "\033[0m");
    print_mem_unit(stats->mem_lex_bytes);
    printf("%s│%s\n", "\033[90m", "\033[0m");
    printf("%s│%s Parsing         %s│%s %8.2f ms %s│%s", "\033[90m", "\033[0m", "\033[90m", "\033[0m", stats->time_parse_ms, "\033[90m", "\033[0m");
    print_mem_unit(stats->mem_parse_bytes);
    printf("%s│%s\n", "\033[90m", "\033[0m");
    printf("%s│%s Semantic        %s│%s %8.2f ms %s│%s", "\033[90m", "\033[0m", "\033[90m", "\033[0m", stats->time_sema_ms, "\033[90m", "\033[0m");
    print_mem_unit(stats->mem_sema_bytes);
    printf("%s│%s\n", "\033[90m", "\033[0m");
    printf("%s│%s Codegen         %s│%s %8.2f ms %s│%s      -       %s│%s\n", "\033[90m", "\033[0m", "\033[90m", "\033[0m", stats->time_codegen_ms, "\033[90m", "\033[0m", "\033[90m", "\033[0m");
    printf("%s├─────────────────┼─────────────┼──────────────┤%s\n", "\033[90m", "\033[0m");
    printf("%s│%s TOTAL           %s│%s %8.2f ms %s│%s", "\033[90m", "\033[1m", "\033[90m", "\033[1m", total_time, "\033[90m", "\033[1m");
    print_mem_unit(total_mem);
    printf("%s│%s\n", "\033[90m", "\033[0m");
    printf("%s└─────────────────┴─────────────┴──────────────┘%s\n", "\033[90m", "\033[0m");
    printf("  %sNodes:%s %zu  %sThroughput:%s %.2f MB/s\n\n", "\033[90m", "\033[0m", ast_nodes, "\033[90m", "\033[0m", throughput);
}
struct accessx_descriptor {
 unsigned int ad_name_offset;
 int ad_flags;
 int ad_pad[2];
};
int getattrlistbulk(int, void *, void *, size_t, uint64_t) __attribute__((availability(macosx,introduced=10.10)));
int getattrlistat(int, const char *, void *, void *, size_t, unsigned long) __attribute__((availability(macosx,introduced=10.10)));
int setattrlistat(int, const char *, void *, void *, size_t, uint32_t) __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0)));
ssize_t freadlink(int, char * restrict, size_t) __attribute__((availability(macos,introduced=13.0))) __attribute__((availability(ios,introduced=16.0))) __attribute__((availability(tvos,introduced=16.0))) __attribute__((availability(watchos,introduced=9.0)));
int faccessat(int, const char *, int, int) __attribute__((availability(macosx,introduced=10.10)));
int fchownat(int, const char *, uid_t, gid_t, int) __attribute__((availability(macosx,introduced=10.10)));
int linkat(int, const char *, int, const char *, int) __attribute__((availability(macosx,introduced=10.10)));
ssize_t readlinkat(int, const char *, char *, size_t) __attribute__((availability(macosx,introduced=10.10)));
int symlinkat(const char *, int, const char *) __attribute__((availability(macosx,introduced=10.10)));
int unlinkat(int, const char *, int) __attribute__((availability(macosx,introduced=10.10)));
void _exit(int) __attribute__((__noreturn__));
int access(const char *, int);
unsigned int
  alarm(unsigned int);
int chdir(const char *);
int chown(const char *, uid_t, gid_t);
int close(int) __asm("_" "close" );
int dup(int);
int dup2(int, int);
int execl(const char * __path, const char * __arg0, ...) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
int execle(const char * __path, const char * __arg0, ...) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
int execlp(const char * __file, const char * __arg0, ...) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
int execv(const char * __path, char * const * __argv) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
int execve(const char * __file, char * const * __argv, char * const * __envp) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
int execvp(const char * __file, char * const * __argv) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
pid_t fork(void) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
long fpathconf(int, int);
char * getcwd(char *, size_t __size);
gid_t getegid(void);
uid_t geteuid(void);
gid_t getgid(void);
int getgroups(int __gidsetsize, gid_t []);
char * getlogin(void);
pid_t getpgrp(void);
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
int isatty(int);
int link(const char *, const char *);
off_t lseek(int, off_t, int);
long pathconf(const char *, int);
int pause(void) __asm("_" "pause" );
int pipe(int [2]);
ssize_t read(int, void *, size_t __nbyte) __asm("_" "read" );
int rmdir(const char *);
int setgid(gid_t);
int setpgid(pid_t, pid_t);
pid_t setsid(void);
int setuid(uid_t);
unsigned int
  sleep(unsigned int) __asm("_" "sleep" );
long sysconf(int);
pid_t tcgetpgrp(int);
int tcsetpgrp(int, pid_t);
char * ttyname(int);
int ttyname_r(int, char *, size_t __len) __asm("_" "ttyname_r" );
int unlink(const char *);
ssize_t write(int __fd, const void * __buf, size_t __nbyte) __asm("_" "write" );
size_t confstr(int, char *, size_t __len) __asm("_" "confstr" );
int getopt(int __argc, char * const [], const char *) __asm("_" "getopt" );
extern char *optarg;
extern int optind, opterr, optopt;
__attribute__((__deprecated__)) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)))
void * brk(const void *);
int chroot(const char *) ;
char * crypt(const char *, const char *);
void encrypt(char *, int) __asm("_" "encrypt" );
int fchdir(int);
long gethostid(void);
pid_t getpgid(pid_t);
pid_t getsid(pid_t);
int getdtablesize(void) ;
int getpagesize(void) __attribute__((__const__)) ;
char * getpass(const char *) ;
char * getwd(char *) ;
int lchown(const char *, uid_t, gid_t) __asm("_" "lchown" );
int lockf(int, int, off_t) __asm("_" "lockf" );
int nice(int) __asm("_" "nice" );
ssize_t pread(int __fd, void * __buf, size_t __nbyte, off_t __offset) __asm("_" "pread" );
ssize_t pwrite(int __fd, const void * __buf, size_t __nbyte, off_t __offset) __asm("_" "pwrite" );
__attribute__((__deprecated__)) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)))
void * sbrk(int);
pid_t setpgrp(void) __asm("_" "setpgrp" );
int setregid(gid_t, gid_t) __asm("_" "setregid" );
int setreuid(uid_t, uid_t) __asm("_" "setreuid" );
void swab(const void * restrict , void * restrict , ssize_t __nbytes);
void sync(void);
int truncate(const char *, off_t);
useconds_t ualarm(useconds_t, useconds_t);
int usleep(useconds_t) __asm("_" "usleep" );
__attribute__((__deprecated__("Use posix_spawn or fork")))
pid_t vfork(void) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
int fsync(int) __asm("_" "fsync" );
int ftruncate(int, off_t);
int getlogin_r(char *, size_t __namelen);
int fchown(int, uid_t, gid_t);
int gethostname(char *, size_t __namelen);
ssize_t readlink(const char * restrict, char * restrict, size_t __bufsize);
int setegid(gid_t);
int seteuid(uid_t);
int symlink(const char *, const char *);
int pselect(int, fd_set * restrict, fd_set * restrict,
    fd_set * restrict, const struct timespec * restrict,
    const sigset_t * restrict)
__asm("_" "pselect" )
;
void _Exit(int) __attribute__((__noreturn__));
int accessx_np(const struct accessx_descriptor *, size_t __sz, int *, uid_t);
int acct(const char *);
int add_profil(char *, size_t __bufsiz, unsigned long, unsigned int) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
void endusershell(void);
int execvP(const char * __file, const char * __searchpath, char * const * __argv) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
char * fflagstostr(unsigned long);
int getdomainname(char *, int __namelen);
int getgrouplist(const char *, int, int *, int *__ngroups);
int gethostuuid(uuid_t, const struct timespec *) __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,unavailable))) __attribute__((availability(tvos,unavailable))) __attribute__((availability(watchos,unavailable)));

mode_t getmode(const void *, mode_t);
int getpeereid(int, uid_t *, gid_t *);
int getsgroups_np(int *, uuid_t);
char * getusershell(void);
int getwgroups_np(int *, uuid_t);
int initgroups(const char *, int);
int issetugid(void);
char * mkdtemp(char *);
int mknod(const char *, mode_t, dev_t);
int mkpath_np(const char *path, mode_t omode) __attribute__((availability(macosx,introduced=10.8)));
int mkpathat_np(int dfd, const char *path, mode_t omode)
  __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0)))
  __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0)));
int mkstemp(char *);
int mkstemps(char *, int);
char * mktemp(char *);
int mkostemp(char * path, int oflags)
  __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0)))
  __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0)));
int mkostemps(char * path, int slen, int oflags)
  __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0)))
  __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0)));
int mkstemp_dprotected_np(char * path, int dpclass, int dpflags)
  __attribute__((availability(macosx,unavailable))) __attribute__((availability(ios,introduced=10.0)))
  __attribute__((availability(tvos,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0)));
char * mkdtempat_np(int dfd, char * path)
  __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0)))
  __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0)));
int mkstempsat_np(int dfd, char * path, int slen)
  __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0)))
  __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0)));
int mkostempsat_np(int dfd, char * path, int slen, int oflags)
  __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0)))
  __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0)));
int nfssvc(int, void *);
int profil(char *, size_t __bufsiz, unsigned long, unsigned int);
__attribute__((__deprecated__("Use of per-thread security contexts is error-prone and discouraged.")))
int pthread_setugid_np(uid_t, gid_t);
int pthread_getugid_np(uid_t *, gid_t *);
int reboot(int);
int revoke(const char *);
__attribute__((__deprecated__)) int rcmd(char * *, int, const char *, const char *, const char *, int *);
__attribute__((__deprecated__)) int rcmd_af(char * *, int, const char *, const char *, const char *, int *,
  int);
__attribute__((__deprecated__)) int rresvport(int *);
__attribute__((__deprecated__)) int rresvport_af(int *, int);
__attribute__((__deprecated__)) int iruserok(unsigned long, int, const char *, const char *);
__attribute__((__deprecated__)) int iruserok_sa(const void *, int, int, const char *, const char *);
__attribute__((__deprecated__)) int ruserok(const char *, int, const char *, const char *);
int setdomainname(const char *, int __namelen);
int setgroups(int, const gid_t *);
void sethostid(long);
int sethostname(const char *, int __namelen);
void setkey(const char *) __asm("_" "setkey" );
int setlogin(const char *);
void *setmode(const char *) __asm("_" "setmode" );
int setrgid(gid_t);
int setruid(uid_t);
int setsgroups_np(int, const uuid_t);
void setusershell(void);
int setwgroups_np(int, const uuid_t);
int strtofflags(char * *, unsigned long *, unsigned long *);
int swapon(const char *);
int ttyslot(void);
int undelete(const char *);
int unwhiteout(const char *);
void * valloc(size_t __size);
__attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)))
__attribute__((availability(ios,deprecated=10.0,message="syscall(2) is unsupported; " "please switch to a supported interface. For SYS_kdebug_trace use kdebug_signpost().")))
__attribute__((availability(macosx,deprecated=10.12,message="syscall(2) is unsupported; " "please switch to a supported interface. For SYS_kdebug_trace use kdebug_signpost().")))
int syscall(int, ...);
extern char *suboptarg;
int getsubopt(char * *, char * const *, char * *);
int fgetattrlist(int,void*,void *,size_t __attrBufSize,unsigned int) __attribute__((availability(macosx,introduced=10.6)));
int fsetattrlist(int,void*,void *,size_t __attrBufSize,unsigned int) __attribute__((availability(macosx,introduced=10.6)));
int getattrlist(const char*,void*,void *,size_t __attrBufSize,unsigned int) __asm("_" "getattrlist" );
int setattrlist(const char*,void*,void *,size_t __attrBufSize,unsigned int) __asm("_" "setattrlist" );
int exchangedata(const char*,const char*,unsigned int) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
int getdirentriesattr(int,void*,void *,size_t __attrBufSize,unsigned int*,unsigned int*,unsigned int*,unsigned int) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
struct fssearchblock;
struct searchstate;
int searchfs(const char *, struct fssearchblock *, unsigned long *, unsigned int, unsigned int, struct searchstate *) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
int fsctl(const char *,unsigned long,void *,unsigned int);
int ffsctl(int,unsigned long,void *,unsigned int) __attribute__((availability(macosx,introduced=10.6)));
int fsync_volume_np(int, int) __attribute__((availability(macosx,introduced=10.8)));
int sync_volume_np(const char *, int) __attribute__((availability(macosx,introduced=10.8)));
extern int optreset;
int main(int argc, char **argv) {
    codegen_initialize();
    Options opts;
    const char *path = ((void*)0);
    if (!parse_options(argc, argv, &opts, &path)) {
        return 1;
    }
    int exit_code = 0;
    Arena *arena = ((void*)0);
    long peak_rss_before_kb = get_peak_rss_kb();
    double t_start = now_seconds();
    arena = arena_create(8 * 1024 * 1024);
    if (!arena) {
        fprintf(__stderrp, "Error: Failed to create memory arena\n");
        return 2;
    }
    DenseArenaInterner *keywords = intern_table_create(hashmap_create(32), arena, string_copy_func, slice_hash, slice_cmp);
    DenseArenaInterner *identifiers = intern_table_create(hashmap_create(256), arena, string_copy_func, slice_hash, slice_cmp);
    DenseArenaInterner *strings = intern_table_create(hashmap_create(128), arena, string_copy_func, slice_hash, slice_cmp);
    lexer_populate_default_keywords(keywords);
    ModuleLoader *loader = module_loader_create(arena, &opts, keywords, identifiers, strings);
    exit_code = load_module_recursive(loader, path, ((void*)0), ((void*)0), 0);
    if (exit_code != 0) goto cleanup;
    double t_load_end = now_seconds();
    double t_parse = t_load_end - t_start;
    if (opts.verbose) printf("Semantic Analysis...\n");
    size_t mem_before_sema = arena_total_allocated(arena);
    double t3 = now_seconds();
    TypeStore *store = typestore_create(arena, identifiers, keywords);
    TypeCheckContext type_ctx = typecheck_context_create(
        arena,
        store,
        identifiers,
        keywords,
        path,
        loader
    );
    typecheck_program(&type_ctx);
    double t4 = now_seconds();
    double t_sema = t4 - t3;
    size_t mem_sema = arena_total_allocated(arena) - mem_before_sema;
    if (opts.print_ast) {
        printf("--- AST ---\n");
        for (size_t i = 0; i < loader->units_ordered->count; i++) {
            CompilationUnit *u = *(CompilationUnit**)dynarray_get(loader->units_ordered, i);
            printf("Module: %s\n", u->absolute_path);
            print_ast(u->ast_root, 0, keywords, identifiers, strings);
        }
    }
    if (opts.print_types) {
        CompilationUnit *main_unit = *(CompilationUnit**)dynarray_get(loader->units_ordered, loader->units_ordered->count - 1);
        type_print_store_dump(store, main_unit->global_scope);
    }
    if (type_ctx.errors->count > 0) {
        for (size_t i = 0; i < type_ctx.errors->count; i++) {
            TypeError *e = (TypeError*)dynarray_get(type_ctx.errors, i);
            print_type_error(e);
        }
        exit_code = 5;
        goto cleanup;
    }
    if (opts.verbose) printf("Code Generation...\n");
    double t5 = now_seconds();
    CodegenContext *cg_ctx = codegen_context_create(store, "main_module", opts.opt_level, loader);
    if (codegen_program(cg_ctx) == 0) {
        if (opts.print_ir) codegen_dump_module(cg_ctx);
        char obj_path[256];
        __builtin___snprintf_chk (obj_path, sizeof(obj_path), 0, __builtin_object_size (obj_path, 2 > 1 ? 1 : 0), "%s.o", opts.output_name);
        codegen_emit_object(cg_ctx, obj_path);
        if (opts.verbose) printf("Linking...\n");
        pid_t pid = fork();
        if (pid == 0) {
            char *args[] = {"cc", obj_path, "src/core/runtime.c", "-o", (char*)opts.output_name, ((void*)0)};
            execvp("cc", args);
            char *fallback_args[] = {"cc", obj_path, "-o", (char*)opts.output_name, ((void*)0)};
            execvp("cc", fallback_args);
            exit(1);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            if ((((*(int *)&(status)) & 0177) == 0) && (((*(int *)&(status)) >> 8) & 0x000000ff) == 0) {
                if (opts.verbose) printf("Successfully compiled to '%s' executable.\n", opts.output_name);
                if (opts.run_executable) {
                    pid_t pid2 = fork();
                    if (pid2 == 0) {
                        char run_cmd[512];
                        __builtin___snprintf_chk (run_cmd, sizeof(run_cmd), 0, __builtin_object_size (run_cmd, 2 > 1 ? 1 : 0), "./%s", opts.output_name);
                        char *run_args[] = { run_cmd, ((void*)0) };
                        execvp(run_cmd, run_args);
                        perror("execvp");
                        exit(1);
                    } else if (pid2 > 0) {
                        waitpid(pid2, ((void*)0), 0);
                    } else {
                        fprintf(__stderrp, "Error: fork failed for execution\n");
                    }
                }
            } else {
                fprintf(__stderrp, "Error: Linking failed\n");
                exit_code = 2;
            }
        } else {
            fprintf(__stderrp, "Error: fork failed\n");
            exit_code = 2;
        }
    } else {
        fprintf(__stderrp, "Error: Code generation failed\n");
        exit_code = 5;
    }
    codegen_context_destroy(cg_ctx);
    double t_codegen = now_seconds() - t5;
    if (opts.print_time) {
        printf("\n--- Metrics ---\n");
        printf("Time Parse/Load: %.3fms\n", t_parse * 1000);
        printf("Time Sema:       %.3fms\n", t_sema * 1000);
        printf("Time Codegen:    %.3fms\n", t_codegen * 1000);
        printf("Peak RSS:        %ld KB\n", get_peak_rss_kb());
    }
cleanup:
    if (arena) arena_destroy(arena);
    return exit_code;
}

