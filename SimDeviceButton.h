#ifndef SimDeviceButton_h
#define SimDeviceButton_h

#include <Arduino.h>

#include "SimDevice.h"

#define BUTTON_DEBOUNCE_TIME 50

class SimDeviceButton : public SimDevice {
public:
  SimDeviceButton(uint8_t id, uint8_t pin);
  void UpdateValue();

private:
  uint8_t _pin;
  bool buttonState;
  bool lastButtonState;
  unsigned long lastDebounceTime;
};

#endif
