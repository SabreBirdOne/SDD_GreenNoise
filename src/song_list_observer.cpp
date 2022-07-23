#include "song_list_observer.h"
#include "song_list.h"

// class SongListObserver 
// private:
// 	std::list<SongListEntry> current_data;

void SongListObserver::update(const std::list<SongListEntry>& data){
	current_data = data;
}
