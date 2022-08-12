#include <list>
#include <limits>
#include <assert.h>
#include <iostream>
#include "song_data.h"
#include "song_data.cpp"
#include "piano_chord.h"
#include "piano_chord.cpp"

typedef std::list<PianoChord> ChordContainer;

/* 

	A testing suite for the song_list_entry class that
	tests the following:
		- Base Constructor Functionality 
		- Constructor with Arguments
		- Copy Constructor Functionality
		- Assignment Operator Functionality

*/

int main(){

	//Initialize testing parameters
	SongData song_1;
	SongData song_2;
	SongData song_3;
	double set_duration;
	double epsilon = 1.19209e-07;
	ChordContainer input_set;


	// Test 1: Base Constructor
	song_1 = SongData();
	assert(std::abs(song_1.getTotalDuration() - 0.0) < epsilon);


	// Test 2: Constructor Arguments 
	set_duration = 0.0;
	song_2 = SongData(input_set);
	assert(song_2.getChordSet() == input_set);
	assert(std::abs(song_2.getTotalDuration() - 0.0) < epsilon);


	// Test 3: Copy Constructor
	song_3 = SongData(song_2);
	assert(song_3.getChordSet() == song_2.getChordSet());
	assert(std::abs(song_3.getTotalDuration() - song_2.getTotalDuration()) < epsilon);


	// Test 4: Assignment Operator
	song_3 = song_1;
	assert(song_3.getChordSet() == song_1.getChordSet());
	assert(std::abs(song_3.getTotalDuration() - song_1.getTotalDuration()) < epsilon);

	std::cout << "All tests passed for song_data." << std::endl;

	return 0;
}