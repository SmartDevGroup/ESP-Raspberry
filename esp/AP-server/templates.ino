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

String getSensorProperty() {
  DS18B20.requestTemperatures(); 
  return String(DS18B20.getTempCByIndex(0));
  return String(25);
}
