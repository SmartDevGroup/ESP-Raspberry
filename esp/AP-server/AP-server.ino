#include <OneWire.h>                                    
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>         


const char *ssid = "**Smart Socket**";
const char *serial = "1596347810";
#define LED 2
#define ONE_WIRE_BUS 0

String status;
String status_old = "Disable";
bool status_var;

char LAN_SSID[16];
char LAN_PSWD[16];
char ipAddr[16];
String accID;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
ESP8266WebServer server(80);
HTTPClient http;
unsigned long timeStart;

void setup() {
  GPIO_setup(); // ініціалізація GPIO
	timeStart = millis(); // початок таймера
	Serial.begin(115200);
	delay(1000);
	readEEPROM(0,16,LAN_SSID); // зчитання даних з енергонезалежної пам'яті
	readEEPROM(17,16,LAN_PSWD);
	delay(1000);
	Serial.println("LAN_SSID and LAN_PSWD");
	Serial.println(LAN_SSID);
	Serial.println(LAN_PSWD);

	wifi_connection(); // підклчення до мережі інтернет

	routes();

  server.begin();
}


void loop() {
  server.handleClient();
  if(millis() - timeStart > 5000 && accID == "") {
  	timeStart = millis();
  	reqToChangeIP(String(ipAddr));
  	Serial.println(String(ipAddr));
  }
}
