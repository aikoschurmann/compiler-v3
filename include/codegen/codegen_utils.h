#pragma once
#include "sema/type.h"
#include <stddef.h>

// Returns the index of a field by name in a struct type.
// Returns false if not found.
bool struct_field_index(Type *struct_type, const char *field_name, size_t *out_index);
bool get_struct_field_index(Type *struct_type, InternResult *field_name, size_t *out_index);
