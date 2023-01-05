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
	volatile uint32_t counter; //32-bitars räknare.
	uint32_t max_count;		   //Maxvärde som uppräkning ska ske till.
	volatile uint8_t* timsk;   //Pekare till maskregister för aktivering av avbrott.
	uint8_t timsk_bit;		   //Bit för aktivering av avbrott i motsvarande maskregister.
	timer_sel_t	timer_sel_t;   //Val av timerkrets
	
} timer_t;


//Initierar en timerkerts som mäts i milliskeunder
void timer_init(timer_t* self, const timer_sel_t timer_sel_t, const double time_ms);

//Nollställer timern så att den kan börja om
void timer_clear(timer_t* self);

//Aktiverar avbrott när räknaren har räknat upp till sitt tal eller får overflow
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

//Räknar upp angiven tid
static inline void timer_count(timer_t* self)
{
	self->counter++;
	return;
}

//Kollar om avbrott är aktiverat eller inte
static inline bool timer_interrupt_enabled(const timer_t* self)
{
	return (*(self->timsk) & (1 << self->timsk_bit));
}

//När räknaren har räknat upp till max så nollställer den räknaren genom att retunera true or false
bool timer_elapsed(timer_t* self);

//Nollställer räknaren på angiven tid
static inline void timer_reset_counter(timer_t* self)
{
	self->counter = 0;
	return;
}

//återställer timern
void timer_reset(timer_t* self);

//Sätter en ny tid på angiven timer
void timer_get_new_time_ms(timer_t* self, const double time_ms);

//Sätter ett nytt max värde på timern som ska användas
static inline void timer_get_new_max_count(timer_t* self, const uint32_t max_count)
{
	self->max_count = max_count;
	return;
}
#endif