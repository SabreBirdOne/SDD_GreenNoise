#ifndef song_list_h
#define song_list_h

#include "song_list_entry.h"
#include "song_list_observer.h"

#include <list>
/* 
	Responsibilities:
	- Store the songs in a List. 
	- Loading songs from a folder on program startup

	This class is the Observable class for the Observer 
	design pattern. 
*/

class SongList {
private:
	std::list<SongListObserver> observer_list;
	std::list<SongListEntry> entries;

public:
	// constructors
	SongList();
	SongList(const std::list<SongListEntry>& input_entries);

	// special: observer design pattern
	void attach(const SongListObserver& new_observer);
	void notifyObservers();
};

#endif