import time
from gpiozero import PWMOutputDevice, DigitalOutputDevice #Chane to pigpio

# Define motor driver pins
PWM_PIN = 18  # Change according to your setup
DIR_PIN = 23  # Direction control pin

# Initialize motor control
pwm = PWMOutputDevice(PWM_PIN, frequency=20000)  # 20KHz PWM
direction = DigitalOutputDevice(DIR_PIN)

# Set motor direction (1 for forward, 0 for reverse)
direction.on()  # Use `direction.off()` for reverse

# Ramp speed from 0% to 100% over 3 seconds
duration = 3  # seconds
steps = 100  # Number of steps
step_delay = duration / steps

try:
    for duty_cycle in range(0, 101, 1):
        pwm.value = duty_cycle / 100  # Scale to 0-1 range
        time.sleep(step_delay)
finally:
    pwm.value = 0  # Stop motor
