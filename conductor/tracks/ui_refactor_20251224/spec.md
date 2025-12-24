# Track Specification: Refactor UI Layout with Updated Assets

## Goal
To refactor the dashboard UI on the 4.2" E-Paper display to a more compact, four-row layout on the left side, freeing up space for future features. This involves updating display logic and regenerating necessary graphical assets (bitmaps or fonts).

## Core Requirements
1.  **Layout Restructuring:**
    -   Organize the left side of the screen into four distinct rows.
    -   **Row 1:** Current Weather (Icon + Text Description).
    -   **Row 2:** Temperature (Current value).
    -   **Row 3:** Rain Forecast (Percentage probability for today).
    -   **Row 4:** Status Info (Last Updated timestamp + City Name + WiFi connection status icon).
2.  **Asset Management:**
    -   Replace or resize existing large bitmaps with smaller versions suitable for the new rows.
    -   Alternatively, implement/utilize built-in fonts for text elements to reduce reliance on static bitmaps.
3.  **Data Integration:**
    -   Ensure "Rain Forecast %" is correctly parsed from the OpenWeatherMap API response.
    -   Ensure WiFi status is dynamically updated.
4.  **Space Reservation:**
    -   Clear the right side of the screen (or the remaining area) to be empty, serving as a placeholder for the future "Afterschool Schedule" feature.

## Technical Considerations
-   **Display Driver:** Continue using the existing `EPD` and `EPD_GUI` libraries.
-   **Fonts/Images:** Existing headers `pic.h` and `EPD_font.h` may need updates or replacements. `convert_to_bmp.py` might be used for generating new assets.
-   **API:** OpenWeatherMap API call might need to be checked to ensure it returns precipitation probability (`pop`) if not already handled.

## Acceptance Criteria
-   The left side of the screen displays the four rows as defined.
-   All information (Weather, Temp, Rain %, Status) is legible and accurate.
-   The right side of the screen is clear of old UI elements.
-   The code compiles without errors and runs on the ESP32.
