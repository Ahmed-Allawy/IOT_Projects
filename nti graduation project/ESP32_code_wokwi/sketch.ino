#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include "HX711.h"
#include "ArduinoJson.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

/******** Load cell settings *******/
HX711 scale;
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 4;

/******** DHT11 sensor settings *******/
#define DHTpin 2   ///GPIO2
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTpin, DHTTYPE);

/******** LED settings *******/
const int led = 5;

/******** HEART RATE sensor settings *******/
const double heartRateData[] = {1.0, 0.8333333134651184, 0.45277777314186096, 0.0, 0.16111111640930176, 0.2916666567325592, 0.3833332538604736, 0.3861111104488373, 0.4333333373069763, 0.4166666567325592, 0.4583333432674408, 0.44999998807907104, 0.4722222089767456, 0.48055556416511536, 0.5222222208976746, 0.5388888716697693, 0.5722222328186035, 0.6138888597488403, 0.6416666507720947, 0.6416666507720947, 0.675000011920929, 0.6555555462837219, 0.6777777671813965, 0.6277777552604675, 0.6083333492279053, 0.5611110925674438, 0.5361111164093018, 0.49444442987442017, 0.4694444537162781, 0.4166666567325592, 0.43611112236976624, 0.4194444417953491, 0.42500001192092896, 0.39722222089767456, 0.4277777671813965, 0.42222222685813904, 0.4333333373069763, 0.4055555462837219, 0.4416666626930237, 0.4472222328186035, 0.46388888359069824, 0.4694444537162781, 0.4694444537162781, 0.4305555522441864, 0.4277777671813965, 0.4194444417953491, 0.4194444417953491, 0.39444443583488464, 0.41111111640930176, 0.39722222089767456, 0.4027777910232544, 0.39722222089767456, 0.4138889014720917, 0.39722222089767456, 0.42500001192092896, 0.39722222089767456, 0.40833333134651184, 0.4027777910232544, 0.42500001192092896, 0.4000000059604645, 0.42222222685813904, 0.574999988079071, 0.7972221970558167, 0.9666666388511655, 0.8166666626930237, 0.4000000059604645, 0.04444444552063941, 0.16388888657093048, 0.3083333373069763, 0.375, 0.42222222685813904, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
const int slidePin = 27;

/////////// Topics  /////////////////////////////////////
const char* weightTopic = "NTI_10/weight";
const char* alarmTopic = "NTI_10/alarm";
const char* temperatureTopic = "NTI_10/temperature";
const char* humidityTopic = "NTI_10/humidity";
const char* heartRateTopic = "NTI_10/heartRate";
////************************************************************///
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin("Wokwi-GUEST", "", 6);
  // WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage = "";
  for (int i = 0; i < length; i++)
    incommingMessage += (char)payload[i];
  Serial.println("message arrived [" + String(topic) + "]" + incommingMessage);
  // write code here (you have topic and message)
  if (strcmp(topic, alarmTopic) == 0) {
    if (incommingMessage.equals("true")) digitalWrite(led, HIGH);
    else digitalWrite(led, LOW);
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe(alarmTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(slidePin, INPUT_PULLUP);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  dht.begin();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // // Wait a few seconds between measurements.
  // delay(2000);
  dhtSensore();
  // calibrateLoadCell();
  getWight();
  heartRateSensor();

}

void dhtSensore() {
  delay(1000);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.println();
    snprintf(msg, sizeof(msg), "%.2f", t);
    client.publish(temperatureTopic, msg);
    snprintf(msg, sizeof(msg), "%.2f", h);
    client.publish(humidityTopic, msg);

  }
}

void calibrateLoadCell() {
  if (scale.is_ready()) {
    scale.set_scale();
    Serial.println("Tare... remove any weights from the scale.");
    delay(5000);
    scale.tare();
    Serial.println("Tare done...");
    Serial.print("Place a known weight on the scale...");
    delay(5000);
    long reading = scale.get_units(10);
    Serial.print("Result: ");
    Serial.println(reading / 420.0);
  }
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}

void getWight() {
  if (scale.is_ready()) {
    Serial.print("Place a known weight on the scale...");
    delay(1000);
    long reading = scale.get_units(10);
    Serial.print("Result: ");
    Serial.println(reading / 420.0); // 420.0 is equal 0.42*1000 (1000 from kg to g) and (0.42 = reading/know wight from calibration)
    snprintf(msg, sizeof(msg), "%.2f", (reading / 420.0));
    client.publish(weightTopic, msg);
  }
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}

void heartRateSensor() {
  if (digitalRead(slidePin)) {
    Serial.println(F("heart rate sensor sending data...."));
    for (int i = 0; i < sizeof(heartRateData) / sizeof(double); i++) {
      snprintf(msg, sizeof(msg), "%.16lf", heartRateData[i]);
      client.publish(heartRateTopic, msg);
      Serial.print(i);
      Serial.print(F(" : value = "));
      Serial.println(heartRateData[i]);
      delay(1000); // Delay between publishing data points (adjust as needed)
    }
  }
}