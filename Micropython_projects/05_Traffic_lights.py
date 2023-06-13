from machine import Pin
import time

led_red = machine.Pin(16, machine.Pin.OUT)
led_yellow = machine.Pin(17, machine.Pin.OUT)
led_green = machine.Pin(18, machine.Pin.OUT)

while True:
    led_red.value(1)
    time.sleep(5)  
    led_red.value(0) 
    led_yellow.value(1)
    time.sleep(0.5)
    led_yellow.value(0)
    time.sleep(0.5)
    led_yellow.value(1)
    time.sleep(0.5)
    led_yellow.value(0)
    time.sleep(0.5)
    led_yellow.value(1)
    time.sleep(0.5)
    led_yellow.value(0)
    time.sleep(0.5)
    led_green.value(1)
    time.sleep(5) 
    led_green.value(0) 