# Node-RED
This Node-RED file in this repository that enables you to replicate the flow of nodes I had created for this tutorial. Import it into your clipboard and Deploy. Then head over to <http://localhost:1880/ui> to view the UI components.

![dashboard](https://user-images.githubusercontent.com/14905480/35630172-bb2f19dc-06b1-11e8-8f63-f6ca49ab34cc.png)


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

## How to Import

1. Copy the Node-RED.txt contents to clipboard
2. Navigate to the setting palette `Import -> Clipboard`

![node red import](https://user-images.githubusercontent.com/14905480/35638271-b90c2d82-06c7-11e8-8f38-f9aa00d1eb3c.png)

3. Paste from clipboard

![mqtt in](https://user-images.githubusercontent.com/14905480/35629653-359cfb5a-06b0-11e8-8baf-62480afe233e.png)


By navigating to the LED Changes tab, you can control the color of the LED by a simple button press. This publishes a message payload as either ‘R’, ‘G’ or ‘B’ depending on the button.
