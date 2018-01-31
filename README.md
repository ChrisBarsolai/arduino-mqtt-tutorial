# arduino-mqtt-tutorial
A comprehensive tutorial on getting started with MQTT protocol using NodeMCU, MQTTBox and Node-RED

This tutorial will get you started on working with the NodeMCU, and using MQTT protocol to publish data (messages) it accrues from the sensors wirelessly to an MQTT topic the NodeMCU is subscribed to.
We will additionally use the MQTTBox and Node-RED as the MQTT clients, to check on the published messages and additionally make changes to the hardware remotely.

The NodeMCU will publish temperature and humidity sensor readings to two different MQTT topics (**“arduinomqtt/temperature”** and **"arduinomqtt/humidity"**). It will also be subscribed to a topic (**arduinomqtt/LEDchange**) that listens to changes to be made on the RGB LED. The Node-RED flow includes buttons that will be publishing LED changes to the MQTT topic. 

## MQTT Intro
MQTT is a Client Server _publish/subscribe_ messaging transport protocol. It is light weight, open, simple, and designed so as to be easy to implement. These characteristics make it ideal for use in many situations, including constrained environments such as for communication in Machine to Machine (M2M) and Internet of Things (IoT) contexts where a small code footprint is required and/or network bandwidth is at a premium.

The MQTT protocol uses a publish / subscribe communications model which allows for data to be sent and received asynchronously. A web service called a broker manages where the data is coming from and going to. It's similar to REST for HTTP communications but with several very important distinctions.

#### Useful Links
* [HiveMQ MQTT Blog Series](https://www.hivemq.com/blog/mqtt-essentials-part-1-introducing-mqtt 'HiveMQ')
* [Random Nerd Tutorials](https://randomnerdtutorials.com/what-is-mqtt-and-how-it-works 'What is MQTT and How It Works | Random Nerd Tutorials')

## Hardware Setup
Hardware you’ll need:
* NodeMCU 12E Development Module
* USB Cable
* DHT11 (Temperature and Humidity sensor)
* RGB Common Cathode LED

Here’s a Fritzing wiring diagram to get to up and running.

![Wiring diagram](https://user-images.githubusercontent.com/14905480/35628569-5fded738-06ad-11e8-9ff1-64dfc0bea10e.jpg)

## Software Setup
Software you’ll need:
* Arduino IDE 1.8.x
* MQTTBox

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

## MQTTBox
MQTTBox is a helper program to develop and load test MQTT based clients, brokers, devices, cloud and apps. We will be using MQTTBox to check on the published messages (sensor data) by subscribing to the sensor MQTT topics on the client end. 
Download here: [MQTTBox]( http://workswithweb.com/html/mqttbox/downloads.html 'MQTTBox')
#### Configure
1. Open your MQTTBox and click ‘Create MQTT Client’
2. Configure the MQTT Client settings:
* MQTT Client Name —- Choose any name you like
* Protocol —- Choose “mqtt/tcp”
* Host — Use “broker.mqtt-dashboard.com”

![mqttbox settings](https://user-images.githubusercontent.com/14905480/35629639-2d7dab7c-06b0-11e8-9346-69ae984bc064.PNG)

3. Ensure the broker connection status is ‘Connected’. Configure your topics to be as shown:

![mqttbox main page](https://user-images.githubusercontent.com/14905480/35629675-487c857e-06b0-11e8-8c76-fd6f576db2d8.PNG)

Upon subscribing to the two topics, sensor data obtained from the DHT11 sensor and published as message payloads to the two topics will be received.

To control the RGB LED colors using the MQTT protocol, add a publisher setting the topic as ‘arduinomqtt/LEDchange’ and using the below strings as message payloads to be received by the NodeMCU:
*	R – Turn the LED to RED
*	G – Turn the LED to GREEN
*	B - Turn the LED to BLUE

![mqttbox values](https://user-images.githubusercontent.com/14905480/35629691-55fc6ed0-06b0-11e8-9870-028e719bdfa3.PNG)

## Node-RED
Node-RED is a flow-based development tool developed originally by IBM for wiring together hardware devices, APIs and online services as part of the Internet of Things.

To check the current state of the LED color, subscribe to the topic **‘arduinomqtt/LEDstate’**.
To install Node-RED:
1. `sudo npm install -g --unsafe-perm node-red`
2. `node-red`
3. Open <http://localhost:1880>

We will use Node-RED to subscribe to an MQTT topic via a broker using an MQTT node, and utilise Node-RED Dashboard to provide a comprehensive set of UI components for building basic dashboards suitable for the Internet of Things (IoT).

*Dependencies:*
1. **MQTT:** ` npm install node-red-contrib-mqtt-broker `
2. **Node-RED Dashboard:** ` npm install node-red-dashboard `

![mqtt in](https://user-images.githubusercontent.com/14905480/35629653-359cfb5a-06b0-11e8-8baf-62480afe233e.png)

I have provided a Node-RED file in this repository that enables you to replicate the flow of nodes I had created for this tutorial. Import it into your clipboard and Deploy. Then head over to <http:// localhost:1880/ui/> to view the UI components.

![dashboard](https://user-images.githubusercontent.com/14905480/35630172-bb2f19dc-06b1-11e8-8f63-f6ca49ab34cc.png)

By navigating to the LED Changes tab, you can control the color of the LED by a simple button press. This publishes a message payload as either ‘R’, ‘G’ or ‘B’ depending on the button.

# Conclusion
I hope this simple tutorial was helpful. This repo will be regularly updated with more awesome content and tools that you can work with using MQTT.
May the force be with you.

## More on IoT and AI
Follow for more tutorials and updates:
* [Medium]( https://medium.com/@chrisbarsolai 'Medium'): For articles on the lates in IoT and AI
* [LinkedIn]( https://ke.linkedin.com/in/chrisbarsolai 'LinkedIn'): Developer in suit and tie
* [Facebook]( https://www.facebook.com/chris.barso 'Facebook'): For all the memes I share
