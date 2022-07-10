/*
 * adxl345.c
 *
 *  Created on: Jul 10, 2022
 *      Author: serkaneray
 */



//----------------------------------------------------------------------------
//                            HOW TO USE THIS DRIVER
//----------------------------------------------------------------------------
/*
 *  1. Initialize the I2C
 *  2. This library should be called to the main.c file                         Example: 	#include "adxl345.h"
 *  3. Include your peripheral functions header file to adxl345.h               Example: 	#include "stm32f4xx_hal.h"
 * 	4. Extern your handler value of I2C_HandleTypeDef to sensor header file     Example: 	extern I2C_HandleTypeDef hi2c1;
 * 	5. Give the device address to <ADXL345_I2C_ADDRESS> in adxl345.h file
 * 	   The address must be entered by push left once
 * 	6. Begin the target device in main.c  <ADXL345_Begin()>
 * 	7. Now you can get the acceleration values with this functions:
 *
 * 		ADXL345_Get_accX(),
 * 		ADXL345_Get_accY(),
 * 		ADXL345_Get_accZ()
 *
 * 	8. You can change the settings of target sensor, gets the settings value or read the device ID with this functions:
 *
 * 		ADXL345_ReadDeviceID();
 *		ADXL345_setRange();
 *		ADXL345_getRange();
 *		ADXL345_getRateBits();
 *		ADXL345_setRateBits();
 */




#include "adxl345.h"


/*
 * @brief	Is the write command for I2C
 * @note	It is an abstract layer function for I2C
 * @param	uint8_t reg, the register to which the buffer will be forwarded
 * @param	uint8_t value, the value you want to write to the other device
 *
 * @retval	void
 */

void writeRegister(uint8_t reg, uint8_t value)
{
	uint8_t data[2];
	data[0] = reg;
	data[1] = value;

	HAL_I2C_Master_Transmit(&hi2c1, ADXL345_I2C_ADDRESS, data, 2, 100);
}


/*
 * @brief	Is the read command for I2C
 * @note	It is an abstract layer function for I2C, just 8 bits
 * @param	uint8_t reg, the register to read
 *
 * @retval	uint8_t
 */

uint8_t readRegister8(uint8_t reg)
{
	uint8_t data[1];

	HAL_I2C_Mem_Read(&hi2c1, ADXL345_I2C_ADDRESS, reg, 1, data, 1, 100);

	return data[0];
}


/*
 * @brief	Is the read command for I2C
 * @note	It is an abstract layer function for I2C, just 16 bits
 * @param	uint8_t reg, the register to read. You have to give LSB
 *
 * @retval	int16_t
 */

int16_t readRegister16(uint8_t reg)
{
	uint8_t data[2];
	int16_t sendData;

	HAL_I2C_Mem_Read(&hi2c1, ADXL345_I2C_ADDRESS, reg, 1, data, 2, 100);

	sendData = data[1];
	sendData = (sendData << 8) | data[0];

	return sendData;
}


/* @brief	The ID number of the target device is read with this function.
 * @note
 * @param	void
 *
 * @retval	uint8_t - ID number by target device
 */

uint8_t ADXL345_ReadDeviceID(void)
{
	uint8_t deviceID;

	deviceID = readRegister8(ADXL345_REG_DEVID);

	return deviceID;
}


/* @brief	Sets and initializes the target device
 * @note	This function is required for operation
 * @param	void
 *
 * @retval	ADXL345 Status
 */

ADXL345_STATUS_t ADXL345_Begin(void)
{
	uint8_t deviceID;
	writeRegister(ADXL345_REG_POWER_CTL, 0x08);

	deviceID = ADXL345_ReadDeviceID();

	if(deviceID == ADXL345_DEVICE_ID)
	{
		return ADXL345_OK;
	}
	else
	{
		return ADXL345_NAN;
	}



	return ADXL345_OK;
}


/*
 * @brief	Set the sensor range
 * @note	default value is ADXL345_RANGE_2_G
 * @param	Chosen Range for ADXL345 sensor - @defgroup ADXL345_RANGE
 *
 * @retval	void
 */

void ADXL345_setRange(ADXL345_RANGE_t Range)
{
	uint8_t dataFormat = readRegister8(ADXL345_REG_DATA_FORMAT);

	dataFormat &= ~0x0F;
	dataFormat |= Range;

	dataFormat |= 0x08;

	writeRegister(ADXL345_REG_DATA_FORMAT, dataFormat);
}


