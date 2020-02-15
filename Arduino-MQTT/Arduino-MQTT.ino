/*

This sketch aims at publishing temperature and humidity sensor readings to an MQTT topic in realtime. 
It also subscribes the NodeMCU to a topic, wherein the message received on the topic
changes the RGD LED colors based on the message character.

**RGB LED Connections**

Connect RED to a 330 ohm resistor. Connect the other end of the resistor to NodeMCU pins D1.
Connect COMMON pin to GND.
Connect GREEN to a 330 ohm resistor. Connect the other end of the resistor to NodeMCU pins D2.
Connect BLUE to a 330 ohm resistor. Connect the other end of the resistor to NodeMCU pins D3.

**DHT11 Connections**

Connect pin 1 (on the left) of the sensor to +5V
Connect pin 2 of the sensor to D5 of NodeMCU
Connect pin 4 (on the right) of the sensor to GROUND
Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor 

	☸ Version 0.1.5 ☸
	Modified Feb 2018
	Sketch written by Barsolai Chris.
	Github: https://github.com/ChrisBarsolai

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "DHT.h"

#define DHTPIN 14 // DHT Sensor connected to D5.
#define DHTTYPE DHT11 // Type of DHT sensor.

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor.

// Setup WiFi SSID and Password
const char* ssid = "your-ssid-here";
const char* password = "your-password-here";
// Setup HiveMQ MQTT broker. Access dashboard via: broker.mqtt-dashboard.com
const char* mqtt_server = "broker.mqtt-dashboard.com";

// Below are alternatives for MQTT brokers. Uncomment to test them out.
/*
const char* mqtt_server = "test.mosquitto.org";
const char* mqtt_server = "iot.eclipse.org";
*/

WiFiClient espClient;
PubSubClient client(espClient);


const int RED_PIN = 5;    //D1: Red Pin
const int GREEN_PIN = 4;  //D2: Green Pin
const int BLUE_PIN = 0; //D3: Blue Pin

long lastMsg = 0;
char msg[50];
int value = 0;



//==================================================================



// Initial state of RGB LED. It sets the RGB LED to green.
void intialState(){

      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(BLUE_PIN, LOW);

      snprintf (msg, 75, "Green");
      client.publish("arduinomqtt/LEDstate", msg);
}



// The function below connects your NodeMCU to the wireless network
void setup_wifi(){

	  Serial.begin(9600);
	  Serial.println();
	  Serial.print("connecting to ");
	  Serial.println(ssid);
	  WiFi.begin(ssid, password);
	  while (WiFi.status() != WL_CONNECTED) {
	    delay(500);
	    Serial.print(".");
	  }
	  Serial.println("");
	  Serial.println("WiFi connected");
	  Serial.println("IP address: ");
	  Serial.println(WiFi.localIP());
	  Serial.println("Experience the magic of MQTT");
	  delay(2000);
}



// The setup function sets your NodeMCU GPIOs attached to LED pins to Outputs, starts the serial communication at a baud rate of 9600
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup(){
  
  // drive the LED to be outputs:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  dht.begin();

  Serial.begin(9600); // Starts the serial communication
  setup_wifi();
  intialState();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}



// This functions is executed when some device publishes a message to a topic that your NodeMCU is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that 
// your NodeMCU is subscribed you can actually do something
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on Red LED if an 'R' was received as first character
  if ((char)payload[0] == 'R') {
    digitalWrite(RED_PIN, HIGH);
	digitalWrite(GREEN_PIN, LOW);
	digitalWrite(BLUE_PIN, LOW);
	snprintf (msg, 75, "Red");
    client.publish("arduinomqtt/LEDstate", msg);
  }

  // Switch on Green LED if an 'G' was received as first character
  if ((char)payload[0] == 'G') {
	digitalWrite(RED_PIN, LOW);
	digitalWrite(GREEN_PIN, HIGH);
	digitalWrite(BLUE_PIN, LOW);
	snprintf (msg, 75, "Green");
    client.publish("arduinomqtt/LEDstate", msg);
  }

  // Switch on Blue LED if an 'B' was received as first character
  if ((char)payload[0] == 'B') {
	digitalWrite(RED_PIN, LOW);
	digitalWrite(GREEN_PIN, LOW);
	digitalWrite(BLUE_PIN, HIGH);
	snprintf (msg, 75, "Blue");
    client.publish("arduinomqtt/LEDstate", msg);
  }
}



// This functions reconnects your NodeMCU to your MQTT broker
// Change the function below if you want to subscribe to more topics with your NodeMCU 
void reconnect() {
  	
  	// Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("arduinomqtt/LEDchange");
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void loop() {

	long sendMsg = millis();

	if (sendMsg - lastMsg > 2000) {

		lastMsg = sendMsg;

		// Obtain temperature sensor readings
		float humidity = dht.readHumidity();
	    // Read temperature as Celsius (the default)
	    float temp = dht.readTemperature();


	    // Check if any reads failed and exit early (to try again).
	    if (isnan(humidity) || isnan(temp)) {
	      Serial.println("Failed to read from DHT sensor!");
	      return;
	    }



	    if (!client.connected()) {
	    	reconnect();
	    }
	  	client.loop();

	    // Publish Temperature and Humidity values to MQTT Topic
	    // To view the published values, use MQTTBox and subscribe to the topics after setting up the broker credentials
	    client.publish("arduinomqtt/temperature", temp);
	    client.publish("arduinomqtt/humidity", humidity);

	    Serial.print("Humidity: ");
	    Serial.print(humidity);
	    Serial.print(" %\t Temperature: ");
	    Serial.print(temp);
	  	
	  	delay(1000);
	}	
}
