#!/bin/env/python
import time

lastMillis = 0
measurements = 0
avg = 0

while True:
    millis = input()
    if millis.isspace() or millis == "":
        continue
    millis = int(millis)
    if (millis > 30000):
        break
while True:
    millis = input()
    if millis.isspace() or millis == "":
        continue
    millis = int(millis)
    if (millis < 5000):
        break
while True:
    millis = input()
    if millis.isspace() or millis == "":
        continue
    measurements+=1
    millis = int(millis)
    pulseLength = millis - lastMillis
    lastMillis = millis
    speed = 0.6666666666666 / (pulseLength / 1000)
    avg = (avg*(measurements-1)+speed)/measurements
    print(str(millis/1000) + " " + str(speed) + " " + str(avg))
    
