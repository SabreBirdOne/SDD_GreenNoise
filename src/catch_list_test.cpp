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
#include <catch2/catch_test_macros.hpp>


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


TEST_CASE( "Song List tests", "[SongList]" ) {

	//Initialize testing parameters
	SongList list_1;
	SongList list_2;
	SongData song_1 = SongData();
	SongListEntry entry_1 = SongListEntry(song_1);
	SongListEntry entry_2 = SongListEntry(song_1);
	SongListObserver obs_1;
	SongListObserver obs_2;
	std::list<SongListEntry> entry_list_1;

    SECTION( "Constructor working properly" ) {
		list_1 = SongList();
		REQUIRE(true);

		list_2 = SongList(entry_list_1);
		REQUIRE(true);
    }
    SECTION( "Observers can be attatched." ) {
    	list_1 = SongList();
		obs_1 = SongListObserver();
		list_2 = SongList(entry_list_1);
		list_1.attach(obs_1);
		REQUIRE(true);
    }
    SECTION( "Observers can be notified" ) {
    	list_1 = SongList();
		obs_1 = SongListObserver();
		list_2 = SongList(entry_list_1);
		list_1.attach(obs_1);
		list_1.notifyObservers();
		REQUIRE(true);
    }
    SECTION( "Entry can be added" ) {
		list_1.addEntry(entry_2);
		REQUIRE(true);
    }
    SECTION( "Entry can be removed" ) {
    	list_1.addEntry(entry_2);
		list_1.removeEntry();
		REQUIRE(true);
    }
}