#include "adc.h"

//Max värdert
#define ADC_MAX 1023.0

//Kollar vilken pin som kan ha adc
void adc_init(adc_t* self, const uint8_t pin)
{
	if(pin >= 0 && pin <= 5)
	{
		self->pin = pin;
	}
	else if(pin >= 14 && pin <= 19)
	{
		self->pin = pin-14;
	}
	return;
}

//Vilka pin som har adc
uint16_t adc_read(adc_t* self)
{
	ADMUX = (1 << REFS0) | self->pin;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	while (read(ADCSRA, ADIF) == 0);
	set(ADCSRA, ADIF);
	
	return ADC;
}

//Räknar ut hur mycket ström som ska gå ut
double adc_duty_cycle(adc_t* self)
{
	return adc_read(self)/ ADC_MAX;
}

//Räknar ut hur lång period tid och hur länge den ska vara på och av i period tiden.
void adc_get_values(adc_t* self, const uint16_t period_us)
{
	self->adc_on_us = (uint16_t)(adc_duty_cycle(self)* period_us + 0.5);
	self->adc_off_us = period_us - self->adc_on_us;
}