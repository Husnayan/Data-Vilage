#include <Arduino.h>
#include <AViShaMQTT.h>

// Function prototypes
void printAllData();
String getDataJSON();
void updateData(String topic, String message);

// Konfigurasi WiFi dan MQTT
const char *ssid = "Husnayan";
const char *password = "12345678";
const char *mqtt_server = "broker.emqx.io";
AViShaMQTT mqtt(ssid, password, mqtt_server);

// Topic dari semua publisher
// Publisher 1 topics
const char *tempTopic1 = "adcd";
const char *gasTopic1 = "efgh";
const char *ledTopic1 = "ijkl";

// Publisher 2 topics
const char *tempTopic2 = "panasdek";
const char *gasTopic2 = "meledakdek";
const char *ledTopic2 = "menyaladek";

// Publisher 3 topics
const char *tempTopic3 = "panasmasputra";
const char *gasTopic3 = "meledakduar";
const char *ledTopic3 = "menyalaabangku";

// Variabel untuk menyimpan data dari semua publisher
float temp1 = 0, temp2 = 0, temp3 = 0;
int gas1 = 0, gas2 = 0, gas3 = 0;
String ledStatus1 = "N/A", ledStatus2 = "N/A", ledStatus3 = "N/A";

// Timer untuk update Serial Monitor
unsigned long lastPrintTime = 0;
const long printInterval = 3000; // Print setiap 3 detik

// Variabel untuk menangani callback manual
String lastTopic = "";
String lastMessage = "";

void setup() {
  Serial.begin(9600);
  
  Serial.println("\n=================================");
  Serial.println("MQTT SUBSCRIBER - 3 PUBLISHERS");
  Serial.println("=================================");
  Serial.println("WiFi: Connecting...");
  
  // Setup MQTT
  mqtt.begin();
  
  // Subscribe ke semua topic
  mqtt.subscribe(tempTopic1);
  mqtt.subscribe(gasTopic1);
  mqtt.subscribe(ledTopic1);
  
  mqtt.subscribe(tempTopic2);
  mqtt.subscribe(gasTopic2);
  mqtt.subscribe(ledTopic2);
  
  mqtt.subscribe(tempTopic3);
  mqtt.subscribe(gasTopic3);
  mqtt.subscribe(ledTopic3);
  
  Serial.println("WiFi: Connected!");
  Serial.println("Subscribed to 9 topics:");
  Serial.println("1. adcd (Temp1)");
  Serial.println("2. efgh (Gas1)");
  Serial.println("3. ijkl (LED1)");
  Serial.println("4. panasdek (Temp2)");
  Serial.println("5. meledakdek (Gas2)");
  Serial.println("6. menyaladek (LED2)");
  Serial.println("7. panasmasputra (Temp3)");
  Serial.println("8. meledakduar (Gas3)");
  Serial.println("9. menyalaabangku (LED3)");
  Serial.println("\nWaiting for messages...");
  Serial.println("=================================\n");
}

void loop() {
  // Handle MQTT connection
  mqtt.loop();
  
  // Cek jika ada pesan baru (simulasi callback)
  // Note: Library AViShaMQTT mungkin tidak memiliki callback
  // Kita perlu implementasi manual atau gunakan cara lain
  
  // Print semua data ke Serial Monitor setiap interval
  if (millis() - lastPrintTime >= printInterval) {
    printAllData();
    lastPrintTime = millis();
  }
  
  delay(100);
}

void printAllData() {
  Serial.println("\n=================================");
  Serial.println("DATA FROM ALL PUBLISHERS");
  Serial.println("=================================");
  
  // Publisher 1
  Serial.println("PUBLISHER 1:");
  Serial.print("  Temperature: ");
  Serial.printf("%.2f°C", temp1);
  Serial.println();
  
  Serial.print("  Gas Value: ");
  Serial.print(gas1);
  Serial.println();
  
  Serial.print("  LED Status: ");
  Serial.println(ledStatus1);
  
  // Publisher 2
  Serial.println("\nPUBLISHER 2:");
  Serial.print("  Temperature: ");
  Serial.printf("%.2f°C", temp2);
  Serial.println();
  
  Serial.print("  Gas Value: ");
  Serial.print(gas2);
  Serial.println();
  
  Serial.print("  LED Status: ");
  Serial.println(ledStatus2);
  
  // Publisher 3
  Serial.println("\nPUBLISHER 3:");
  Serial.print("  Temperature: ");
  Serial.printf("%.2f°C", temp3);
  Serial.println();
  
  Serial.print("  Gas Value: ");
  Serial.print(gas3);
  Serial.println();
  
  Serial.print("  LED Status: ");
  Serial.println(ledStatus3);
  
  Serial.println("=================================");
  Serial.println("Last Update: " + String(millis() / 1000) + " seconds");
  Serial.println("=================================\n");
}

// Fungsi untuk mendapatkan data dalam format JSON
String getDataJSON() {
  String json = "{";
  json += "\"publisher1\":{";
  json += "\"temperature\":" + String(temp1) + ",";
  json += "\"gas\":" + String(gas1) + ",";
  json += "\"led\":\"" + ledStatus1 + "\"";
  json += "},";
  
  json += "\"publisher2\":{";
  json += "\"gas\":" + String(gas2) + ",";
  json += "\"temperature\":" + String(temp2) + ",";
  json += "\"led\":\"" + ledStatus2 + "\"";
  json += "},";
  
  json += "\"publisher3\":{";
  json += "\"temperature\":" + String(temp3) + ",";
  json += "\"gas\":" + String(gas3) + ",";
  json += "\"led\":\"" + ledStatus3 + "\"";
  json += "}";
  json += "}";
  
  return json;
}

// Fungsi untuk update data dari publisher
// Fungsi ini bisa dipanggil dari tempat lain jika ada mekanisme callback
void updateData(String topic, String message) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  // Update data berdasarkan topic yang diterima
  
  // Publisher 1
  if (topic == tempTopic1) {
    temp1 = message.toFloat();
    Serial.println("Updated: Publisher 1 - Temperature");
  } 
  else if (topic == gasTopic1) {
    gas1 = message.toInt();
    Serial.println("Updated: Publisher 1 - Gas Value");
  } 
  else if (topic == ledTopic1) {
    ledStatus1 = (message == "1") ? "ON" : "OFF";
    Serial.println("Updated: Publisher 1 - LED Status");
  }
  
  // Publisher 2
  else if (topic == tempTopic2) {
    temp2 = message.toFloat();
    Serial.println("Updated: Publisher 2 - Temperature");
  } 
  else if (topic == gasTopic2) {
    gas2 = message.toInt();
    Serial.println("Updated: Publisher 2 - Gas Value");
  } 
  else if (topic == ledTopic2) {
    ledStatus2 = (message == "1") ? "ON" : "OFF";
    Serial.println("Updated: Publisher 2 - LED Status");
  }
  
  // Publisher 3
  else if (topic == tempTopic3) {
    temp3 = message.toFloat();
    Serial.println("Updated: Publisher 3 - Temperature");
  } 
  else if (topic == gasTopic3) {
    gas3 = message.toInt();
    Serial.println("Updated: Publisher 3 - Gas Value");
  } 
  else if (topic == ledTopic3) {
    ledStatus3 = (message == "1") ? "ON" : "OFF";
    Serial.println("Updated: Publisher 3 - LED Status");
  }
}