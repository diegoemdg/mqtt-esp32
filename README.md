# Mosquitto MQTT — Raspberry Pi + ESP32 Publisher

Proyecto IoT con broker MQTT Mosquitto y Publisher en ESP32.

## Arquitectura

ESP32 (Publisher) → [WiFi] → Raspberry Pi / WSL (Broker Mosquitto) → mosquitto_sub (Subscriber)

## Instalación del Broker

```bash
sudo apt update && sudo apt install -y mosquitto mosquitto-clients
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
```

## Configuración con Autenticación

```bash
sudo mosquitto_passwd -c /etc/mosquitto/passwd admin
sudo nano /etc/mosquitto/conf.d/default.conf
```

Contenido del archivo:
```
listener 1883
allow_anonymous false
password_file /etc/mosquitto/passwd
```

```bash
sudo chown mosquitto:mosquitto /etc/mosquitto/passwd
sudo chmod 600 /etc/mosquitto/passwd
sudo systemctl restart mosquitto
```

## Prueba del Broker

Terminal 1 - Subscriber:
```bash
mosquitto_sub -h localhost -p 1883 -u admin -P admin -t "woox/sensores/#" -v
```

Terminal 2 - Publisher:
```bash
mosquitto_pub -h localhost -p 1883 -u admin -P admin -t "woox/sensores/temperatura" -m '{"device":"ESP32_Publisher","temp":27.4,"unidad":"C","msg":1}'
```

## ESP32 - Configuración

1. Instalar librería **PubSubClient** en Arduino IDE
2. Editar `esp32_mqtt_publisher.ino`:
   - `ssid` y `password` de tu WiFi
   - `mqtt_server` con la IP del broker
3. Cargar a la ESP32

## Credenciales MQTT
- Usuario: `admin`
- Contraseña: `admin`
- Puerto: `1883`
- Tópico: `woox/sensores/temperatura`
