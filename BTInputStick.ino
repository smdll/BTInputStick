#include <SoftSerial.h>
#include <TinyPinChange.h>
#include <DigiKeyboard.h>

SoftSerial mySerial(2, 3); // RX, TX

void setup() {
  mySerial.begin(9600);
  mySerial.print("AT+NAMEBTInputStick\r\n");// Pre-config
}

void loop() {
  while (mySerial.available())
    mySerial.read();
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println("Hello Digispark!");
  DigiKeyboard.delay(5000);
}
