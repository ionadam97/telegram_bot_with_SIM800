#include "functions.h"

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Start");
  wifi();
  botSetup();
  simSetup();
}

void loop() {
  bot.tick();
  reciverSim800l();
  reciverSerial();
  checkWiFi();
}

void reciverSerial() {  // control sim800l with serial console
  while (Serial.available()) {
    sim800.println(Serial.readString());
  }
}
