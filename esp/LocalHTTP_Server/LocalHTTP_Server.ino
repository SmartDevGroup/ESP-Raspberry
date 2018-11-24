#include <OneWire.h>                                    // Подключаем библиотеку Wire
#include <DallasTemperature.h>
    
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define ONE_WIRE_BUS 0
#define LED 2

// temperature sens
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
  

// Wi-Fi
const char* ssid = "DIR-300NRUB7";
const char* password = "";

String status;
String status_old = "Disable";
bool status_var;
 
IPAddress ip(192, 168, 0, 55);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

void setup(void) {  
  delay(100);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  DS18B20.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", chek_control());
  });
  server.on("/Sensor", []() {
    server.send(200, "text/html", getSensorProperty());
  });
  server.on("/start", []() {
    server.send(200, "text/html", "Hello");
  });
  server.begin();
  Serial.println("HTTP server started");
  Serial.end();
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
}

void loop(void) {
  server.handleClient();
}

String chek_control(){
  status = server.arg(0);
  if(status != status_old){
    if(status == "Enable")status_var = false;
    else if(status == "Disable")status_var = true;
    status_old = status;
    digitalWrite(3,status_var);
    digitalWrite(LED,status_var);
    
    }
    
    delay(10);
    return status;
  }

String getSensorProperty(){
  DS18B20.requestTemperatures(); 
  return String(DS18B20.getTempCByIndex(0));
}
