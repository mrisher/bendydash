# Track Plan: Refactor UI Layout with Updated Assets

## Phase 1: Asset Preparation & API Verification
- [ ] Task: Verify OpenWeatherMap API Response for Rain Data
    - [ ] Sub-task: Write Tests (Create a small script or sketch to print the full JSON response and verify the `pop` field exists and is accessible).
    - [ ] Sub-task: Implement Feature (Update `bendydash.ino` or data parsing logic to extract rain probability).
- [ ] Task: Prepare Visual Assets (Fonts/Bitmaps)
    - [ ] Sub-task: Analyze existing `pic.h` and `EPD_font.h` to determine what needs resizing.
    - [ ] Sub-task: Generate smaller weather icons and WiFi status icons using `convert_to_bmp.py` or find suitable built-in fonts.
    - [ ] Sub-task: Integrate new assets into the project (update header files).

## Phase 2: UI Logic Implementation
- [ ] Task: Implement Row 1 (Current Weather)
    - [ ] Sub-task: Write Tests (Mock display output or use serial logging to verify correct coordinates and data).
    - [ ] Sub-task: Implement drawing logic for Weather Icon and Text on the E-Paper.
- [ ] Task: Implement Row 2 (Temperature)
    - [ ] Sub-task: Write Tests (Verify temperature formatting and placement).
    - [ ] Sub-task: Implement drawing logic for Temperature.
- [ ] Task: Implement Row 3 (Rain Forecast)
    - [ ] Sub-task: Write Tests (Verify percentage formatting and placement).
    - [ ] Sub-task: Implement drawing logic for Rain Forecast %.
- [ ] Task: Implement Row 4 (Status Info)
    - [ ] Sub-task: Write Tests (Verify timestamp generation, city name, and WiFi icon toggling).
    - [ ] Sub-task: Implement drawing logic for Status Row.
- [ ] Task: Clear Right Side of Screen
    - [ ] Sub-task: Ensure no drawing commands target the right half of the display buffer.

## Phase 3: Integration & cleanup
- [ ] Task: Full System Test
    - [ ] Sub-task: compile and flash to device (if possible) or verify via logs that the full render loop completes without crashing.
    - [ ] Sub-task: Verify data freshness handling and WiFi status updates.
- [ ] Task: Conductor - User Manual Verification 'Integration & cleanup' (Protocol in workflow.md)
