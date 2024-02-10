import wiringpi
from wiringpi import GPIO
import time

wiringpi.wiringPiSetup()
# wiringpi.pinMode(2, GPIO.OUTPUT)
# wiringpi.digitalWrite(2, GPIO.LOW)
wiringpi.pinMode(2, GPIO.INPUT)
wiringpi.pullUpDnControl(2, GPIO.PUD_DOWN)
while(True):
    pin_value = wiringpi.digitalRead(2)
    print('pin_value = ' + str(pin_value))
    time.sleep(1)
