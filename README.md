# HBF-Project

Demo Link --> https://drive.google.com/file/d/1EOCsXqlSqc-n9RxMkglAcv1pIpKRFYnA/view?usp=sharing

## Connections & Steps
- Connect ATTiny85 and flash Attiny.ino using Arduino IDE
- Connect ESP8266 and flash Wifi.ino using Arduino IDE
- Connect GND between both using female to female wire
- Connect D5 on ESP8266 to P2 on ATTiny85
- Plug in the ATTiny85 and power ESP8266 using either the target machine using a USB-A cable to power using the 5V pin on ATTiny
- Now connect your phone to the Wifi server started by the ESP8266
- Visit the server IP 192.168.1.4
- Follow instructions to send commands to the ESP8266 which then relays them to ATTin85 to execute commands remotely
