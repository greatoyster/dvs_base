# The `dvs_base`: header only event-base vision toolkit and prototyping system 

Some **generic** and relatively **stable** code about event-based vision from daily research and open source repositories, intergrated in ROS framework.

# Current Plan

- Single and packed event representation

- Event temporal-spatial representation

- Generic trajectory representation

- Geometry transform representation

- IO function with numpy interface

- Experiment system

- Generic motion model representation

- Generic Gradient descent solver

# Future Plan

- Embedded visualization code in C++ and related RViz plugin

# Finished Part

 Installation

```shell
mkdir -p catkin_ws/src
cd catkin_ws
catkin init
catkin config --extend /opt/ros/melodic --cmake-args -DCMAKE_BUILD_TYPE=Release

sudo apt-get install python-vcstool
cd src
git clone https://github.com/greatoyster/dvs_base.git
vcs-import < dvs_base/dependencies.yaml

cd ..
catkin_make
source ./devel/setup.bash
```

# Developer suggestions

```shell script
astyle --style=google -R -n ./*.cpp,*.h,*.hpp,*.c
```

# Possible compile problem solution

https://github.com/ethz-asl/lidar_align/issues/16

```shell script
sudo mv /usr/include/flann/ext/lz4.h /usr/include/flann/ext/lz4.h.bak
sudo mv /usr/include/flann/ext/lz4hc.h /usr/include/flann/ext/lz4.h.bak
sudo ln -s /usr/include/lz4.h /usr/include/flann/ext/lz4.h
sudo ln -s /usr/include/lz4hc.h /usr/include/flann/ext/lz4hc.h
```


