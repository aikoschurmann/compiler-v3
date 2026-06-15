#pragma once
#include <stdio.h>
#include "type.h"
#include "datastructures/scope.h"

void type_print(FILE *out, const Type *type);
void type_print_store_dump(TypeStore *store, Scope *global_scope);