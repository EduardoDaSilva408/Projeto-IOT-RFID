#include <SPI.h>


#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
//WiFiServer server(80);
//char ssid[] = "";
//char senha[] = "";
void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  //WiFi.begin(ssid, senha);
  //while(WiFi.status() != WL_CONNECTED){
    //Serial.println(WiFi.status());
      //Serial.println("conectado");

  //server.begin();
  //RFID SÓ PODE SER INICIADO DEPOIS DO WIFI
    delay(5000);
    SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
 }


void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  String ID = "";
  for ( uint8_t i = 0; i < 4; i++) { 
    //readCard[i] = mfrc522.uid.uidByte[i];
    ID.concat(String(mfrc522.uid.uidByte[i], HEX)); 
  }
  //Esse ID será enviado para o hiveMQTT
  Serial.println(ID);
}
