#include "song_list_entry.h"
#include "song_list.h"


#include <list>
/* 
	Responsibilities:
	- Store the songs in a List. 
	- Loading songs from a folder on program startup

	This class is the Model class for the Model-View-Controller 
	Design pattern. 
*/

// class SongList
// private:
// 	std::list<SongListObserver> observer_list;
// 	std::list<SongListEntry> entries;

// constructors
SongList::SongList(){
	entries = std::list<SongListEntry>();
}
SongList::SongList(const std::list<SongListEntry>& input_entries){
	entries = input_entries;
}
// special: observer design pattern
void SongList::attach(const SongListObserver& new_observer){
	observer_list.push_back(new_observer);
}
void SongList::notifyObservers(){
	for (std::list<SongListObserver>::iterator itr = observer_list.begin();
		itr != observer_list.end(); itr++ ){
		itr->update(entries);
	}
}

void SongList::addEntry(const SongListEntry& new_entry){
	entries.push_back(new_entry); 
	notifyObservers();
}
void SongList::removeEntry(std::list<SongListEntry>::iterator& entry_itr){
	entries.erase(entry_itr);
	notifyObservers();
}

