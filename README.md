<p align="center">
  <img src="https://imgur.com/EFZqWFS.png"/>
</p>

![PlatformIO CI](https://github.com/hyphenspace/spiral-launchpad/workflows/PlatformIO%20CI/badge.svg)

## Launch System
The launch system consists of the controller and the launchpad. The controller sends a start signal directly to the launchpad. And if no abort is triggered, then after the countdown timer is complete, the controller sends another signal that will start the launch sequence, releasing the clamps and igniting the rockets motor.

<img src="https://imgur.com/3sHSgjb.jpg" alt="GroudSystem" width="500" height="500" />

# Directory Structure
* controller -- Code that handles communication with launchpad
* launchpad -- Code that controls the holddown sequence and ignition of rocket motor
