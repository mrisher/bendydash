import requests
import json

API_KEY = "8694ad45d8092e69dab4743c96065901"
CITY = "Paris"
COUNTRY_CODE = "2968815"

def test_current_weather():
    url = f"http://api.openweathermap.org/data/2.5/weather?q={CITY},{COUNTRY_CODE}&APPID={API_KEY}&units=metric"
    print(f"Testing Current Weather API: {url}")
    response = requests.get(url)
    data = response.json()
    print(f"Status Code: {response.status_code}")
    if response.status_code == 200:
        has_pop = "pop" in data
        print(f"Has 'pop' field: {has_pop}")
        if not has_pop:
            print("Current Weather API does NOT contain 'pop' field.")
    else:
        print(f"Error: {data}")

def test_forecast_weather():
    url = f"http://api.openweathermap.org/data/2.5/forecast?q={CITY},{COUNTRY_CODE}&APPID={API_KEY}&units=metric"
    print(f"\nTesting Forecast Weather API: {url}")
    response = requests.get(url)
    data = response.json()
    print(f"Status Code: {response.status_code}")
    if response.status_code == 200:
        if "list" in data and len(data["list"]) > 0:
            first_forecast = data["list"][0]
            has_pop = "pop" in first_forecast
            print(f"Has 'pop' field in first forecast entry: {has_pop}")
            if has_pop:
                print(f"First forecast 'pop' value: {first_forecast['pop']}")
        else:
            print("No forecast list found.")
    else:
        print(f"Error: {data}")

if __name__ == "__main__":
    test_current_weather()
    test_forecast_weather()
