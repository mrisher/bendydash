# Track Specification: Bug Fix - Syntax Error in Avatar Includes

## Goal
To resolve the compiler error caused by placing `#include` directives on the same line as namespace declarations in `bendydash.ino`.

## Problem Description
The compiler reports "stray '#' in program" because C++ preprocessor directives like `#include` must appear on their own lines.
Incorrect: `namespace Oliver { #include "oliver_avatar.h" }`
Correct:
```cpp
namespace Oliver {
#include "oliver_avatar.h"
}
```

## Acceptance Criteria
-   `bendydash.ino` compiles without "stray #" errors.
-   The avatar data is correctly accessible via the namespaces (e.g., `Oliver::IMAGE`).
