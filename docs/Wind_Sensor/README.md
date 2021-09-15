# Wind Direction Sensor
![3D Printed Wind Direction Sensor](https://github.com/Electronic-Emily/WeatherMonitoringSensors/blob/main/docs/Wind_Sensor/pictures/WindDirection_SensorV2_main_angle_zoomed_in.PNG)

## Summary
This wind direction sensor is a proof of consent to determine the feasibility 
to use reed switches in combination with a magnet and a GPIO expander to determine wind direction.
The reed switches are soldered onto circular PCB spaced every 45 degrees. The magnet is embedded into 
the top rotating section of the sensor, and activates the reed switches as it rotates. This can then be 
used to determine the direction based on which switch is active. 

## Functionality
The GPIO expander (SX1502I087TRT) is an 8 I/O IC that is configured in an all input mode with edge detection triggering. 
Thus when the magnet moves to a new location activating a different switch, the GPIO will SET the interrupt 
output pin to inform the MCU that there has been a change. The communication and configuration is done through I2C.

![Assembled Picture]https://github.com/Electronic-Emily/WeatherMonitoringSensors/blob/main/docs/Wind_Sensor/pictures/WindDirect_Assembled_01.PNG

## Hardware
### PCB
The PCB was developed within Eagle Cad and was hand soldered, with the exception of the GPIO expander. 
The GPIO expander was re-flowed using a countertop oven and a thermal couple to monitor the temperature 
(not the best option, but functional for this proof of concept).

![Unpopulated PCB] https://github.com/Electronic-Emily/WeatherMonitoringSensors/blob/main/docs/Wind_Sensor/pictures/WindDirection_PCB_top.jpg


### Other Hardware
All of the mechanical hardware is stainless steel 304:
- Two ball bearings
- one thrust bearing
- 4-40 button hex bolts of different sizes
- 4-40 nuts
- #4 size washers
- 6mm shaft cut to size
- 6-32 Socket Head Screws
- 6-32 nuts
- #6 washer
- 3/32 tig welding rod cut to size (used to mount the vertical fin)

Stainless steel was chosen due its environmental abilities.  


### 3D Print
This wind direction sensor is housed in a 3D printed housing made from PLA for this build, future 
versions will be housed in SAS filament because of SAS's UV and high temperature resistance. The 3d print was 
developed using SolidWorks 2020, and 3d printed on a Qidi X-Plus printer.
![SolidWorks Wind Direction Half] https://github.com/Electronic-Emily/WeatherMonitoringSensors/blob/main/docs/Wind_Sensor/pictures/WindDirection_SensorV2_Half_Zoomed.PNG



## Working Version
The link is to a short video of the sensor in action. With the help of a display showing an arrow to depict direction.
https://www.youtube.com/watch?v=b739gNtUACo


## Future Improvements
Future improvements to this version include:
- [] Add retention pin to the main rotating shaft
- [] Add a threaded hole to the bottom of the shaft to attach end cap to prevent top section of the sensor from being removed.
- [] Design print and mount a bottom section of the top spinner for the purpose of weatherproofing
