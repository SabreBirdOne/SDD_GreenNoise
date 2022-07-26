#ifndef song_list_entry_h
#define song_list_entry_h

#include <string>
#include <unordered_map>
#include "song_data.h"

typedef std::unordered_map<std::string, std::string> MetaDataContainer; 
/*
	A concrete class. Represents an entry inside the song list. 
	Decorator design pattern: A wrapper/decorator around SongData. 
	It stores song data and metadata (data about data).
	
	This is arguably not an ADT (abstract data type)
	No representation invariant. But it does contain data.

	for this specific implementation, see song_data.h for SongData class
	info. As for metadata, it is an associative container mapping 
	a category to its content. (e.g. Song Name: Never Gonna Give You Up)
*/
class SongListEntry {
private:
	MetaDataContainer metadata;
	SongData song_data;
public:
	// constructors
	/* SPECS:
		@PARAM: sd: SongData to construct an entry
		@EFFECTS: constructs a new SongListEntry with given SongData and
		arbitrary (default) metadata.
	*/
	SongListEntry(const SongData& sd);

	// accessors
	
	/* SPECS:
		@RETURNS: a copy of internal SongData
	*/
	const SongData& getSongData() { return song_data; }
	
	/* SPECS:
		@RETURNS: a copy of internal metadata
	*/
	const MetaDataContainer& getMetaData() { return metadata; }
};

#endif
