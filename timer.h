#ifndef TIMER_H_
#define TIMER_H_

#include "main.h"

typedef enum
{
	TIMER_SEL_0,
	TIMER_SEL_1, //Timer 1
	TIMER_SEL_NONE //Icke specifierad timer

}timer_sel_t;


typedef struct
{
	volatile uint32_t counter; //32-bitars r�knare.
	uint32_t max_count;		   //Maxv�rde som uppr�kning ska ske till.
	volatile uint8_t* timsk;   //Pekare till maskregister f�r aktivering av avbrott.
	uint8_t timsk_bit;		   //Bit f�r aktivering av avbrott i motsvarande maskregister.
	timer_sel_t	timer_sel_t;   //Val av timerkrets
	
} timer_t;


//Initierar en timerkerts som m�ts i milliskeunder
void timer_init(timer_t* self, const timer_sel_t timer_sel_t, const double time_ms);

//Nollst�ller timern s� att den kan b�rja om
void timer_clear(timer_t* self);

//Aktiverar avbrott n�r r�knaren har r�knat upp till sitt tal eller f�r overflow
static inline void timer_enable_interrupt(timer_t* self)
{
	asm("SEI");
	*(self->timsk) |= (1 << self->timsk_bit);
	return;
}

//Inaktiverar avbrott
static inline void timer_disable_interrupt(timer_t* self)
{
	*(self->timsk) &= ~(1 << self->timsk_bit);
}

//R�knar upp angiven tid
static inline void timer_count(timer_t* self)
{
	self->counter++;
	return;
}

//Kollar om avbrott �r aktiverat eller inte
static inline bool timer_interrupt_enabled(const timer_t* self)
{
	return (*(self->timsk) & (1 << self->timsk_bit));
}

//N�r r�knaren har r�knat upp till max s� nollst�ller den r�knaren genom att retunera true or false
bool timer_elapsed(timer_t* self);

//Nollst�ller r�knaren p� angiven tid
static inline void timer_reset_counter(timer_t* self)
{
	self->counter = 0;
	return;
}

//�terst�ller timern
void timer_reset(timer_t* self);

//S�tter en ny tid p� angiven timer
void timer_get_new_time_ms(timer_t* self, const double time_ms);

//S�tter ett nytt max v�rde p� timern som ska anv�ndas
static inline void timer_get_new_max_count(timer_t* self, const uint32_t max_count)
{
	self->max_count = max_count;
	return;
}
#endif