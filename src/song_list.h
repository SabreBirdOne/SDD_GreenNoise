#ifndef song_list_h
#define song_list_h

#include "song_list_entry.h"
#include "song_list_observer.h"

#include <list>

/* 
	A concrete class. It stores multiple SongListEntry objects.
	It can also add and remove entries upon request.

	This class is the Observable class for the Observer 
	design pattern. 

	This class is arguably not an ADT (abstract data type)
	So no representation invariant.
*/

class SongList {
private:
	std::list<SongListObserver> observer_list;
	std::list<SongListEntry> entries;

public:
	// constructors
	/* SPECS:
		@EFFECTS: explicit default constructor. constructs an emtpy SongList
		@NOTES: helpful upon program start up for the first time.
	*/
	SongList();

	/* SPECS:
		@PARAM: input_entries: a collection of entries containing song data 
		and metadata.
		@EFFECTS: constructs a SongList with initial collection of entries.
		@NOTES: great when app starts in normal routine. Specifically, 
		use this constructor after a collection of entries has been parsed
		from appdata files.
	*/
	SongList(const std::list<SongListEntry>& input_entries);

	// special: observer design pattern
	/* SPECS:
		@PARAM: new_observer: a new observer that will watch this SongList
		@EFFECTS: attach a new observer to internal collection of observers
		@NOTES: use this in a controller class during intialization. 
		Specifically, attach observers after the SongList is set up. 
		SongList needs to know which object is currently watching it and to call
		update() for, in order for GUI to work.
	*/
	void attach(const SongListObserver& new_observer);

	/* SPECS:
		@EFFECTS: updates the information of watching observers.
	*/
	void notifyObservers();

	// modifiers - need to notifyObservers() to show internal changes to GUI.

	/* SPECS:
		@PARAM: new_entry: a new entry to the SongList
		@EFFECTS: adds the new entry to the SongList, and notify observers.
		@NOTES: helpful when user wants to enter a new entry via the GUI.
	*/
	void addEntry(const SongListEntry& new_entry);

	/* SPECS:
		@PARAM: entry_itr: a reference to an entry to the SongList
		@EFFECTS: precisely remove the referred entry from the SongList.
		and notify observers.
		
		@WARNING: entry_itr will be "broken" after calling this function.
		this is expected since the removed entry can no longer be 
		refered to in the list.

		@NOTES: you can probably gather such an entry iterator via 
		an observer to this SongList. Talk to Duy to contract a new
		method, depending on how the selecting functionality.
	  Duy needs a reference to an entry, not the entry itself,
	  because duplicates are a pain here.
	*/
	void removeEntry(std::list<SongListEntry>::iterator& entry_itr);
};

#endif