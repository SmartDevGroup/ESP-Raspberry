String first_conncet() {
  String data = "<!DOCTYPE HTML> ";
  data += "<html> ";
  data += "<head> ";
  data += "<meta charset='utf-8'> ";
  data += "<title>Configuration page</title> ";
  data += "<style type='text/css'>";
  data += " .par button {";
  data += " height: 15%;";
  data += " width: 30%;";
  data += "} </style>";  
  data += "</head> ";

  data += "<body> ";
  data += "<h1 align='center'> Welcome <hr> </h1> ";
  data += "<h2 align='center'> This is first connection.  <p> Plese choose Your WIFI and input PASSWD</p> </h2> ";
  for(int i = 0; i < 32; i++){
    if(WiFi.SSID(i) != ""){
      data += "<div align='center' class='par'>";
      data +=   "<button onclick=\"buttonAction('"+SSIDS[i]+"')\">"+SSIDS[i]+"</button>";
      data += "<form action='/config' hidden> <p><button>bla </button> </p> </form>";
      data +=   "<form  id=\""+SSIDS[i]+"\" action='/config' hidden> ";
      data +=     "<p>";
      data +=     "Please enter password";
      data +=     "<input style='margin-left: 25px' type='password' name='PASSWORD_'>";
      data +=     "<button type='submit' name='SSID_' value=\""+SSIDS[i]+"\">Send</button>";
      data +=     "</p>";
      data +=   "</form>";
      
      data += "</div>";
    }
  }
  data += "<script>";
  data += "function buttonAction(id_){ ";
  data += "var doc = document.getElementById(id_);doc.hidden = !(doc.hidden);";
  data += "};";
  data += "</script>";
  data += "</body> ";
  data += "</html> ";
  return data;
}

String normal_connected() {
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
String getSensorProperty(){
  
}
