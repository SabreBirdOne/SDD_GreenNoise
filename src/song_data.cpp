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
SongData::SongData(){
	chord_set = ChordContainer();
	total_beat_duration = 0.0;
}

SongData::SongData(const ChordContainer& input_chord_set, double duration){
	chord_set = input_chord_set;
	total_beat_duration = duration;
}
SongData::SongData(const SongData& sd){
	this->chord_set = sd.chord_set;
	this->total_beat_duration = sd.total_beat_duration; 
}
void SongData::operator=(const SongData& sd){
	this->chord_set = sd.chord_set;
	this->total_beat_duration = sd.total_beat_duration; 	
}
// Accessors
const ChordContainer& SongData::getChordSet() const {
	return chord_set;
}
double SongData::getTotalDuration() const {
	return total_beat_duration;
}

