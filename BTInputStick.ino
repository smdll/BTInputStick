#include <SoftSerial.h>
#include <TinyPinChange.h>
#include <DigiKeyboard.h>
#include "Base64.h"
// TODO: 加入AES

SoftSerial mySerial(2, 3); // RX, TX

void setup() {
  mySerial.begin(9600);
  mySerial.print("AT+NAMEBTInputStick\r\n");// Pre-config
}

void loop() {
  if (mySerial.available())
    String buf = mySerial.readString();
  // TODO: 解码解密buf
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println();
  DigiKeyboard.delay(5000);
}
