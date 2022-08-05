#include "song_player.h"
#include "song_data.h"
#include <list>
#include <string>

// https://www.techiedelight.com/sleep-in-cpp/
#include <chrono>
#include <thread>

typedef std::list<PianoChord> ChordContainer;

/*
class SongPlayer {
private:
	SongData song_data;
	double seconds_per_beat; // default: 100 bpm (Beats per minute)
	double current_time;
	bool running;
*/

/* SPECS:
	@PARAM: sd: the song data for the song player
	@EFFECTS: construct a Song Player with the song data and 
	the tempo of 100 beats per minute
	@NOTES: this is the only constructor provided for this class.
*/
SongPlayer::SongPlayer(const SongData& sd){
	song_data = sd;
	seconds_per_beat = 60/100;
	current_time = 0;
	running = false;
}


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
SongPlayer::playSong(ChordContainer& displayed_chords){
	running = true;
	for(; current_time < song_data.getTotalDuration; current_time++){
		// display the chords played during this time.
		// Use this displayed_chords to see played chords.
		displayed_chords = song_data.getChordsAtTime(current_time);
		// check if the song is paused
		if (!running){
			break;
		}
		// wait until the next beat
		std::this_thread::sleep_for(std::chrono::seconds(seconds_per_beat));
	}
}

/* SPECS:
	@EFFECTS: pauses the song at the current_time
*/
SongPlayer::pauseSong(){
	running = false;
}

/* SPECS:
	@PARAM: new_current_time: the new time to start playing the Song
	@REQUIRES: 
		the SongPlayer is paused
		0 <= new_current_time <= song_data.total_beat_duration
	@EFFECTS: sets the current_time to new_current_time
*/
SongPlayer::setTime(double new_current_time){
	current_time = new_current_time;
}

/* SPECS:
	@PARAM: new_bpm: new beats per minute tempo
	@EFFECTS: 
		converts new_bpm to correct unit
		assigns speed to seconds_per_beat
*/
SongPlayer::setTempo(double new_bpm){
	seconds_per_beat = (60/new_bpm);
}