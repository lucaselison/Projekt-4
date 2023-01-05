#include "timer.h"

/* Statiska funktioner: */
static void timer_init_circuit(timer_t* self);
static void timer_disable_circuit(timer_t* self);
static inline uint32_t timer_get_max_count(const double time_ms);

static void timer_init_circuit(timer_t* self)
{
	sei();
	
	if(self->timer_sel_t == TIMER_SEL_1)
	{
		self->timsk = &TIMSK1;
		self->timsk_bit = OCIE1A;
		TCCR1B = (1 << CS11) | (1 << WGM12);
		OCR1A = 256;
	}
	else if(self->timer_sel_t == TIMER_SEL_0)
	{
		self->timsk = &TIMSK0;
		self->timsk_bit = TOIE0;
		TCCR0B = (1 << CS01);
	}
	
	return;
}

static void timer_disable_circuit(timer_t* self)
{
	if(self->timer_sel_t == TIMER_SEL_1)
	{
		TCCR1B = 0x00;
		TIMSK1 = 0x00;
		OCR1A  = 0x00;
	}
	return;
}

static inline uint32_t timer_get_max_count(const double time_ms)
{
	return (uint32_t)(time_ms/TIMER_INTERRUPT_MS + 0.5);
}

void timer_init(timer_t* self, const timer_sel_t timer_sel_t, const double time_ms)
{
	self->counter = 0;
	self->max_count = timer_get_max_count(time_ms);
	self->timer_sel_t = timer_sel_t;
	timer_init_circuit(self);
	return;
}

void timer_clear(timer_t* self)
{
	timer_disable_circuit(self);
	self->counter = 0;
	self->max_count = 0;
	self->timsk = 0;
	self->timsk_bit = 0;
	self->timer_sel_t = TIMER_SEL_NONE;
	return;
}

bool timer_elapsed(timer_t* self)
{
	if (self->counter >= self->max_count)
	{
		self->counter = 0;
		return true;
	}
	else
	{
		return false;
	}
	
}

void timer_reset(timer_t* self)
{
	timer_disable_interrupt(self);
	self->counter = 0;
	return;
}

void timer_get_new_time_ms(timer_t* self, const double time_ms)
{
	self->max_count = timer_get_max_count(time_ms);
	return;
}