#include <IRremote.h>
#include <Servo.h>

#define IR_PIN 11
#define SERVO_PIN 9

Servo doorServo;

void setup() {
  IrReceiver.begin(IR_PIN);
  doorServo.attach(SERVO_PIN);
  doorServo.write(0);   // closed
}

void loop() {
  if (IrReceiver.decode()) {

    uint16_t addr = IrReceiver.decodedIRData.address;
    uint8_t cmd   = IrReceiver.decodedIRData.command;
    if (addr == 0) {

      if (cmd == 22) {          // Button "1"
        doorServo.write(90);    // OPEN
      }

      if (cmd == 25) {          // Button "2"
        doorServo.write(0);     // CLOSE
      }
    }

    IrReceiver.resume();
  }
}
