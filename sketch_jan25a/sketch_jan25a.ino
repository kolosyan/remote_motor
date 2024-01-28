
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "TP-Link_D410"; // заменить на ssid вашей сети
const char* password = "18364804"; // заменить на пароль вашей сети 

const char* mqtt_server = "192.168.0.110"; // IP адрес брокера MQTT
const int mqtt_port = 1883; // порт брокера MQTT
const char* mqtt_topic = "esp/led"; // топик для подписки

WiFiClient espClient;
PubSubClient client(espClient);

// Пин светодиода 
const int ledPin = 4; 

// Подключение к WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

// Подключение к MQTT брокеру
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP32Cam")) {
      Serial.println("connected");  
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Получение сообщения
void callback(char* topic, byte* message, unsigned int length) {

  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  
  if (message[0] == '1') {
    digitalWrite(ledPin, HIGH);  
  }
  else if (message[0] == '0') {
    digitalWrite(ledPin, LOW); 
  }
}

void setup() {

  pinMode(ledPin, OUTPUT);
  
  // Serial.begin(115200);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

}