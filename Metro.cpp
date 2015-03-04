
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Metro.h"

Metro::Metro(unsigned long interval_millis)
{   
	interval(interval_millis);
	reset();
}

void Metro::interval(unsigned long interval_millis)
{
  this->interval_millis = interval_millis;
}

// Simplest check behavior:
// When a check is true, it simply returns true

bool Metro::expired() const
{
  if (millis() - this->previous_millis >= this->interval_millis)
    return 1;
  else  
  	return 0;
}

// Original check behavior:
// When a check is true, it resets the timer to the current time.
bool Metro::check()
{
	int now = millis();

	if (this->expired())
	{
		this->previous_millis = now;
		return 1;
	}
	else 
		return 0;
}

// Ketchup check behavior:
// When a check is true, it increments the base time by the interval. Thus any lag is taken out of subsequent intervals.
bool Metro::checkCatchUp()
{
	if (this->expired())
	{
		this->previous_millis += this->interval_millis;
		return 1;
	}
	return 0;
}

bool Metro::running()
{
	return !this->expired();
}

void Metro::reset() 
{
  this->previous_millis = millis();
}


