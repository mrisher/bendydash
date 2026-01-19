#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "EPD.h"  // Include the EPD library for controlling the electronic ink screen (E-Paper Display)
#include "EPD_GUI.h"  // Include the EPD_GUI library for graphical user interface (GUI) operations
#include "pic.h"
#include "small_assets.h"
#include "secrets.h"

namespace Oliver {
#include "oliver_avatar.h"
}
namespace Naomi {
#include "naomi_avatar.h"
}
namespace Daddy {
#include "daddy_avatar.h"
}
namespace Mommy {
#include "mommy_avatar.h"
}

#include <time.h>

// Define a black and white image array as the buffer for the e-paper display
uint8_t ImageBW[15000];  // Define the size based on the resolution of the e-paper display

// Structure for family schedule
struct FamilyMember {
    const char* name;
    const unsigned char* avatar;
    const char* home_time;
    uint16_t width;
    uint16_t height;
};

// Mock Data for Schedule
// Dimensions taken from header file comments
FamilyMember family_schedule[] = {
    {"Oliver", Oliver::IMAGE, "4:30 PM Bus", 64, 87},
    {"Naomi", Naomi::IMAGE, "7:30 PM Bus", 64, 87},
    {"Daddy", Daddy::IMAGE, "6:00 PM", 64, 87},
    {"Mommy", Mommy::IMAGE, "8:00 PM", 64, 87}
};

// WiFi network SSID and password are in secrets.h (gitignored)
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// OpenWeatherMap API key
String openWeatherMapApiKey = OPEN_WEATHER_MAP_API_KEY;

// City and country code to query
String city = "Paris";
String countryCode = "2968815";

// NTP Server settings
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

// Timer variables
unsigned long lastTime = 0;
// Set the timer to 10 seconds (10000 milliseconds) for testing
// unsigned long timerDelay = 10000;
// In production, set the timer to 10 minutes (600000 milliseconds), adjust according to API call limits
unsigned long timerDelay = 600000;

String jsonBuffer;  // To store the JSON data retrieved from the API
int httpResponseCode;  // HTTP response code
JSONVar myObject;  // JSON data object

// Weather-related information
String weather;
String temperature; // Celsius formatted
String temp_f;      // Fahrenheit formatted
String humidity;
String sea_level;
String wind_speed;
String rain_pop;
String city_js;
String time_str;
String date_str; // New date string
String wifi_ssid; // New SSID string
int weather_flag = 0;
unsigned long last_success_millis = 0;
bool last_fetch_failed = true;

// Clear all content on the display
void clear_all()
{
  EPD_Clear(); // Clear the display content
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE); // Create a new image buffer, fill with white
  EPD_Full(WHITE); // Fill the entire screen with white
  EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW); // Update the display content
}

// Display weather forecast information
void UI_weather_forecast()
{
  // Create character arrays to store information
  char buffer[40];

  EPD_GPIOInit();  // Initialize the screen GPIO
  EPD_Clear();  // Clear the screen
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE);  // Create a new canvas, set the canvas to white
  EPD_Full(WHITE);  // Clear the canvas, fill with white
  EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW);  // Display a blank canvas

  EPD_Init_Fast(Fast_Seconds_1_5s);  // Initialize the screen, set update speed to 1.5 seconds

  // Check for stale data or fetch failure
  bool is_stale = (last_success_millis == 0) || (millis() - last_success_millis > 3600000);
  bool show_error = last_fetch_failed || is_stale;

  // --- NEW COMPACT LAYOUT (Left Side) ---
  
  // Row 1: Current weather (Icon + Text)
  // use Mist icon (0) for error
  EPD_ShowPicture(10, 10, 64, 64, Small_Weather_Icons[show_error ? 0 : weather_flag], WHITE);
  EPD_ShowString(85, 30, show_error ? "Error" : weather.c_str(), 16, BLACK);

  // Row 2: Temperature (Large Font)
  memset(buffer, 0, sizeof(buffer));
  EPD_ShowString(10, 90, show_error ? "---" : temperature.c_str(), 48, BLACK);
  
  // Fahrenheit below it (Smaller Font)
  EPD_ShowString(15, 138, show_error ? "" : temp_f.c_str(), 24, BLACK);

  // Row 3: Rain forecast % today
  EPD_ShowString(10, 195, "Rain:", 24, BLACK);
  EPD_ShowString(85, 195, show_error ? "---" : rain_pop.c_str(), 24, BLACK);

  // Row 4: Status Info (WiFi + SSID + Last Updated)
  // WiFi status icon (Smaller 12x12)
  if (WiFi.status() == WL_CONNECTED) {
    EPD_ShowPicture(10, 248, 12, 12, gImage_wifi_small, WHITE);
  }
  
  // Network SSID (Smaller font, lower position)
  EPD_ShowString(30, 248, wifi_ssid.c_str(), 12, BLACK);
  
  // Last Updated (Time + Date)
  memset(buffer, 0, sizeof(buffer));
  if (last_fetch_failed) {
    snprintf(buffer, sizeof(buffer), "error at %s", time_str.c_str());
  } else {
    snprintf(buffer, sizeof(buffer), "Updated: %s %s", date_str.c_str(), time_str.c_str());
  }
  EPD_ShowString(10, 270, buffer, 12, BLACK);

  // --- RIGHT SIDE: Family Schedule ---
  int num_members = sizeof(family_schedule) / sizeof(family_schedule[0]);
  for (int i = 0; i < num_members; i++) {
      int col = i % 2;
      int row = i / 2;
      draw_schedule_cell(col, row, i);
  }

  // Update the display
  EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW); 
}

