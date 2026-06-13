#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include "utils.h"

typedef struct AstNode AstNode;

/**
 * @brief Internal Compiler Error (ICE). 
 * Prints a fatal error message with file/line information and aborts.
 */
#define ICE(msg, ...) ice_impl(__FILE__, __LINE__, msg, ##__VA_ARGS__)

/**
 * @brief ICE with source location reporting.
 */
#define ICE_AT(node, msg, ...) ice_impl_at(__FILE__, __LINE__, (node)->span, msg, ##__VA_ARGS__)

void ice_impl(const char *file, int line, const char *fmt, ...) __attribute__((noreturn));
void ice_impl_at(const char *file, int line, Span span, const char *fmt, ...) __attribute__((noreturn));
