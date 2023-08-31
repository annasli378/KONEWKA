# Electronic system to irrigate plants

<!-- PROJECT LOGO -->
<br />
  <p align="left">
    The goal of the project was to create a system for watering plants. The device detects and signals under-watering of the soil by taking a measurement at a certain time. The system then delivers water to the soil thanks to a pump.
</p>


<!-- ABOUT THE PROJECT -->
## About The Project

![Layout](https://github.com/annasli378/KONEWKA/blob/main/images/schem.JPG)


### Components used
* STM32F0308 DISCOVER
* 16x2 LCD display
* board
* module equipped with relay JQC-3FF-S-Z
* pump
* rotary potentiometer
* drop sensor
* 3 buttons
* LED

### Build with
* STMM32 CubeIDE
* C language

### Libraries used
* stm32f0xx_it
* stm320xx_hal_conf
* LCD16x2
* LCD16x2_cfg

### Features
* Setting the time by the user using the buttons
* Checking the current time and taking measurements
* Turning the water pump on and off

### How it works

After starting the device, enter the current time using the buttons (the system does not use an external clock). From then on, the program automatically checks the time, taking a moisture measurement by the sensor every morning. If the soil in the pot is dry, the pump is started. Thanks to a flexible hose, water is transported from the water container to the potholder. After 10s, the pump is turned off. Watering system mounted at the plant is shown below:

![Watering system mounted at the plant](https://github.com/annasli378/KONEWKA/blob/main/images/layout.JPG)









<!-- README created using the following template -->
<!-- https://github.com/othneildrew/Best-README-Template -->
