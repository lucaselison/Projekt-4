#include "Header.h"

//Alla interrupts som behövs för att kunna temp sensorn och knappen som har ett studs skydd.
ISR(PCINT0_vect)
{
	PCICR &= ~(1 << PCIE0);//Överiga bitars bibehåller
	TIMSK0 = (1 << TOIE0);//Sätter timer 0 till 300 ms
	
	
	if(BUTTON1_IS_PRESSED)
	{
		tmp36_temp_print(&temp1);// Mät temp.
		timer_reset_counter(&timer1);// Nollställ timer1.
	}
	return;
}

ISR (TIMER0_OVF_vect)
{
	timer_count(&timer0);
	
	if (timer_elapsed(&timer0))
	{
		PCICR |= (1 << PCIE0);
		timer_disable_interrupt(&timer0);
	}
}

ISR (TIMER1_COMPA_vect)
{
	timer_count(&timer1);

	if (timer_elapsed(&timer1))
	{
		tmp36_temp_print(&temp1);
	}

	return;
}