#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "AKO IKAW"; // Change to your WiFi network's SSID
const char* password = "2444666667"; // Change to your WiFi network's password
const char* host = "192.168.45.230"; // Change to your server's IP or domain
const char* phpScript = "/bcc/send-data.php";

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Connect to your WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (Serial.available() > 0) {
      String dataReceived = Serial.readStringUntil('\n');
      int level = dataReceived.toInt();
      Serial.print("Received alcohol level: ");
      Serial.println(level);
      if(level > 0){
      String url = "http://" + String(host) + phpScript + "?data=" + String(level);
      WiFiClient client;
      HTTPClient http;

      if (http.begin(client, url)) {
        int httpCode = http.GET();
        
        if (httpCode > 0) {
          String payload = http.getString();
          Serial.println("Server Response: " + payload);
        } else {
          Serial.println("Error on HTTP request: " + http.errorToString(httpCode));
        }

        http.end();
      } else {
        Serial.println("Failed to connect to the server");
      }
      }else{
        Serial.println("No value");
      }
    }
  }
}
