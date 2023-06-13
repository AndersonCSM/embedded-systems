import time
from machine import Pin, PWM

PWM_pulsewidth = 0

pwm_led = PWM(Pin(16))

pwm_led.freq(500)

while True:
    while PWM_pulsewidth < 65535:
        PWM_pulsewidth += 50
        time.sleep_ms(1)

        pwm_led.duty_u16(PWM_pulsewidth)
    
    while PWM_pulsewidth > 0:
        PWM_pulsewidth -= 50
        time.sleep_ms(1)

        pwm_led.duty_u16(PWM_pulsewidth)
