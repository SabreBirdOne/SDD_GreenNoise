#include <string>
#include <unordered_map>
#include "song_data.h"
#include "song_list_entry.h"

// https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
#include <ctime> 

typedef std::unordered_map<std::string, std::string> MetaDataContainer; 

// class SongListEntry 
// private:
// 	MetaDataContainer metadata;
// 	SongData song_data;

// constructors
SongListEntry::SongListEntry(const SongData& sd){
	song_data = sd;
	metadata["SONG NAME"] = "cool name";
	metadata["COMPOSER"] = "cool composer";
	metadata["ALBUM"] = "cool album";

	std::time_t result = std::time(nullptr);
	metadata["DATE ADDED TO LIST"] = std::asctime(std::localtime(&result));
}
