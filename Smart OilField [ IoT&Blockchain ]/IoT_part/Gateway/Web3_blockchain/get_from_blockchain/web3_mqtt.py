import time
import json
import paho.mqtt.client as mqtt

id = 'ahmed@Allawy_2023'
client_name = id + 'nightlight_virtual_client'
blockchain_topic = '/light' # take this from blockchain payload

mqtt_client = mqtt.Client(client_name)
mqtt_client.connect('127.0.0.1')

light = 6 # take this from blockchain payload
print('Light level:', light)
mqtt_client.publish(blockchain_topic, json.dumps({'light' : light}))
