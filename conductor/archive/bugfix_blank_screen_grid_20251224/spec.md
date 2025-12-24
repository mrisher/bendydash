# Track Specification: Bug Fix - Blank Screen Regression (Grid Logic)

## Goal
To identify and fix the cause of the blank screen regression that occurred after implementing the second column (Afterschool Schedule Grid).

## Problem Description
The user reports the screen is "completely blank". This happened after the grid layout was added. The previous fix addressed avatar data size, but we switched to new C++ headers provided by the user. If these headers have different dimensions than the code expects (64x87), `EPD_ShowPicture` will crash or corrupt memory.

## Investigation Plan
1.  **Verify Header Dimensions:** Read the `*_avatar.h` files to check the comments or array sizes to confirm if they are exactly 696 bytes (64*87/8).
2.  **Verify Drawing Bounds:** Check `draw_schedule_cell` logic to ensure it doesn't draw outside 400x300.
3.  **Memory Usage:** Check if the `ImageBW` buffer size (15000) is sufficient. 400 * 300 / 8 = 15000 bytes. This is exact. If any drawing function writes even one byte past, it overflows.

## Acceptance Criteria
-   The display works again (shows weather and grid).
-   Avatar dimensions in code match the data in headers.
