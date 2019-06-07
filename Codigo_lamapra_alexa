include <ESP8266WiFi.h>
#include <ArduinoJson.h>      //  https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries
#include <WebSocketsClient.h> //  https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

#define MyApiKey "3681507d-785c-4d4a-b9a3-edbeb8a6ea53" // Sinric API Key.
#define MySSID "BUAP_Estudiantes" // Wifi network SSID
#define MyWifiPassword "f85ac21de4" // Wifi network password

#define API_ENDPOINT "http://sinric.com"
#define HEARTBEAT_INTERVAL 300000 // 5 Minutes

#define DEVICE_1 D0
#define DEVICE_2 D1

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

void turnOn(String deviceId) {
  
  if( deviceId == "5cf9a694c2176d3be680f9ea" ) {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(DEVICE_1, LOW);
  }else if( deviceId == "5cfa92bbb0dae23e2f3e0202" ) {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(DEVICE_2, LOW);
  }else {
    Serial.print("Turn on for unknown device id: ");
    Serial.println(deviceId);
  }
  
}

void turnOff(String deviceId) {
  
  if( deviceId == "5cf9a694c2176d3be680f9ea" ) {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(DEVICE_1, HIGH);
  }else if( deviceId == "5cfa92bbb0dae23e2f3e0202" ) {
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(DEVICE_2, HIGH);
  }else {
    Serial.print("Turn on for unknown device id: ");
    Serial.println(deviceId);
  }
  
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      isConnected = false;    
      Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
      break;
    case WStype_CONNECTED: {
      isConnected = true;
      Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
      Serial.printf("Waiting for commands from sinric.com ...\n");        
      }
      break;
    case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject((char*)payload); 
        String deviceId = json ["deviceId"];     
        String action = json ["action"];
        
        if(action == "setPowerState") { // Switch or Light
            String value = json ["value"];
            if(value == "ON") {
                turnOn(deviceId);
            } else {
                turnOff(deviceId);
            }
        }
        else if(action == "SetColor") {
            String hue = json ["value"]["hue"];
            String saturation = json ["value"]["saturation"];
            String brightness = json ["value"]["brightness"];

            Serial.println("[WSc] hue: " + hue);
            Serial.println("[WSc] saturation: " + saturation);
            Serial.println("[WSc] brightness: " + brightness);
        }
        else if(action == "setBrightness") {
          
        }
        else if(action == "AdjustBrightness") {
          
        }
        else if (action == "test") {
            Serial.println("[WSc] received test command from sinric.com");
        }
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(DEVICE_1, OUTPUT); digitalWrite(DEVICE_1, HIGH);
  pinMode(DEVICE_2, OUTPUT); digitalWrite(DEVICE_2, HIGH);
  
  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);  

  // Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if(WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  // server address, port and URL
  webSocket.begin("iot.sinric.com", 80, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);
  
  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000);   // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
}

void loop() {
  webSocket.loop();

  if(isConnected) {
      uint64_t now = millis();
      
      // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night. Thanks @MacSass
      if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
          heartbeatTimestamp = now;
          webSocket.sendTXT("H");          
      }
  }   
}
