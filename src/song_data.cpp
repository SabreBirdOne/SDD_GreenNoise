#include <unordered_set>
#include "piano_chord.h"
#include "piano_chord_specific.h"
#include "song_data.h"

// class SongData
// private:
// 	std::unordered_set<PianoChord> chord_set;
// 	double total_beat_duration;

// Constructor
SongData::SongData(const std::unordered_set<PianoChord>& input_chord_set, double duration){
	chord_set = input_chord_set;
	total_beat_duration = duration;
}

// Accessors
const std::unordered_set<PianoChord>& SongData::getChordSet() const {
	return chord_set;
}
double SongData::getTotalDuration() const {
	return total_beat_duration;
}