/*
 * @brief	Get the sensor range
 * @note
 * @param	void
 *
 * @retval	ADXL345_RANGE_t
 */

ADXL345_RANGE_t ADXL345_getRange(void)
{
	return (ADXL345_RANGE_t)(readRegister8(ADXL345_REG_DATA_FORMAT) & (0x03));
}


/*
 * @brief	Set the Rate Bits for target device
 * @note	Default value is ADXL345_RATE_100
 * @param	Chosen Rate Bits for ADXL345 sensor - @defgroup ADXL345_RATE
 *
 * @retval	void
 */


void ADXL345_setRateBits(ADXL345_RATE_BITS_t Rate)
{
	writeRegister(ADXL345_REG_BW_RATE, Rate);
}


/*
 * @brief	Get the Rate Bits for target device
 * @note
 * @param	void
 *
 * @retval	ADXL345_RATE_BITS_t
 */

ADXL345_RATE_BITS_t ADXL345_getRateBits(void)
{
  return (ADXL345_RATE_BITS_t)(readRegister8(ADXL345_REG_BW_RATE) & 0x0F);
}


/*
 * @brief	Get the acceleration value of the X-axis.
 * @note	This function returns the value with the coefficient < g >
 * @param	void
 *
 * @retval	float value of X-acc
 */

float ADXL345_Get_accX(void)
{
	int16_t data;
	uint8_t range;
	float rangeResolution = 0.0039;
	uint8_t LSB_g = 1;
	float returnData;

	range = ADXL345_getRange();
	switch (range)
	{
	case ADXL345_RANGE_16_G:
		rangeResolution = 0.0312;
		LSB_g = 8;
		break;

	case ADXL345_RANGE_8_G:
		rangeResolution = 0.0156;
		LSB_g = 4;
		break;

	case ADXL345_RANGE_4_G:
		rangeResolution = 0.0078;
		LSB_g = 2;
		break;

	default:
		rangeResolution = 0.0039;
		LSB_g = 1;
	}

	data = readRegister16(ADXL345_REG_DATAX0);

	returnData = ( data * rangeResolution ) / ( LSB_g );

	return returnData * 10.0;
}


/*
 * @brief	Get the acceleration value of the Y-axis.
 * @note	This function returns the value with the coefficient < g >
 * @param	void
 *
 * @retval	float value of Y-acc
 */

float ADXL345_Get_accY(void)
{
	int16_t data;
	uint8_t range;
	float rangeResolution = 0.0039;
	uint8_t LSB_g = 1;
	float returnData;

	range = ADXL345_getRange();
	switch (range)
	{
	case ADXL345_RANGE_16_G:
		rangeResolution = 0.0312;
		LSB_g = 8;
		break;

	case ADXL345_RANGE_8_G:
		rangeResolution = 0.0156;
		LSB_g = 4;
		break;

	case ADXL345_RANGE_4_G:
		rangeResolution = 0.0078;
		LSB_g = 2;
		break;

	default:
		rangeResolution = 0.0039;
		LSB_g = 1;
	}

	data = readRegister16(ADXL345_REG_DATAY0);

	returnData = ( data * rangeResolution ) / ( LSB_g );

	return returnData * 10.0;
}


/*
 * @brief	Get the acceleration value of the Z-axis.
 * @note	This function returns the value with the coefficient < g >
 * @param	void
 *
 * @retval	float value of Z-acc
 */

float ADXL345_Get_accZ(void)
{
	int16_t data;
	uint8_t range;
	float rangeResolution = 0.0039;
	uint8_t LSB_g = 1;
	float returnData;

	range = ADXL345_getRange();
	switch (range)
	{
	case ADXL345_RANGE_16_G:
		rangeResolution = 0.0312;
		LSB_g = 8;
		break;

	case ADXL345_RANGE_8_G:
		rangeResolution = 0.0156;
		LSB_g = 4;
		break;

	case ADXL345_RANGE_4_G:
		rangeResolution = 0.0078;
		LSB_g = 2;
		break;

	default:
		rangeResolution = 0.0039;
		LSB_g = 1;
	}

	data = readRegister16(ADXL345_REG_DATAZ0);

	returnData = ( data * rangeResolution ) / ( LSB_g );

	return returnData * 10.0;
}
