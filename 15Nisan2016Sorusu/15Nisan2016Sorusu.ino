int ledPinArray[6] = {2,3,4,5,6,7};
int arrayLength = sizeof(ledPinArray) / sizeof(ledPinArray[0]);

void mixLed(){
   for(int i = 0; i<arrayLength; i++){
    int value = random(0,arrayLength)
    digitalWrite(ledPinArray[value], HIGH);
    delay(1000);
  }
}

void turnOffLed(){
  for(int i = 0; i<arrayLength; i++){
    digitalWrite(ledPinArray[i], LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i<arrayLength; i++){
    pinMode(ledPinArray[i],OUTPUT);
    digitalWrite(ledPinArray[i], HIGH);
  }
  for(int i = 0; i<arrayLength; i++){
    digitalWrite(ledPinArray[i], LOW);
  }

  for(int i = 0; i<10; i++){
    mixLed();
    turnOffLed();
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
