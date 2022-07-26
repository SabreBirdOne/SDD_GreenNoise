#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "song_list_entry.h"
#include "song_data.h"

typedef std::unordered_map<std::string, std::string> MetaDataContainer;
/*
	SongListEntry has:
		metadata: mapping category to content
		songdata: 
			total_beat_duration: double
			chord_set: collection of PianoChords.
				PianoChord has:
*/

/* SPECS:
	@PARAM: filename: name of the file to parse from
	@RETURNS: a song list entry
*/
static SongListEntry SongListDataParserTxt::parse(const std::string& filename){
	
}
