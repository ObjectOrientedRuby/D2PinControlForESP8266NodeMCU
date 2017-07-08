#include <ESP8266WiFi.h>
WiFiServer server(80);

////////////Edit this///////////////
const char* ssid = "YOUR LITTERAL SSID";
const char* password = "THEPASWORDTOYOURNETWORK";
////////////Edit thit///////////////
bool ON = false;
////Define a function to turn pin D2 on.
bool turnOn(){
  digitalWrite(D2, HIGH);
  ON = true;
}
////Define a function to turn pin D2 off.
bool turnOff(){
  digitalWrite(D2, LOW);
  ON = false;
}
void setup() {
pinMode(D2,OUTPUT);
turnOff();
Serial.begin(115200);
delay(10);
// Lets you know the the device is trying to connect.
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
//Actually starts the connection.
WiFi.begin(ssid, password);
//Shows dots until a conection is found.
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
//Lets you know you have a connection.
Serial.println("");
Serial.println("WiFi connected");
// Start the server
server.begin();
//lets you know the server is started
Serial.println("Server started");
// Print the IP address so you can see the webpage.
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
}
void loop() {
// Checks if the server is available.
//If it is not it will restart this loop.
WiFiClient client = server.available();
if (!client) {
  return;
}
// Wait until the client sends some data.
Serial.println("new client");
while(!client.available()){
  delay(1);
}
// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);
// Match the request
if (request.indexOf("/ON") != -1) {
  turnOn();
}
if (request.indexOf("/OFF") != -1) {
  turnOff();
}
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
////////The HTML///////////////////
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("  <head>");
client.println("    <meta name=\"veiwport\" content=\"width=device-width, initial-scale=1.0\" />");
////////////CSS////////////
client.println("    <style>");
//Button tags default.
client.println("      button {");
client.println("        width: 100%;");
client.println("        font-size: 1500%;");
client.println("        background-color: #ffffff;");
client.println("      }");
//Button tags mouse hover.
client.println("      button:hover {");
client.println("        color: #630063;");
client.println("        background-color: #dddddd;");
client.println("      }");
//Body tags.
client.println("      body {");
client.println("        color: #ffffff;");
client.println("        background-color: #000000;");
client.println("        text-align: center;");
client.println("      }");
client.println("    </style>");
/////////////End of CSS/////////////
client.println("  </head>");
client.println("  <body>");
////Body///////////////////////////////
client.print("    <h1>Led pin 2 is now: ");
if (ON == true) {
  client.print("On");
}else if (ON == false)
  client.print("Off");
else {
 client.print("Problem");
}
client.println("</h1><br /><br />");
client.println("<a href=\"/ON\"><button>Turn ON</button></a><br>");
client.println("<a href=\"/OFF\"><button >Turn OFF</button></a><br>");
if (request.indexOf("/ON") != -1) {
  turnOn();
}
if (request.indexOf("/OFF") != -1) {
  turnOff();
}
client.println("  </body>");
client.println("</html>");
///////End of HTML////////////////////////////////////
delay(1);
Serial.println("Client disonnected");
Serial.println("");
}
