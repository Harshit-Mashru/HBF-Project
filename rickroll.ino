// Prank code to play rick roll on usb insert automatically 
// For digispark (ATTiny85)

#include "DigiKeyboard.h"

#define LED_PIN PB1

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(2000);
}

void loop() {
  
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(600);
  DigiKeyboard.print("https://youtu.be/dQw4w9WgXcQ?t=43s");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(5000);
  
  digitalWrite(LED_PIN, LOW);
  for (;;) {}
}
