# ros-pi-camera-interface
ROS package for handling communication with the Pi Camera



ROS Nodes:

- talker.py: 
runs on the robot, captures the image flow from the Raspberry pi integrated camera and publishes the images on its topic. Also reads the Serial port for incoming informations about the brightness level, eventually adapting the image before uploading it.

- listener.py:
runs on the remote computer, displays the captured image as it is

- mask_listener.py:
runs on the remote computer, displays the red masked image published on red_mask_topic

- grey_listener.py:
runs on the remote computer, displays the greyscale masked image published on grey_scale_topic



Arduino Code:

- photoResistor.ino:
reads the value of an analogic photoresistor and sends it to the Raspberry over the Serial port (USB)
