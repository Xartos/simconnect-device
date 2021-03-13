#include "SimEvent.h"

SimEvent::SimEvent(uint8_t id, String name) {
  _ID = id;
  _name = name;
  _value = "";
}

uint8_t SimEvent::GetID() {
  return _ID;
}

String SimEvent::GetName() {
  return _name;
}


String SimEvent::GetValue() {
  return _value;
}

void SimEvent::SetValue(String value) {
  _value = value;
}
