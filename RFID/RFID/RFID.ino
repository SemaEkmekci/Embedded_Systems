#include <MFRC522.h>
#include <SPI.h>

int rst_PIN = 9;
int sda_PIN = 10;

MFRC522 rfid(sda_PIN, rst_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  // put your main code here, to run repeatedly:

  if(rfid.PICC_IsNewCardPresent())
  {
    if(rfid.PICC_ReadCardSerial())
    {
        Serial.print(rfid.uid.uidByte[0]);
        Serial.print(rfid.uid.uidByte[1]);
        Serial.print(rfid.uid.uidByte[2]);
        Serial.print(rfid.uid.uidByte[3]);
    
    }
    Serial.println();
    rfid.PICC_HaltA();
  }

}
