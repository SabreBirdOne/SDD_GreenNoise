#include <ctime> 
#include <string>
#include <cstring>
#include <assert.h>
#include <iostream>
#include <unordered_map>
#include "song_data.h"
#include "song_data.cpp"
#include "piano_chord.h"
#include "piano_chord.cpp"
#include "song_list_entry.h"
#include "song_list_entry.cpp"

/* 

	A testing suite for the song_list_entry class that tests:
		- Constructors with and without predefined metadata.
		- Retrieving metadata
		- Editing metadata

*/

int main(){
	
	//Initialize testing parameters
	double duration = 1.55;
	double epsilon = 1.19209e-07;
	ChordContainer chord_set_1;
	SongData song_1 = SongData(chord_set_1);
	SongData song_2 = SongData();
	MetaDataContainer metadata_1;
	MetaDataContainer metadata_2 = {
		{"SONG NAME", "GREEN NOISE"},
		{"COMPOSER", "GREEN NOISE"},
		{"ALBUM", "GREEN NOISE"},
		{"EXTRA INFO", "GREEN NOISE"},
	};
	MetaDataContainer metadata_3;
	SongListEntry entry_1 = SongListEntry(song_1);
	SongListEntry entry_2 = SongListEntry(song_1, metadata_2);;


	//Test 1: Constructors
	song_2 = entry_1.getSongData();
	metadata_1 = entry_1.getAllMetaData();
	int x = strcmp(metadata_1["SONG NAME"].c_str(), "Cool Name");

	assert(song_2.getChordSet() == song_1.getChordSet());
	assert(std::abs(song_2.getTotalDuration() - song_1.getTotalDuration()) < epsilon);
	assert(strcmp(metadata_1["SONG NAME"].c_str(), "Cool Name") == 0);
	assert(strcmp(metadata_1["COMPOSER"].c_str(), "Cool Composer") == 0);
	assert(strcmp(metadata_1["ALBUM"].c_str(), "Cool Album") == 0);
	assert(strcmp(metadata_1["EXTRA INFO"].c_str(), "none") == 0);


	//Test2: Constructors with Metadata
	metadata_3 = entry_2.getAllMetaData();

	assert(strcmp(metadata_3["SONG NAME"].c_str(), "GREEN NOISE") == 0);
	assert(strcmp(metadata_3["COMPOSER"].c_str(), "GREEN NOISE") == 0);
	assert(strcmp(metadata_3["ALBUM"].c_str(), "GREEN NOISE") == 0);
	assert(strcmp(metadata_3["EXTRA INFO"].c_str(), "GREEN NOISE") == 0);


	//Test 3: Retrieving Metadata
	assert(strcmp(entry_2.getSpecificMetaData("SONG NAME").c_str(), "GREEN NOISE") == 0);
	assert(strcmp(entry_2.getSpecificMetaData("COMPOSER").c_str(), "GREEN NOISE") == 0);
	assert(strcmp(entry_2.getSpecificMetaData("ALBUM").c_str(), "GREEN NOISE") == 0);
	assert(strcmp(entry_2.getSpecificMetaData("EXTRA INFO").c_str(), "GREEN NOISE") == 0);
	assert(strcmp(entry_2.getSpecificMetaData("BAD NOISE").c_str(), "category not found") == 0);


	//Test 4: Editing Metadata
	entry_2.editMetaData("SONG NAME", "BLUE NOISE");
	entry_2.editMetaData("ALBUM", "RED NOISE");

	assert(strcmp(entry_2.getSpecificMetaData("SONG NAME").c_str(), "BLUE NOISE") == 0);
	assert(strcmp(entry_2.getSpecificMetaData("COMPOSER").c_str(), "GREEN NOISE") == 0);
	assert(strcmp(entry_2.getSpecificMetaData("ALBUM").c_str(), "RED NOISE") == 0);
	assert(strcmp(entry_2.getSpecificMetaData("EXTRA INFO").c_str(), "GREEN NOISE") == 0);

	std::cout << "All tests passed for song_list_entry." << std::endl;

	return 0;
}
