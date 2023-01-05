#ifndef ADC_H_
#define ADC_H_

#include "main.h"

typedef struct
{
	uint8_t pin;
	uint16_t adc_on_us;
	uint16_t adc_off_us;
	
} adc_t;

//Vad som self pekar p� n�r man definerar den
void adc_init(adc_t* self, const uint8_t pin);

//R�knar ut hur mycket str�m som ska g� ut
double adc_duty_cycle(adc_t* self);

//Vilka pin som har adc
uint16_t adc_read(adc_t* self);

//R�knar ut hur l�ng den ska vara p� och av i en period tid f�r att f� r�tt sp�nning
void adc_get_values(adc_t* self, const uint16_t period_us);

#endif /* ADC_H_ */