#ifndef song_list_data_writer_txt_h
#define song_list_data_writer_txt_h

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "song_list_entry.h"
#include "song_data.h"


typedef std::unordered_map<std::string, std::string> MetaDataContainer;
/*
	A concrete class. It writes data from a SongListEntry object, 
	to ONE specially formatted .txt file 

	When the app terminates, we'd like a form of persistent 
	data so that when the app is run again, the song list data
	is restored and ready for use.

	Each .txt file represents an entry in the song list.
	All .txt files for song list entries are in the AppData directory.
	The path is "../AppData/song_name_data.txt"

	.txt data format:
	song name\n
	composer\n
	album\n
	date added to list\n
	extra info \r\t\n\r...
	| (needs this delimiter)
	(song data: each chord on its own line.)
	end (delimiter to end chord data)
*/
class SongListDataWriterTxt {
public:
	/* SPECS:
		@PARAM: 
			filename: name of the file to write to
			sle: song list entry to write from
		@EFFECTS: writes data from SongListEntry to .txt file
	*/
	void writeData(const std::string& filename, const SongListEntry& sle);
};

#endif