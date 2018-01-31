# Importing Code
Download the [Arduino-MQTT.ino](https://github.com/ChrisBarsolai/arduino-mqtt-tutorial/blob/master/Arduino-MQTT/Arduino-MQTT.ino) and open in Arduino 1.8.x

**On Arduino IDE:**
#### Install PubSubClient
This library provides a client for doing simple publish/subscribe messaging with a server that supports MQTT. The library can be installed into the Arduino IDE using the built-in Library Manager.
- Open the Library Manager by selecting ` Sketch -> Include Library -> Manage Libraries`
- Search for “PubSubClient”
- Click the “Install” button

The latest release can also be downloaded directly from [Github PubSubClient repo]( https://github.com/knolleary/pubsubclient/releases/latest 'PubSubClient')
#### Install DHT Sensor Library
Download the ZIP from the [Adafruit Github repo]( https://github.com/adafruit/DHT-sensor-library 'DHT Sensor').  
Place the DHT library folder in the `/libraries/ folder` of your Arduino IDE. You may need to create the libraries subfolder if its your first library. Restart the IDE.

### Arduino code
Download the Arduino Code in this repo and open it in your Arduino IDE.
Select the NodeMCU on the suitable COM port by navigating to `Tools -> Board-> NodeMCU 1.0 (ESP-12E Module)`.

#### Changes to code
1. Configure the WiFi SSID and password to your own network credentials
```c
// Setup WiFi SSID and Password
const char* ssid = "your-ssid-here";
const char* password = "your-password-here";
```
2. Setup MQTT Broker. We’ll be using HiveMQ as our broker, accessed via [broker.mqtt-dashboard.com]( broker.mqtt-dashboard.com). Other brokers available include [Eclipse](iot.eclipse.org) and [Mosquitto](test.mosquitto.org)
```c
// Setup HiveMQ MQTT broker. Access dashboard via: broker.mqtt-dashboard.com
const char* mqtt_server = "broker.mqtt-dashboard.com";

// Below are alternatives for MQTT brokers.
const char* mqtt_server = "test.mosquitto.org";
const char* mqtt_server = "iot.eclipse.org";

```

The NodeMCU publishes temperature and humidity data to two MQTT topics. Topics in MQTT can be changed dynamically and do not require additional configurations.
```c
// Publish Temperature and Humidity values to MQTT Topic
// To view the published values, use MQTTBox and subscribe to the topics after setting up the broker credentials
client.publish("arduinomqtt/temperature", temp);
client.publish("arduinomqtt/humidity", humidity);
```


## More on IoT and AI
Follow for more tutorials and updates:
* [Medium]( https://medium.com/@chrisbarsolai 'Medium'): For articles on the lates in IoT and AI
* [LinkedIn]( https://ke.linkedin.com/in/chrisbarsolai 'LinkedIn'): Developer in suit and tie
* [Facebook]( https://www.facebook.com/chris.barso 'Facebook'): For all the memes I share
