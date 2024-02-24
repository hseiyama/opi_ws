#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(void) {
    /* initialize */
    // wiringPiSetup();
    int serial = serialOpen("/dev/ttyS5", 115200);
    if(serial < 0) {
        fprintf(stderr, "Unable to open serial device.\n");
        return 1;
    }

    /* main process */
    serialPuts(serial, "\r\n");
    serialPuts(serial, "Start loop back.\r\n");
    while(TRUE) {
        int data_avail = serialDataAvail(serial);
        if(data_avail > 0) {
            int character = serialGetchar(serial);
            if(character == 0x1b) {
                break;
            }
            serialPutchar(serial, character);
        }
        delay(10);
    }
    serialPuts(serial, "\r\n");
    serialPuts(serial, "End loop back.\r\n");
    serialClose(serial);

    return 0;
}
