#ifndef song_list_data_parser_txt_h
#define song_list_data_parser_txt_h

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "song_list_entry.h"
#include "song_data.h"

typedef std::unordered_map<std::string, std::string> MetaDataContainer;
/*
	A concrete class. It is mainly responsible for parsing 
	specially formatted .txt files into data used to reconstruct 
	SongListEntry objects.

	Notes: when the app terminates, we'd like a form of persistent 
	data so that when the app is run again, the song list data
	is restored and ready for use. 

	To accomplish this, we plan on writing all data into specially formatted .txt when 
	the app closes, and read from those .txt files when the app is 
	opened. Each .txt file represents an entry in the song list.

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
class SongListDataParserTxt {
public:
	/* SPECS:
		@PARAM: filename: name of the file to parse from
		@RETURNS: a song list entry
	*/
	static SongListEntry parse(const std::string& filename);
};

#endif