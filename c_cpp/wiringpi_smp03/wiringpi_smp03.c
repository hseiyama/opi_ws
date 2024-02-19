#include <wiringPi.h>
#include <stdio.h>

typedef unsigned char uint8;
typedef unsigned short uint16;

/* PIN_PWM */
#define PIN_PWM2 22

int main (void) {
    uint16 brightness;
    /* initialize */
    wiringPiSetup();
    /* gpio mode <pin> pwm */
    pinMode(PIN_PWM2, PWM_OUTPUT);
    /* gpio pwmr <pin> <range> */
    pwmSetRange(PIN_PWM2, 1024);
    /* gpio pwmc <pin> <clock> */
    pwmSetClock(PIN_PWM2, 1);
    /* gpio pwm <pin> <value> */
    pwmWrite(PIN_PWM2, 512);
    delay(1000);
    while(TRUE) {
        for(brightness=4; brightness<=10; brightness++) {
            pwmWrite(PIN_PWM2, 1 << brightness);
            delay(1000);
        }
        pwmWrite(PIN_PWM2, 0);
        delay(1000);
        for(brightness=0; brightness<=6; brightness++) {
            pwmWrite(PIN_PWM2, 1024 >> brightness);
            delay(1000);
        }
        pwmWrite(PIN_PWM2, 1024);
        delay(1000);
    }

    return 0;
}
