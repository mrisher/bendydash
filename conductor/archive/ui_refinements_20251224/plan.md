# Track Plan: UI Refinements - Temperature, Date, and Network Info

## Phase 1: Asset & Data Preparation
- [x] Task: Generate Smaller WiFi Icon 3fcbb9c
    - [ ] Sub-task: Update `generate_small_assets.py` to create a 12x12 WiFi icon.
    - [ ] Sub-task: Run script and update `small_assets.h`.
- [x] Task: Implement Temperature Conversion & Formatting Logic 1ece46c
    - [ ] Sub-task: Write Tests (verify C to F conversion and string formatting without spaces).
    - [ ] Sub-task: Implement helper function or inline logic for conversion and formatting.
- [x] Task: Implement Date & SSID Retrieval 1852bf9
    - [ ] Sub-task: Write Tests (verify date formatting from `struct tm` and SSID retrieval mock).
    - [ ] Sub-task: Update `js_analysis` or setup to fetch/store date and SSID.

## Phase 2: UI Implementation
- [x] Task: Update Temperature Row 8b8dc02
    - [x] Sub-task: Implement drawing logic for corrected Celsius string.
    - [x] Sub-task: Implement drawing logic for Fahrenheit string (smaller font, below Celsius).
- [x] Task: Update Status Row (WiFi & SSID) 8b8dc02
    - [x] Sub-task: Implement drawing logic for new smaller WiFi icon.
    - [x] Sub-task: Implement drawing logic for SSID (smaller font, lower position).
- [x] Task: Update Status Row (Date/Time) 8b8dc02
    - [x] Sub-task: Implement drawing logic for combined Date & Time string.

## Phase 3: Integration & cleanup
- [x] Task: Full System Test 75a0341
    - [x] Sub-task: Verify compilation.
    - [x] Sub-task: Verify visual layout via code review/logic check.
- [x] Task: Conductor - User Manual Verification 'Integration & cleanup' (Protocol in workflow.md) 75a0341
