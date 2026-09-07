/*
 * Arduino UNO - LED Chaser 5 Buah dengan Buzzer
 * Lagu: Super Mario Bros Original Theme
 * Efek LED mengikuti ritme musik
 */

// ===== PIN DEFINITIONS =====
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;
const int LED5 = 6;
const int BUZZER = 9;  // PWM pin

// ===== FREKUENSI NADA =====
#define REST      0
#define NOTE_C4   262
#define NOTE_CS4  277
#define NOTE_D4   294
#define NOTE_DS4  311
#define NOTE_E4   330
#define NOTE_F4   349
#define NOTE_FS4  370
#define NOTE_G4   392
#define NOTE_GS4  415
#define NOTE_A4   440
#define NOTE_AS4  466
#define NOTE_B4   494
#define NOTE_C5   523
#define NOTE_CS5  554
#define NOTE_D5   587
#define NOTE_DS5  622
#define NOTE_E5   659
#define NOTE_F5   698
#define NOTE_FS5  740
#define NOTE_G5   784
#define NOTE_GS5  831
#define NOTE_A5   880
#define NOTE_AS5  932
#define NOTE_B5   988
#define NOTE_C6   1047

// Array LED pins
int ledPins[] = {LED1, LED2, LED3, LED4, LED5};
int ledCount = 5;

// ===== SUPER MARIO BROS ORIGINAL THEME =====
// Melodi asli Super Mario Bros
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_G5,
  NOTE_G4, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_A4, NOTE_B4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5,
  NOTE_F5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4,
  NOTE_C5, NOTE_A4, NOTE_E4, NOTE_C4, NOTE_A4, NOTE_B4,
  NOTE_AS4, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_E5, NOTE_D5,
  NOTE_E5
};

// Durasi nada (dalam milliseconds) - quarter note = 200ms
int durations[] = {
  200, 200, 200, 200, 200, 400,
  400, 200, 200, 200, 200, 200,
  400, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 600,
  200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200,
  400, 200, 200, 200, 200, 200,
  600
};

int melodySize = sizeof(melody) / sizeof(melody[0]);

void setup() {
  // Inisialisasi LED pins
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  
  // Inisialisasi Buzzer
  pinMode(BUZZER, OUTPUT);
  
  // Test LED - nyalakan semua sebentar
  testLED();
}

void loop() {
  // Mainkan lagu dengan efek LED yang memukau
  playMarioTheme();
  
  // Jeda sebelum mengulang
  delay(2000);
  
  // Efek LED chasing sebelum mengulangi
  ledChasingEffect();
  delay(1000);
}

// ===== FUNCTION: PLAY MARIO THEME =====
void playMarioTheme() {
  for (int i = 0; i < melodySize; i++) {
    int frequency = melody[i];
    int duration = durations[i];
    
    // Efek LED yang bergerak sesuai ritme
    if (frequency > 0) {
      // LED chasing effect
      ledChasingMovement(i);
      
      // Mainkan nada
      tone(BUZZER, frequency, duration);
    } else {
      // Rest - matikan semua LED
      allLEDOff();
    }
    
    delay(duration + 50);
  }
  
  allLEDOff();
}

// ===== FUNCTION: LED CHASING MOVEMENT =====
void ledChasingMovement(int noteIndex) {
  int pattern = noteIndex % ledCount;
  
  // Matikan semua LED
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  
  // Nyalakan LED berdasarkan pola
  digitalWrite(ledPins[pattern], HIGH);
}

// ===== FUNCTION: LED CHASING EFFECT =====
void ledChasingEffect() {
  // Bergerak maju
  for (int i = 0; i < ledCount; i++) {
    allLEDOff();
    digitalWrite(ledPins[i], HIGH);
    delay(100);
  }
  
  // Bergerak mundur
  for (int i = ledCount - 1; i >= 0; i--) {
    allLEDOff();
    digitalWrite(ledPins[i], HIGH);
    delay(100);
  }
  
  // Pulse effect
  for (int j = 0; j < 3; j++) {
    allLEDOn();
    delay(150);
    allLEDOff();
    delay(150);
  }
}

// ===== FUNCTION: TEST LED =====
void testLED() {
  // Nyalakan semua LED secara berurutan
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
  }
  
  delay(300);
  allLEDOff();
  delay(300);
  
  // Pulse test
  allLEDOn();
  delay(500);
  allLEDOff();
  delay(500);
}

// ===== FUNCTION: ALL LED ON =====
void allLEDOn() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

// ===== FUNCTION: ALL LED OFF =====
void allLEDOff() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}