#ifndef _I2C_H
    #define _I2C_H          
    #include "0_SPARKBOX.h"
   
	BOOL StartTransfer( I2C_MODULE i2cBus, BOOL restart );
	BOOL TransmitOneByte( I2C_MODULE i2cBus, UINT8 data );
	BYTE mI2CGetByte(I2C_MODULE i2cBus, BOOL ack);
	void StopTransfer( I2C_MODULE i2cBus );
    
#endif
