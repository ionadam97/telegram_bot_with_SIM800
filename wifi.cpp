#include "functions.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <LittleFS.h>
#include <GyverPortal.h>
GyverPortal ui(&LittleFS);

struct LoginPass {
  char ssid[20], pass[20];
} lp;  // login and password in eeprom

void wifi() {
  EEPROM.begin(100);
  EEPROM.get(0, lp);  // get login and password from eeprom
  setWifi();
  connectWiFi();
}

// html for wifi login acces point
void wifi_login() {
  GP.BUILD_BEGIN();
  GP.THEME(GP_DARK);
  GP.FORM_BEGIN("/login");
  GP.TEXT("lg", "Login", lp.ssid);
  GP.BREAK();
  GP.TEXT("ps", "Password", lp.pass);
  GP.SUBMIT("Submit");
  GP.FORM_END();
  GP.BUILD_END();
}

void save_login(GyverPortal& p) {
  if (p.form("/login")) {
    p.copyStr("lg", lp.ssid);
    p.copyStr("ps", lp.pass);
    EEPROM.put(0, lp);
    EEPROM.commit();
    WiFi.softAPdisconnect();
    ESP.restart();
  }
}

// turn on acces point to add login and password for wifi
void loginPortal() {
  Serial.println("Portal start");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("WiFi Config");
  GyverPortal ui;
  ui.attachBuild(wifi_login);
  ui.start();
  ui.attach(save_login);
  while (ui.tick())
    ;
}

void setWifi() {
  pinMode(D6, INPUT_PULLUP);
  if (!digitalRead(D6)) {  // if button is pressed conect acces point
    pinMode(D4, OUTPUT);   // turn on led from board
    loginPortal();
  }
}

void connectWiFi() {
  pinMode(D4, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(lp.ssid, lp.pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(D4, !digitalRead(D4));
    if (millis() > 15000) ESP.restart(); // if conection take longer than 15 sec, esp is restarded
  }
  digitalWrite(D4, true);
  Serial.println(WiFi.localIP());
}

// check if wifi is connected every 5 minutes
void checkWiFi() {
  static uint32_t tmr;
  if (millis() - tmr >= 300000) {
    tmr = millis();
    if (WiFi.status() != WL_CONNECTED) {
      connectWiFi();
    }
  }
}