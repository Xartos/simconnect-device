#include "SimDeviceButton.h"

SimDeviceButton::SimDeviceButton(uint8_t id, uint8_t pin) : SimDevice(id) {
  _pin = pin;
  pinMode(pin, INPUT);

  buttonState = digitalRead(_pin);
  lastDebounceTime = 0;
  lastButtonState = buttonState;
}

void SimDeviceButton::UpdateValue() {
  bool currentButtonState = digitalRead(_pin);
  unsigned long currentTime = millis();

  if (currentButtonState != lastButtonState) {
    lastDebounceTime = currentTime;
  }

  if (currentTime - lastDebounceTime > BUTTON_DEBOUNCE_TIME) {

  
    if (currentButtonState != buttonState) {
      buttonState = currentButtonState;
      SetValue(currentButtonState);
    }
  }
  
  lastButtonState = currentButtonState;
}
