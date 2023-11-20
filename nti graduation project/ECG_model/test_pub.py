import paho.mqtt.client as paho
import os
import json
import time
from counterfit_connection import CounterFitConnection
CounterFitConnection.init('127.0.0.1', 5000)
from counterfit_shims_grove.adc import ADC
from counterfit_shims_seeed_python_dht import DHT

sendECG = False
sensor = DHT("11", 5)
weight = ADC()
data = [1.0,
 0.8333333134651184,
 0.45277777314186096,
 0.0,
 0.16111111640930176,
 0.2916666567325592,
 0.38333332538604736,
 0.3861111104488373,
 0.4333333373069763,
 0.4166666567325592,
 0.4583333432674408,
 0.44999998807907104,
 0.4722222089767456,
 0.48055556416511536,
 0.5222222208976746,
 0.5388888716697693,
 0.5722222328186035,
 0.6138888597488403,
 0.6416666507720947,
 0.6416666507720947,
 0.675000011920929,
 0.6555555462837219,
 0.6777777671813965,
 0.6277777552604675,
 0.6083333492279053,
 0.5611110925674438,
 0.5361111164093018,
 0.49444442987442017,
 0.4694444537162781,
 0.4166666567325592,
 0.43611112236976624,
 0.4194444417953491,
 0.42500001192092896,
 0.39722222089767456,
 0.4277777671813965,
 0.42222222685813904,
 0.4333333373069763,
 0.4055555462837219,
 0.4416666626930237,
 0.4472222328186035,
 0.46388888359069824,
 0.4694444537162781,
 0.4694444537162781,
 0.4305555522441864,
 0.4277777671813965,
 0.4194444417953491,
 0.4194444417953491,
 0.39444443583488464,
 0.41111111640930176,
 0.39722222089767456,
 0.4027777910232544,
 0.39722222089767456,
 0.4138889014720917,
 0.39722222089767456,
 0.42500001192092896,
 0.39722222089767456,
 0.40833333134651184,
 0.4027777910232544,
 0.42500001192092896,
 0.4000000059604645,
 0.42222222685813904,
 0.574999988079071,
 0.7972221970558167,
 0.9666666388511655,
 0.8166666626930237,
 0.4000000059604645,
 0.04444444552063941,
 0.16388888657093048,
 0.3083333373069763,
 0.375,
 0.42222222685813904,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0,
 0.0]


def on_connect(client, userdata, flags, rc, properties=None):
    print("CONNACK received with code %s." % rc)


def on_subscribe(client, userdata, mid, granted_qos, properties=None):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))


def on_message(callBack_client, userdata, msg):
    global sendECG
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    if msg.topic =="NTI_10/get_ecg":
        sendECG=True
        print("ecg = "+str(sendECG))
        # client.subscribe("ECG/predicted_state")
        # client.subscribe("NTI_10/get_ecg")


client = paho.Client()
client.on_connect = on_connect
client.connect('broker.hivemq.com')
# client.connect('test.mosquitto.org')
client.on_subscribe = on_subscribe
client.on_message = on_message

client.subscribe("ECG/predicted_state")
client.subscribe("NTI_10/get_ecg")

client.loop_start()

while True:
    if client.is_connected():
        temp = CounterFitConnection.get_sensor_float_value(6)
        client.publish(
                # "ECG/data",
                "NTI_10/temperature",
            payload=temp,
            )
        print("temperature = "+str(temp))
        hum = CounterFitConnection.get_sensor_float_value(5)
        client.publish(
                # "ECG/data",
                "NTI_10/humidity",
            payload=hum,
            )
        print("humidity = "+str(hum))
        weightValue = weight.read(0)
        client.publish(
                # "ECG/data",
                "NTI_10/weight",
            payload=weightValue,
            )
        print("weight = "+str(weightValue))
        if weightValue<30 or temp>60:
             client.publish(
                # "ECG/data",
                "driverState/",
            payload=True,
            )
        if sendECG:
            count=0
            while count<187:
                client.publish(
                    # "ECG/data",
                    "NTI_10/heartRate",
                payload=data[count],
                )
                print(data[count])
                count=count+1
                time.sleep(0.5)
            sendECG=False
    time.sleep(5)