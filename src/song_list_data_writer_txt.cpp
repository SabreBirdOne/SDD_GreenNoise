#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "song_list_entry.h"
#include "song_data.h"
#include "song_list_data_writer_txt.h"
typedef std::unordered_map<std::string, std::string> MetaDataContainer;
/*
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

/* SPECS:
	@PARAM: 
		filename: name of the file to write to
		sle: song list entry to write from
	@EFFECTS: writes data from SongListEntry to .txt file
*/
void SongListDataWriterTxt::writeData
(const std::string& filename, const SongListEntry& sle){
	std::ofstream outfile;
  outfile.open(filename);
  
  // write metadata first
 	const std::string ordered_keys[] = 
	{ "SONG NAME", "COMPOSER", "ALBUM", "DATE ADDED TO LIST", "EXTRA INFO" };
	for (int i = 0; i < sle.getAllMetaData().size(); i++){
		outfile << sle.getSpecificMetaData(ordered_keys[i]) << std::endl;
	}
	outfile << " | " << std::endl;

  // write songdata
  SongData sd = sle.getSongData();


  outfile.close();
}