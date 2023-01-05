#ifndef TMP36_H_
#define TMP36_H_

#include "main.h"
#include "Serial.h"
#include "adc.h"

typedef struct
{
	adc_t input;
	
} tmp36_t;

//Vilken pin som tempen är på och hur stor överförings hastighet
static inline void tmp36_init(tmp36_t* self,const uint8_t pin)
{
	adc_init(&self->input, pin);
	serial_init(9600);
	return;
}

//Räknar ut temperaturen i rummet
static inline double tmp36_room_temp(tmp36_t* self)
{
	const double voltage_in = adc_read(&self->input) / 1023.0 * 5.0;
	return 100 * voltage_in - 50;
}

//Skriver ut i seriall monitorn
static inline void tmp36_temp_print(tmp36_t* self)
{
	serial_print_string("Temperature: ");
	serial_print_double(tmp36_room_temp(self));
	serial_print_string("° Celcius\n");
}
#endif /* TMP36_H_ */