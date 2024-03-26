// Libraries
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>

// Setup WiFi
const char * ap_ssid = "alvin";
const char * ap_pass = "alvin123";
const char * sta_ssid = "TEKNIK UNSOED D3";
const char * sta_pass = "";
AsyncWebServer server(80);
String webpage;

// Setup PIN
#define LED1 D5
#define LED2 D6
#define LED3 LED_BUILTIN

void setup() {
  // Initialize PIN
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  Serial.begin(9600);

  // Initialize access point
  // Serial.println("Configuring access point...");
  // WiFi.mode(WIFI_AP);
  // WiFi.softAP(ap_ssid, ap_pass);
  // Serial.print("Wifi: ");
  // Serial.println(ap_ssid);
  // Serial.print("IP address: ");
  // Serial.println(WiFi.softAPIP());

  // Initialize wifi as station
  Serial.print("Connecting to ");
  Serial.println(sta_ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(sta_ssid, sta_pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Create webpage
  webpage = "<h1> Web Control ESP8266</h1>";
  webpage += "<p>LED 1: ";
  webpage += "<a href=\"LED1ON\"\"><button>ON</button></a><a href=\"LED1OFF\"\"><button>OFF</button></a></p><br>";
  webpage += "<p>LED 2: ";
  webpage += "<a href=\"LED2ON\"\"><button>ON</button></a><a href=\"LED2OFF\"\"><button>OFF</button></a></p><br>";
  webpage += "<p>LED 3: ";
  webpage += "<a href=\"LED3ON\"\"><button>ON</button></a><a href=\"LED3OFF\"\"><button>OFF</button></a></p>";

  // Handle webpage actions
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", webpage);
  });
  
  server.on("/LED1ON", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED1, HIGH);
    request->send(200, "text/html", webpage);
  });
  
  server.on("/LED2ON", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED2, HIGH);
    request->send(200, "text/html", webpage);
  });

  server.on("/LED3ON", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED3, LOW);
    request->send(200, "text/html", webpage);
  });

  server.on("/LED1OFF", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED1, LOW);
    request->send(200, "text/html", webpage);
  });
  
  server.on("/LED2OFF", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED2, LOW);
    request->send(200, "text/html", webpage);
  });

  server.on("/LED3OFF", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED3, HIGH);
    request->send(200, "text/html", webpage);
  });

  server.begin();
}

void loop() {

}
