#include "Serial.h"

void serial_init(const uint32_t baud_rate_kbps)
{
	static bool serial_initalized = false;
	if(serial_initalized) return;
	
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	
	UBRR0 = (uint16_t)(F_CPU/(16.0 * baud_rate_kbps) - 0.5);
	UDR0 = '\r'; //Carriage return. \r så att man hamnar längst till vänster igen
	serial_initalized = true;
	return;
}

void serial_print_char(const char c)
{
	while ((UCSR0A & (1 << UDRE0)) == 0);
	UDR0 = c;
	return;
}

void serial_print_string(const char* s)
{
	for (size_t i = 0; s[i]; ++i)
	{
		serial_print_char(s[i]);
	}
	return;
}

void serial_print_integer(const int32_t number)
{
	char s[20] = { '\0' };
	sprintf(s, "%ld", number);
	serial_print_string(s);
	return;
}

void serial_print_unsigned(const uint32_t number)
{
	char s[20] = { '\0' };
	sprintf(s, "%lu", number);
	serial_print_string(s);
	return;
}

void serial_print_double(const double number)
{
	char s[30] = { '\0' };
	const int32_t integer = (int32_t)number;
	int32_t decimal;
	
	if (integer >= 0)
	{
		decimal = (int32_t)((number - integer)* 100 + 0.5);
	}
	else
	{
		decimal = (int32_t)((integer - number)* 100 + 0.5);
	}
	sprintf(s, "%ld.%ld",integer , decimal);
	serial_print_string(s);
	return;
}