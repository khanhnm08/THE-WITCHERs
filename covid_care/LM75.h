
#ifndef _LM75_H
#define _LM75_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define LM75_11BIT
#define LM75_ADDRESS  (0x48 << 1 )

#define LM75_TEMPERATURE    0x00
#define LM75_CONFIGURATION    0x01
#define LM75_THYST        0x02
#define LM75_TOS        0x03


#define ABS(x)   ((x) > 0 ? (x) : -(x))

//----------------------------------------------------------------------------//

/**
* @brief      Read config register of LM75
*
* @return     Value of LM75 config register
*/
uint8_t LM75_ReadConfig(void);

/**
* @brief      Read 9-bit format temperature from register
*
* @param[in]  reg   -   address of temperature register
* @return     Value of temperature
*/
float LM75_ReadTemperature_9BitReg(void);

/**
* @brief      Read 11-bit format temperature from register
*
* @param[in]  reg   -   address of temperature register
* @return     Value of temperature
*/
float LM75_ReadTemperature_11BitReg(void);

/**
* @brief      Config LM75 into sleep mode (shutdown)
*
* @param[in]  mode    - 0: normal (defaul); 1: shutdown
* @return     none
*/
void LM75_SleepMode(uint8_t mode);

/**
* @brief    Read temparature
*
* @return   value of temperature
*/
float LM75_ReadTemperature(void);

#ifdef __cplusplus
}
#endif

#endif
