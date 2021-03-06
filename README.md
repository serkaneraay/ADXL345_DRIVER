# ADXL345_DRIVER


### This library is written on STM32F407VGT6 with I2C protocol for ADXL345 accelerometer sensor.


----------------------------------------------------------------------------
                                      HOW TO USE THIS DRIVER
----------------------------------------------------------------------------

 *  1. Initialize the I2C
 *  2. This library should be called to the main.c file                         Example: 	#include "adxl345.h"
 *  3. Include your peripheral functions header file to adxl345.h               Example: 	#include "stm32f4xx_hal.h"
 * 	4. Extern your handler value of I2C_HandleTypeDef to sensor header file     Example: 	extern I2C_HandleTypeDef hi2c1;
 * 	5. Give the device address to <ADXL345_I2C_ADDRESS> in adxl345.h file
  	   The address must be entered by push left once
 * 	6. Begin the target device in main.c  <ADXL345_Begin()>
 * 	7. Now you can get the acceleration values with this functions:
 
 * 		ADXL345_Get_accX(),
 * 		ADXL345_Get_accY(),
 * 		ADXL345_Get_accZ()
 
 * 	8. You can change the settings of target sensor, gets the settings value or read the device ID with this functions:
 
 * 		ADXL345_ReadDeviceID();
 *		ADXL345_setRange();
 *		ADXL345_getRange();
 *		ADXL345_getRateBits();
 *		ADXL345_setRateBits();


----------------------------------------------------------------------------
Library Files Are In The Following Paths
--
- ADXL345_DRIVER/Core/Src/adxl345.c
- ADXL345_DRIVER/Core/Inc/adxl345.h

