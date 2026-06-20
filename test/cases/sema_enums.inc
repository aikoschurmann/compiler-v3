SEMA_VALID("enums_basic",
    "enum Color { Red, Green, Blue } "
    "fn main() -> i32 { "
    "   c: Color = Color.Green; "
    "   return c; "
    "}")

SEMA_VALID("enums_explicit_values",
    "enum Status { Ok = 200, NotFound = 404, InternalError = 500 } "
    "fn main() -> i32 { "
    "   s1: Status = Status.Ok; "
    "   s2: Status = Status.NotFound; "
    "   if (s1 == 200) { return s2; } "
    "   return 0; "
    "}")

SEMA_ERROR("enums_invalid_variant",
    "enum Color { Red, Green, Blue } "
    "fn main() -> i32 { "
    "   c: Color = Color.Yellow; "
    "   return c; "
    "}", TE_FIELD_ACCESS)

SEMA_ERROR("enums_duplicate_variant",
    "enum Color { Red, Green, Red } "
    "fn main() -> i32 { "
    "   return 0; "
    "}", TE_REDECLARATION)

SEMA_ERROR("enums_invalid_value",
    "enum Color { Red = \"Red\" } "
    "fn main() -> i32 { "
    "   return 0; "
    "}", TE_TYPE_MISMATCH)
