import paho.mqtt.client as paho
import os
from sktime.base import load
import json
import numpy as np
import time

model = load("trained_ECG_model")

def HeartRatePrediction(p):
    if p == 0.0:
        return "Normal beat"
    elif p == 1.0:
         return "Supraventricular premature beat"
    elif p == 2.0:
         return "Premature ventricular contraction"
    elif p == 3.0:
         return " Fusion of ventricular and normal beat"
    else:
         return "Unclassifiable beat"

# print which topic was subscribed to
def on_subscribe(client, userdata, mid, granted_qos, properties=None):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))


current_data = []

# setting callbacks for different events to see if it works, print the message etc.
def on_connect(client, userdata, flags, rc, properties=None):
    print("CONNACK received with code %s." % rc)

# print message, useful for checking if it was successful
def on_message(client, userdata, msg):
    global current_data
    data = json.loads(str(msg.payload.decode("utf-8")))
    print(data)
    current_data.append(data)
    ## Once the data collection gets to 187, we can start predicting
    ## Then remove it and the data will gather 187 more points for the next prediction
    print(len(current_data))
    if len(current_data) == 187:
        np_array = np.array(current_data)
        np_array = np_array[np.newaxis, ...]
        prediction = model.predict(np_array)[0]
        print("Model is predicting: ", prediction)
        client.publish(
           "ECG/predicted_state",
            payload= HeartRatePrediction(prediction),
        )
        if prediction == 1.0 or prediction == 4.0:
            client.publish(
                # "ECG/data",
                "driverState/",
            payload=True,
            )
        del current_data[0:187]

client = paho.Client()
client.on_connect = on_connect

client.connect('broker.hivemq.com')
client.on_subscribe = on_subscribe
client.on_message = on_message

client.subscribe("NTI_10/heartRate")

client.loop_forever()

# while True:
#     time.sleep(2)