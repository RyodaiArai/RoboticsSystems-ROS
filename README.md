# Robotics Systems-ROS

---

## Overview
This is a ROS package to control wheels with Raspberry Pi.

---

## Environment
Ubuntu Server 20.04.3 LTS (ROS: Noetic)

---

## Requirement
| Name | Quantity | Datasheet |
| :--: | :------: | :-------: |
| [Raspberry Pi 4 ModelB](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/) | 1 | [PDF](https://github.com/RyodaiArai/Robotics_Systems-Device_driver/files/7833504/raspberry-pi-4-datasheet.pdf) |
| [L298N (Motor driver)](https://www.amazon.co.jp/-/en/VKLSVAN-Stepper-Controller-Compatible-Arduino/dp/B08B87WWHV/ref=sr_1_5) | 1 | [PDF](https://github.com/RyodaiArai/Robotics_Systems-Device_driver/files/7833507/l298.pdf)
| [DC Motor with Wheel](https://www.amazon.co.jp/-/en/Treedix-Electric-Plastic-Arduino-Electronic/dp/B088NMV7C6/ref=sr_1_1) | 4 |
| AA Battery | 4 |
| [4 AA Battery Holder](https://www.amazon.com/abcGoodefg-Battery-Holder-Switch-Leads/dp/B071XTF3Z9/ref=sr_1_34) | 1 |
| Jump wire male-to-male | 1 |
| Jump wire male-to-female | 4 |

---

## Schematic
<img src="https://user-images.githubusercontent.com/71488207/148551537-0493e93f-8110-4c06-87a2-c42404b92d16.png" width="600px">

## Connection
| GPIO | L298N | Motor | Battery Holder |
| :--: | :---: | :---: | :-----: |
| 17 | IN1 |
| 18 | IN2 |
| 27 | IN3 |
| 22 | IN4 |
|| OUT1 | 2 motors+ |
|| OUT2 | 2 motors- |
|| OUT3 | 2 motors- |
|| OUT4 | 2 motors+ |
|| +12V || + (Red) |
|GND PIN | GND || - (Black) |

---

## Model
<img src="https://user-images.githubusercontent.com/71488207/148588983-0917a38b-b10c-49bf-8c56-caae8d74ad70.png" width="600px">
<img src="https://user-images.githubusercontent.com/71488207/148589209-8408da05-e588-46f1-aab9-53dfaa98a288.png" width="600px">

---

## Install & Build (catkin_make)
### Package
```
$ cd ~/catkin_ws/src
```
```
$ https://github.com/RyodaiArai/RoboticsSystems-ROS
```
```
$ cd ~/catkin_ws
```
```
$ catkin_make
```
```
$ source ~/.bashrc
```

### [pigpio](https://abyz.me.uk/rpi/pigpio/download.html)
```
$ wget https://github.com/joan2937/pigpio/archive/master.zip
```
```
$ unzip master.zip
```
```
$ cd pigpio-master
```
```
$ make
```
```
$ sudo make install
```
```
$ sudo pigpiod
```

## Usage
```
$ rosrun control_wheels wheels_listener
```
### Forward
```
$ rostopic pub -1 /robotics_systems_ros geometry_msgs/Twist  '{linear:  {x: 0.5, y: 0.0, z: 0.0}, angular: {x: 0.0,y: 0.0,z: 0.0}}'
```
### Backward
```
$ rostopic pub -1 /robotics_systems_ros geometry_msgs/Twist  '{linear:  {x: -0.5, y: 0.0, z: 0.0}, angular: {x: 0.0,y: 0.0,z: 0.0}}'
```
### Stop
```
$ rostopic pub -1 /robotics_systems_ros geometry_msgs/Twist  '{linear:  {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0,y: 0.0,z: 0.0}}'
```
### Right rotation
```
$ rostopic pub -1 /robotics_systems_ros geometry_msgs/Twist  '{linear:  {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0,y: 0.0,z: -0.5}}'
```
### Left rotation
```
$ rostopic pub -1 /robotics_systems_ros geometry_msgs/Twist  '{linear:  {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0,y: 0.0,z: 0.5}}'
```

---

## Video
[<img src="https://user-images.githubusercontent.com/71488207/149451103-a255e839-b01e-4def-95e4-d709648c2cb5.png" width="600px">](https://youtu.be/81plt-eDLuI)

Click on the image to play the video on YouTube.

---

## License
[BSD 3-Clause "New" or "Revised" License](https://github.com/RyodaiArai/Robotics_Systems-ROS/blob/main/LICENSE)

---

## References
[pigpio](https://abyz.me.uk/rpi/pigpio/download.html)

[botamochi6227 (2019)](https://github.com/botamochi6277/tamiya_cam_robot)
