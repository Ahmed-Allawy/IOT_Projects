import time
import json
import paho.mqtt.client as mqtt

id = 'Gate1'
client_name = id
general_topic = 'Phone/01013299050'

Gate_topic = general_topic+'/allawy/Gate1'
# print(Gate_topic)
def call_back(client, userdata, message):
    # payload = json.loads(message.payload.decode())
    print("Message received:", message.payload.decode())
    # print("Topic received:", message.topic)


mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
# mqtt_client = mqtt.Client(callback_api_version=, client_name)
mqtt_client.username_pw_set(username="MoTSensorKitv2.0", password="MoTSensorKitv2.0Pass")
mqtt_client.connect('learning.masterofthings.com')
mqtt_client.loop_start()
mqtt_client.on_message = call_back
mqtt_client.subscribe(Gate_topic)


while True:
    # mqtt_client.publish(pump_topic,"ON")
    time.sleep(5)