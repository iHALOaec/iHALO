#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "7d3e42e0198246fea198b65b5fc3bc39"; //get thi frm ur app
char ssid[] = "Starcable";// Your WiFi credentials.
char pass[] = "k03@d033";// Set password to "" for open networks.
BlynkTimer timer;

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX
#define ESP8266_BAUD 9600 // Your ESP8266 baud rate:
ESP8266 wifi(&EspSerial);
void sendSensor()
{
 int val = analogRead(A0);
  float mv = ( val/1024.0)*5000;    //mv stands for millivolts. 
  float cel = mv/10;      //10mv for per degree rise in temperature
  float farh = (cel*9)/5 + 32; 
  Blynk.virtualWrite(V5, farh);  //V5 is the virtual pin
}
void setup()
{
  pinMode(A0,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  Serial.begin(9600);
  delay(10);
  EspSerial.begin(ESP8266_BAUD); // Set ESP8266 baud rate
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
