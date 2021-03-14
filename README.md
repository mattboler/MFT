# MFT

A minimal feature tracker for visual or visual-inertial systems.

The ROS interface subscribes to a ```sensor_msgs::Image``` and publishes 
a ```sensor_msgs::PointCloud``` where the channels are as follows:

1. Feature ID
2. Feature age
3. Feature u coordinate
4. Feature v coordinate

## Dependencies

* OpenCV (Written and tested with 4.2.0)
* ROS (Written and tested with ROS Noetic on Ubuntu 20.04)

## Installation

```>> git clone https://github.com/mattboler/mft```

```>> catkin build```

## Usage

```roslaunch mft <your launch file>```