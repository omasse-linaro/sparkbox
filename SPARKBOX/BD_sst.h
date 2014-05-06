#ifndef _BD_SST_H
	#define _BD_SST_H
    #include "0_SPARKBOX.h"

	void				BD_Init(void);
	void				BD_Enregistre_Jour_Index(void);
	unsigned int		BD_Lecture_Jour_Teleinfo(unsigned char no, time_t tlecture);
	void				BD_Enregistre_Coef_GFCI(void);
	void				BD_Lecture_Coef_GFCI(void);

	void				BD_Erase_All(void);

#endif