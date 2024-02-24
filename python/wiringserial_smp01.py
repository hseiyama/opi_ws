import wiringpi
import sys
import time

def main():
    # initialize
    # wiringpi.wiringPiSetup()
    serial = wiringpi.serialOpen("/dev/ttyS5", 115200)
    if(serial < 0):
        print("Unable to open serial device.", file=sys.stderr)
        sys.exit(1)

    # main process
    wiringpi.serialPuts(serial, "\r\n")
    wiringpi.serialPuts(serial, "Start loop back.\r\n")
    while(True):
        data_avail = wiringpi.serialDataAvail(serial)
        if(data_avail > 0):
            character = wiringpi.serialGetchar(serial)
            if(character == 0x1b):
                break
            wiringpi.serialPutchar(serial, character)
        time.sleep(0.01)
    wiringpi.serialPuts(serial, "\r\n")
    wiringpi.serialPuts(serial, "End loop back.\r\n")
    wiringpi.serialClose(serial)

    sys.exit(0)

if(__name__ == "__main__"):
    main()
