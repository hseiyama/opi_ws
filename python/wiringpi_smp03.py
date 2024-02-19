import wiringpi
from wiringpi import GPIO
import time

# PIN_PWM
PIN_PWM2 = 22

def main():
    # initialize
    wiringpi.wiringPiSetup()
    # gpio mode <pin> pwm
    wiringpi.pinMode(PIN_PWM2, GPIO.PWM_OUTPUT)
    # gpio pwmr <pin> <range>
    wiringpi.pwmSetRange(PIN_PWM2, 1024)
    # gpio pwmc <pin> <clock>
    wiringpi.pwmSetClock(PIN_PWM2, 1)
    # gpio pwm <pin> <value>
    wiringpi.pwmWrite(PIN_PWM2, 512)
    time.sleep(1)
    while(True):
        for brightness in range(4, 10+1):
            wiringpi.pwmWrite(PIN_PWM2, 1 << brightness)
            time.sleep(1)
        wiringpi.pwmWrite(PIN_PWM2, 0)
        time.sleep(1)
        for brightness in range(0, 6+1):
            wiringpi.pwmWrite(PIN_PWM2, 1024 >> brightness)
            time.sleep(1)
        wiringpi.pwmWrite(PIN_PWM2, 1024)
        time.sleep(1)

if __name__ == '__main__':
    main()
