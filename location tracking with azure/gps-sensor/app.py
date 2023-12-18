from counterfit_connection import CounterFitConnection
CounterFitConnection.init('127.0.0.1', 5000)
import time
import datetime
import counterfit_shims_serial
import json
from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse

connection_string = ' '

# serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')

device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

print('Connecting')
device_client.connect()
print('Connected')

def handle_method_request(request):
    print("Direct method received - ", request.name)
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)

device_client.on_method_request_received = handle_method_request

def get_correct_direction(latitude_direction, longitude_direction):
    lat, lon =1,1
    if latitude_direction == 'S':
            lat =-1
    if longitude_direction == 'W':
        lon =-1
    return lat, lon

def decode_time_string(time_string):
    hours = int(time_string[:2])
    minutes = int(time_string[2:4])
    seconds = int(time_string[4:6])
    milliseconds = int(time_string[7:])
    time = datetime.time(hours, minutes, seconds, milliseconds * 1000)
    return time

def decode_gps_data(gpgga_string):
    fields = gpgga_string.split(',')

    # Decoding message identifier
    message_identifier = fields[0][1:]

    # Decoding time
    time_string = fields[1]
    time = decode_time_string(time_string)

    # Decoding latitude
    latitude = float(fields[2])/100
    latitude_direction = fields[3]
    # Decoding longitude
    longitude = float(fields[4])/100
    longitude_direction = fields[5]

    # Decoding GPS fix quality and number of satellites
    fix_quality = int(fields[6])
    satellites_tracked = int(fields[7])

    # Decoding altitude
    altitude = float(fields[9])
    altitude_unit = fields[10]

    # Decoding height above geoid
    height_geoid = float(fields[11])
    height_geoid_unit = fields[12]

    # Get correct direction
    lat, lon = get_correct_direction(latitude_direction, longitude_direction)

    # Creating a dictionary object
    gps_data = {
        'message_identifier':message_identifier,
        'time': str(time),
        'latitude': latitude*lat,
        'longitude':longitude*lon,
        'fix_quality': fix_quality,
        'satellites_tracked': satellites_tracked,
        'altitude': altitude,
        'altitude_unit': altitude_unit,
        'height_geoid': height_geoid,
        'height_geoid_unit': height_geoid_unit
    }

    return gps_data

gps_data_example = [[
          30.291642728655546,
          31.24762181573722
        ], [
          30.532699226209587,
          31.264794191498467
        ], [
          30.75366768230083,
          31.264794191498467
        ],[
          30.974636138392015,
          31.135925283182146
        ], [
          31.014812221317698,
          30.912137400969797
        ], [
          31.05498830424341,
          30.722368586271102
        ],[
          31.165472532288987,
          30.635986229525656
        ],[
          30.543208880305656,
          31.28292030959652
        ],  [
          31.286000781066065,
          30.558176098738585
        ],]
count = 0
while True:
    # line = serial.readline().decode('utf-8')

    # while len(line) > 0:
    #     gps_data = decode_gps_data(line)
    #     line = serial.readline().decode('utf-8')
    #     message_json = { "gps" : { "lat":gps_data["latitude"], "lon":gps_data["longitude"] } }
    #     print("Sending telemetry", message_json)
    #     message = Message(json.dumps(message_json))
    #     device_client.send_message(message)
    
    message_json = { "gps" : { "lat":gps_data_example[count][1], "lon":gps_data_example[count][0] } }
    print("Sending telemetry", message_json)
    message = Message(json.dumps(message_json))
    device_client.send_message(message)
    if count!=len(gps_data_example)-1:
        count = count+1
    time.sleep(60)
















#def get_data_until_comma(index):
#     data = ""
#     while line[index] != ",":
#        data = data+""+line[index]
#        index  = index+1
#     return data, index

# def get_correct_direction(latitude_direction, longitude_direction):
#     lat, lon ="",""
#     if latitude_direction == 'S':
#             lat ="-"
#     if longitude_direction == 'W':
#         lon ="-"
#     return lat, lon

# def decode_gps_data(line):
#     source  = line[1]+""+line[2]
#     type_of_message =  line[3]+""+line[4]+""+line[5]
#     current_time, index = get_data_until_comma(7)
#     latitude, index = get_data_until_comma(index+1)
#     latitude_direction, index = get_data_until_comma(index+1)
#     longitude, index = get_data_until_comma(index+1)
#     longitude_direction, index = get_data_until_comma(index+1)
#     lat, lon = get_correct_direction(latitude_direction, longitude_direction)
#     print(lon)
#     location ={
#         "source":source,
#         "type_of_message":type_of_message,
#         "current_time":current_time,
#         "latitude":lat+""+latitude,
#         "longitude":lon+""+longitude,
#     }
#     print(location)