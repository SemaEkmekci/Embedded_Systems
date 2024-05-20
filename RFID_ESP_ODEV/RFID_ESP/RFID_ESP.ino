#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "LiquidCrystal_I2C.h"
#include <SPI.h>  // harici modül ile iletişim kurabilmek için veri gönderme veri alma işlemleri vs.
#include <MFRC522.h>  //  RFID-RC522 modülüyle iletişim kurmayı sağlar
#include <Preferences.h>
#include "led_functions.h"


#define SS_PIN  5  
#define RST_PIN 4
#define LED_PIN 2

led_functions custom_led_lib(LED_PIN);



Preferences preferences;


// #define WiFi_SSID "ekmekci"
// #define WiFi_PASSWORD "1234567890"
// wifi connect ----------------------------------------------------
// TURKSAT-KABLONET-A41A-5G
// dce35953
// 192.168.170.84
// const char* ssid = "ekmekci";
// const char* password = "1234567890";

LiquidCrystal_I2C lcd(0x27, 16, 2);

String ssid = "";
String password = "";

// send data json ---------------------------------------------------

// unsigned long lm;
// unsigned long delayTime;
String JsonData = "";
// String url = "http://192.168.0.22:9000/api/postData";
    

// RFID control ---------------------------------------------------

int readsuccess;
char str[32] = "";  //id bilgisini tutmak için dizi
String UID_Result = ""; //id bilgisini tutmak için string
String classID = "";


MFRC522 mfrc522(SS_PIN, RST_PIN); // MFRC522.h kütüphanesinden bir nesne oluşturuyor.

// read RFID
int readRFID() {  
  if(!mfrc522.PICC_IsNewCardPresent()) { //Yeni bir kart mı?
    return 0;
  }
  if(!mfrc522.PICC_ReadCardSerial()) { //id okundu mu?
    return 0;
  }
  
  byteArray_to_string(mfrc522.uid.uidByte, mfrc522.uid.size, str);
  UID_Result = str;
  
  mfrc522.PICC_HaltA(); //kartın çalışmasını durdur
  mfrc522.PCD_StopCrypto1(); //kriptololamayı durdur.
  
  return 1;
}

void byteArray_to_string(byte array[], unsigned int len, char buffer[]) {  //byte olarak okunan kart id'sini string bir değere döndürüyor.
  for (unsigned int i = 0; i < len; i++) {
    byte nib1 = (array[i] >> 4) & 0x0F; // İlk yarıbayt
    byte nib2 = (array[i] >> 0) & 0x0F;  // İkinci yarıbayt
    buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA; // İlk yarıbaytı ASCII'ye dönüştür
    buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;  // İkinci yarıbaytı ASCII'ye dönüştür
  }
  buffer[len*2] = '\0'; // Stringi sonlandır
}
//________________________________________________________________________________


// wifi connect ----------------------------------------------------
void connectToWiFi(){

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the Wifi network");
}

void sendDataToServer(const char* url, const char* contentType) {
  StaticJsonDocument<50> doc;
  StaticJsonDocument<300> responseDoc;


  doc["userID"] = UID_Result;
  doc["classID"] = classID;
  serializeJson(doc, JsonData);
  Serial.print("Sending JSON data: ");
  Serial.println(JsonData);

  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", contentType);
  int httpResponseCode = http.POST(JsonData);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    DeserializationError error = deserializeJson(responseDoc, response);

    Serial.println(response);
    // if (response == "success") {  
    if (responseDoc["message"] == "success") {
      custom_led_lib.power_time_led(2000);
      // digitalWrite(LED_PIN, HIGH);
      // delay(2000);
      // digitalWrite(LED_PIN, LOW);
      Serial.println("Turn on LED");
      if(responseDoc["lessonState"] == "on"){
        if(responseDoc["studentState"] == "off"){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(responseDoc["msg"].as<String>().c_str());
          delay(3000);
        }else{
          lcd.clear(); 
          lcd.setCursor(0, 0);
          lcd.print(responseDoc["ogrenci_no"].as<String>().c_str());
          lcd.setCursor(0, 1);
          lcd.print(responseDoc["ad"].as<String>().c_str());
          lcd.print(" ");
          lcd.print(responseDoc["soyad"].as<String>().c_str());
          delay(3000);
        }
    
      }
      else if(responseDoc["lessonState"] == "off"){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(responseDoc["msg"].as<String>().c_str());
        delay(3000);
      }



    } else {
      Serial.println("Response from server is not 'success'");
    }
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}



void getDataToServer(const char* url) {
  String urlWithUid = String(url) + "?UID=" + UID_Result;

  HTTPClient http;
  http.begin(urlWithUid);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error on sending GET: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

//________________________________________________________________________________VOID SETUP()
void setup(){
  
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Hello world!");
  lcd.setCursor(2, 1);
  lcd.print("SEMA");
  Serial.begin(115200); // Seri haberleşme başlatılıyor
  Serial.println();
  delay(1000);
  preferences.begin("oys", false);
  classID = preferences.getString("classID", "undefined");
  ssid = preferences.getString("ssid", "undefined");
  password = preferences.getString("password", "undefined");
  Serial.println(ssid);
  Serial.println(password);
  connectToWiFi();
// RFID control ---------------------------------------------------
  SPI.begin();       // SPI başlatılıyor 
  mfrc522.PCD_Init(); // MFRC522 modülü başlatılıyor
  delay(1000);
  Serial.println();
  // pinMode(LED_PIN, OUTPUT);
}

void loop(){

  if (WiFi.status() == WL_CONNECTED) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Connected to");
      lcd.setCursor(2, 1);
      lcd.print(" Network");
      delay(2000);
      readsuccess = readRFID();
      if(readsuccess){
      Serial.println();
      Serial.print("UID : ");
      Serial.println(UID_Result);
      delay(500);
      getDataToServer("http://192.168.0.22:9000/RFID/info");
      sendDataToServer("http://192.168.0.22:9000/RFID/ID", "application/json");
      }
      else{
        Serial.println("KART OKUTUNUZ");
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("KART OKUTUNUZ");
      }
  }else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("İnternet yok");
    Serial.println("İnternet bağlantısı yok.");
    connectToWiFi();
  }
  delay(1000);
  JsonData = "";
}





