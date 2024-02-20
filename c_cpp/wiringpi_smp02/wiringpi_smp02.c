#include <stdio.h>
#include <wiringPi.h>

typedef unsigned char uint8;
typedef unsigned short uint16;

/* PIN_SW */
#define PIN_SW0 5
#define PIN_SW1 7
#define PIN_SW2 8
#define PIN_SW3 11
/* PIN_LED */
#define PIN_LED0 12
#define PIN_LED1 14
#define PIN_LED2 17
#define PIN_LED3 19
#define PIN_LED4 20
#define PIN_LED5 22
#define PIN_LED6 23
#define PIN_LED7 25

uint8 count_value = 0;

void set_pinInput(int pin) {
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);
}

void set_pinOutput(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void setup(void) {
    /* initialize */
    wiringPiSetup();
    /* input setting */
    set_pinInput(PIN_SW0);
    set_pinInput(PIN_SW1);
    set_pinInput(PIN_SW2);
    set_pinInput(PIN_SW3);
    /* output setting */
    set_pinOutput(PIN_LED0);
    set_pinOutput(PIN_LED1);
    set_pinOutput(PIN_LED2);
    set_pinOutput(PIN_LED3);
    set_pinOutput(PIN_LED4);
    set_pinOutput(PIN_LED5);
    set_pinOutput(PIN_LED6);
    set_pinOutput(PIN_LED7);
}

void loop_1s(void) {
    /* main process */
    uint8 led4_value = (count_value & 0x01) != 0x00;
    uint8 led5_value = (count_value & 0x02) != 0x00;
    uint8 led6_value = (count_value & 0x04) != 0x00;
    uint8 led7_value = (count_value & 0x08) != 0x00;
    /* output process */
    digitalWrite(PIN_LED4, led4_value);
    digitalWrite(PIN_LED5, led5_value);
    digitalWrite(PIN_LED6, led6_value);
    digitalWrite(PIN_LED7, led7_value);
    count_value = count_value + 1;
}

void loop(void) {
    /* input process */
    uint8 sw0_value = digitalRead(PIN_SW0);
    uint8 sw1_value = digitalRead(PIN_SW1);
    uint8 sw2_value = digitalRead(PIN_SW2);
    uint8 sw3_value = digitalRead(PIN_SW3);
    /* main process */
    uint8 led0_value = sw0_value;
    uint8 led1_value = sw1_value;
    uint8 led2_value = sw2_value;
    uint8 led3_value = sw3_value;
    /* output process */
    digitalWrite(PIN_LED0, led0_value);
    digitalWrite(PIN_LED1, led1_value);
    digitalWrite(PIN_LED2, led2_value);
    digitalWrite(PIN_LED3, led3_value);
}

int main(void) {
    uint16 loop_count = 0;
    /* setup process */
    setup();
    while(TRUE) {
        loop_count = loop_count + 1;
        /* loop process */
        loop();
        if(loop_count >= 100) {
            loop_count = 0;
            loop_1s();
        }
        /* wait */
        delay(10);
    }

    return 0;
}
