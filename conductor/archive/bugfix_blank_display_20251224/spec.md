# Track Specification: Bug Fix - Blank Display

## Goal
To resolve the critical issue where the display remains blank after the "Afterschool Schedule Grid" update.

## Problem Description
The user reports the display is "completely blank". This suggests the application is crashing, hanging, or failing to push the buffer to the display during the update cycle. The likely culprit is the newly added `draw_schedule_cell` logic or the `avatars.h` data.

## Investigation Plan
1.  **Verify Avatar Data:** Check if the generated C arrays in `avatars.h` match the expected size for 64x87 bitmaps. Reading past the array bounds would cause a crash.
2.  **Isolate the Fault:** Temporarily disable the grid drawing to confirm the weather part still works.
3.  **Fix Data/Logic:** Correct the data generation or drawing parameters.

## Acceptance Criteria
-   The display is no longer blank.
-   The Weather UI (left side) is visible.
-   The Afterschool Schedule Grid (right side) is visible and renders correctly without crashing.
