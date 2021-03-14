# MFT

A minimal feature tracker for visual or visual-inertial systems.

The ROS interface subscribes to a ```sensor_msgs::Image``` and publishes 
a ```sensor_msgs::PointCloud``` where the channels are as follows:

1. Feature ID
2. Feature age
3. Feature u coordinate
4. Feature v coordinate

## Dependencies

## Installation

```>> git clone <url>```

```>> catkin build```

## Usage

```roslaunch mft <your launch file>```