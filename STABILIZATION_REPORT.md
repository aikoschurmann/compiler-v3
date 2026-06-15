

### Medium Priority: Type System & Duplication

| ID | Description | Impact |
| --- | --- | --- |
| **TD-2** | **Dummy Symbols:** Namespaces for modules are represented as "dummy module" symbols in the standard scope chain, complicating scope iteration. | Medium |
| **PS-3** | **Intrinsic Inconsistency:** `print`/`println` are typed via Symbol lookup in Sema, but caught via raw `memcmp` string matching in Codegen (ignoring `INTRINSIC_PRINT`). | Low |

### Low Priority: Cleanup & Inefficiencies

| ID | Description | Impact |
| --- | --- | --- |
| **I-1** | **O(n²) Struct Resolution:** Struct literals resolve fields using nested loops instead of linear matching. | Low |
