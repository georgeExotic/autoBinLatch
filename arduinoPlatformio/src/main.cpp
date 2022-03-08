#include <Arduino.h>
#include <BinLatch.h>
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>

const char SSID[] = "Cobotics_Lab_2.4GHz";
const char PASSWORD[] = "cobotics001";
// const char SSID[] = "Whitesky-712";
// const char PASSWORD[] = "krt3dyn5";
const char mqttBroker[] = "192.168.0.3";
const int mqttPort = 1883;
int keyIndex = 0;
int status = WL_IDLE_STATUS;


WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
// BinLatch Bin_1(14,15);
// BinLatch Bin_2(18,19);
// BinLatch Bin_3(16,17);
BinLatch Bin_4(14,15);
boolean firstLoop = 1;
boolean status_1 = 1;

const char topic_1[]  = "/bin_rack/Bin_4/status";
const char topic_1_1[]  = "/bin_rack/Bin_4/command";

void onMqttMessage(int messageSize) {

  if (mqttClient.messageTopic() = topic_1_1){
    String _msg = "";
    while (mqttClient.available()) {
      char letter = char(mqttClient.read());
      _msg += letter;}
      if (_msg == "RELEASE"){
        Bin_4.releaseLatch();
      }
  }
}

void _connectWiFi(){
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WEP network, SSID: ");
    Serial.println(SSID);
    status = WiFi.begin(SSID, keyIndex, PASSWORD);
    // wait 5 seconds for connection:
    delay(5000);
  }
  // once you are connected :
  Serial.println("WiFi CONNECTION SUCCESSFULL");
}

void _connectMqtt(){
  if (!mqttClient.connect(mqttBroker,mqttPort)){
    Serial.print("MQTT CONNECTION FAILED! ERROR CODE = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  Serial.println("MQTT CONNECTION IS SUCCESFULL");
  mqttClient.onMessage(onMqttMessage);
  mqttClient.subscribe(topic_1);
  mqttClient.subscribe(topic_1_1);
}

void setup() {
  Serial.begin(9600);
  _connectWiFi();
  delay(2000);
  _connectMqtt();
}

void loop() {

  mqttClient.poll();
  // Serial.println(Bin_4.getBinStatus());
  // delay(200);
  
  if (Bin_4.getBinStatus() != status_1 || firstLoop){ 
    status_1 = Bin_4.getBinStatus();
    firstLoop = 0;
    if (!status_1){
      mqttClient.beginMessage(topic_1);
      mqttClient.print(status_1);
      mqttClient.endMessage();
      // Bin_4.releaseLatch();
      }
      else if (status_1){
      mqttClient.beginMessage(topic_1);
      mqttClient.print(status_1);
      mqttClient.endMessage();
      Bin_4.lockLatch();
      }
  }
} 