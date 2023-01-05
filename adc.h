#ifndef ADC_H_
#define ADC_H_

#include "main.h"

typedef struct
{
	uint8_t pin;
	uint16_t adc_on_us;
	uint16_t adc_off_us;
	
} adc_t;

//Vad som self pekar på när man definerar den
void adc_init(adc_t* self, const uint8_t pin);

//Räknar ut hur mycket ström som ska gå ut
double adc_duty_cycle(adc_t* self);

//Vilka pin som har adc
uint16_t adc_read(adc_t* self);

//Räknar ut hur läng den ska vara på och av i en period tid för att få rätt spänning
void adc_get_values(adc_t* self, const uint16_t period_us);

#endif /* ADC_H_ */