
int array[10][10]; 
int value;
int F = 0;
int pinNum = 2;
int result;
int n;



void createArray(int n){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      Serial.print(i);
      Serial.print(j);
      Serial.println(".Değer");
      while (Serial.available() > 0) {
      Serial.read();
      }
      while (!Serial.available()) {}
      value = Serial.parseInt();
      array[i][j] = value;
    }
  }
}

int sumF(int n) {
   for (int k = 0; k < n; k++) {
    result = 0; 
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i != k && j != k) {
          result += array[i][j]; 
        }
      }
    }
      Serial.println(result);
    F += result; 
  }
  return F;
}

void writeArray(int n){
  for(int i = 0; i< n; i++){
 for(int j = 0; j<n; j++){
    Serial.print(array[i][j]);
    Serial.print("\t"); 

  }
  Serial.println();
}
}

  

void setup() {

  Serial.begin(9600);
  delay(2000);
  pinMode(pinNum, OUTPUT);

  Serial.println("Tablo boyutunu girin ");
  while (!Serial.available()) {}
  n = Serial.parseInt();

  createArray(n);
  writeArray(n);
  F = sumF(n);
  Serial.println("F: " + String(F));

}

void loop() {
  digitalWrite(pinNum, HIGH);
  delay(F); 
  digitalWrite(pinNum, LOW); 
  delay(F); 
}







