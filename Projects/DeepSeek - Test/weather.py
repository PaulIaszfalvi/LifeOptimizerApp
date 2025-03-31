import folium
import pandas as pd
import requests

# Your OpenWeatherMap API key
API_KEY = 'dcdef5d31e8f6dd17fe128d0204a4ad8'

# Dataset of major cities with their coordinates
cities_data = {
    'City': ['New York', 'London', 'Tokyo', 'Sydney', 'Paris', 'Berlin', 'Moscow', 'Beijing'],
    'Latitude': [40.7128, 51.5074, 35.6895, -33.8688, 48.8566, 52.5200, 55.7558, 39.9042],
    'Longitude': [-74.0060, -0.1278, 139.6917, 151.2093, 2.3522, 13.4050, 37.6173, 116.4074]
}

# Convert the data into a DataFrame
cities_df = pd.DataFrame(cities_data)

# Create a base map centered on the world
world_map = folium.Map(location=[20, 0], zoom_start=2)

# Function to get weather data for a city
def get_weather_data(lat, lon):
    url = f"http://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={API_KEY}&units=metric"
    response = requests.get(url)
    data = response.json()
    if data.get("cod") != 200:
        return "Weather data unavailable"
    weather = data['weather'][0]['description']
    temp = data['main']['temp']
    return f"Weather: {weather}, Temperature: {temp}°C"

# Add markers for each city with a popup showing weather data
for index, row in cities_df.iterrows():
    city = row['City']
    lat = row['Latitude']
    lon = row['Longitude']
    
    # Get weather data
    weather_info = get_weather_data(lat, lon)
    
    # Create a popup with the city name and weather info
    popup_text = f"<b>{city}</b><br>{weather_info}"
    popup = folium.Popup(popup_text, max_width=250)
    
    # Add a marker to the map
    folium.Marker(
        location=[lat, lon],
        popup=popup,
        tooltip=f"Click for {city} weather"
    ).add_to(world_map)

# Save the map to an HTML file
world_map.save("world_cities_weather_map.html")

# Open the map in the default web browser
import webbrowser
webbrowser.open("world_cities_weather_map.html")



