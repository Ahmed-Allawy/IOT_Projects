#include <DHT_U.h>
#include <DHT.h>
#include <Wire.h>
#include <LCD_I2C.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <WebSocketsServer.h> 
#include<ESP8266WebServer.h>
#include <Arduino_JSON.h>
//===============================================================//
// SSID and password of Wifi connection:
const char* ssid = "Orange-Eng";
const char* password = "SetokaibaNew@2023";
//===============================================================//
//webSite//
#include "page.h"
String webpage = MAIN_page;
//===============================================================//
// Initialization of webserver and websocket
ESP8266WebServer server(80);                        
WebSocketsServer webSocket = WebSocketsServer(81);
//========================================================================================//
LCD_I2C lcd(0x27, 16, 2); 
//========================================================================================//
//temperature and humidity sensor//
#define DHTTYPE DHT11      //set type of sensor
uint8_t DHTPIN = D1;        //set pin of sensor(pin D1)
DHT dht(DHTPIN,DHTTYPE);   //initialize sensore
int temperature; // this variable to store value of temperature
int humidity;    // this variable to store value of humidity
//========================================================================================//
//soil moisture sensor//
int SoilPin = A0; //set pin of sensor
float moisturePersentage; // this variable store persentage value of soil moistur
//========================================================================================//
//interval between last and next read data from sensores//
unsigned long lastTime = 0;
unsigned long interval = 3000;
//========================================================================================//
//functions//
bool isIntervalEnd();
void readSensores();
float calculatePersentage(float);
void printDataOnSerial();
void printDataAtLCD();
void sendJSON(int, int, float);
void receiveJSON();
void updateData();
//========================================================================================//
int TEMDataArray[11];
int HUMDataArray[11];
int SOILDataArray[11];
//========================================================================================//
void setup() {
  Serial.begin(9600);                               
 
  WiFi.begin(ssid, password);                         
  Serial.println("Establishing connection to WiFi with SSID: " + String(ssid));  
  while (WiFi.status() != WL_CONNECTED) {            
    delay(1000);
    Serial.print(".\n");
  }
  Serial.print("Connected to network with IP address: ");
  Serial.println(WiFi.localIP());                     
  
  server.on("/", []() {                              
    server.send(200, "text/html", webpage);         
  });
  server.begin();  
  webSocket.begin();            
  webSocket.onEvent(webSocketEvent);  
  lcd.begin();
  lcd.backlight();
  dht.begin();
}

void loop() {
  server.handleClient();                              
  webSocket.loop();    
  if(isIntervalEnd()){
     Serial.println(WiFi.localIP());
    readSensores();
    printDataOnSerial();
//    /printDataAtLCD();
    updateData();
    sendJSON(temperature, humidity, moisturePersentage);
//    Serial.println(WiFi.localIP()); 
    }   
}
//*******************************//
bool isIntervalEnd(){
  if((millis()-lastTime)>interval){
    lastTime = millis();
    return true;
  }
  else 
    return false;
  }
//*******************************//
void readSensores(){
  //soil//
  moisturePersentage = calculatePersentage(analogRead(SoilPin));
  //temp&hum//
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  }
//*******************************//
float calculatePersentage(float val){
  return (100-((val/1023.00)*100));
  }
//*******************************//
void printDataOnSerial(){
  Serial.print("temperature = ");
  Serial.print(temperature);
  Serial.print(" , humidity = ");
  Serial.print(humidity);
  Serial.print(" , soil moisture Persentage = ");
  Serial.print(moisturePersentage);
  Serial.println("%");
  }
  //*******************************//
void printDataAtLCD(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("temperature = ");
  lcd.print(temperature);
  lcd.print(" , humidity = ");
  lcd.print(humidity);
  lcd.setCursor(1, 0);
  lcd.print(" , soil moisture Persentage = ");
  lcd.print(moisturePersentage);
  lcd.println("%");
  }
  //*******************************//
  void webSocketEvent(byte clienNumber, WStype_t type, uint8_t * message, size_t length) {     
  switch (type) {                                     
    case WStype_DISCONNECTED:                         
      Serial.println("Client " + String(clienNumber) + " disconnected");
      break;
    case WStype_CONNECTED:                           
      Serial.println("Client " + String(clienNumber) + " connected");
      break;
    case WStype_TEXT:                                
      Serial.println("");
      break;
  }
}
//*******************************//
void sendJSON(int temperature, int humidity, float soil){
  JSONVar myObject;
  JSONVar TEM_Object;
  JSONVar HUM_Object;
  JSONVar SOIL_Object;
  for(int i=0; i<10; i++){
    TEM_Object[i] = TEMDataArray[i];
    HUM_Object[i] = HUMDataArray[i];
    SOIL_Object[i] = SOILDataArray[i];
    }
  myObject["temperature"] = TEM_Object;
  myObject["humidity"] = HUM_Object;
  myObject["soil"] = SOIL_Object;
  Serial.print("myObject = ");
  Serial.println(myObject);
  Serial.println();
  String jsonString = JSON.stringify(myObject);
  Serial.println(jsonString);
  Serial.println();
  webSocket.broadcastTXT(jsonString);   
}
void receiveJSON(){
  // 2147483647
  }
void updateData(){
  for(int i=9; i>0; i--){
    TEMDataArray[i] = TEMDataArray[i-1];
    HUMDataArray[i] = HUMDataArray[i-1];
    SOILDataArray[i] = SOILDataArray[i-1];
    }
    if(temperature >= 2147483647)
      TEMDataArray[0] = TEMDataArray[1];
    else 
      TEMDataArray[0] = temperature;
    if(humidity >= 2147483647)
      HUMDataArray[0] = HUMDataArray[1];
    else 
      HUMDataArray[0] = humidity;
    SOILDataArray[0] = moisturePersentage;
  }