// Function to draw a single schedule cell
void draw_schedule_cell(int col, int row, int index) {
  int x_start = 190 + (col * 100);
  int y_start = (row * 150);
  
  uint16_t w = family_schedule[index].width;
  uint16_t h = family_schedule[index].height;

  // Center avatar in the 95px width
  // Offset = (100 - width) / 2
  int avatar_x = x_start + (100 - w) / 2;
  int avatar_y = y_start + 10; // Padding from top
  
  EPD_ShowPicture(avatar_x, avatar_y, w, h, family_schedule[index].avatar, WHITE);
  
  // Name below avatar (adjusted for max height of 93)
  EPD_ShowString(x_start + 5, y_start + 105, family_schedule[index].name, 16, BLACK);
  
  // Time below name
  EPD_ShowString(x_start + 5, y_start + 125, family_schedule[index].home_time, 16, BLACK);
}

void setup() {
  Serial.begin(115200); // Initialize serial communication

  // Connect to the WiFi network
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); // Wait 0.5 seconds
    Serial.print("."); // Print a dot in the serial monitor
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP()); // Print the IP address of the WiFi connection

  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Set the power pin of the screen to output mode and set it to high level to turn on the power
  pinMode(7, OUTPUT);  // Set GPIO 7 to output mode
  digitalWrite(7, HIGH);  // Set GPIO 7 to high level

  // Initialize the e-ink display
  EPD_GPIOInit();  // Initialize the GPIO pins of the e-ink display
}

void loop() {
  js_analysis();  // Parse JSON data (this function is not provided in the code)
  UI_weather_forecast();  // Display weather forecast information
  delay(timerDelay); // Wait for the specified delay
}

