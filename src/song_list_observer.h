#ifndef song_list_observer_h
#define song_list_observer_h

#include <list>
#include "song_list_entry.h"

/*
	A concrete class. Observes a SongList, which notifies
	the observer when SongList changes.

	(7/23) This class is currently a poltergeist. >:(
*/
class SongListObserver {
private:
	std::list<SongListEntry> current_data;
	int number_of_entries;
public:
	/* SPECS:
		@PARAM: data: the data from the SongList object
		@EFFECT: updates the Observer's data to match the SongList.
	*/
	void update(const std::list<SongListEntry>& data);
};

#endif
