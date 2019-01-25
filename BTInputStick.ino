#include "SoftSerial_INT0.h"
#include "DigiKeyboard.h"
#include "aes.h"

#define BLE_TIMEOUT 10000

SoftSerial mySerial(2, 3); // RX, TX
AES aes;
bool isRecv = false;
uint8_t buf[64];
uint8_t key[] = {0x32, 0xDA, 0xF8, 0xD3, 0x87, 0x43, 0x83, 0xC0, 0x91, 0xF6, 0xB7, 0x23, 0x7D, 0xC5, 0xE9, 0x83};
uint8_t iv[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
struct AES_ctx ctx;

bool checksum(uint8_t *data, uint8_t dataSize, uint16_t sum) {
  uint16_t check = 0;
  for (uint8_t i = dataSize - 2; i >= 0; i--)
    check += data[i];
  check = ((check >> 8) & 0xFF) + (check & 0xFF);
  if (check == sum)
    return true;
  return false;
}

void setup() {
  mySerial.begin(9600);
  DigiKeyboard.delay(BLE_TIMEOUT);
  AES_init_ctx_iv(&ctx, key, iv);
  while (1){
    if (mySerial.available() > 0){
      int dataSize = mySerial.read();
      if (dataSize == 0x12) {//IV Fixed length
        int sum = dataSize;
        for(int i = 0; i < dataSize - 1; i++)
          buf[i] = mySerial.read();
        if (checksum(buf, dataSize - 2, buf[dataSize - 1])
          break;
      } else
          mySerial.flush();
    }
  }
}

void loop() {
  if (mySerial.available()) {
    int dataSize = mySerial.read();
    if (dataSize > sizeof(buf))
      dataSize = sizeof(buf);
    for(int i = 0; i < dataSize; i++) {
      buf[i] = mySerial.read();
    }
    
  }
    
  AES_CBC_decrypt_buffer(&ctx, in, 64);
  DigiKeyboard.println();
  DigiKeyboard.update();
}
