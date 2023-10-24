#include "Subject.h"

void Subject::subscribe(Observer* obs)
{
	observers.push_back(obs);
}

void Subject::notify()
{
	for (Observer* o : observers) {
		o->update();
	}
}
