void routes(){
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

    server.on("/Sensor", []() {
      server.send(200, "text/html", getSensorProperty());
    });

      server.on("/config", []() {
        writeEEPROM(0,16,strdup((server.arg("SSID_").c_str())));
        writeEEPROM(17,33,strdup((server.arg("PASSWORD_").c_str())));
        server.send(200, "text/html", "OK" );
        delay(1000);
        ESP.restart();
      });
  }
}
