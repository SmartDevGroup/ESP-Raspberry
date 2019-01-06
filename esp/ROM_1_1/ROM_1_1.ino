#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>         


const char *ssid = "**Smart Socket**";
const char *serial = "1596347899";

#define LED 2

String status;
String status_old = "Disable";
bool status_var;

char LAN_SSID[16];
char LAN_PSWD[16];
char ipAddr[16];  
String accID;
String SSIDS[32];

ESP8266WebServer server(80);
HTTPClient http;

void setup() {
	Serial.begin(115200);
	delay(1000);
	readEEPROM(0,16,LAN_SSID); // зчитання даних з енергонезалежної пам'яті
	readEEPROM(17,16,LAN_PSWD);
	delay(1000);
	Serial.println("LAN_SSID and LAN_PSWD");
	Serial.println(LAN_SSID);
	Serial.println(LAN_PSWD);

	wifi_connection(); // підклчення до мережі інтернет

  server.begin();
}


void loop() {
  server.handleClient();
}