// Function js_analysis is used to parse weather data and update weather information
void js_analysis()
{
  // Always update time first if possible
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    if (time_str == "") time_str = "--:--";
    if (date_str == "") date_str = "--/--";
  } else {
    char time_buffer[10];
    strftime(time_buffer, sizeof(time_buffer), "%H:%M", &timeinfo);
    time_str = String(time_buffer);
    
    char date_buffer[10];
    strftime(date_buffer, sizeof(date_buffer), "%m-%d", &timeinfo);
    date_str = String(date_buffer);
  }

  // Check if WiFi is connected successfully
  if (WiFi.status() == WL_CONNECTED) {
    wifi_ssid = WiFi.SSID();
    // Build the OpenWeatherMap API request URL - Using forecast to get probability of precipitation (pop)
    String serverPath = "http://api.openweathermap.org/data/2.5/forecast?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey + "&units=metric&cnt=1";
    Serial.println(serverPath);

    // Try to fetch weather data
    jsonBuffer = httpGETRequest(serverPath.c_str());
    Serial.println(jsonBuffer); // Print the retrieved JSON data
    
    if (httpResponseCode == 200) {
      myObject = JSON.parse(jsonBuffer); // Parse the JSON data

      // Check if the JSON data was parsed successfully
      if (JSON.typeof(myObject) != "undefined" && myObject.hasOwnProperty("list")) {
        // Success path
        last_fetch_failed = false;
        last_success_millis = millis();

        // Extract weather information from the first forecast entry (next 3 hours)
        JSONVar currentForecast = myObject["list"][0];
        
        weather = (const char*)currentForecast["weather"][0]["main"]; // Get the main weather description
        
        // Process Temperature
        double temp_val = (double)currentForecast["main"]["temp"];
        char temp_buff[20];
        
        // Format Celsius: "XX.XXC"
        snprintf(temp_buff, sizeof(temp_buff), "%.2fC", temp_val);
        temperature = String(temp_buff);
        
        // Calculate and Format Fahrenheit: "XX.XF"
        double temp_f_val = (temp_val * 9.0 / 5.0) + 32.0;
        snprintf(temp_buff, sizeof(temp_buff), "(%.1fF)", temp_f_val);
        temp_f = String(temp_buff);
        
        // Get humidity
        int hum_val = (int)currentForecast["main"]["humidity"];
        humidity = String(hum_val) + "%";
        
        // Get Probability of Precipitation (pop) - usually 0 to 1
        if (currentForecast.hasOwnProperty("pop")) {
            double pop_val = (double)currentForecast["pop"];
            rain_pop = String((int)(pop_val * 100)) + "%";
        } else {
            rain_pop = "0%";
        }

        sea_level = JSON.stringify(currentForecast["main"]["sea_level"]); // Get the sea level pressure
        wind_speed = JSON.stringify(currentForecast["wind"]["speed"]); // Get the wind speed
        city_js = (const char*)myObject["city"]["name"];  // city name is in a different place in forecast API

        // Set the weather flag based on the weather description
        weather_flag = 0; // Default to Mist/Unknown
        if (weather.indexOf("Thunderstorm") != -1) {
          weather_flag = 2; // Thunderstorm
        } else if (weather.indexOf("Drizzle") != -1) {
          weather_flag = 5; // Drizzle (treated as Rain)
        } else if (weather.indexOf("Rain") != -1) {
          weather_flag = 5; // Rain
        } else if (weather.indexOf("Snow") != -1) {
          weather_flag = 4; // Snow
        } else if (weather.indexOf("Clear") != -1) {
          weather_flag = 3; // Clear
        } else if (weather.indexOf("Clouds") != -1) {
          weather_flag = 1; // Clouds
        } else if (weather.indexOf("Mist") != -1 || weather.indexOf("Smoke") != -1 || weather.indexOf("Haze") != -1 || 
                   weather.indexOf("Dust") != -1 || weather.indexOf("Fog") != -1 || weather.indexOf("Sand") != -1 || 
                   weather.indexOf("Ash") != -1 || weather.indexOf("Squall") != -1 || weather.indexOf("Tornado") != -1) {
          weather_flag = 0; // Atmosphere conditions (Mist, etc.)
        }
        
        Serial.print("Weather update successful. Flag: "); Serial.println(weather_flag);
        return; // Success, exit function
      } else {
        Serial.println("Parsing failed or missing 'list' key");
      }
    } else {
      Serial.print("HTTP request failed, code: "); Serial.println(httpResponseCode);
    }
  } else {
    Serial.println("WiFi Disconnected");
  }

  // If we reached here, the weather update failed
  last_fetch_failed = true;
}

// Function httpGETRequest sends an HTTP GET request and returns the response content
String httpGETRequest(const char* serverName) {
  WiFiClient client; // Create a WiFi client object
  HTTPClient http; // Create an HTTP client object

  // Initialize the HTTP request with the specified URL
  http.begin(client, serverName);

  // Send the HTTP GET request
  httpResponseCode = http.GET(); // Get the HTTP response code

  String payload = "{}"; // Default response content is an empty JSON object

  // Check if the HTTP response code is greater than 0 (indicating success)
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode); // Print the HTTP response code
    payload = http.getString(); // Get the response content
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode); // Print the error code
  }
  // Free the HTTP client resources
  http.end();

  return payload; // Return the response content
}
