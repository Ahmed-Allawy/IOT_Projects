#include <WiFi.h>
#include <PubSubClient.h>
#include "ArduinoJson.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>

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
  char payloadStr[length + 1]; // Create a char array that's 1 byte longer than the incoming payload to copy it to and make room for the null terminator so it can be treated as string.
  memcpy(payloadStr, payload, length);
  payloadStr[length + 1] = '\0';
}

/**************** publishing mqtt messages ********/
void publishMessage(const char* topic, String payload, boolean retained) {
  if (client.publish(topic, payload.c_str(), true))
    Serial.println("message published [" + String(topic) + "]" + payload);
}

//========================================================================================//
// This part determines the time between each sensor reading
unsigned long duration = 0; // use for millis 
unsigned long interval = 50000;
//*******************************//
void setupDuration(){
  duration = millis();
}
//*******************************//
bool isIntervalEnd(){
  if((millis()-duration)>interval){
    duration = millis();
    return true;
  }
  else 
    return false;
  }
//========================================================================================//
//=======================PH meter===============================//
float calibration_value = 22.34+4.4;// for calibration 
int phval = 0; 
unsigned long int avgval; //average value
int buffer_arr[10],temp;
float ph_act, volt;

//void get_10_readings();
//void sort_readings();
//void readSensors();
//void calculate_average();
//void displaySensors();
//==================//
void get_10_readings(){
  for(int i=0;i<10;i++) { 
    buffer_arr[i]=analogRead(A0);
    delay(30);
 }
}
//====================================
void sort_readings(){
  for(int i=0;i<9;i++){
    for(int j=i+1;j<10;j++){
      if(buffer_arr[i]>buffer_arr[j]){
        temp = buffer_arr[i]; ///swap value
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
   }
}
//====================================
void calculate_average(){
   avgval=0;
   for(int i=2;i<8;i++)
      avgval+=buffer_arr[i];
   avgval = (float)avgval/6;
}
//====================================
void readSensors(){
  get_10_readings();
  sort_readings();
  calculate_average();
  volt = (float)avgval*5.0/1024; 
  ph_act = -5.70 * volt + calibration_value;
}
//====================================
void displaySensors()
{
  Serial.print("volt = ");
  Serial.print(volt);
  Serial.print(" , ph_act = ");
  Serial.println(ph_act);
  
}
//====================================
void publishPHSensorData(){
  readSensors();
  displaySensors();
  
  DynamicJsonDocument doc(1024);
  doc["ph"] = ph_act;
  char mqtt_message[128];
  serializeJson(doc, mqtt_message);
  publishMessage("alpasha/agriculture/ph",mqtt_message,false);
}

//=======================BME 280===============================//
#define BME_SDA_PIN 21
#define BME_SCL_PIN 22

Adafruit_BME280 bme;

float temperature;
float humidity;
float pressure;
//====================================
void setup_BME280(){
  if (!bme.begin(0x76, &Wire)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
//    while (1);
  }
}
//====================================
void readBme280Data(){
   temperature = bme.readTemperature();
   humidity = bme.readHumidity();
   pressure = bme.readPressure() / 100.0;

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
}
//====================================
void publishBME280Data(){
  readBme280Data();
  
  DynamicJsonDocument doc(1024);
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["pressure"] = pressure;
  char mqtt_message[128];
  serializeJson(doc, mqtt_message);
  publishMessage("alpasha/agriculture/bme280",mqtt_message,false);
}
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  setup_BME280();
  setupDuration();
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if(isIntervalEnd()){
    publishBME280Data();
    publishPHSensorData();
  }
}
