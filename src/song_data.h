#ifndef song_data_h
#define song_data_h

#include <list>
#include "piano_chord.h"
#include "piano_chord_specific.h"

typedef std::list<PianoChord> ChordContainer;

class SongData {
private:
	ChordContainer chord_set;
	double total_beat_duration;

public:
	// Constructor
	SongData();
	SongData(const ChordContainer& input_chord_set, double duration);
	SongData(const SongData& sd);
	void operator=(const SongData& sd);
	
	// Accessors
	const ChordContainer& getChordSet() const;
	double getTotalDuration() const;

	// Modifiers
	
};

#endif