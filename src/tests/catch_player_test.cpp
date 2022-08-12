#include <list>
#include <limits>
#include <string>
#include <cstring>
#include <iostream>
#include <assert.h>
#include "song_data.h"
#include "song_data.cpp"
#include "piano_chord.h"
#include "piano_chord.cpp"
#include "song_player.h"
#include "song_player.cpp"
#include <catch2/catch_test_macros.hpp>

typedef std::list<PianoChord> ChordContainer;

/*
	A testing suite for the SongPlayer class that
	tests the following:
		- SongPlayer constructor
		- Play Song
		- Pause Song
		- setTime
		- setTempo
*/

TEST_CASE( "Song Player tests", "[SongPlayer]" ) {

    //initialize variables
	double time = 12.03;
	double tempo = 120.0;
	double epsilon = 1.19209e-07;
	SongData sd1;
	ChordContainer c1;
	SongPlayer p1 = SongPlayer(sd1);

    SECTION( "Constructor working properly" ) {
    	REQUIRE(std::abs(sd1.getTotalDuration() - p1.getSongData().getTotalDuration()) < epsilon);
		REQUIRE(sd1.getChordSet() == p1.getSongData().getChordSet());
		REQUIRE(std::abs(p1.getSecondsPerBeat() - 60/100) < epsilon);
		REQUIRE(std::abs(p1.getCurrentTime() - 0) < epsilon);
		REQUIRE(p1.isRunning() == false);
    }
    SECTION( "Song can be played" ) {
    	p1.playSong(&c1);
		REQUIRE(p1.isRunning() == true);
    }
    SECTION( "Song can be paused" ) {
    	p1.pauseSong();
		REQUIRE(p1.isRunning() == false);
    }
    SECTION( "Time can be set" ) {
    	p1.setTime(time);
		REQUIRE(std::abs(p1.getCurrentTime() - time) < epsilon);
    }
    SECTION( "Tempo can be set" ) {
    	p1.setTempo(tempo);
		assert(std::abs(p1.getSecondsPerBeat() - 60/tempo) < epsilon);
    }
}