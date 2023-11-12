import json
import time

import paho.mqtt.client as mqtt

id = 'ahmed@Allawy_2023'

command_topic = id + '/commands'
client_name = id + 'nightlight_server'
light_topic = id + '/light'

mqtt_client = mqtt.Client(client_name)
mqtt_client.connect('test.mosquitto.org')

mqtt_client.loop_start()

def call_back(client, userdata, message):
    payload = json.loads(message.payload.decode())
    print("Message received:", payload)

    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)

    client.publish(command_topic, json.dumps(command))

mqtt_client.subscribe(light_topic)
mqtt_client.on_message = call_back

while True:
    time.sleep(2)