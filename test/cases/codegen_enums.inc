CODEGEN_EXIT("enums_basic",
    "enum Color { Red, Green, Blue } "
    "fn main() -> i32 { "
    "   c: Color = Color.Green; "
    "   return c; "
    "}", 1)

CODEGEN_EXIT("enums_explicit_values",
    "enum Status { Ok = 200, NotFound = 404, InternalError = 500 } "
    "fn main() -> i32 { "
    "   s1: Status = Status.Ok; "
    "   s2: Status = Status.NotFound; "
    "   if (s1 == 200) { return s2; } "
    "   return 0; "
    "}", 404)

CODEGEN_EXIT("enums_auto_increment",
    "enum Weekday { Mon = 1, Tue, Wed, Thu, Fri, Sat, Sun } "
    "fn main() -> i32 { "
    "   return Weekday.Sun; "
    "}", 7)
