import json
import time

import paho.mqtt.client as mqtt

from os import path
import csv
from datetime import datetime

id = 'ahmed@Allawy_2023'

client_name = id + 'temperature_sensor_server'
temperature_topic = id + '/temperature'

mqtt_client = mqtt.Client(client_name)
mqtt_client.connect('test.mosquitto.org')

mqtt_client.loop_start()

# csv headers
temperature_file_name = 'temperature.csv'
fieldnames = ['date', 'temperature']

# open csv file or create it and set headers
if not path.exists(temperature_file_name):
    with open(temperature_file_name, mode='w', newline='') as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()

def call_back(client, userdata, message):
    payload = json.loads(message.payload.decode())
    print("Message received:", payload)

    with open(temperature_file_name, mode='a', newline='') as temperature_file:        
        temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
        temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})

mqtt_client.subscribe(temperature_topic)
mqtt_client.on_message = call_back

while True:
    time.sleep(2)