
# Weather Monitoring Project


## Purpose
The purpose of this project is to create a prototype outdoor real-time weather monitoring station. The data from the station will then be transmitted and displayed to update the user on the current weather conditions.
   
The station's environmental sensing abilities should include:
- Temperature
- Atmospheric Pressure
- Relative Humidity
- Wind Speed (anemometer)
- Wind Direction
- Light Brightness



![3D Printed Wind Direction Sensor](https://github.com/Electronic-Emily/WeatherMonitoringSensors/blob/main/docs/Wind_Sensor/pictures/WindDirection_SensorV2_main_angle_zoomed_in.PNG)



## Solution

For the first proof of concept a Nucleo-L4R5ZI-P (STM32L4R5ZI) was chosen to interface with the sensors.


## Parts list
	
### Sensors	
  
  |      | Part # | Mfr. Name| Part Source                         |
|----------------|-------------------|--------------|------------------|
|Temperature          |Si7021-A20 | Silicon Labs | digikey.com |
|Relative Humidity    |Si7021-A20 | Silicon Labs | digikey.com  |
|Atmospheric Pressure | MS5803-02BA | TE Connectivity|  digikey.com |
|Light Brightness | VEML6035 | VISHAY | digikey.com |
|Wind Speed | ID: 1733 | | adafruit.com |
|Wind Direction | NA |  Self-Built | NA |


### Other
  |                | Part #  |  Mfr. Name                    | Part Source                         |
|--------|--------|----------|-----------|
|Display Dev Board | 3.5" TFT 320x480 HXD8357D |  | adafruit.com |
|MCU Dev Board| Nucleo-L4R5ZI | STM  | digikey.com |


### Custom Wind Direction Sensor 
  |    | Part #  |  Mfr. Name      | Part Source      |
|------|-----|----|-----------|
|GPIO Expander | SX1502I087TRT | SEMTECH  | digikey.com |
|Reed-switches | PMC-0701S1015 | PIC GmbH | digikey.com |


