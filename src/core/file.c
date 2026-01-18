#include "file.h"
#include <string.h>

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");  // Open in binary mode
    if (!file) {
        perror("fopen");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);  // Get file size
    if (length < 0) {
        perror("ftell");
        fclose(file);
        return NULL;
    }
    rewind(file);

    char *buffer = malloc(length + 1);
    if (!buffer) {
        perror("malloc");
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, length, file) != (size_t)length) {
        perror("fread");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[length] = '\0';  // Null-terminate the string
    fclose(file);
    return buffer;
}

void free_file_content(char *content) {
    if (content) {
        free(content);
    }
}

/* --- Shared source excerpt helpers (moved here) --- */
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

    fprintf(stderr, "\x1b[33m%4zu\x1b[0m | %s\n", line_no, buf);
    fprintf(stderr, "     | ");
    
    // Spaces until start
    for (size_t i = 1; i < start_col; i++) fputc(' ', stderr);
    
    // Underline
    fprintf(stderr, "\x1b[31m");
    size_t width = (end_col >= start_col) ? (end_col - start_col) : 1;
    if (width == 0) width = 1; 
    for (size_t i = 0; i < width; i++) fputc('^', stderr);
    fprintf(stderr, "\x1b[0m\n");
}

void print_source_excerpt(const char *filename, size_t line_no, size_t col) {
    print_source_excerpt_span(filename, line_no, col, col + 1);
}