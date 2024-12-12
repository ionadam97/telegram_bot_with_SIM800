#include "functions.h"
#include <Arduino.h>
#include <FastBot.h>

#define BOT_TOKEN "" //BOT_TOKEN is needed
#define CHAT_ID "" //CHAT_ID is needed
FastBot bot(BOT_TOKEN);
String menu = "/get_info \t /get_all_msg \t /del_all_msg \n /cont \t  /100 \t /suna_2_luni \n /close \t  /reboot \t /format_msg";
void botSetup() {
  bot.setChatID(CHAT_ID);
  bot.attach(reciverMsg);
  bot.showMenu(menu);
}

// processes received messages
void reciverMsg(FB_msg &msg) {
  if (msg.OTA)
    bot.update();

  if (msg.text == "/get_info") sim800.println("ATI");
  else if (msg.text == "/get_all_msg") sim800.println("AT+CMGL=\"ALL\"");
  else if (msg.text == "/del_all_msg") sim800.println("AT+CMGDA=\"DEL READ\"");
  else if (msg.text == "/format_msg") sim800.println("AT+CMGF=1");
  else if (msg.text == "/100") {
    sim800.println("AT+CUSD=2");
    sim800.println("AT+CUSD=1,\"*100#\"");
  } else if (msg.text == "/cont") {
    sim800.println("AT+CUSD=2");
    sim800.println("AT+CUSD=1,\"*133#\"");
  } else if (msg.text == "/suna_2_luni") {
    sim800.println("AT+CUSD=2");
    sim800.println("AT+CUSD=1,\"*100*33#\"");
  } else if (msg.text == "/reboot") reboot();
  else if (msg.text == "/close") bot.closeMenu();
  else if (msg.text == "/start") bot.showMenu(menu);
  else sim800.println(msg.text);
}

//reboot funtion works if esp is started more than 20 sec
void reboot() {
  static uint32_t tmr;
  if (millis() - tmr >= 20000) {
    tmr = millis();
    bot.sendMessage("rebooting");
    ESP.restart();
  }
}