#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Zyxel_D9B1";
const char* password = "UNHTF48UEY";
const char* serverUrl = "http://192.168.1.140:8081/update-location"; // Replace with your server URL

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Scanning Wi-Fi signals...");
}

void loop() {
  // Scan Wi-Fi networks
  int numNetworks = WiFi.scanNetworks();
  String wifiData = "";
  if (numNetworks > 0) {
    for (int i = 0; i < numNetworks; ++i) {
      String ssid = WiFi.SSID(i);
      int rssi = WiFi.RSSI(i);
      wifiData += ssid + ":" + String(rssi) + ",";
    }
    wifiData = wifiData.substring(0, wifiData.length() - 1); // Remove trailing comma
  }

  // Send data to server
  if (wifiData.length() > 0) {
    String postData = "wifi=" + wifiData;
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST(postData);
    
    if (httpResponseCode == HTTP_CODE_OK) {
      Serial.println("Data sent to server successfully");
    } else {
      Serial.print("Error sending data to server. Error code: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  } else {
    Serial.println("No Wi-Fi data to send");
  }

  delay(5000); // Delay between scans
}