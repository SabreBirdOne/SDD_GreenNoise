#ifndef song_data_h
#define song_data_h

#include <list>
#include "piano_chord.h"
#include "piano_chord_specific.h"

typedef std::list<PianoChord> ChordContainer;

/*
	A concrete class. SongData stores the chord data about the song and the song's duration.
	Measurements of time are in beats.
	
	Representation Invariant: 
		total_beat_duration >= the time when the last chord ends.
		total_beat_duration >= 0
		all times for each chord >= 0
	Abstraction Function: 
		total_beat_duration -> duration of the song data in beats
		chord_set -> collection of chords
*/
class SongData {
private:
	ChordContainer chord_set;
	double total_beat_duration;
	void checkRep();

public:
	// Constructor
	/* SPECS:
		@EFFECTS: create an empty SongData object
		@NOTES: I don't know why you would need it but just in case.
	*/
	SongData();

	/* SPECS:
		@PARAM:	input_chord_set: a set of chords going in.
		@EFFECTS: create SongData with initial chord set and duration.
	*/
	SongData(const ChordContainer& input_chord_set);
	
	/* SPECS:
		@PARAM: sd: a SongData object
		@EFFECTS: copy constructor
	*/
	SongData(const SongData& sd);

	/* SPECS:
		@PARAM: sd: a SongData object
		@EFFECTS: overload of the assignment operator.
	*/
	void operator=(const SongData& sd);
	
	// Accessors

	/* SPECS:
		@RETURN: a copy of the collection of chords in the SongData
	*/
	const ChordContainer& getChordSet() const;
	
	/* SPECS:
		@RETURN: the total duration of the SongData in beats
	*/
	double getTotalDuration() const;

	/* SPECS: 
		@PARAM:	time: the time point to get PianoChord data from
		@REQUIRES: 0 <= time
		@RETURNS: a collection of PianoChords that are played at the specified time
		@NOTES:
			recommended that the time parameter be something sensical, or else
			you get an empty list. This is confounding because:
			Is the time beyond the duration of the song data or is it really
			that there is no sound at that time?
	*/
	const ChordContainer& getChordsAtTime(double time) const;  

	// Modifiers
	// maybe for editing chords in the edit screen??
	// When debugging, remember to checkRep() to validate object 
	// after internal state changes.
};

#endif