
//Used libraries in this project
#include <Firebase.h>  
#include <FirebaseArduino.h>  
#include <FirebaseCloudMessaging.h>  
#include <FirebaseError.h>  
#include <FirebaseHttpClient.h>  
#include <FirebaseObject.h>  
#include <ESP8266WiFi.h>  
#include <FirebaseArduino.h>  


  
// Firebase API and WiFi cridentials 
#define FIREBASE_HOST "esp8266-34204.firebaseio.com"  
#define FIREBASE_AUTH "mhd0P12dsY3Ne323J0BYV08242Ylmkzx"  
#define WIFI_SSID "Wroo1m"  
#define WIFI_PASSWORD "for231ker220"  
  
void setup() {  

  //Display communication baudrate
  Serial.begin(9600);  
  
  // Settup to connect to wifi.  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  Serial.print("connecting"); 

   //Checks for WiFi reconnection
  while (WiFi.status() != WL_CONNECTED) {  
    Serial.print(".");  
    delay(500);  
  }  

  //Prints connection status
  Serial.println();  
  Serial.print("connected: ");  
  Serial.println(WiFi.localIP());  

  //Connects to firebase for transaction
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  

  //Initialises the GPIO pin as an output
  pinMode(D1,OUTPUT);  

  //Sets the initial state of the GPIO as OFF/LOW
  Firebase.set("PUMP_STATUS",0);  
}  
  

int n = 0;  
  
void loop() {  
  
  // Get the value from firebase RTDB
  n=Firebase.getInt("PUMP_STATUS");  
  
  //Checks the switch status in RTDB and make swithcing decision 
  if (n==1) {  
      Serial.println("Pump is dispensing");  
      digitalWrite(D1,HIGH); 
       
   // handle any error 
      Serial.println(Firebase.error());    
      return;  
       delay(100);  
  }  
 else{  
   Serial.println("Pump is OFF");  
   digitalWrite(D1,LOW);  
 }  
    
  // update value  
    
} 
