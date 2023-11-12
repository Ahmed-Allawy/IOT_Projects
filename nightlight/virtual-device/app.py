import time
from counterfit_connection import CounterFitConnection
from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
from counterfit_shims_grove.grove_led import GroveLed
import json
import paho.mqtt.client as mqtt


CounterFitConnection.init('127.0.0.1', 5000)

light_sensor = GroveLightSensor(0)
led = GroveLed(5)


id = 'ahmed@Allawy_2023'

client_name = id + 'nightlight_virtual_client'
light_topic = id + '/light'
command_topic = id + '/commands'

mqtt_client = mqtt.Client(client_name)
mqtt_client.connect('test.mosquitto.org')

mqtt_client.loop_start()

def call_back(client, userdata, message):
    payload = json.loads(message.payload.decode())
    print("Message received:", payload)

    if payload['led_on']:
        led.on()
    else:
        led.off()

mqtt_client.subscribe(command_topic)
mqtt_client.on_message = call_back

while True:
    light = light_sensor.light
    print('Light level:', light)

    mqtt_client.publish(light_topic, json.dumps({'light' : light}))
    time.sleep(5)