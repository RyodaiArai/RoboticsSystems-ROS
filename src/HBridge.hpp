#ifndef HBRIDGE_H
#define HBRIDGE_H

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <pigpiod_if2.h>

class HBridge
{
private:
    int pi_;
    int pin_in1_;
    int pin_in2_;
    int pin_pwm_;
    int type_;

public:
    HBridge()
    {
    }

    void setPin(int pi, int pin_in1, int pin_in2, int pin_pwm)
    {
        pi_ = pi;
        pin_in1_ = pin_in1;
        pin_in2_ = pin_in2;
        pin_pwm_ = pin_pwm;

        type_ = 0;

        set_mode(pi_, pin_in1_, PI_OUTPUT);
        set_mode(pi_, pin_in2_, PI_OUTPUT);
        set_mode(pi_, pin_pwm_, PI_OUTPUT);
    }

    void setPin(int pi, int pin_in1, int pin_in2)
    {
        pi_ = pi;
        pin_in1_ = pin_in1;
        pin_in2_ = pin_in2;

        type_ = 1;

        set_mode(pi_, pin_in1_, PI_OUTPUT);
        set_mode(pi_, pin_in2_, PI_OUTPUT);
    }

    void drive(int power)
    {
        switch (type_)
        {
        case 0:

            if (power > 0)
            {
                gpio_write(pi_, pin_in1_, 1);
                gpio_write(pi_, pin_in2_, 0);
            }
            else
            {
                gpio_write(pi_, pin_in1_, 0);
                gpio_write(pi_, pin_in2_, 1);
                power = -power;
            }
            set_PWM_dutycycle(pi_, pin_pwm_, power);
            break;

        case 1:

            if (power > 0)
            {
                set_PWM_dutycycle(pi_, pin_in1_, power);
                gpio_write(pi_, pin_in2_, 0);
            }
            else
            {
                power = -power;
                gpio_write(pi_, pin_in1_, 0);
                set_PWM_dutycycle(pi_, pin_in2_, power);
            }
            break;
        }
    }
};

#endif