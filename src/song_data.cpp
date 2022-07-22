#include <list>
#include "piano_chord.h"
#include "piano_chord_specific.h"
#include "song_data.h"

typedef std::list<PianoChord> ChordContainer;

// class SongData
// private:
// 	ChordContainer<PianoChord> chord_set;
// 	double total_beat_duration;

// Constructor
SongData::SongData(const ChordContainer& input_chord_set, double duration){
	chord_set = input_chord_set;
	total_beat_duration = duration;
}

// Accessors
const ChordContainer& SongData::getChordSet() const {
	return chord_set;
}
double SongData::getTotalDuration() const {
	return total_beat_duration;
}

