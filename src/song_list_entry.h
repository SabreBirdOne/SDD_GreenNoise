#ifndef song_list_entry_h
#define song_list_entry_h

#include <string>
#include <map>
#include "song_data.h"

typedef std::map<std::string, std::string> MetaDataContainer; 
class SongListEntry {
private:
	MetaDataContainer metadata;
	SongData song_data;
public:
	// constructors
	SongListEntry(const SongData& sd);
	SongListEntry(const SongData& sd, const MetaDataContainer& md);

	// accessors
	const SongData& getSongData() { return song_data; }
	const MetaDataContainer& getMetaData() { return metadata; }
};

#endif
