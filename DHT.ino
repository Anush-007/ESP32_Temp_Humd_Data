#include "DHT.h"
#include "ThingSpeak.h"
#include "WiFi.h"

#define CHANNEL_ID 1550255
#define API_KEY "PZPF0JSIHU0DIDQZ"

WiFiClient client;
DHT dht(4, DHT11);


const char* ssid = "Pachkate's Wi-Fi";
const char* password = "53839077";


float humd, temp;

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT11"));

  Serial.println("Connecting");

  int count = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
    count += 1;
    if (count > 30) {
      ESP.restart(); 
    }
  }

  Serial.println("Connected");
  ThingSpeak.begin(client);
  dht.begin();

}

void loop() {
  
  humd = dht.readHumidity();
  temp = dht.readTemperature();

  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, humd);

  ThingSpeak.writeFields(CHANNEL_ID, API_KEY);
  
  Serial.print(F("Humidity :"));
  Serial.print(humd);
  Serial.print(F("% Temperature :"));
  Serial.print(temp);
  Serial.println(F(" C"));

  // ThingSpeak updates data entry at interval of 15 seconds.
  delay(15000);

}
