#ifndef song_list_observer_h
#define song_list_observer_h

#include <list>
#include "song_list_entry.h"

class SongListObserver {
private:
	std::list<SongListEntry> current_data;
public:
	void update(const std::list<SongListEntry>& data);
};

#endif
