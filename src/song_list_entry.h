#ifndef song_list_entry_h
#define song_list_entry_h

#include <string>
#include <unordered_map>
#include <iostream>
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
		@NOTES: use this when creating brand new entry
	*/
	SongListEntry(const SongData& sd);

	/* SPECS:
		@PARAM: 
			old_sd: old SongData to reconstruct entry
			old_md: old metadata to reconstruct entry
		@EFFECTS: reconstructs a SongListEntry using parameters
		@NOTES: use this when loading SongData from the appdata.
	*/
	SongListEntry(const SongData& old_sd, const MetaDataContainer& old_md);

	// accessors
	
	/* SPECS:
		@RETURNS: a copy of internal SongData
	*/
	const SongData& getSongData() { return song_data; }
	
	/* SPECS:
		@RETURNS: a copy of internal metadata
	*/
	const MetaDataContainer& getAllMetaData() { return metadata; }

	
	/* SPECS:
		@PARAM: category: the category to look up
		@RETURNS: a copy of the content associated with the category in the metadata
		or error message if category not found
	*/
	std::string getSpecificMetaData(const std::string& category) const; 
	
	/* SPECS:
		@PARAM: ostr: the output stream to print to
		@EFFECTS: prints all of metadata in default order to ostr.
		order: SONG NAME, COMPOSER, ALBUM, DATE ADDED TO LIST, EXTRA INFO
	*/
	void printMetaData(std::ostream& ostr) const;


	// modifiers
	
	/* SPECS:
		@PARAM: 
			category: the category of metadata to edit
			new_content: the new content from user to edit the metadata
		@EFFECTS:
			if category is found in the metadata: 
				edits the metadata using category and new_content
		@EXCEPTIONS:
			prints error message if category not found
		@WARNING:
			once editMetaData is done, observers watching SongList MUST be updated
			to reflect changes.
	*/
	void editMetaData(const std::string& category, const std::string& new_content);
};

#endif
