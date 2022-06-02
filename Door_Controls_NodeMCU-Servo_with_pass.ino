//Code For ESP8266 And Servo With Password

#include <ESP8266WiFi.h>  //NodeMCU library
#include "SLib.h"  //My Servo Library.. created by me 😎😎😎😎😎😎😎
#define m D4  //servo pin
int last = 3;  //Last State(Lock/Unlock)
String ssid = "Darshan";  //Network SSID
String pass = "ardarshan75";  //Network Password
String door_pass = "un1234567";

WiFiClient client;  //Renaming WiFi Client As client
WiFiServer server(80);  //Renaming WiFi server As server and server port = 80

IPAddress local_IP(192, 168, 1, 111);  // Defining Page Address
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

void mainPage(){
  client.println("HTTP/1.1 200 OK\nContent-type:text/html\nConnection: close\n\n<!DOCTYPE html>\n<html>\n<head>\n<title>Door Controls</title>\n<link rel='icon' type='image/x-icon' href='https://findicons.com/files/icons/1786/oxygen_refit/128/lock.png'>\n<style>\nbody{\nbackground-image: url('https://www.fmsh.fr/sites/default/files/styles/programme_page_img_principale/public/image/hacking-dea.jpg?itok=26jKKR9J');\nbackground-repeat: no-repeat\nbackground-attachment: fixed;\nbackground-size: cover;\n}\n#container{\ntext-align: center;\n}\n</style>\n</head>\n<h1 style='color: AliceBlue; text-align: center;'>Door Controls<h1>\n<div id = 'container'>\n<a href=\"/lock\"\"><button class='button button3' style='background-color:DarkCyan;color:AliceBlue;width:200;height:75;'><h1>Lock Door<h1></button></a>\n<label for='pwd' style='color: AliceBlue;'><h3>Enter Password To Unlock Door:</h3></label>\n<form action='/action_page'>\n<input type='password' id='pwd' name='pwd' style='background-color:DarkCyan;color:AliceBlue;width:300;height:25;'><br><br>\n<input type='submit' id='search' value='Search'  class='button button3' style='font-size:20px;background-color:DarkCyan;color:AliceBlue;height:55px; width:150px' />\n</form>\n</div>\n</html>\n");
  //Sending HTML to client
}

void unlock(){
  servo(180,m);  //180 degree
  delay(1000);
  last = 1;//last request = 1
  Serial.println("Unlocked");
}

void setup() {
  pinMode(m,OUTPUT);
  Serial.begin(112500);
  delay(1000);
  Serial.println("Connecting...");  
  //WiFi.begin("JOSHI'S", "EdcThN@1pA@SN");
  WiFi.begin(ssid, pass);  //connect to WiFi
  if (!WiFi.config(local_IP, gateway, subnet)) {  //Set Page Link
    Serial.println("STA Failed to configure");  //Print This In Case Of Error
  }
  while(WiFi.status() != WL_CONNECTED)  //Wait For WiFi To Connect
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());  //Print Page Link
  server.begin();  //Begin Webpage
}

void loop() {
  client = server.available();  //client has got data from user or not
  if (client == 1)  //If client gets data from user
  {  
    String request =  client.readStringUntil('\n');  //read data
    Serial.println(request);
    request.trim();  //remove \n (new line)
    if(request == "GET /action_page?pwd=%s HTTP/1.1",door_pass && last!=1){  //correct password
      unlock();
    }
    else if(request.startsWith("GET /action_page?pwd=")){  //wrong password
      Serial.println("Wrong password");
    }
    if(request == "GET /lock HTTP/1.1" && last!=0)  //lock
    {
      servo(1,m);  //1 degree
      delay(1000);
      last = 0;  //last state = 0
      Serial.println("Locked");
    }
  }
  mainPage();
  
}
