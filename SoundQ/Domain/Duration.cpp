#include "Duration.h"

Duration::Duration()
{
	this->minutes = 0;
	this->seconds = 0;
}

Duration::Duration(const int& minutes, const int& seconds)
{
	this->minutes = minutes;
	this->seconds = seconds;
}

int Duration::getMinutes() const
{
	return this->minutes;
}

int Duration::getSeconds() const
{
	return this->seconds;
}

void Duration::setMinutes(const int& newMinutes)
{
	this->minutes = newMinutes;
}

void Duration::setSeconds(const int& newSeconds)
{
	this->seconds = newSeconds;
}
