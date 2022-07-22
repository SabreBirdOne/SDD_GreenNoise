#include <string>
#include <map>
#include "song_data.h"
#include "song_list_entry.h"

// https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
#include <ctime> 

typedef std::map<std::string, std::string> MetaDataContainer; 

// class SongListEntry 
// private:
// 	MetaDataContainer metadata;
// 	SongData song_data;

// constructors
SongListEntry::SongListEntry(const SongData& sd){
	song_data = sd;
	metadata["Song name"] = "cool name";
	metadata["Composer"] = "cool composer";
	metadata["Album"] = "cool album";

	std::time_t result = std::time(nullptr);
	metadata["Added to list on"] = std::asctime(std::localtime(&result));
}
SongListEntry::SongListEntry(const SongData& sd, const MetaDataContainer& md){
	song_data = sd;
	metadata = md;
}