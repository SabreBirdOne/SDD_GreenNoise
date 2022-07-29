#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "song_list_entry.h"
#include "song_data.h"
#include "song_list_data_parser_txt.h"
// https://cplusplus.com/reference/string/string/getline/

typedef std::unordered_map<std::string, std::string> MetaDataContainer;
typedef std::list<PianoChord> ChordContainer;

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
  (chord data: each chord on its own line.)
  end (delimiter to end chord data)
*/
SongListEntry SongListDataParserTxt::parse(const std::string& filename){
	std::ifstream infile;
  infile.open(filename);

  // parse meta data first
  MetaDataContainer md;
  std::string song_name;
  std::string composer;
  std::string album;
  std::string date_added_to_list;
  std::string extra_info;

  std::getline(infile, song_name);
  std::getline(infile, composer);
  std::getline(infile, album);
  std::getline(infile, date_added_to_list);
  std::getline(infile, extra_info, '|');

  md["SONG NAME"] = song_name;
  md["COMPOSER"] = composer;
  md["ALBUM"] = album;
  md["DATE ADDED TO LIST"] = date_added_to_list;
  md["EXTRA INFO"] = extra_info;

  // parse song data
  ChordContainer chord_set;
  
  
  
  SongData sd(chord_set);

  // (re)construct SongListEntry
  SongListEntry sle(sd, md);
  infile.close();

  return sle;
}
