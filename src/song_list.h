#ifndef song_list_h
#define song_list_h

#include "song_list_entry.h"
#include "observable.h"
#include "observer.h"

#include <list>
/* 
	Responsibilities:
	- Store the songs in a List. 
	- Loading songs from a folder on program startup

	This class is the Model class for the Model-View-Controller 
	Design pattern. 
*/

// class Observable // pull model Observable-Observer pair
// private:
// 	std::list<Observer> observer_list;

class SongList : public Observable {
private:
	std::list<SongListEntry> entries;

public:
	// constructors
	SongList();
	SongList(const std::list<SongListEntry>& input_entries);
}

#endif