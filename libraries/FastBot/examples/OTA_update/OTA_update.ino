// пример обновления прошивки из чата

#define WIFI_SSID "Aion"
#define WIFI_PASS "12348765"
#define BOT_TOKEN "6151368927:AAGTYo8AFakJcEax3Pzxi3TWhtVQBzYmeq0"
#define CHAT_ID "682037374"

#include <FastBot.h>
FastBot bot(BOT_TOKEN);

void setup() {
  connectWiFi();
  Serial.println("v1.0");
  bot.attach(newMsg);
}

// обработчик сообщений
void newMsg(FB_msg& msg) {
  // выводим всю информацию о сообщении
  Serial.println(msg.toString());

  // обновить, если прислали bin файл
  if (msg.OTA) bot.update();

  // обновить, если файл имеет нужную подпись
  //if (msg.OTA && msg.text == "update") bot.update();

  // обновить, если прислал известный человек (админ)
  //if (msg.OTA && msg.chatID == "123456") bot.update();
}

void loop() {
  bot.tick();
}

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}
