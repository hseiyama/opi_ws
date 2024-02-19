#!/bin/bash

# PIN_PWM
readonly PIN_PWM2=22

function main () {
    # gpio mode <pin> pwm
    gpio mode $PIN_PWM2 pwm
    # gpio pwmr <pin> <range>
    gpio pwmr $PIN_PWM2 1024
    # gpio pwmc <pin> <clock>
    gpio pwmc $PIN_PWM2 1
    # gpio pwm <pin> <value>
    gpio pwm $PIN_PWM2 512
    sleep 1s
    while :
    do
        for brightness in {4..10}
        do
            gpio pwm $PIN_PWM2 $((1 << $brightness))
            sleep 1s
        done
        gpio pwm $PIN_PWM2 0
        sleep 1s
        for brightness in {0..6}
        do
            gpio pwm $PIN_PWM2 $((1024 >> $brightness))
            sleep 1s
        done
        gpio pwm $PIN_PWM2 1024
        sleep 1s
    done

    return 0
}

main
