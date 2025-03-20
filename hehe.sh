#!/bin/bash
CHANNEL=2
CHIP=pwmchip2
PWM=pwm$CHANNEL

echo $CHANNEL > /sys/class/pwm/$CHIP/export
sleep 1
echo 240000 > /sys/class/pwm/$CHIP/$PWM/period
echo 120000 > /sys/class/pwm/$CHIP/$PWM/duty_cycle
echo 1 > /sys/class/pwm/$CHIP/$PWM/enable