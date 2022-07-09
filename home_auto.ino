#include <ESP8266WiFi.h>
#define LED D2
const char* ssid = "TurkTelekom_ZK3KU";
const char* password = "7619f881f4779";
unsigned char status_led = 0;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("."); 
  }
  
  Serial.println("");
  Serial.println("Wifi Connected");
  server.begin();
  Serial.println("Server Connected");
  Serial.println(WiFi.localIP());

}

void loop() {
 WiFiClient client = server.available();
 if (!client){
  return;
  }
 Serial.println("new client");
 while(!client.available()){
  delay(1);
 }
  
 String req = client.readStringUntil('\r');
 Serial.println(req);
 client.flush();
 if (req.indexOf("/dooroff") != -1)
 {
  status_led = 0;
  digitalWrite(LED,LOW);
  Serial.println("LED OFF");
  }
 else if(req.indexOf("/dooron") != -1)
 {
  status_led = 0;
  digitalWrite(LED, HIGH);
  Serial.println("LED ON");
  }


  
}
