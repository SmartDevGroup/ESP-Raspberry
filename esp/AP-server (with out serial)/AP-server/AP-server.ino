#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>         


const char *ssid = "**Smart Socket**";
const char *serial = "1596347812";
#define LED 2

String status;
String status_old = "Disable";
bool status_var;

char LAN_SSID[16];
char LAN_PSWD[16];
char ipAddr[16];
String accID;

ESP8266WebServer server(80);
HTTPClient http;
unsigned long timeStart;

void setup() {
  pinMode(LED,OUTPUT);
  digitalWrite(LED,1);
  //pinMode(3,OUTPUT);
	timeStart = millis();
	Serial.begin(115200);
	delay(1000);
	readEEPROM(0,16,LAN_SSID);
	readEEPROM(17,16,LAN_PSWD);
	delay(1000);
	Serial.println("LAN_SSID and LAN_PSWD");
	Serial.println(LAN_SSID);
	Serial.println(LAN_PSWD);

	if (LAN_SSID[15] =='*') {
	  WiFi.mode(WIFI_AP); 
	  WiFi.softAP(ssid);
	} else {
		Serial.println("Connect to WIFI");
  		Serial.print(LAN_SSID);
  		Serial.print(" ");
		Serial.println(LAN_PSWD);  
		WiFi.mode(WIFI_STA);
		WiFi.begin(LAN_SSID,LAN_PSWD);
		byte tries = 30;
		while (--tries && WiFi.status() != WL_CONNECTED) {
			delay(500);
    		Serial.print(".");
  		}

		if (WiFi.status() == WL_CONNECTED) {
			Serial.println(WiFi.localIP());
			Serial.print("WiFi connected to ");
			Serial.println(LAN_SSID);

  			readEEPROM(34,16,ipAddr);
  			IPAddress broadCast = WiFi.localIP();
    		String ip;
		    for(int i = 0; i < 4; i++) {
		    	ip += String(broadCast[i]);
		      	if(i < 3)ip += ".";
		  	}

			for(int i = 0; i<16;i++) {
				if(ip[i]!= ipAddr[i]) {
					reqToChangeIP(ip);
					writeEEPROM(34,16,strdup(ip.c_str()));
					break;
				}
			}    
  
  		}


		if (WiFi.status() != WL_CONNECTED)  {
			Serial.println("");
		    Serial.println("WiFi up AP");
		    WiFi.mode(WIFI_AP); 
		    WiFi.softAP(ssid);
		    Serial.println(WiFi.softAPIP());
		}
  
	}

	if(LAN_SSID[15] =='*'){
	  server.on("/", []() {
	    server.send(200, "text/html", first_conncet());
	  });
	  server.on("/config", []() {
	    writeEEPROM(0,16,strdup((server.arg("SSID_").c_str())));
	    writeEEPROM(17,33,strdup((server.arg("PASSWORD_").c_str())));
	    server.send(200, "text/html", "OK" );
	    delay(1000);
	    ESP.restart();
	  });
	}
	else {
		Serial.println("normal work");

		server.on("/", []() {
			server.send(200, "text/html", normal_conncet());
		});

		server.on("/LED", [](){
			server.send(200, "text/html", chek_control());
			});

	  	server.on("/clean_ssid", []() {
	  		char * ssid_ = strdup(ssid);
		    writeEEPROM(0,16,ssid_);
		    server.send(200, "text/html", "OK" );
		    delay(1000);
		    ESP.restart();
		});
/*
		server.on("/Sensor", []() {
			server.send(200, "text/html", getSensorProperty());
		});
*/
	  	server.on("/config", []() {
	  		writeEEPROM(0,16,strdup((server.arg("SSID_").c_str())));
	    	writeEEPROM(17,33,strdup((server.arg("PASSWORD_").c_str())));
	    	server.send(200, "text/html", "OK" );
	    	delay(1000);
	    	ESP.restart();
	    });
	}

  server.begin();
}


void loop() {
  server.handleClient();
  if(millis() - timeStart > 5000 && accID == "") {
  	timeStart = millis();
  	reqToChangeIP(String(ipAddr));
  	Serial.println(String(ipAddr));
  	//Serial.println(String(millis()));
  }
}

