int LED_Pin = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_Pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(LED_Pin, HIGH);
  while(Serial.available() > 0)
  {
    char data = Serial.read();
    if ( data == '1'){
      digitalWrite(LED_Pin, HIGH);
    }
    else if(data == '0'){
      digitalWrite(LED_Pin, LOW);
    }
  }

  delay(100);
}
