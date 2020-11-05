//Libraries used in this project
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
 #include <ESP8266HTTPClient.h>

//Firebase Authentication API credentials
#define FIREBASE_HOST "esp8266-34212.firebaseio.com"
#define FIREBASE_AUTH "mhd0Pt7nKwe24dsY3NejhZxGxJ0BYV08uMNt2Ylmkzx"

//Wifi configuration 
#define WIFI_SSID "Wroom"
#define WIFI_PASSWORD "fowe231rker220"

//Any global variable to be initialised here
    String UsersId;     
    String Tokens;      
    String Serialno;     
    String NationalId; 


//Setup section that run once
void setup()
{
  // Serial connection baudrate
  Serial.begin(9600);


  // Connection of the wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  
  //Tries reconnection for set miliseconds
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print("Reconnecting");
    delay(500);
      }

  //Prints WiFi status
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

 //Syncronises with firebase Host and Authentication for access database.
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
//Create database collection in Realtime database.
    Firebase.setString("Users ID/Value","0");
    Firebase.setString("Tokens/Value","0");
    Firebase.setString("Serialno/Value","0");
    Firebase.setString("National ID/Value","0");
}



// Accepts any loop operation to read/write data
void loop()
{
  
 //Setting values for variables

 UsersId        = ("Ken Ronoh");
 Tokens         = String(12);
 Serialno       = ("MAG342345");
 NationalId     = String(28367945);


//Prints current Data
Serial.println(UsersId);
Serial.println(Tokens);
Serial.println(Serialno);
Serial.println(NationalId);

//Updates on firebase Realtime database
Firebase.setString("Users ID/Value",UsersId);
Firebase.setString("Tokens/Value",Tokens);
Firebase.setString("Serialno/Value",Serialno);
Firebase.setString("National ID/Value",NationalId);

//Delays for a second before next loop
delay(1000);
}
void IsOnline()
{
  
  }
