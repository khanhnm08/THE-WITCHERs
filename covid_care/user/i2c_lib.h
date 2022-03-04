#ifndef I2C_LIB_H
#define I2C_LIB_H
#include "em_i2c.h"
#include "em_cmu.h"

// I2C Setting
// <o> Reference clock frequency
// <i> Frequency in Hz of the reference clock.
// <i> Select 0 to use the frequency of the currently selected clock.
// <i> Default: 0
#define I2C_REFERENCE_CLOCK 0

// <o>  Speed mode
// <0=> Standard mode (100kbit/s)
// <1=> Fast mode (400kbit/s)
// <2=> Fast mode plus (1Mbit/s)
// <i> Default: 0
#define I2C_SPEED_MODE    1
// </h> end I2CSPM config

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <i2c signal=SCL,SDA> SL_I2CSPM_SENSOR
// $[I2C_SL_I2CSPM_SENSOR]
#define I2C_PERIPHERAL              I2C0
#define I2C_PERIPHERAL_NO           0

// I2C0 SCL on PD02
#define I2C_SCL_PORT                gpioPortD
#define I2C_SCL_PIN                 2

// I2C0 SDA on PD03
#define I2C_SDA_PORT               gpioPortD
#define I2C_SDA_PIN                3
// [I2C_SL_I2CSPM_SENSOR]$
// <<< sl:end pin_tool >>>

#define I2C_TXBUFFER_SIZE                 10
#define I2C_RXBUFFER_SIZE                 10

void i2c_init(void);
void i2c_read(uint16_t followerAddress, uint8_t targetAddress, uint8_t *rxBuff, uint8_t numBytes);
void i2c_write(uint16_t followerAddress, uint8_t targetAddress, uint8_t txBuff);

#endif // SL_I2CSPM_SENSOR_CONFIG_H