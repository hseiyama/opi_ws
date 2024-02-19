#!/bin/bash

# PIN_SW
readonly PIN_SW0=5
readonly PIN_SW1=7
readonly PIN_SW2=8
readonly PIN_SW3=11
# PIN_LED
readonly PIN_LED0=12
readonly PIN_LED1=14
readonly PIN_LED2=17
readonly PIN_LED3=19
readonly PIN_LED4=20
readonly PIN_LED5=22
readonly PIN_LED6=23
readonly PIN_LED7=25

count_value=0

function set_pinInput() {
    gpio mode $1 in
    gpio mode $1 up
}

function set_pinOutput() {
    gpio mode $1 out
    gpio write $1 0
}

function setup() {
    # input setting
    set_pinInput $PIN_SW0
    set_pinInput $PIN_SW1
    set_pinInput $PIN_SW2
    set_pinInput $PIN_SW3
    # output setting
    set_pinOutput $PIN_LED0
    set_pinOutput $PIN_LED1
    set_pinOutput $PIN_LED2
    set_pinOutput $PIN_LED3
    set_pinOutput $PIN_LED4
    set_pinOutput $PIN_LED5
    set_pinOutput $PIN_LED6
    set_pinOutput $PIN_LED7
}

function loop_1s() {
    # main process
    led4_value=$((($count_value & 0x01) != 0x00))
    led5_value=$((($count_value & 0x02) != 0x00))
    led6_value=$((($count_value & 0x04) != 0x00))
    led7_value=$((($count_value & 0x08) != 0x00))
    # output process
    gpio write $PIN_LED4 $led4_value
    gpio write $PIN_LED5 $led5_value
    gpio write $PIN_LED6 $led6_value
    gpio write $PIN_LED7 $led7_value
    count_value=$(($count_value + 1))
}

function loop() {
    # input process
    sw0_value=$(gpio read $PIN_SW0)
    sw1_value=$(gpio read $PIN_SW1)
    sw2_value=$(gpio read $PIN_SW2)
    sw3_value=$(gpio read $PIN_SW3)
    # main process
    led0_value=$sw0_value;
    led1_value=$sw1_value;
    led2_value=$sw2_value;
    led3_value=$sw3_value;
    # output process
    gpio write $PIN_LED0 $led0_value
    gpio write $PIN_LED1 $led1_value
    gpio write $PIN_LED2 $led2_value
    gpio write $PIN_LED3 $led3_value
}

function main () {
    loop_count=0
    # setup process
    setup
    while :
    do
        loop_count=$(($loop_count + 1))
        # loop process
        loop
        # 100 counts is very slow, so adjust it
        # if [ $loop_count -ge 100 ]; then
        if [ $loop_count -ge 23 ]; then
            loop_count=0
            loop_1s
        fi
        # wait
        sleep 0.01s
    done

    return 0
}

main
