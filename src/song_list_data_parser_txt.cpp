#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "song_list_entry.h"
#include "song_data.h"

typedef std::unordered_map<std::string, std::string> MetaDataContainer;
typedef std::list<PianoChord> ChordContainer;

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
  @NOTES:
  .txt data format:
  song name\n
  composer\n
  album\n
  date added to list\n
  extra info \r\t\n\r...
  | (delimiter to end extra info data)
  (song data: each chord on its own line.)
  end (delimiter to end chord data)
*/
static SongListEntry SongListDataParserTxt::parse(const std::string& filename){
	std::ofstream myfile;
  myfile.open(filename);

  // parse meta data first
  MetaDataContainer md();

  // parse song data
  double total_beat_duration = 0.0;
  ChordContainer chord_set;
  
  SongData sd(chord_set, total_beat_duration);

  // (re)construct SongListEntry
  SongListEntry sle(sd, md);
  myfile.close();

  return sle;
}
