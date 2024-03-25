#include <WiFi.h>
#include <PubSubClient.h>

/******** wifi settings *******/
const char* ssid = "";
const char* password = "";

/******** mqtt broker settings *******/
const char* mqtt_server = "";
const char* mqtt_username = "";
const char* mqtt_password = "";
const int mqtt_port = 1883;

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

WiFiClient espClient;
PubSubClient client(espClient);

/***** connect to wifi **************/
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password, 6);
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

/************** connect to mqtt borker ************/
void reconnect() {
  // loop until connect
  while (!client.connected()) {
    Serial.print("Attempting mqtt connection...");
    String clientId = "myRoom";
    clientId += String(random(0xffff), HEX);
    //Atempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");

      client.subscribe("led_state"); // led topic
    }
    else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

/***** call back method for receiving mqtt messages ********/
void callback(char* topic, byte* payload, unsigned int length)
{
  char payloadStr[length + 1];              // Create a char array that's 1 byte longer than the incoming payload to copy it to and make room for the null terminator so it can be treated as string.
  memcpy(payloadStr, payload, length);
  payloadStr[length + 1] = '\0';
  Serial.println(payloadStr);
}

/**************** publishing mqtt messages ********/
void publishMessage(const char* topic, String payload, boolean retained) {
  if (client.publish(topic, payload.c_str(), true))
    Serial.println("message published [" + String(topic) + "]" + payload);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  

}
