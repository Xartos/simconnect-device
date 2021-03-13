#include "SimDeviceRotary.h"

SimDeviceRotary::SimDeviceRotary(uint8_t id, uint8_t clkPin, uint8_t dtPin) : SimDevice(id) {
  _clkPin = clkPin;
  _dtPin = dtPin;
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);

  ResetSeen();
}

void SimDeviceRotary::ResetSeen() {
  SetValue(0);
  _hasChanged = false;
}

void SimDeviceRotary::UpdateValue() {
  //bool clkValue = digitalRead(_clkPin);
  //bool dtValue = digitalRead(_dtPin);
  int8_t newReading = read_rotary();
  if(newReading) {
    SetValue(GetValue() + newReading);
  }
}

int8_t SimDeviceRotary::read_rotary() {
  static int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

  lastCode <<= 2;
  if (digitalRead(_dtPin)) lastCode |= 0x02;
  if (digitalRead(_clkPin)) lastCode |= 0x01;
  lastCode &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table[lastCode] ) {
      store <<= 4;
      store |= lastCode;
      //if (store==0xd42b) return 1;
      //if (store==0xe817) return -1;
      if ((store&0xff)==0x2b) return -1;
      if ((store&0xff)==0x17) return 1;
   }
   return 0;
}
