#ifndef SimEvent_h
#define SimEvent_h

#include <inttypes.h>
#include <Arduino.h>

class SimEvent {
public:
  SimEvent(uint8_t id, String name);
  uint8_t GetID();
  String GetName();
  void SetValue(String value);
  String GetValue();

private:
  uint8_t _ID;
  String _name;
  String _value;
};

#endif
