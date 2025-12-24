# Track Plan: UI Refinements - Temperature, Date, and Network Info

## Phase 1: Asset & Data Preparation
- [x] Task: Generate Smaller WiFi Icon 3fcbb9c
    - [ ] Sub-task: Update `generate_small_assets.py` to create a 12x12 WiFi icon.
    - [ ] Sub-task: Run script and update `small_assets.h`.
- [ ] Task: Implement Temperature Conversion & Formatting Logic
    - [ ] Sub-task: Write Tests (verify C to F conversion and string formatting without spaces).
    - [ ] Sub-task: Implement helper function or inline logic for conversion and formatting.
- [ ] Task: Implement Date & SSID Retrieval
    - [ ] Sub-task: Write Tests (verify date formatting from `struct tm` and SSID retrieval mock).
    - [ ] Sub-task: Update `js_analysis` or setup to fetch/store date and SSID.

## Phase 2: UI Implementation
- [ ] Task: Update Temperature Row
    - [ ] Sub-task: Implement drawing logic for corrected Celsius string.
    - [ ] Sub-task: Implement drawing logic for Fahrenheit string (smaller font, below Celsius).
- [ ] Task: Update Status Row (WiFi & SSID)
    - [ ] Sub-task: Implement drawing logic for new smaller WiFi icon.
    - [ ] Sub-task: Implement drawing logic for SSID (smaller font, lower position).
- [ ] Task: Update Status Row (Date/Time)
    - [ ] Sub-task: Implement drawing logic for combined Date & Time string.

## Phase 3: Integration & cleanup
- [ ] Task: Full System Test
    - [ ] Sub-task: Verify compilation.
    - [ ] Sub-task: Verify visual layout via code review/logic check.
- [ ] Task: Conductor - User Manual Verification 'Integration & cleanup' (Protocol in workflow.md)
