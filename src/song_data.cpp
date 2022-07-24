#include <list>
#include "piano_chord.h"
#include "piano_chord_specific.h"
#include "song_data.h"

typedef std::list<PianoChord> ChordContainer;

// class SongData
// private:
// 	ChordContainer chord_set;
// 	double total_beat_duration;

// checking representation invariant
void SongData::checkRep(){
	for (ChordContainer::const_iterator itr = chord_set.begin();
		itr != chord_set.end(); itr++){
		double chord_end_time = itr->getBeatStart() + itr->getBeatDuration();
		if (total_beat_duration < chord_end_time){
			std::cerr << "ERROR: SongData.checkRep(): ";
			std::cerr << "a chord ends before the total duration." << std::endl;
			std::cerr << "total_beat_duration: " << total_beat_duration;
			std::cerr << "end time of the last chord: " << chord_end_time << std::endl;
		}
	}
}

// Constructor
SongData::SongData(){
	chord_set = ChordContainer();
	total_beat_duration = 0.0;
	checkRep();
}

SongData::SongData(const ChordContainer& input_chord_set, double duration){
	chord_set = input_chord_set;
	total_beat_duration = duration;
	checkRep();
}
SongData::SongData(const SongData& sd){
	this->chord_set = sd.chord_set;
	this->total_beat_duration = sd.total_beat_duration; 
	this->checkRep();
}
void SongData::operator=(const SongData& sd){
	this->chord_set = sd.chord_set;
	this->total_beat_duration = sd.total_beat_duration; 
	this->checkRep();	
}
// Accessors
const ChordContainer& SongData::getChordSet() const {
	return chord_set;
}
double SongData::getTotalDuration() const {
	return total_beat_duration;
}

