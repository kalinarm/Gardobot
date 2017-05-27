import paho.mqtt.client as mqtt
import json
import time
import serial

arduino = serial.Serial('COM7', 9600)

THINGSBOARD_HOST = "demo.thingsboard.io"
#THINGSBOARD_HOST = 'https://demo.thingsboard.io/dashboards/870c2890-4274-11e7-9e69-c7f326cba909'
ACCESS_TOKEN = 'oh66Ir7m6Pc8eBp5I1cX'


# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, rc):
    print('Connected with result code ' + str(rc))
    client.subscribe('v1/devices/me/rpc/request/+')
    # Sending current GPIO status
    #client.publish('v1/devices/me/attributes', get_gpio_status(), 1)
    
client = mqtt.Client()
# Register connect callback
client.on_connect = on_connect
# Registed publish message callback
#client.on_message = on_message
# Set access token
client.username_pw_set(ACCESS_TOKEN)
# Connect to Thingsboard using default MQTT port and 60 seconds keepalive interval
client.connect(THINGSBOARD_HOST, 1883, 60)

t = 1
while True:
    #arduino.flush()
    line = str(arduino.readline())
    line = line[2:-1].replace("\\n","").replace("\\r","")
    if isinstance(line, str):
        lines = line.split(";");
        print(line)
        if (len(lines)==4)and t%4==1:
            sensor_data = {}
            sensor_data['temperature'] = float(lines[0])
            sensor_data['humidity'] = float(lines[1])
            sensor_data['moisture'] = float(lines[2])
            sensor_data['light'] = float(lines[3])
            client.publish('v1/devices/me/telemetry', json.dumps(sensor_data), 1)
    t=t+1
    #time.sleep(1)

try:
    client.loop_forever()
except KeyboardInterrupt:
    serial.close()



