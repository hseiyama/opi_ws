#include <wiringPi.h>
#include <stdio.h>

int main (void)
{
    unsigned char pin_value;
    wiringPiSetup();
//    pinMode(2, OUTPUT);
//    digitalWrite(2, LOW);
    pinMode(2, INPUT);
    pullUpDnControl(2, PUD_UP);
    while(TRUE) {
        pin_value = digitalRead(2);
        printf("pin_value = %d\n",pin_value);

        delay(1000);
    }

    return 0;
}
