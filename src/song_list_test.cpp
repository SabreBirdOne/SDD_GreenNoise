#include <list>
#include <assert.h>
#include "song_data.h"
#include "song_data.cpp"
#include "song_list.h"
#include "song_list.cpp"
#include "song_list_entry.h"
#include "song_list_entry.cpp"
#include "song_list_observer.h"
#include "song_list_observer.cpp"


/*

	A testing suite for the song_list class that
	tests:
		- SongList Constructors
		- Attaching Observers
		- Notifying Observers
		- Adding an Entry
		- Removing an Entry

	Uncomment Entry Removal Tests and replace assert(true)s
	once we can retrieve data from Observers.

*/

int main(){

	//Initialize testing parameters
	SongList list_1;
	SongList list_2;
	SongData song_1 = SongData();
	SongListEntry entry_1 = SongListEntry(song_1);
	SongListEntry entry_2 = SongListEntry(song_1);
	SongListObserver obs_1;
	SongListObserver obs_2;
	std::list<SongListEntry> entry_list_1;


	//Test 1: Constructors
	list_1 = SongList();
	assert(true);

	list_2 = SongList(entry_list_1);
	assert(true);


	//Test 2: Attach
	obs_1 = SongListObserver();
	list_1.attach(obs_1);
	assert(true);


	//Test 3: Notify Observers
	list_1.notifyObservers();
	assert(true);


	//Test 4: Add Entry
	list_1.addEntry(entry_2);
	assert(true);


	//Test 5: Remove Entry
	//list_1.removeEntry();
	assert(true);

	return 0;
}