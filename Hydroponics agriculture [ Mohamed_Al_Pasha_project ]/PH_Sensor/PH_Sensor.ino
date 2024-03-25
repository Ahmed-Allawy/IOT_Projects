//=======================PH meter===============================//
float calibration_value = 22.34+4.4;// for calibration 
int phval = 0; 
unsigned long int avgval; //average value
int buffer_arr[10],temp;
float ph_act, volt;

void get_10_readings();
void sort_readings();
void readSensors();
void calculate_average();
void displaySensors();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(30);
}

void loop() {
  // put your main code here, to run repeatedly:
  void readSensors();
  void displaySensors();
  delay(1000);
}
//====================================
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
void displaySensors(void)
{
  Serial.print("volt = ");
  Serial.print(volt);
  Serial.print(" , ph_act = ");
  Serial.println(ph_act);
  
}
