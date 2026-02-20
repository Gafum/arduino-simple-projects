// HERE IS THE CODE FOR THE Stepper Motor thet go one step after pussing the button

// #include <Stepper.h>

// int STEPS = 2048;

// // PIN4 = IN4, PIN2 = IN2, PIN3 = IN3, PIN1 = IN1
// Stepper Motor(STEPS, 4, 2, 3, 1);

// int ButtonPin = 12;
// int isButtonOn = 0;

// // It is importent to connect button with 5V, PIN12 and throught the resistor to GRN!

// void setup() {
//   Motor.setSpeed(5);  
//   pinMode(ButtonPin, INPUT);
//   pinMode(13, OUTPUT);
// }

// void loop() {
//   while( digitalRead(ButtonPin) == HIGH){
//     // delay(1);
//     digitalWrite(13, HIGH);
//     Motor.step(1);
//   }

//   digitalWrite(13, LOW);
// }

// // ========================================================================================
// // HERE IS THE CODE ONLY FOR THE RFID-TAG (MFRC522-READER)

// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN 53
// #define RST_PIN 9

// MFRC522 mfrc522(SS_PIN, RST_PIN);

// void setup() {
//   Serial.begin(9600);
//   while (!Serial);          // Needed for Mega
//   SPI.begin();              // Start SPI
//   mfrc522.PCD_Init();       // Init RC522
//   Serial.println("Scan RFID card...");
// }

// void loop() {

//   // Check for card
//   if (!mfrc522.PICC_IsNewCardPresent()) {
//     return;
//   }

//   // Read card
//   if (!mfrc522.PICC_ReadCardSerial()) {
//     return;
//   }

//   Serial.print("UID: ");

//   for (byte i = 0; i < mfrc522.uid.size; i++) {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     Serial.print(" ");
//   }

//   Serial.println();

//   mfrc522.PICC_HaltA();
// }



#include <SPI.h>
#include <MFRC522.h>
#include <Stepper.h>

// ---------------- STEPPER ----------------
#define STEPS 2048
Stepper Motor(STEPS, 4, 2, 3, 1);

// ---------------- RFID ----------------
#define SS_PIN 53
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// ---------------- BUTTONS ----------------
#define START_BUTTON 10
#define RESET_BUTTON 11

// ---------------- LED ----------------
#define ACCESS_LED 13

// ---------------- ACCESS ----------------
bool accessGranted = false;

// Allowed card UID
byte allowedUID[4] = {0x43, 0x05, 0xE5, 0x35};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // SPI for MEGA
  pinMode(53, OUTPUT);
  SPI.begin();
  mfrc522.PCD_Init();

  // Stepper
  Motor.setSpeed(10);   // slightly faster = stronger movement

  // Buttons (your wiring: HIGH = pressed)
  pinMode(START_BUTTON, INPUT);
  pinMode(RESET_BUTTON, INPUT);

  // LED
  pinMode(ACCESS_LED, OUTPUT);
  digitalWrite(ACCESS_LED, LOW);

  Serial.println("System Ready - Scan Card");
}

void loop() {

  // ---------------- RESET BUTTON ----------------
  if (digitalRead(RESET_BUTTON) == HIGH) {
    accessGranted = false;
    digitalWrite(ACCESS_LED, LOW);
    Serial.println("Access Removed - Scan Card Again");
    delay(500);
  }

  // ---------------- RFID PART ----------------
  if (!accessGranted) {

    if (!mfrc522.PICC_IsNewCardPresent()) return;
    if (!mfrc522.PICC_ReadCardSerial()) return;

    if (checkUID()) {
      accessGranted = true;
      digitalWrite(ACCESS_LED, HIGH);   // LED ON
      Serial.println("Access Granted");
    } else {
      Serial.println("Access Denied");
    }

    mfrc522.PICC_HaltA();
  }

  // ---------------- MOTOR PART ----------------
  if (accessGranted) {

    if (digitalRead(START_BUTTON) == HIGH) {

      Serial.println("Motor Moving");

      Motor.step(50);   // REAL visible movement
    }
  }
}

// ------------ UID CHECK ------------
bool checkUID() {

  if (mfrc522.uid.size != 4) return false;

  for (byte i = 0; i < 4; i++) {
    if (mfrc522.uid.uidByte[i] != allowedUID[i]) {
      return false;
    }
  }
  return true;
}