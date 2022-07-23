#include "song_list_entry.h"
#include "song_list.h"
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

// constructors
SongList::SongList(){
	entries = std::list<SongListEntry>();
}
SongList::SongList(const std::list<SongListEntry>& input_entries){
	entries = input_entries;
}

