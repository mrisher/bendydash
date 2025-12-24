# Track Specification: Bug Fix - Avatar Generation Corruption

## Goal
To fix the `generate_avatars.py` script so that it produces valid C arrays in `avatars.h`. Currently, it outputs literal format strings (e.g., `0x{b:02x}`) and has syntax errors.

## Problem Description
The `to_c_array` function in the python script used an f-string incorrectly, likely failing to evaluate the variable `b` inside the inner format string or misusing the list comprehension string joining.
The error message `/Users/mrisher/Documents/Arduino/bendydash/avatars.h:183:89: error: expected unqualified-id before ',' token 0x{b:02x}, ...` confirms that the file contains the literal characters `{b:02x}` instead of hex values like `0x00` or `0xff`.

## Acceptance Criteria
-   `generate_avatars.py` runs without error.
-   `avatars.h` contains valid C code (arrays of hex bytes like `0x00, 0xff, ...`).
-   The avatar data is non-zero (contains the actual image data).
