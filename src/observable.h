#ifndef observable_h
#define observable_h

#include <list>
#include "observer.h"

// abstract class to be observed by observers
class Observable { // pull model Observable-Observer pair
private:
	std::list<Observer> observer_list;

public:
	void attach(const Observer& new_observer);
	void notify(const Observable& subject);
}

#endif