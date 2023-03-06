#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT_U.h>
#include <DHT.h>
#include <Wire.h>

#define FIREBASE_HOST "" // url to your firebase real time


#define FIREBASE_AUTH ""

//Define Firebase Data object
FirebaseData firebase;
const char* ssid = "";
const char* password = "";
//========================================================================================//
// some variable declaration
unsigned long duration = 0; // use for millis 
unsigned long interval = 50000;
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
//functions//
bool isIntervalEnd();
void readSensores();
float calculatePersentage(float);
void printDataOnSerial();
void printDataAtLCD();
void sendToFireBase(int, int, float);
//========================================================================================//
void setup() {
  Serial.begin(9600); // initialze Serial for priniting 
  delay(10);
  Serial.println();
  Serial.print("Connecting with ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("WiFi conected. IP: ");
  Serial.println(WiFi.localIP());
  duration = millis();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
    if(isIntervalEnd()){
      readSensores();
      printDataOnSerial();
      sendToFireBase( temperature,  humidity,  moisturePersentage); 
    }  
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
   
   Firebase.getInt(firebase,"ESP/H");
   int data2 = firebase.intData();
  Serial.print("Received int: ");
  Serial.println(data2);
  }
  //*******************************//
//void printDataAtLCD(){
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("temperature = ");
//  lcd.print(temperature);
//  lcd.print(" , humidity = ");
//  lcd.print(humidity);
//  lcd.setCursor(1, 0);
//  lcd.print(" , soil moisture Persentage = ");
//  lcd.print(moisturePersentage);
//  lcd.println("%");
//  }
  //*******************************//
  void sendToFireBase(int temperature, int humidity, float moisturePersentage){
    Firebase.setInt(firebase,"ESP/T", temperature);
    Firebase.setInt(firebase,"ESP/H", humidity);
    Firebase.setFloat(firebase,"ESP/S", moisturePersentage);
    Firebase.getInt(firebase,"ESP/M");
    int minutes = firebase.intData();
    if(minutes >=1000)
      minutes = 0;
    else minutes++;
    Serial.println(minutes);
    Firebase.setInt(firebase, "/ESP/M", minutes);
    }
