#ifndef song_player_h
#define song_player_h

#include "song_data.h"
#include <list>
#include <string>

/*
	A Concrete class. It uses SongData to display the set of PianoChord
	to play at certain times. Useful for the practice screen.

	Strategy Design Pattern, State Design Pattern

	representation invariant: 
		0 <= current_time <= song_data.total_beat_duration
	
	abstraction function:
		song_data -> namesake
		seconds_per_beat -> tempo of the song
		current_time -> namesake
		running: true -> song is running
						 false -> song is paused

*/
class SongPlayer {
private:
	SongData song_data;
	double seconds_per_beat; // default: 100 bpm (Beats per minute)
	double current_time;
	bool running;
public:
	
	/* SPECS:
		@PARAM: sd: the song data for the song player
		@EFFECTS: construct a Song Player with the song data and 
		the tempo of 100 beats per minute
		@NOTES: this is the only constructor provided for this class.
	*/
	SongPlayer(const SongData& sd);

	/* SPECS:
		@EFFECTS: play the song at the specified bpm/seconds_per_beat
		@NOTES:
			This algorithm's behavior will change based on the internal state
			of the song. 
				The pauseSong() function will interrupt the internal 
				for loop of this function.
				The setTempo() function can alter the speed of the song
				when the song is paused.
				The setTime() function lets user alter the time when the
				song is paused.
	*/
	playSong();

	/* SPECS:
		@EFFECTS: pauses the song at the current_time
	*/
	pauseSong();

	/* SPECS:
		@PARAM: new_current_time: the new time to start playing the Song
		@REQUIRES: 
			the SongPlayer is paused
			0 <= new_current_time <= song_data.total_beat_duration
		@EFFECTS: sets the current_time to new_current_time
	*/
	setTime(double new_current_time);

	/* SPECS:
		@PARAM: new_bpm: new beats per minute tempo
		@EFFECTS: 
			converts new_bpm to correct unit
			assigns speed to seconds_per_beat
	*/
	setTempo(double new_bpm);
}

#endif