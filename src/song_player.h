#ifndef song_player_h
#define song_player_h

#include "song_data.h"
#include <list>
#include <string>

typedef std::list<PianoChord> ChordContainer;

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
	
	EXTRA: to convert beats per minute to seconds per beat:
	Let n be the bpm.
	then seconds_per_beat = (60/n) seconds
*/
class SongPlayer {
private:
	SongData song_data;
	double seconds_per_beat; // default: 100 bpm (Beats per minute)
	double current_time; // measured in abstract beats
	bool running;
	void checkRep();
public:
	
	/* SPECS:
		@PARAM: sd: the song data for the song player
		@EFFECTS: construct a Song Player with the song data and 
		the tempo of 100 beats per minute
		@NOTES: this is the only constructor provided for this class.
	*/
	SongPlayer(const SongData& sd);

	// ACCESSORS:
	const SongData& getSongData() const { return song_data; }
	double getSecondsPerBeat() const { return seconds_per_beat; }
	double getCurrentTime() const { return current_time; }
	bool isRunning() const { return running; }

	// MODIFIERS
	/* SPECS:
		@PARAM: displayed_chords: the chord container to contain displayed
		chords at certain times during play.
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
	void playSong(ChordContainer& displayed_chords);

	/* SPECS:
		@EFFECTS: pauses the song at the current_time
	*/
	void pauseSong();

	/* SPECS:
		@PARAM: new_current_time: the new time to start playing the Song
		@REQUIRES: 
			the SongPlayer is paused
			0 <= new_current_time <= song_data.total_beat_duration
		@EFFECTS: sets the current_time to new_current_time
	*/
	void setTime(double new_current_time);

	/* SPECS:
		@PARAM: new_bpm: new beats per minute tempo
		@EFFECTS: 
			converts new_bpm to correct unit
			assigns speed to seconds_per_beat
	*/
	void setTempo(double new_bpm);
};

#endif