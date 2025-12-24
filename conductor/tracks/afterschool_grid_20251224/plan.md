# Track Plan: Implement Afterschool Schedule Grid

## Phase 1: Data & Asset Integration
- [x] Task: Integrate Avatars and Mock Data 6cd3581
    - [ ] Sub-task: Include `avatars.h` in `bendydash.ino`.
    - [ ] Sub-task: Define a C struct and an array of mock data for the 4 family members (name, avatar index, coming home time).

## Phase 2: UI Implementation
- [x] Task: Implement Grid Drawing Logic 1fc05fb
    - [ ] Sub-task: Define grid cell coordinates (top-left, top-right, bottom-left, bottom-right).
    - [ ] Sub-task: Create a helper function `draw_schedule_cell(int x, int y, int index)` to render a single person's info.
    - [ ] Sub-task: Update `UI_weather_forecast` to call the grid drawing logic.

## Phase 3: Integration & Verification
- [x] Task: Full System Test 767ea7f
    - [x] Sub-task: Verify alignment and legibility on the 4.2" screen.
- [x] Task: Conductor - User Manual Verification 'Integration & Verification' (Protocol in workflow.md) 767ea7f
