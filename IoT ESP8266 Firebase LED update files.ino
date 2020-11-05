
//Used libraries in this project
#include <Firebase.h>  
#include <FirebaseArduino.h>  
#include <FirebaseCloudMessaging.h>  
#include <FirebaseError.h>  
#include <FirebaseHttpClient.h>  
#include <FirebaseObject.h>  
#include <ESP8266WiFi.h>  
#include <FirebaseArduino.h> 
 
//Cloned libs
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

  
// Firebase API and WiFi cridentials 
#define FIREBASE_HOST "esp8266-65fg4.fireb7aseio.com"  
#define FIREBASE_AUTH "mhd0Pt7nKfdytv66765rtV08uMNt2Ylmkzx"  
#define WIFI_SSID "Wroom"  
#define WIFI_PASSWORD "fod6rker220"  

//Cloned globals
//Any global variable to be initialised here
    String UsersId;     
    String Tokens;      
    String Serialno;     
    String NationalId; 
  
void setup() {  

  //Display communication baudrate
  Serial.begin(9600);  
  
  // Settup to connect to wifi.  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  Serial.print("connecting"); 

   //Checks for WiFi reconnection
  while (WiFi.status() != WL_CONNECTED) {  
    Serial.print("Reconnecting");  
    delay(500);  
  }  

  //Prints connection status
  Serial.println();  
  Serial.print("connected: ");  
  Serial.println(WiFi.localIP());  

  //Connects to firebase for transaction
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  

  //Initialises the GPIO pin as an output
  pinMode(D2,OUTPUT);  

  //Sets the initial state of the GPIO as OFF/LOW
  Firebase.set("Pump Status",0);  

  //Cloned
  //Syncronises with firebase Host and Authentication for access database.
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
//Create database collection in Realtime database.
    Firebase.setString("Users ID/Value","0");
    Firebase.setString("Tokens/Value","0");
    Firebase.setString("Serialno/Value","0");
    Firebase.setString("National ID/Value","0");

}  
  

int n = 0; 
// Accepts any loop operation functions to read/write data
void loop() {

    update1(); 
    update2();
    

}
 
  
void update1() {  
  
  // Get the value from firebase RTDB
  n=Firebase.getInt("Pump Status");  
  
  Serial.println(n);
  
  //Checks the switch status in RTDB and make swithcing decision 
  if (n==1) {  
      Serial.println("Pump is dispensing");  
      digitalWrite(D2,HIGH); 
       
   // handle any error 
      Serial.println(Firebase.error());    
      return;  
       delay(100);  
  }  
 else{  
   Serial.println("Pump is OFF");  
   digitalWrite(D2,LOW);  
 }  
    
  // update value  
    
} 

void update2()
{
  
 //Setting values for variables

 UsersId        = ("Ken Ronoh");
 Tokens         = String(111);
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
