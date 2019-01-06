void wifi_connection(){
  if (LAN_SSID[15] == '*') { // перевірка на стандартний ssid
    WiFi.mode(WIFI_AP); 
    WiFi.softAP(ssid);
  } else {                   // інакше підключення до зчитаної мережі
    Serial.println("Connect to WIFI");
      Serial.print(LAN_SSID);
      Serial.print(" ");
    Serial.println(LAN_PSWD);  
    WiFi.mode(WIFI_STA);
    WiFi.begin(LAN_SSID,LAN_PSWD);
    byte tries = 30; // час на підключення до мережі
    while (--tries && WiFi.status() != WL_CONNECTED) {
      delay(500);
        Serial.print(".");
      }

    if (WiFi.status() == WL_CONNECTED) {  // якщо підключення встановленно то перевірити IP адрессу
      Serial.println(WiFi.localIP());
      Serial.print("WiFi connected to ");
      Serial.println(LAN_SSID);

        readEEPROM(34,16,ipAddr); // зчитання попередньої адреси
        IPAddress broadCast = WiFi.localIP();
        String ip;
        for(int i = 0; i < 4; i++) {
          ip += String(broadCast[i]);
            if(i < 3)ip += ".";
        }

      for(int i = 0; i<16;i++) {
        if(ip[i]!= ipAddr[i]) {
          reqToChangeIP(ip);
          writeEEPROM(34,16,strdup(ip.c_str())); // якщо адреса відрізняється перезаписати її
          break;
          }
        }    
      }


    if (WiFi.status() != WL_CONNECTED)  {  // інакше редим роботи як точка доступу
      Serial.println("");
        Serial.println("WiFi up AP");
        WiFi.mode(WIFI_AP); 
        WiFi.softAP(ssid);
        Serial.println(WiFi.softAPIP());
    }
  
  }
}
