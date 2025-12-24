# Product Guidelines

## Visual Identity

-   **Style:** Minimalist and Clean.
-   **Priority:** High contrast and readability are paramount, especially for E-Paper's black-and-white (or grayscale) limitations.
-   **Layout:** Use whitespace effectively to separate the compact weather section from the afterschool schedule.

## User Experience (UX)

-   **Data Freshness:** If a data fetch fails, the dashboard should continue to display the last known state.
-   **Status Indicators:** Provide subtle visual cues (e.g., small icons) to indicate WiFi connection status or stale data (including "last updated" timestamp).
-   **Update Frequency:** Balance data freshness with power consumption (e.g., updating every 15-30 minutes).

## Technical Constraints

-   **E-Paper Specifics:** Minimize full-screen refreshes to avoid ghosting and flashing. Use partial updates where the hardware supports it.
-   **Storage:** Use simple, accessible online storage for the schedule (e.g., a JSON file on GitHub Gist, Firebase, or similar). If we can read from Google Calendar that would be great.
