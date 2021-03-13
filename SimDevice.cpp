#include "SimDevice.h"

SimDevice::SimDevice(uint8_t id) {
  _ID = id;
  _value = 0;
  _hasChanged = false;
}

uint8_t SimDevice::GetID() {
  return _ID;
}

long SimDevice::GetValue() {
  return _value;
}

bool SimDevice::HasChanged() {
  return _hasChanged;
}

void SimDevice::ResetSeen() {
  _hasChanged = false;
}

void SimDevice::SetValue(long value) {
  _value = value;
  _hasChanged = true;
}
