#!/bin/bash

# gpio mode 2 out
# gpio write 2 0
gpio mode 2 in
gpio mode 2 down
while :
do
    pin_value=$(gpio read 2)
    echo pin_value = $pin_value
    sleep 1
done
