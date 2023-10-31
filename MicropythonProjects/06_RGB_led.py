# import Pin, PWM and Random function modules.
from machine import Pin, PWM
from random import randint
import time

# configura o ouput mode das portas GP 12, 13, 14
# PWM frequency em 10000Hz.
pins = [12, 13, 14]
freq_num = 10000

pwm0 = PWM(Pin(pins[0]))  # set PWM
pwm1 = PWM(Pin(pins[1]))
pwm2 = PWM(Pin(pins[2]))
pwm0.freq(freq_num)
pwm1.freq(freq_num)
pwm2.freq(freq_num)


# define a função para definir a cor do led RGB
def setColor():
    # O case serviu para testar se os diodos estão funcionando separadamente e
    # no random
    case = 3
    if case == 0:
        pwm0.duty_u16(65535)
        pwm1.duty_u16(0)
        pwm2.duty_u16(0)
    elif case == 1:
        pwm0.duty_u16(0)
        pwm1.duty_u16(65535)
        pwm2.duty_u16(0)

    elif case == 2:
        pwm0.duty_u16(0)
        pwm1.duty_u16(0)
        pwm2.duty_u16(65535)

    elif case == 3:
        red = randint(500, 65535)
        green = randint(500, 65535)
        blue = randint(500, 65535)

        pwm0.duty_u16(65535 - red)
        pwm1.duty_u16(65535 - green)
        pwm2.duty_u16(65535 - blue)


try:
    while True:
        setColor()
        time.sleep_ms(200)
except:
    pwm0.deinit()
    pwm1.deinit()
    pwm2.deinit()
