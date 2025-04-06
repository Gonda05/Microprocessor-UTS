// Pin Konstanta
const int potPin = A0;      // Potensiometer
const int buttonPin = 2;    // Tombol Start
const int ledPin = 3;       // LED indikator
const int buzzerPin = 9;    // Buzzer

// Variabel status
bool timerRunning = false;
unsigned long startTime = 0;
unsigned long targetDuration = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Tombol aktif LOW
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (!timerRunning && digitalRead(buttonPin) == LOW) {
    delay(50); // debounce sederhana
    if (digitalRead(buttonPin) == LOW) {
      // Baca nilai potensiometer dan konversi ke detik
      int potValue = analogRead(potPin);
      int timeInSeconds = map(potValue, 0, 1023, 5, 60); // 5–60 detik
      targetDuration = timeInSeconds * 1000UL; // konversi ke ms

      Serial.print("Waktu disetel: ");
      Serial.print(timeInSeconds);
      Serial.println(" detik");

      startTime = millis();
      timerRunning = true;

      digitalWrite(ledPin, HIGH);  // LED nyala
    }
  }

  // Cek apakah timer sedang berjalan
  if (timerRunning) {
    unsigned long elapsed = millis() - startTime;
    if (elapsed >= targetDuration) {
      // Waktu habis
      timerRunning = false;
      digitalWrite(ledPin, LOW);  // LED mati
      tone(buzzerPin, 1000);      // Nyalakan buzzer 1kHz
      delay(1000);                // Bunyikan 1 detik
      noTone(buzzerPin);          // Matikan buzzer
    }
  }
}