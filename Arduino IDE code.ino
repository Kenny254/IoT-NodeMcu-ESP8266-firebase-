//Libraries used in this project
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
 #include <ESP8266HTTPClient.h>

//Firebase Authentication API credentials
#define FIREBASE_HOST "esp8266-2qw2304.firebaseio.com"
#define FIREBASE_AUTH "Secrets" // in the project settings, security secrets

//Wifi configuration 
#define WIFI_SSID "Wroom"
#define WIFI_PASSWORD "for23kewe23r220"




//Data capture methods from an Analog GPIO
String myString;
int vr = A0; // variable resistor connected
int sdata = 0; // The variable resistor value will be stored in sdata.



//Setup section that run once
void setup()
{
  // Serial connection baudrate
  Serial.begin(9600);

  //Definitio of Analog pin as an input
  pinMode(vr ,INPUT);
  
  // Connection of the wifi
  pinMode(D0,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

    Firebase.setString("Users ID/Value","Odhams Ronoh");
    Firebase.setString("Tokens/Value","12");
    Firebase.setString("Serial/Value","MAG304852NA");
    Firebase.setString("National ID/Value","23432343");
}

void loop()
{

sdata = analogRead(vr);
myString = String(sdata);
Serial.println(myString);
Firebase.setString("Variable/Value",myString);
delay(1000);
}
