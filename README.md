# Telegram Bot with SIM800

## Project Overview
This project integrates the ESP8266 microcontroller with a SIM800L GSM module to create a versatile Telegram bot.
The bot, running on the ESP8266, communicates with a SIM card via the SIM800L module to send and receive SMS messages.
These messages are then forwarded to a Telegram chat, allowing for remote management of the ESP8266 through the Telegram bot. 

## Features
- **Receive SMS Messages**: ESP8266 receives SMS messages from the SIM card and forwards them to a designated Telegram chat.
- **Remote Commands**: Through the Telegram chat, users can:
  - Restart the ESP8266
  - Check SIM card credit
  - Make phone calls
- **Wi-Fi Configuration**: ESP8266 can connect to a Wi-Fi network through a special access point where users can input login credentials.

## Hardware Requirements
- ESP8266 module
- SIM800L GSM module
- SIM card with active subscription
- Power supply 3.3V
- Antenna for SIM800L (optional for better signal reception)
- Various connectors and wires


## Setup Instructions

1. **Hardware Setup**:
   - Connect the SIM800L module to the ESP8266.
   - Ensure the SIM card is inserted in the SIM800L module.
   - Power the ESP8266 and SIM800L modules correctly.

2. **Software Setup**:
   - Clone this repository to your local machine.
   - Open the project in Arduino IDE.
   - Install the necessary libraries for ESP8266.
   - Configure the Telegram Bot API key in the code.
   - Upload the code to the ESP8266.

3. **Wi-Fi Configuration**:
   - Power on the ESP8266, press and hold button from D6 pin to create an access point.
   - Connect to the access.
   - Enter the Wi-Fi login credentials.


