#include <i2c_lib.h>
#include "stddef.h"
//#include "em_i2c.h"

void i2c_init(void)
{
  CMU_ClockEnable(cmuClock_I2C0, true);
  // Use default settings
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

  // Using PA5 (SDA) and PA6 (SCL)
  GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAndPullUpFilter, 1);
  GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAndPullUpFilter, 1);

  // Route I2C pins to GPIO
  GPIO->I2CROUTE[0].SDAROUTE = (GPIO->I2CROUTE[0].SDAROUTE & ~_GPIO_I2C_SDAROUTE_MASK)
                        | (I2C_SDA_PORT << _GPIO_I2C_SDAROUTE_PORT_SHIFT
                        | (I2C_SDA_PIN << _GPIO_I2C_SDAROUTE_PIN_SHIFT));
  GPIO->I2CROUTE[0].SCLROUTE = (GPIO->I2CROUTE[0].SCLROUTE & ~_GPIO_I2C_SCLROUTE_MASK)
                        | (I2C_SCL_PORT << _GPIO_I2C_SCLROUTE_PORT_SHIFT
                        | (I2C_SCL_PIN << _GPIO_I2C_SCLROUTE_PIN_SHIFT));
  GPIO->I2CROUTE[0].ROUTEEN = GPIO_I2C_ROUTEEN_SDAPEN | GPIO_I2C_ROUTEEN_SCLPEN;

  // Initialize the I2C
  I2C_Init(I2C_PERIPHERAL , &i2cInit);

  // Set the status flags and index
  //I2C_startTx = false;

  // Enable automatic STOP on NACK
  I2C_PERIPHERAL ->CTRL = I2C_CTRL_AUTOSN;
}

void i2c_write(uint16_t deviceAddress, uint8_t regAddress, uint8_t txBuff)
{
  // Transfer structure
   I2C_TransferSeq_TypeDef i2cTransfer;
   I2C_TransferReturn_TypeDef result;
//   uint8_t txBuffer[numBytes + 1];
   uint8_t txBuffer[2];

   txBuffer[0] = regAddress;
   txBuffer[1] = txBuff;
//   for(int i = 0; i < numBytes; i++)
//   {
//       txBuffer[i + 1] = txBuff[i];
//   }

   // Initialize I2C transfer
   i2cTransfer.addr          = deviceAddress;
   i2cTransfer.flags         = I2C_FLAG_WRITE;
   i2cTransfer.buf[0].data   = txBuffer;
   i2cTransfer.buf[0].len    = 2;
   i2cTransfer.buf[1].data   = NULL;
   i2cTransfer.buf[1].len    = 0;

   result = I2C_TransferInit(I2C_PERIPHERAL , &i2cTransfer);

   // Send data
   while (result == i2cTransferInProgress) {
     result = I2C_Transfer(I2C_PERIPHERAL);
   }
}

void i2c_read(uint16_t deviceAddress, uint8_t regAddress, uint8_t *rxBuff, uint8_t numBytes)
{
    I2C_TransferSeq_TypeDef i2cTransfer;
    I2C_TransferReturn_TypeDef result;

    // Initialize I2C transfer
    i2cTransfer.addr          = deviceAddress;
    i2cTransfer.flags         = I2C_FLAG_WRITE_READ; // must write target address before reading
    i2cTransfer.buf[0].data   = &regAddress;
    i2cTransfer.buf[0].len    = 1;
    i2cTransfer.buf[1].data   = rxBuff;
    i2cTransfer.buf[1].len    = numBytes;

    result = I2C_TransferInit(I2C_PERIPHERAL , &i2cTransfer);

    // Send data
    while (result == i2cTransferInProgress) {
      result = I2C_Transfer(I2C_PERIPHERAL );
    }

}