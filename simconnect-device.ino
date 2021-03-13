#include "SimDeviceButton.h"
#include "SimDeviceRotary.h"
#include "SimDevice.h"
#include "SimEvent.h"

#include <LiquidCrystal_I2C.h>

#define WARNING_PIN 13

#define SIM_DEVICES_NR 2
SimDevice** devices = new SimDevice*[SIM_DEVICES_NR];

#define SIM_EVENTS_NR 2
SimEvent** events = new SimEvent*[SIM_EVENTS_NR];

LiquidCrystal_I2C lcd(0x27, 20, 4);

void announceMyDevices() {
  for (int i = 0; i < SIM_DEVICES_NR; i++) {
    Serial.println(devices[i]->GetID());
  }
  Serial.println();
}

void announceMySubscriptions() {
  for (int i = 0; i < SIM_EVENTS_NR; i++) {
    Serial.print(events[i]->GetID());
    Serial.println(events[i]->GetName());
  }
  Serial.println();
}

void updatePollingDevices() {
  for (int i = 0; i < SIM_DEVICES_NR; i++) {
    devices[i]->UpdateValue();
  }
}

void sendDeviceEvent(uint8_t ID, uint8_t type, long value) {
  Serial.write(ID);
  Serial.write(type);
  Serial.write(sizeof(value));
  //Serial.write(value >> 8*3 & 0xff);
  //Serial.write(value >> 8*2 & 0xff);
  //Serial.write(value >> 8   & 0xff);
  Serial.write(value);
  Serial.write('\n');
}

void stopWarning(unsigned long sleepTime) {
  while (true) {
    digitalWrite(WARNING_PIN, HIGH);
    delay(sleepTime);
    digitalWrite(WARNING_PIN, LOW);
    delay(sleepTime);
  }
}

void printAlt(String alt) {
  lcd.setCursor(0, 0);
  lcd.print("ALT:       ");
  lcd.setCursor(5, 0);
  lcd.print(alt);
}

void printComOneStandby(String freq) {
  lcd.setCursor(0, 1);
  lcd.print("COM1:        ");
  lcd.setCursor(6, 1);
  lcd.print(freq);
}

void setup() {
  Serial.begin(115200);

  devices[0] = new SimDeviceButton(0, 51);
  devices[1] = new SimDeviceRotary(1, 44, 50);

  events[0] = new SimEvent(2, String("ALTITUDE"));
  events[1] = new SimEvent(3, String("COM1_STANDBY"));

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
  printAlt("0");
  printComOneStandby("100.000");

  pinMode(WARNING_PIN, OUTPUT);
  digitalWrite(WARNING_PIN, LOW);

  // Indicate start
  Serial.println();
  Serial.println();

  // Announce my devices
  announceMyDevices();
  // Announce what I want to subscribe to
  announceMySubscriptions();
 
}

void loop() {
  // Update polling devices
  updatePollingDevices();
  
  // Check my devices
  for (int i = 0; i < SIM_DEVICES_NR; i++) {
    if (devices[i]->HasChanged()) {
      // If so, send the data
      long value = devices[i]->GetValue();
      sendDeviceEvent(devices[i]->GetID(), 0, value);

      devices[i]->ResetSeen();
    }
  }
  
  // Check if any events have occured
  if (Serial.available() > 0) {

    #define READ_BUFF_SIZE 256
    byte buff[READ_BUFF_SIZE];
    size_t b_read = Serial.readBytesUntil('\n', buff, READ_BUFF_SIZE);

    if (b_read > 3) {
      uint8_t id = buff[0];
      uint8_t type = buff[1];
      uint8_t dataLen = buff[2];
      
      if (b_read == 3 + dataLen) {
        // Correct size
        String newValue = "";
        switch (id) {
          case 2: // ALTITUDE
            for (int i = 0; i < dataLen; i++) {
              newValue = String(newValue + (char) buff[3 + i]);
            }
            events[0]->SetValue(newValue);
            printAlt(newValue);
            break;
          case 3: // COM1
            for (int i = 0; i < dataLen; i++) {
              newValue = String(newValue + (char) buff[3 + i]);
            }
            events[1]->SetValue(newValue);
            printComOneStandby(newValue);
            break;
        }
      } else {
        stopWarning(1000);
      }
    } else {
      stopWarning(5000);
    }
  }

  // Update output devices

  // Print ALT
  

  // Print COM1 Standby

}
