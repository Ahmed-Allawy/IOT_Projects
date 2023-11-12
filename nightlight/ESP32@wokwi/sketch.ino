#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "config.h"

/******** Light sensor settings *******/
const int lightPin = 34;

/******** LED settings *******/
const int led = 5;

////************************************************************///

void connectWiFi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID,PASSWORD, 6);
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

WiFiClient wioClient;
PubSubClient client(wioClient);

void clientCallback(char *topic, uint8_t *payload, unsigned int length)
{
  char buff[length + 1];
  for (int i = 0; i < length; i++)
  {
    buff[i] = (char)payload[i];
  }
  buff[length] = '\0';

  Serial.print("Message received:");
  Serial.println(buff);

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, buff);
  JsonObject obj = doc.as<JsonObject>();

  bool led_on = obj["led_on"];

  if (led_on)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
}

void reconnectMQTTClient()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    if (client.connect(CLIENT_NAME.c_str()))
    {
      Serial.println("connected");
      client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    }
    else
    {
      Serial.print("Retying in 5 seconds - failed, rc=");
      Serial.println(client.state());

      delay(5000);
    }
  }
}

void createMQTTClient()
{
  client.setServer(BROKER.c_str(), 1883);
  client.setCallback(clientCallback);
  reconnectMQTTClient();
}

void setup()
{
  Serial.begin(9600);

  while (!Serial)
    ; // Wait for Serial to be ready

  delay(1000);

  pinMode(lightPin, INPUT);
  pinMode(led, OUTPUT);

  connectWiFi();
  createMQTTClient();
}


void loop()
{
  reconnectMQTTClient();
  client.loop();

  int light = analogRead(lightPin);

  DynamicJsonDocument doc(1024);
  doc["light"] = light;

  string telemetry;
  serializeJson(doc, telemetry);

  Serial.print("Sending telemetry ");
  Serial.println(telemetry.c_str());

  client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());

  delay(2000);
}