#ifndef SD_SPI1A_H
#define SD_SPI1A_H

#define  putcSPI1A(data_out) do{while(!SPI1ASTATbits.SPITBE); SPI1ABUF=(data_out); }while(0)

#define ReadSPI1A()         (SPI1ABUF)

#define  DataRdySPI1A()       (SPI1ASTATbits.SPIRBF)



unsigned int getcSPI1A(void);

void OpenSPI1A(unsigned int config1, unsigned int config2);

#endif