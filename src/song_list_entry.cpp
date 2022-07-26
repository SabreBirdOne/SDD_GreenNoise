#include <string>
#include <unordered_map>
#include "song_data.h"
#include "song_list_entry.h"

// https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
#include <ctime> 

typedef std::unordered_map<std::string, std::string> MetaDataContainer; 

std::string rtrim(const std::string &s)
{
	const std::string WHITESPACE = " \n\r\t\f\v";
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

// class SongListEntry 
// private:
// 	MetaDataContainer metadata;
// 	SongData song_data;

// constructors
SongListEntry::SongListEntry(const SongData& sd){
	song_data = sd;
	metadata["SONG NAME"] = "Cool Name";
	metadata["COMPOSER"] = "Cool Composer";
	metadata["ALBUM"] = "Cool Album";

	std::time_t result = std::time(nullptr);
	metadata["DATE ADDED TO LIST"] = rtrim(std::asctime(std::localtime(&result)));
	metadata["EXTRA INFO"] = "none";
}

SongListEntry::SongListEntry(const SongData& old_sd, const MetaDataContainer& old_md){
	song_data = old_sd;
	metadata = old_md;
}

// accessors
std::string SongListEntry::getSpecificMetaData(const std::string& category) const {
	MetaDataContainer::const_iterator itr = metadata.find(category);
	if (itr != metadata.end()){
		return itr->second;
	}
	return "category not found";
}

void SongListEntry::printMetaData(std::ostream& ostr) const {
	const std::string ordered_keys[] = 
	{ "SONG NAME", "COMPOSER", "ALBUM", "DATE ADDED TO LIST", "EXTRA INFO" };
	for (unsigned int i = 0; i < metadata.size(); i++){
		ostr << ordered_keys[i] << ": " << getSpecificMetaData(ordered_keys[i]) << std::endl;
	}
}

// modifiers
void SongListEntry::editMetaData(const std::string& category, 
																const std::string& new_content){
	MetaDataContainer::iterator itr = metadata.find(category);
	if (itr == metadata.end()){
		std::cerr << "ERROR: category \"" << category << "\" not found" << std::endl;
		return;
	}
	metadata[category] = new_content;
}