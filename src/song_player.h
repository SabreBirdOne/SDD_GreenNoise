#ifndef song_player_h
#define song_player_h

#include "song_data.h"
#include <list>
#include <string>

/*
	A Concrete class. It uses SongData to display the set of PianoChord
	to play at certain times. Useful for the practice screen.

	Strategy Design Pattern, State Design Pattern
*/
class SongPlayer {
private:
	double seconds_per_beat; // default: 100 bpm (Beats per minute)
	double current_time;
	bool state;
public:
	
	/* SPECS:
		@EFFECTS: construct a Song Player with the tempo of 100 beats per minute
	*/
	SongPlayer();

	/* SPECS:
		@PARAM: song_data: the song data to display chord data.
		@EFFECTS: play the song at the specified bpm/seconds_per_beat
		@NOTES:
			This algorithm's behavior will change based on the internal state
			of the song! 
				The pauseSong() function will interrupt the internal 
				for loop of this function.
				The setTempo() function can alter the speed of the song
				when the song is paused.
				The setTime() function lets user alter the time when the
				song is paused.
	*/
	playSong(const SongData& song_data);

	/* SPECS:
		@EFFECTS: pauses the song at the current_time
	*/
	pauseSong();

	/* SPECS:
		@PARAM: new_current_time: the new time to start playing the Song
		@REQUIRES: 
			the SongPlayer is paused
			0 <= new_current_time <= total_beat_duration
		@EFFECTS: sets the current_time to new_current_time
	*/
	setTime(double new_current_time);
	setTempo(double new_bpm);
}

#endif