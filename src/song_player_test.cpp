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

int main(){

	//initialize testing parameters.
	double time = 12.03;
	double tempo = 120.0;
	double epsilon = 1.19209e-07;
	SongData sd1;
	ChordContainer c1;

	//Test 1: Constructor
	SongPlayer p1 = SongPlayer(sd1);
	assert(std::abs(sd1.getTotalDuration() - p1.getSongData().getTotalDuration()) < epsilon);
	assert(sd1.getChordSet() == p1.getSongData().getChordSet());
	assert(std::abs(p1.getSecondsPerBeat() - 60/100) < epsilon);
	assert(std::abs(p1.getCurrentTime() - 0) < epsilon);
	assert(p1.isRunning() == false);

	//Test 2: Playing a Song
	p1.playSong(&c1);
	assert(p1.isRunning() == true);

	//Test 3: Pausing a Song
	p1.pauseSong();
	assert(p1.isRunning() == false);

	//Test 4: Setting the Time
	p1.setTime(time);
	assert(std::abs(p1.getCurrentTime() - time) < epsilon);

	//Test 5: Setting the Tempo
	p1.setTempo(tempo);
	assert(std::abs(p1.getSecondsPerBeat() - 60/tempo) < epsilon);

	return 0;
}
