/*
  Proyek: Advance Traffic Light System with Pedestrian Crossing
  Deskripsi: Simulasi Lampu Lalu Lintas Pintar dengan Tombol Penyeberangan Pejalan Kaki
  Penulis: Faiq Arkan Nabil Santoso
*/

// --- PIN LAMPU LALU LINTAS UTAMA (KENDARAAN) ---
const int LED_MERAH_UTAMA  = 12;
const int LED_KUNING_UTAMA = 11;
const int LED_HIJAU_UTAMA  = 10;

// --- PIN LAMPU PEJALAN KAKI (PEDESTRIAN) ---
const int LED_MERAH_PED  = 9;
const int LED_HIJAU_PED  = 8;

// --- PIN TOMBOL PENYEBERANGAN ---
const int BUTTON_PIN = 2;

void setup() {
  // Konfigurasi pin LED sebagai OUTPUT
  pinMode(LED_MERAH_UTAMA, OUTPUT);
  pinMode(LED_KUNING_UTAMA, OUTPUT);
  pinMode(LED_HIJAU_UTAMA, OUTPUT);
  
  pinMode(LED_MERAH_PED, OUTPUT);
  pinMode(LED_HIJAU_PED, OUTPUT);

  // Konfigurasi pin Push Button menggunakan Internal Pull-Up Resistor
  // (Tombol bernilai LOW saat ditekan)
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Inisialisasi Serial Monitor untuk debugging
  Serial.begin(9600);
  Serial.println("==========================================");
  Serial.println("System Ready: Advance Traffic Light Active");
  Serial.println("==========================================");
}

void loop() {
  // 1. KONDISI NORMAL (Default)
  // Jalan Utama: HIJAU | Pejalan Kaki: MERAH
  setMainTrafficLight(LOW, LOW, HIGH); // (Merah, Kuning, Hijau)
  setPedestrianLight(HIGH, LOW);        // (Merah, Hijau)

  // 2. CEK APAKAH TOMBOL PENYEBERANGAN DITEKAN
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("\n[EVENT] Push Button Ditekan!");
    Serial.println("[INFO] Memproses permintaan penyeberangan...");
    
    // Safety Delay: Menunggu 5 detik sebelum sinyal berubah
    delay(5000);

    // TRANSISI 1: Lampu Utama Berubah ke KUNING (Peringatan Kendaraan)
    Serial.println("[STATUS] Lampu Utama: KUNING (2 detik)");
    setMainTrafficLight(LOW, HIGH, LOW);
    delay(2000); 

    // TRANSISI 2: Lampu Utama MERAH & Pejalan Kaki HIJAU (Silakan Menyeberang)
    Serial.println("[STATUS] Lampu Utama: MERAH | Pejalan Kaki: HIJAU");
    setMainTrafficLight(HIGH, LOW, LOW);
    setPedestrianLight(LOW, HIGH);
    delay(5000); // Waktu aman menyeberang selama 5 detik

    // TRANSISI 3: Peringatan Waktu Menyeberang Akan Habis (Blinking Effect)
    Serial.println("[STATUS] Waktu menyeberang hampir habis (Lampu Kedip)");
    for (int i = 0; i < 3; i++) {
      setPedestrianLight(LOW, LOW); // Mati
      delay(250);
      setPedestrianLight(LOW, HIGH); // Nyala
      delay(250);
    }

    // TRANSISI 4: Mengembalikan Lampu Pejalan Kaki ke MERAH
    setPedestrianLight(HIGH, LOW);
    delay(1000);

    Serial.println("[INFO] Kembali ke mode lalu lintas normal.\n");
  }
}

// --- FUNGSI BANTUAN (HELPER FUNCTIONS) ---

// Fungsi untuk mengatur status 3 LED Jalan Utama
void setMainTrafficLight(bool merah, bool kuning, bool hijau) {
  digitalWrite(LED_MERAH_UTAMA, merah);
  digitalWrite(LED_KUNING_UTAMA, kuning);
  digitalWrite(LED_HIJAU_UTAMA, hijau);
}

// Fungsi untuk mengatur status 2 LED Pejalan Kaki
void setPedestrianLight(bool merah, bool hijau) {
  digitalWrite(LED_MERAH_PED, merah);
  digitalWrite(LED_HIJAU_PED, hijau);
}
