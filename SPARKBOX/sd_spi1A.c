#include "sd_spi1A.h"
#include <peripheral/spi.h>
#include <peripheral/legacy/spi_legacy.h>


extern const int _SpiBrgConvTbl[32];

void OpenSPI1A(unsigned int config1, unsigned int config2)
{
	SPI1ABRG=_SpiBrgConvTbl[config1&0x1f]; // keep the prescaler 5 bits
	if( !((SpiOpenConfig2)config2).SPIROV )
	{
		SPI1ASTATCLR=_SPI1ASTAT_SPIROV_MASK; // clear overrun
	}
	SPI1ACON=(config1&0xc0001fe0)|(config2&0x2002e000); // get FRMEN, FRMSYNC, DISSDO-MSTEN; get FRMPOL, SPIFE, ON, FRZ, SIDL
// set control word
}


unsigned int getcSPI1A(void)
{
	while(!DataRdySPI1A()); // wait receive data available
	return ReadSPI1A();
} 