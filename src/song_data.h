#ifndef song_data_h
#define song_data_h

#include <unordered_set>
#include "piano_chord.h"
#include "piano_chord_specific.h"

class SongData {
private:
	std::unordered_set<PianoChord> chord_set;
	double total_beat_duration;

public:
	SongData(const std::unordered_set& input_chord_set, double duration);
	

};

#endif