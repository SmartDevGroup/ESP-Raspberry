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
      url += "http://smartdevgroup.hopto.org/service/add_socket.php?";
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
