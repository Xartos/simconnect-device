#ifndef SimDevice_h
#define SimDevice_h

#include <inttypes.h>

class SimDevice {
public:
  SimDevice(uint8_t id);
  uint8_t GetID();
  long GetValue();
  void SetValue(long value);
  bool HasChanged();
  virtual void ResetSeen();
  virtual void UpdateValue() = 0;

protected:
  uint8_t _ID;
  long _value;
  bool _hasChanged;
};

#endif
