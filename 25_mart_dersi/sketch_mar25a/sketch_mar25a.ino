int k = -1;
float e = -1;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("K değerini giriniz");
  
  while (Serial.available() == 0) {}
  k = Serial.parseInt();

  delay(1000);
  while (Serial.available() > 0) {
    Serial.read();
  }

  Serial.println("E değerini giriniz");
  while (Serial.available() == 0) {}
  e = Serial.parseFloat();

  int SD[k], KD[k], MF[k], EB[k], hata_orani = 0;

  for (int i = 0; i < k; i++) {
    SD[i] = random(10, 30);
  }

  for (int i = 0; i < k; i++) {
    Serial.println(SD[i]);
  }

  Serial.println("KD değerlerini giriniz");
  
  for (int i = 0; i < k; i++) {
    Serial.print(i);
    Serial.println(". KD değeri");
     while (Serial.available() > 0) {
    Serial.read();
  }
    while (Serial.available() == 0) {}
    KD[i] = Serial.parseInt();

  }

  for (int i = 0; i < k; i++) {
    MF[i] = abs(SD[i] - KD[i]);
    if (MF[i] > e) {
      EB[i] = -1;
    } else {
      EB[i] = 0;
    }
    hata_orani = hata_orani + MF[i];
  }
  Serial.println("SD     KD    MF    EB");
  for (int i = 0; i < k; i++) {
    Serial.print(SD[i]);
    Serial.print("\t");
    Serial.print(KD[i]);
    Serial.print("\t");
    Serial.print(MF[i]);
    Serial.print("\t");
    Serial.println(EB[i]);
  }
  Serial.print("Toplam Hata Orani");
  Serial.println(hata_orani);
}

void loop() {
}
