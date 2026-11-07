const int LED_MERAH_UTAMA  = 12;
const int LED_KUNING_UTAMA = 11;
const int LED_HIJAU_UTAMA  = 10;

const int LED_MERAH_PED  = 9;
const int LED_HIJAU_PED  = 8;

const int BUTTON_PIN = 2;

void setup() {
  pinMode(LED_MERAH_UTAMA, OUTPUT);
  pinMode(LED_KUNING_UTAMA, OUTPUT);
  pinMode(LED_HIJAU_UTAMA, OUTPUT);
  
  pinMode(LED_MERAH_PED, OUTPUT);
  pinMode(LED_HIJAU_PED, OUTPUT);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("==========================================");
  Serial.println("System Ready: Advance Traffic Light Active");
  Serial.println("==========================================");
}

void loop() {
  setMainTrafficLight(LOW, LOW, HIGH); // (Merah, Kuning, Hijau)
  setPedestrianLight(HIGH, LOW);        // (Merah, Hijau)

  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("\n[EVENT] Push Button Ditekan!");
    Serial.println("[INFO] Memproses permintaan penyeberangan...");
    
    delay(5000);

    Serial.println("[STATUS] Lampu Utama: KUNING (2 detik)");
    setMainTrafficLight(LOW, HIGH, LOW);
    delay(2000); 

    Serial.println("[STATUS] Lampu Utama: MERAH | Pejalan Kaki: HIJAU");
    setMainTrafficLight(HIGH, LOW, LOW);
    setPedestrianLight(LOW, HIGH);
    delay(5000); 

    Serial.println("[STATUS] Waktu menyeberang hampir habis (Lampu Kedip)");
    for (int i = 0; i < 3; i++) {
      setPedestrianLight(LOW, LOW);
      delay(250);
      setPedestrianLight(LOW, HIGH); 
      delay(250);
    }

    setPedestrianLight(HIGH, LOW);
    delay(1000);

    Serial.println("[INFO] Kembali ke mode lalu lintas normal.\n");
  }
}

void setMainTrafficLight(bool merah, bool kuning, bool hijau) {
  digitalWrite(LED_MERAH_UTAMA, merah);
  digitalWrite(LED_KUNING_UTAMA, kuning);
  digitalWrite(LED_HIJAU_UTAMA, hijau);
}

void setPedestrianLight(bool merah, bool hijau) {
  digitalWrite(LED_MERAH_PED, merah);
  digitalWrite(LED_HIJAU_PED, hijau);
}
