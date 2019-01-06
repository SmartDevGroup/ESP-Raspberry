void wifi_connection(){
  if (LAN_SSID[15] == '*') { //---------------------------------- перевірка на стандартний ssid
    WiFi.mode(WIFI_AP_STA); 
    wifiScan();              //---------------------------------- пошук мереж
    WiFi.mode(WIFI_AP); 
    WiFi.softAP(ssid);       //---------------------------------- запуск сеоверу як точка доступу
    routeFirstConn();
  } else {
    // --------------------------------- спроба підключення до мережі WIFI
    Serial.println("Connection to WIFI");
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
          Serial.println("ip is changed");
          reqToChangeIP(ip);
          writeEEPROM(34,16,strdup(ip.c_str())); // якщо адреса відрізняється перезаписати її
          break;
          }
        }    
      routeNormalConn();
      } else {
        Serial.println("Invalid connections");
        WiFi.mode(WIFI_AP_STA); 
        wifiScan();   
        Serial.println("WiFi up AP");
        WiFi.mode(WIFI_AP); 
        WiFi.softAP(ssid);
        Serial.println(WiFi.softAPIP());
        routeFirstConn();
      }

  }

  
}

void wifiScan(){
  int n = WiFi.scanNetworks();
  if (n != 0){  
    for (int i = 0; i < 32; ++i) {
      SSIDS[i] = WiFi.SSID(i);
    }
  }
}
