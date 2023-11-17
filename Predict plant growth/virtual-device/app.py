from counterfit_connection import CounterFitConnection
CounterFitConnection.init('127.0.0.1', 5000)

import time
from counterfit_shims_seeed_python_dht import DHT
import paho.mqtt.client as mqtt
import json

sensor = DHT("11", 5)


id = 'ahmed@Allawy_2023'

client_name = id + 'temperature_sensor_client'
temperature_topic = id + '/temperature'

mqtt_client = mqtt.Client(client_name)
mqtt_client.connect('test.mosquitto.org')

mqtt_client.loop_start()

print("MQTT connected!")

while True:
    # humi, temp = sensor.read()
    # _, temp = sensor.read()
    temp = CounterFitConnection.get_sensor_float_value(6)
    telemetry = json.dumps({'temperature' : temp})

    print("Sending telemetry ", telemetry)

    mqtt_client.publish(temperature_topic, telemetry)

    time.sleep(10)


# from counterfit_connection import CounterFitConnection
# CounterFitConnection.init('127.0.0.1', 5000)

# import time
# from counterfit_shims_seeed_python_dht import DHT

# sensor = DHT("11", 5)

# while True:
#     humi, temp = sensor.read()
#     # print(f'Temperature {temp}°C')

#     time.sleep(10)