String first_conncet() {
  String data = "<!DOCTYPE HTML> ";
  data += "<html> ";
  data += "<head> ";
  data += "<meta charset='utf-8'> ";
  data += "<title>Welcome to Smart Socket</title> ";
  data += "</head> ";

  data += "<body> ";
  data += "<h1 align='center'> Welcome <hr> </h1> ";
  data += "<h2 align='center'> This is first connection.  <p> Plese to input SSID and password of Your WIFI</p> </h2> ";
  data += "<form action='config' align='center'>";
  data += "<p> <b> SSID : </b><input type='text' name='SSID_'></p>";
  data += "<p> <b> PASSWORD : </b><input type='text' name='PASSWORD_'></p>";  
  data += "<p><button type='submit'>Restart</button></p>";
  data += "</form>";

  data += "</body> ";
  data += "</html> ";
  return data;
}
String normal_conncet() {
  String data = "<!DOCTYPE HTML> ";
  data += "<html> ";
  data += "<head> ";
  data += "<meta charset='utf-8'> ";
  data += "<title>Welcome to Smart Socket</title> ";
  data += "</head> ";

  data += "<body> ";
  data += "<h1 align='center'> Welcome <hr> </h1> ";

  data += "<h2 align='center'> This is normal connection.  <p> If your want to clean SSID and password click button</p> </h2> ";
  data += "<form action='clean_ssid' align='center'>";
  data += "<p><button type='submit'>CLEAN</button></p>";
  data += "</form>";

  data += "<hr> <p> if your want change SSID do it this <hr> </p>";
  data += "<form action='config' align='center'>";
  data += "<p> <b> SSID : </b><input type='text' name='SSID_'></p>";
  data += "<p> <b> PASSWORD : </b><input type='text' name='PASSWORD_'></p>";  
  data += "<p><button type='submit'>Restart</button></p>";
  data += "</form>";

  data += "</body> ";
  data += "</html> ";
  return data;
}

void writeEEPROM(int startAdr, int laenge, char* writeString) {
  EEPROM.begin(512); //Max bytes of eeprom to use
  yield();
  Serial.println();
  Serial.print("writing EEPROM: ");
  //write to eeprom 
  for (int i = 0; i < laenge; i++) {
      EEPROM.write(startAdr + i, writeString[i]);
      Serial.print(writeString[i]);
    }
  EEPROM.commit();
  EEPROM.end();           
}

void readEEPROM(int startAdr, int maxLength, char* dest) {
  EEPROM.begin(512);
  delay(10);
  for (int i = 0; i < maxLength; i++) {
      dest[i] = char(EEPROM.read(startAdr + i));
    }
  EEPROM.end();    
  Serial.print("ready reading EEPROM:");
  Serial.println(dest);
}

void reqToChangeIP(String ip) {
	if (WiFi.status() == WL_CONNECTED) {
    IPAddress broadCast = WiFi.localIP();
        String ip;
        for(int i = 0; i < 4; i++) {
          ip += String(broadCast[i]);
            if(i < 3)ip += ".";
        }
		Serial.println("Start GET request");
	    String url;
	    url += "http://192.168.43.56/service/add_socket.php?";
	    url += "serial=";
	    url += String(serial);
	    url += "&ip=";
      url += ip;
	    Serial.println("ip is");
	    Serial.println(ip);
	    http.begin(url);
	    Serial.println("send");
	    int httpCode = http.GET(); 
	    if (httpCode > 0) { 
	    	String payload = http.getString(); 
	        Serial.println(payload);
	        if(payload != NULL && payload != "repeat") accID = payload;
	      }
	    http.end(); 
	}
}

String chek_control() {
  status = server.arg(0);
  if(status != status_old){
    if(status == "Enable")status_var = false;
    else if(status == "Disable")status_var = true;
    status_old = status;
    //digitalWrite(3,status_var);
    digitalWrite(LED,status_var);
    
    }
    
    delay(10);
    return status;
  }
/*
String getSensorProperty() {
  DS18B20.requestTemperatures(); 
  return String(DS18B20.getTempCByIndex(0));
}
*/
