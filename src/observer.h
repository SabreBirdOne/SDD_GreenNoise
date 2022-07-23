#ifndef observer_h
#define observer_h

#include "observable.h"

// abstract class to observe an observable.
class Observer { // pull model Observable-Observer pair
public:
	void update(const Observable& subject);
};


#endif