
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Set these to run example.
#define SS_PIN 4  //D2
#define RST_PIN 5 //D1
#define FIREBASE_HOST ".........." 
#define FIREBASE_AUTH ".........."
#define WIFI_SSID ".............."
#define WIFI_PASSWORD ".........."


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance/object.
int variable = 0;
int n = 0;

void setup() {

Serial.begin(9600);   // Initiate a serial communication
SPI.begin();      // Initiate  SPI bus
mfrc522.PCD_Init();   // Initiate MFRC522
Serial.println("Show your card:");



  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

   
}





void loop() {

// Look for new cards
if ( ! mfrc522.PICC_IsNewCardPresent()) 
{
return;
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial()) 
{
return;
}
//Show UID on serial monitor
Serial.println();
String content= "";
byte letter;
for (byte s = 0; s < mfrc522.uid.size; s++) 
{
//Serial.print(mfrc522.uid.uidByte[s]); //rfid.uid.uidByte[s]    //

! mfrc522.PICC_HaltA();

// append a new value to /logs
  String name = Firebase.pushInt("logs",mfrc522.uid.uidByte[s]);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  //Serial.print("pushed: /logs/(mfrc522.uid.uidByte[s])");
  Serial.println(name);
}
 
  // set value
  Firebase.setFloat("number", 42.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number2 failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // update value
  Firebase.setFloat("number", 43.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number1 failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);

  // remove value
  Firebase.remove("number");
  delay(1000);

  // set string value
  Firebase.setString("message", "hello world");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);

}
