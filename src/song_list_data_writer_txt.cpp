#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "song_list_entry.h"
#include "song_data.h"
#include "song_list_data_writer_txt.h"

typedef std::unordered_map<std::string, std::string> MetaDataContainer;
typedef std::list<PianoChord> ChordContainer;
/*
	.txt data format:
	song name\n
	composer\n
	album\n
	date added to list\n
	extra info \r\t\n\r...
	| (needs this delimiter)
	(song data: each chord on its own line.)
	chord_name chord_inversion_int start_time duration_time
	end (delimiter to end chord data)
*/

/* SPECS:
	@PARAM: 
		filename: name of the file to write to
		sle: song list entry to write from
	@EFFECTS: writes data from SongListEntry to .txt file
*/
void SongListDataWriterTxt::writeData
(const std::string& filename, SongListEntry& sle) {
	std::ofstream outfile;
  outfile.open(filename);
  
  // write metadata first
 	const std::string ordered_keys[] = 
	{ "SONG NAME", "COMPOSER", "ALBUM", "DATE ADDED TO LIST", "EXTRA INFO" };
	for (unsigned int i = 0; i < sle.getAllMetaData().size(); i++){
		outfile << sle.getSpecificMetaData(ordered_keys[i]) << std::endl;
	}
	outfile << " | " << std::endl;

  // write songdata
  SongData sd = sle.getSongData();
  ChordContainer chord_set = sd.getChordSet();
  double total_beat_duration = sd.getTotalDuration();
  
  for (ChordContainer::iterator itr = chord_set.begin();
  	itr != chord_set.end(); itr++){
  	// write the name of the chord
  	outfile << itr->getName() << " ";
  	// write the specific chord index
  	outfile << itr->getSpecificChordIndex() << " ";
  	// write the start time and duration time
  	outfile << itr->getBeatStart() << " " << itr->getBeatDuration() << std::endl;
  }
  outfile << total_beat_duration << std::endl;
  outfile << "end" << std::endl;

  outfile.close();
}