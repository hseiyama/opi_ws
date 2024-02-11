import wiringpi
from wiringpi import GPIO
import time

# PIN_SW
PIN_SW0 = 5
PIN_SW1 = 7
PIN_SW2 = 8
PIN_SW3 = 11
# PIN_LED
PIN_LED0 = 12
PIN_LED1 = 14
PIN_LED2 = 17
PIN_LED3 = 19
PIN_LED4 = 20
PIN_LED5 = 22
PIN_LED6 = 23
PIN_LED7 = 25

count_value = 0

def set_pinInput(pin):
    wiringpi.pinMode(pin, GPIO.INPUT)
    wiringpi.pullUpDnControl(pin, GPIO.PUD_UP)

def set_pinOutput(pin):
    wiringpi.pinMode(pin, GPIO.OUTPUT)
    wiringpi.digitalWrite(pin, GPIO.LOW)

def setup():
    # initialize
    wiringpi.wiringPiSetup()
    # input setting
    set_pinInput(PIN_SW0)
    set_pinInput(PIN_SW1)
    set_pinInput(PIN_SW2)
    set_pinInput(PIN_SW3)
    # output setting
    set_pinOutput(PIN_LED0)
    set_pinOutput(PIN_LED1)
    set_pinOutput(PIN_LED2)
    set_pinOutput(PIN_LED3)
    set_pinOutput(PIN_LED4)
    set_pinOutput(PIN_LED5)
    set_pinOutput(PIN_LED6)
    set_pinOutput(PIN_LED7)

def loop_1s():
    global count_value
    # main process
    led4_value = (count_value & 0x01) != 0x00
    led5_value = (count_value & 0x02) != 0x00
    led6_value = (count_value & 0x04) != 0x00
    led7_value = (count_value & 0x08) != 0x00
    # output process
    wiringpi.digitalWrite(PIN_LED4, led4_value)
    wiringpi.digitalWrite(PIN_LED5, led5_value)
    wiringpi.digitalWrite(PIN_LED6, led6_value)
    wiringpi.digitalWrite(PIN_LED7, led7_value)
    count_value = count_value + 1

def loop():
    # input process
    sw0_value = wiringpi.digitalRead(PIN_SW0)
    sw1_value = wiringpi.digitalRead(PIN_SW1)
    sw2_value = wiringpi.digitalRead(PIN_SW2)
    sw3_value = wiringpi.digitalRead(PIN_SW3)
    # main process
    led0_value = sw0_value
    led1_value = sw1_value
    led2_value = sw2_value
    led3_value = sw3_value
    # output process
    wiringpi.digitalWrite(PIN_LED0, led0_value)
    wiringpi.digitalWrite(PIN_LED1, led1_value)
    wiringpi.digitalWrite(PIN_LED2, led2_value)
    wiringpi.digitalWrite(PIN_LED3, led3_value)

def main():
    loop_count = 0
    # setup process
    setup()
    while(True):
        loop_count = loop_count + 1
        # loop process
        loop()
        if loop_count >= 100:
            loop_count = 0
            loop_1s()
        # wait
        time.sleep(0.01)

if __name__ == '__main__':
    main()
