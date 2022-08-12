#include <list>
#include <limits>
#include <assert.h>
#include <iostream>
#include "song_data.h"
#include "song_data.cpp"
#include "piano_chord.h"
#include "piano_chord.cpp"
#include <catch2/catch_test_macros.hpp>

typedef std::list<PianoChord> ChordContainer;

/* 

	A testing suite for the song_list_entry class that
	tests the following:
		- Base Constructor Functionality 
		- Constructor with Arguments
		- Copy Constructor Functionality
		- Assignment Operator Functionality

*/

TEST_CASE( "Song Data tests", "[SongData]" ) {

	//Initialize testing parameters
	SongData song_1;
	SongData song_2;
	SongData song_3;
	double set_duration = 0.0;
	double epsilon = 1.19209e-07;
	ChordContainer input_set;

	song_1 = SongData();
	song_2 = SongData(input_set);
	song_3 = SongData(song_2);

    SECTION( "Constructor working properly" ) {
		REQUIRE(std::abs(song_1.getTotalDuration() - 0.0) < epsilon);
    }
    SECTION( "Constructor with arguments working properly" ) {
		REQUIRE(song_2.getChordSet() == input_set);
		REQUIRE(std::abs(song_2.getTotalDuration() - 0.0) < epsilon);
    }
    SECTION( "Copy constructor working" ) {
		REQUIRE(song_3.getChordSet() == song_2.getChordSet());
		REQUIRE(std::abs(song_3.getTotalDuration() - song_2.getTotalDuration()) < epsilon);
    }
    SECTION( "Assignment operator" ) {
		song_3 = song_1;
		REQUIRE(song_3.getChordSet() == song_1.getChordSet());
		REQUIRE(std::abs(song_3.getTotalDuration() - song_1.getTotalDuration()) < epsilon);

    }
}