# Track Specification: UI Refinements - Temperature, Date, and Network Info

## Goal
To refine the dashboard UI based on user feedback, specifically targeting temperature formatting, date/time display, and network status information.

## Core Requirements
1.  **Temperature Display:**
    -   Fix the spacing issue in the Celsius readout (remove extra space after the decimal point).
    -   Add the Fahrenheit equivalent temperature in parentheses, displayed in a smaller font below the Celsius value.
2.  **Status Row - Timestamp:**
    -   Include the current date (e.g., "MM-DD") alongside the existing timestamp in the "Updated" field.
3.  **Status Row - Network Info:**
    -   Resize the WiFi icon to be 50% smaller than its current size (currently 24x24, target ~12x12).
    -   Replace the City Name with the connected Network SSID.
    -   Display the SSID in a smaller font and position it lower than the previous city text.

## Technical Considerations
-   **Temperature Conversion:** Implement C to F conversion logic: `(C * 9/5) + 32`.
-   **Date Retrieval:** Ensure `struct tm` populates the date fields correctly from the NTP sync.
-   **Asset Update:** Regenerate the WiFi icon at the new smaller size (12x12).
-   **Layout Adjustments:** Fine-tune coordinates for the new elements (Fahrenheit temp, SSID, Date) to ensure they fit within the row limits.

## Acceptance Criteria
-   Celsius temperature displays as "XX.XXC" without weird spaces.
-   Fahrenheit temperature is visible below Celsius in a smaller font.
-   "Updated" field shows both time and date.
-   WiFi icon is smaller.
-   Network SSID is displayed instead of City Name.
-   Code compiles and runs without errors.
