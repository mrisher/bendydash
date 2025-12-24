# Technology Stack

## Core Hardware
- **Microcontroller:** ESP32-S3
- **Display:** 4.2" E-Paper Display (SPI interface)

## Software & Frameworks
- **Framework:** Arduino (C++)
- **Core Libraries:**
    - `WiFi`: Network connectivity
    - `HTTPClient`: API requests
    - `Arduino_JSON`: JSON parsing for weather and schedule data
    - `Time`: NTP synchronization and local time management
- **Display Driver:** Custom/Project-local E-Paper Driver (`EPD.h`, `EPD_GUI.h`)

## Integration
- **Weather API:** OpenWeatherMap
- **Schedule Source:** Simple online storage (e.g., JSON file on GitHub Gist) or Google Calendar (TBD)

## Tools (Optional/Development)
- **Python:** Image processing and font conversion utilities (`convert_to_bmp.py`, etc.)
- **Library Dependencies:** `Pillow`, `cairosvg`, `fonttools` (for Python scripts)
