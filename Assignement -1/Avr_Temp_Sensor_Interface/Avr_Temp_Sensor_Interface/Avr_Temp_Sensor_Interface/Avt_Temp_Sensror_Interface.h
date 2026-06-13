/*
 * Avt_Temp_Sensror_Interface.h
 *
 * Created: 07-Jun-26 5:13:34 PM
 *  Author: SHAHEEM
 */ 


#ifndef AVT_TEMP_SENSROR_INTERFACE_H_
#define AVT_TEMP_SENSROR_INTERFACE_H_
#define F_CPU 16000000UL

void ADC_init();
uint16_t ADC_read();



#endif /* AVT_TEMP_SENSROR_INTERFACE_H_ */