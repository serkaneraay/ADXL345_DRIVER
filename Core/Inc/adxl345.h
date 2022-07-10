/*
 * adxl345.h
 *
 *  Created on: Jul 10, 2022
 *      Author: serkaneray
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_


/*
 *
 * This field is replaced with the appropriate value
 */

#include "stm32f4xx_hal.h"
extern I2C_HandleTypeDef hi2c1;
#define ADXL345_I2C_ADDRESS   0x53<<1


/*
 *
 * @brief  ADXL345 memory map
 */

#define ADXL345_REG_DEVID             (0x00)
#define ADXL345_REG_THRESH_TAP        (0x1D)
#define ADXL345_REG_OFSX              (0x1E)
#define ADXL345_REG_OFSY              (0x1F)
#define ADXL345_REG_OFSZ              (0x20)
#define ADXL345_REG_DUR               (0x21)
#define ADXL345_REG_LATENT            (0x22)
#define ADXL345_REG_WINDOW            (0x23)
#define ADXL345_REG_THRESH_ACT        (0x24)
#define ADXL345_REG_THRESH_INACT      (0x25)
#define ADXL345_REG_TIME_INACT        (0x26)
#define ADXL345_REG_ACT_INACT_CTL     (0x27)
#define ADXL345_REG_THRESH_FF         (0x28)
#define ADXL345_REG_TIME_FF           (0x29)
#define ADXL345_REG_TAP_AXES          (0x2A)
#define ADXL345_REG_ACT_TAP_STATUS    (0x2B)
#define ADXL345_REG_BW_RATE           (0x2C)
#define ADXL345_REG_POWER_CTL         (0x2D)
#define ADXL345_REG_INT_ENABLE        (0x2E)
#define ADXL345_REG_INT_MAP           (0x2F)
#define ADXL345_REG_INT_SOURCE        (0x30)
#define ADXL345_REG_DATA_FORMAT       (0x31)
#define ADXL345_REG_DATAX0            (0x32)
#define ADXL345_REG_DATAX1            (0x33)
#define ADXL345_REG_DATAY0            (0x34)
#define ADXL345_REG_DATAY1            (0x35)
#define ADXL345_REG_DATAZ0            (0x36)
#define ADXL345_REG_DATAZ1            (0x37)
#define ADXL345_REG_FIFO_CTL          (0x38)
#define ADXL345_REG_FIFO_STATUS       (0x39)


/*
 *
 * @brief  ADXL345 Device register value for HEX.    11100101
 */

#define ADXL345_DEVICE_ID   0xE5


/*
 *
 * @defgroup ADXL345_Status
 */

typedef enum ADXL345_STATUS_e
{
	ADXL345_NAN		= 0x00U,
	ADXL345_OK		= 0x01U,
	ADXL345_BUSY	= 0x02U

} ADXL345_STATUS_t;


/*
 *
 * @defgroup ADXL345_RATE
 */

typedef enum
{
	ADXL345_RATE_3200	= 0x0F,
	ADXL345_RATE_1600	= 0x0E,
	ADXL345_RATE_800	= 0x0D,
	ADXL345_RATE_400	= 0x0C,
	ADXL345_RATE_200	= 0x0B,
	ADXL345_RATE_100	= 0x0A,
	ADXL345_RATE_50		= 0x09,
	ADXL345_RATE_25		= 0x08,
	ADXL345_RATE_12_5	= 0x07,
	ADXL345_RATE_6_25	= 0x06,
	ADXL345_RATE_3_13	= 0x05,
	ADXL345_RATE_1_56	= 0x04,
	ADXL345_RATE_0_78	= 0x03,
	ADXL345_RATE_0_39	= 0x02,
	ADXL345_RATE_0_20	= 0x01,
	ADXL345_RATE_0_10	= 0x00

} ADXL345_RATE_BITS_t;


/*
 *
 * @defgroup ADXL345_RANGE
 */

typedef enum
{
  ADXL345_RANGE_16_G	= 0x03,
  ADXL345_RANGE_8_G 	= 0x02,
  ADXL345_RANGE_4_G 	= 0x01,
  ADXL345_RANGE_2_G 	= 0x00

} ADXL345_RANGE_t;




ADXL345_STATUS_t ADXL345_Begin(void);
void ADXL345_setRange(ADXL345_RANGE_t Range);
ADXL345_RANGE_t ADXL345_getRange(void);
void ADXL345_setRateBits(ADXL345_RATE_BITS_t Rate);
ADXL345_RATE_BITS_t ADXL345_getRateBits(void);
uint8_t ADXL345_ReadDeviceID(void);

void writeRegister(uint8_t reg, uint8_t value);
uint8_t readRegister8(uint8_t reg);
int16_t readRegister16(uint8_t reg);

float ADXL345_Get_accX(void);
float ADXL345_Get_accY(void);
float ADXL345_Get_accZ(void);



#endif /* INC_ADXL345_H_ */
