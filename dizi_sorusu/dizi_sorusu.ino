int LED_Pin = 2;

const int n = 4;
int D = 0;
int D1 = 0;
int D2 = 0;
int D3 = 0;
int D4 = 0;
int C = 0;
int C1 = 0;
int C2 = 0;
int C3 = 0;
int C4 = 0;
int Cms = 1;
int Dms = 1;
int value = -1;

int array[n][n] = {{0,4,1,3},{2,0,3,5},{1,3,0,2},{2,6,5,0}};

void setup() {
  Serial.begin(9600);
  delay(2000);
  pinMode(LED_Pin, OUTPUT);
  Serial.println("Değer Giriniz: 1 veya 0");
  while (Serial.available() == 0) {}
  value = Serial.parseInt();
  if(value == 1){

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if (i != 0 && j != 0) {
        D1 += array[i][j];
      }
      if (i != 1 && j != 1) {
        D2 += array[i][j];
      }
      if (i != 2 && j != 2) {
        D3 += array[i][j];
      }
      if (i != 3 && j != 3) {
        D4 += array[i][j];
      }
      if(array[0][j] == 0){
        C1 = C1 + array[i][j];
      }
      if(array[1][j] == 0){
        C2 = C2 + array[i][j];
      }
      if(array[2][j] == 0){
        C3 = C3 + array[i][j];
      }
      if(array[3][j] == 0){
        C4 = C4 + array[i][j];
      }
    }
  
  }
  D = D1 + D2 + D3 + D4;
  C = C1 + C2 + C3 + C4;
  Serial.println("C: " + String(C));
  Serial.println("D: " + String(D));
}

  Cms = C * 1000;
  Dms = D * 1000;

}

void loop() {
  digitalWrite(LED_Pin, HIGH);
  delay(Cms);
  digitalWrite(LED_Pin, LOW);
  delay(Dms);
}
