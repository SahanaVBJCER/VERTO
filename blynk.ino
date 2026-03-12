/************* BLYNK SETTINGS *************/
#define BLYNK_TEMPLATE_ID "TMPL3Ef8xI9Qe"
#define BLYNK_TEMPLATE_NAME "tunnelrover"
#define BLYNK_AUTH_TOKEN "zl212WyefBDt8SY1oOfblByUQfDJ_s85"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

/************* WiFi *************/
char ssid[] = "Pooja";
char pass[] = "12052005";

/************* DHT11 *************/
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/************* MQ2 *************/
int mq2Pin = 1;   // GPIO 1

/************* Virtual Pins *************/
#define VPIN_TEMP        V1
#define VPIN_HUM         V2
#define VPIN_GAS         V3
#define VPIN_TEMP_STATUS V4
#define VPIN_HUM_STATUS  V5
#define VPIN_GAS_STATUS  V6

BlynkTimer timer;

/************* Sensor Function *************/
void sendSensorData() {

  // -------- Temperature & Humidity --------
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {

    String tempStatus;
    String humStatus;

    // Temperature Threshold
    if (temperature < 40)
      tempStatus = "Normal";
    else if (temperature >= 40 && temperature <= 50)
      tempStatus = "Monitor";
    else
      tempStatus = "Alert";

    // Humidity Threshold
    if (humidity >= 40 && humidity <= 70)
      humStatus = "Normal";
    else if (humidity > 70 && humidity <= 85)
      humStatus = "Monitor";
    else
      humStatus = "Alert";

    Blynk.virtualWrite(VPIN_TEMP, temperature);
    Blynk.virtualWrite(VPIN_HUM, humidity);
    Blynk.virtualWrite(VPIN_TEMP_STATUS, tempStatus);
    Blynk.virtualWrite(VPIN_HUM_STATUS, humStatus);

    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print(" °C | ");
    Serial.println(tempStatus);

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" % | ");
    Serial.println(humStatus);
  }

  // -------- Gas Sensor --------
  int gasValue = analogRead(mq2Pin);
  String gasStatus;

  if (gasValue < 1200)
    gasStatus = "Normal";
  else if (gasValue >= 1200 && gasValue < 1800)
    gasStatus = "Leak Detected";
  else if (gasValue >= 1800 && gasValue < 2400)
    gasStatus = "Action Needed";
  else
    gasStatus = "Extremely Dangerous";

  Blynk.virtualWrite(VPIN_GAS, gasValue);
  Blynk.virtualWrite(VPIN_GAS_STATUS, gasStatus);

  Serial.print("Gas: ");
  Serial.print(gasValue);
  Serial.print(" | ");
  Serial.println(gasStatus);

  Serial.println("----------------------------------");
}

/************* Setup *************/
void setup() {
  Serial.begin(115200);
  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensorData);
}

/************* Loop *************/
void loop() {
  Blynk.run();
  timer.run();
}