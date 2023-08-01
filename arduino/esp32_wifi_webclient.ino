#include <WiFi.h>

const char *ssid = "dnpsys";
const char *password = "0167584307";

const char *host = "hardcopyworld.com";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(4000);

  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Wifi connected");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  
  WiFiClient client;
  const int httpPort = 80;
  if(!client.connect(host,httpPort))
  {
    Serial.println("Connect failed");
    return;
  }

    // We now create a URI for the request
  String url = "/";
//  url += streamId;
//  url += "?private_key=";
//  url += privateKey;
//  url += "&value=";
//  url += value;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
  
}
