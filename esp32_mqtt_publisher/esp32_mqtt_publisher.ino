#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid          = "TU_RED_WIFI";
const char* password      = "TU_PASSWORD_WIFI";
const char* mqtt_server   = "192.168.1.100";
const int   mqtt_port     = 1883;
const char* mqtt_user     = "admin";
const char* mqtt_password = "admin";
const char* client_id     = "ESP32_Publisher";
const char* topic         = "woox/sensores/temperatura";
const unsigned long PUBLISH_INTERVAL = 5000;

WiFiClient   espClient;
PubSubClient client(espClient);
unsigned long lastPublishTime = 0;
int messageCount = 0;

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\n✅ WiFi conectado IP: " + WiFi.localIP().toString());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando al broker MQTT...");
    if (client.connect(client_id, mqtt_user, mqtt_password)) {
      Serial.println(" ✅ conectado");
    } else {
      Serial.print(" ❌ rc="); Serial.print(client.state());
      Serial.println(" reintentando en 5s..."); delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
  unsigned long now = millis();
  if (now - lastPublishTime >= PUBLISH_INTERVAL) {
    lastPublishTime = now;
    messageCount++;
    float temp = 20.0 + random(0, 150) / 10.0;
    char payload[128];
    snprintf(payload, sizeof(payload),
      "{\"device\":\"%s\",\"temp\":%.1f,\"unidad\":\"C\",\"msg\":%d}",
      client_id, temp, messageCount);
    client.publish(topic, payload);
    Serial.print("📤 "); Serial.println(payload);
  }
}
