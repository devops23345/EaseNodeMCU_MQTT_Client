#include <Arduino.h>
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <EasyNodeMCU_MQTT_Client.h>

unsigned long lastReconnectAttempt = 0;

void setup_easy_mqtt(){
  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  Serial.print("Connecting to MQTT Broker @ ");
  Serial.println(easy_MQTT_server);
  // Create a random client ID
  // clientID = clientID + String(random(0xff), HEX);

  //Wait while trying to connect with broker
  // This is a blocking call
  while (!client.connect(clientID, easy_MQTT_username, easy_MQTT_password)) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to MQTT Broker");
  return;
}

void loop_easy_mqtt(){
    unsigned long now = millis();

    // Check status.  Reconnect if needed.
    // This is a blocking call
    if (!client.connected()) {
        if (now - lastReconnectAttempt > 5000) {
            lastReconnectAttempt = now;
            // Attempt to reconnect
            setup_easy_mqtt();
        }
    }
}
