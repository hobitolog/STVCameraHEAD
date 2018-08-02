<<<<<<< HEAD
## STVCameraHEAD

SpacjaTV Camera head project.

---

## Overview

Project design is to create Opensource

=======
# STVCameraHEAD
In this project we control the movement of two step motors using the Arduino Uno R3. It is possible 
to do it with the joystick or via webpage. The project is design in such a way that none of the user's 
inputs or power blackouts can destabilize the system or tangle the wires.

## Getting Started
In order to use the STVCameraHEAD we just need to download:
- [the Arduino IDE](https://www.arduino.cc/en/Main/Software)
- [the code](adres)

Then we must open it with downloaded earlier environment, connect the ethernet cable to the Arduino board, power up the hardware components and run the program.

## IP Confuguration
We are able to control the STVCameraHOLDER with a web iterface only when the ip implemented in the code corresponds 
to the router which ethernet cable is connected to the Arduino UNO R3. The initial code correlates to the router in Spacja TV office.
In case of connecting out system to the new network we need to check the ip of the current router. We can do it in two ways:
- manually (it should be somewhere on the router's case, usually on the bottom)
- by the sowtware (this depends on the operating system):
1. *WINDOWS* - open cmd -> call ipconfig -> read the network gateway
2. *LINUX* - open terminal -> call ip a -> read the network gateway

## Built With
- [Accelstepper.h](https://www.arduinolibraries.info/libraries/accel-stepper)
- [Multistepper.h](http://www.airspayce.com/mikem/arduino/AccelStepper/classMultiStepper.html)
- [Ethernet.h](https://www.arduinolibraries.info/libraries/ethernet)
- [SPI.h](https://www.arduino.cc/en/Reference/SPI)
- [SD.h](https://www.arduino.cc/en/Reference/SD)

## License
This project is licensed under the MIT License. The licence should be downloaded with the github code, if not you can find it [here.](https://github.com/hobitolog/STVCameraHEAD/blob/master/LICENSE)

## Authors
- Adam Banaszczyk
- Krzysztof Stężała
>>>>>>> da6f0dd29aeaab37f5d621bebf5380e3e1966067
