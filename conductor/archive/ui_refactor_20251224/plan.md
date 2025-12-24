# Track Plan: Refactor UI Layout with Updated Assets

## Phase 1: Asset Preparation & API Verification
- [x] Task: Verify OpenWeatherMap API Response for Rain Data 33dfa5e
    - [ ] Sub-task: Write Tests (Create a small script or sketch to print the full JSON response and verify the `pop` field exists and is accessible).
    - [ ] Sub-task: Implement Feature (Update `bendydash.ino` or data parsing logic to extract rain probability).
- [x] Task: Prepare Visual Assets (Fonts/Bitmaps) b9bdb91
    - [ ] Sub-task: Analyze existing `pic.h` and `EPD_font.h` to determine what needs resizing.
    - [ ] Sub-task: Generate smaller weather icons and WiFi status icons using `convert_to_bmp.py` or find suitable built-in fonts.
    - [ ] Sub-task: Integrate new assets into the project (update header files).

## Phase 2: UI Logic Implementation
- [x] Task: Implement Row 1 (Current Weather) 3c60e9b
- [x] Task: Implement Row 2 (Temperature) 3c60e9b
- [x] Task: Implement Row 3 (Rain Forecast) 3c60e9b
- [x] Task: Implement Row 4 (Status Info) 3c60e9b
- [x] Task: Clear Right Side of Screen 3c60e9b

## Phase 3: Integration & cleanup
- [x] Task: Full System Test 76001c0
- [x] Task: Conductor - User Manual Verification 'Integration & cleanup' (Protocol in workflow.md) 76001c0
