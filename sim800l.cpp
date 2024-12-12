#include "functions.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

// GSM Module RX pin to NodeMCU D6
// GSM Module TX pin to NodeMCU D5
#define rxPin D5
#define txPin D6
SoftwareSerial sim800(rxPin, txPin);

void simSetup() {
  sim800.begin(9600);
  Serial.println("SIM800L serial initialize");
  sim800.println("AT+CMGF=1");  // set type string for msg
}

//receive messages from Sim800l
void reciverSim800l() {
  while (sim800.available()) {
    parseData(sim800.readString());
  }
}

// processes received messages from Sim800l
void parseData(String buff) {
  bot.sendMessage(buff);

  unsigned int len, index;
  // Remove sent "AT Command" from the response string.
  index = buff.indexOf("\r");
  buff.remove(0, index + 2);
  buff.trim();


  if (buff != "OK") {
    index = buff.indexOf(":");
    String cmd = buff.substring(0, index);
    cmd.trim();
    buff.remove(0, index + 2);

    if (cmd == "+CMTI") { //if a mesage is recived, a request to open it will be sent to sim800l
      index = buff.indexOf(",");
      String message_number = buff.substring(index + 1, buff.length());
      String get_msg_comand = "AT+CMGR=" + message_number + "\r";
      sim800.println(get_msg_comand);
    }
  }
}