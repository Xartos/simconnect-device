#ifndef SimDeviceRotary_h
#define SimDeviceRotary_h

#include <Arduino.h>

#include "SimDevice.h"

class SimDeviceRotary : public SimDevice {
public:
  SimDeviceRotary(uint8_t id, uint8_t clkPin, uint8_t dtPin);
  void ResetSeen();
  void UpdateValue();

private:
  uint8_t _clkPin;
  uint8_t _dtPin;
  uint8_t lastCode;
  uint16_t store;

  int8_t read_rotary();
};

#endif
