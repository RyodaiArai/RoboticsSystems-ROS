#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <HBridge.hpp>
#include <pigpiod_if2.h>

class Wheels
{
private:
    HBridge right_;
    HBridge left_;

public:
    Wheels()
    {
    }

    void setPin(int pi, int pin_m1a, int pin_m1b, int pin_m2a, int pin_m2b)
    {
        right_.setPin(pi, pin_m1a, pin_m1b);
        left_.setPin(pi, pin_m2a, pin_m2b);
    }

    void drive(int power_r, int power_l)
    {
        right_.drive(power_r);
        left_.drive(power_l);
    }

    void twistCallback(const geometry_msgs::Twist::ConstPtr &msg)
    {
        static int pwm_r, pwm_l;
        pwm_r = 255 * (msg->linear.x + msg->angular.z);
        pwm_l = 255 * (msg->linear.x - msg->angular.z);

        if (std::abs(pwm_r) > 255)
        {
            float c = 255.0 / std::abs(pwm_r);
            pwm_r *= c;
            pwm_l *= c;
        }

        if (std::abs(pwm_l) > 255)
        {
            float c = 255.0 / std::abs(pwm_l);
            pwm_r *= c;
            pwm_l *= c;
        }

        drive(pwm_r, pwm_l);
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "wheels_listener");
    ros::NodeHandle nh;
    ros::NodeHandle node_private("~");

    int pi;
    pi = pigpio_start(NULL, NULL);

    if (pi < 0)
    {
        ROS_ERROR("cannot connect pigpiod\n");
        return -1;
    }

    int pin_ain1, pin_ain2, pin_bin1, pin_bin2;
    int pin_apwm = -1;
    int pin_bpwm = -1;

    if (!node_private.getParam("AIN1", pin_ain1))
    {
        pin_ain1 = 17;
    }

    if (!node_private.getParam("AIN2", pin_ain2))
    {
        pin_ain2 = 18;
    }

    if (!node_private.getParam("BIN1", pin_bin1))
    {
        pin_bin1 = 27;
    }

    if (!node_private.getParam("BIN2", pin_bin2))
    {
        pin_bin2 = 22;
    }

    if (node_private.getParam("PWMA", pin_apwm))
    {
    }

    if (node_private.getParam("PWMB", pin_bpwm))
    {
    }

    Wheels wheels;
    ROS_INFO("DC-MOTOR DRIVER is working");
    if (pin_apwm >= 0)
    {
    }
    
    else
    {
        wheels.setPin(pi, pin_ain1, pin_ain2, pin_bin1, pin_bin2);
        ROS_INFO("R_IN1: %02d, R_IN2: %02d, L_IN1: %02d, L_IN2: %02d", pin_ain1, pin_ain2, pin_bin1, pin_bin2);
    }

    ros::Subscriber sub = nh.subscribe("robotics_systems_ros", 1000, &Wheels::twistCallback, &wheels);
    ros::spin();

    ROS_INFO("Finish driving.");
    wheels.drive(0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    pigpio_stop(pi);

    return 0;
}