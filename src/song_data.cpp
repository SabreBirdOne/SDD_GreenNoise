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
	if (total_beat_duration < 0){
		std::cerr << "ERROR: SongData.checkRep(): total_beat_duration is negative" << std::endl;
		std::cerr << "total_beat_duration: " << total_beat_duration << std::endl;
	}

	for (ChordContainer::const_iterator itr = chord_set.begin();
		itr != chord_set.end(); itr++){

		if (itr->getBeatStart() < 0){
			std::cerr << "ERROR: SongData.checkRep(): beat start time is negative" << std::endl;
			std::cerr << "itr->getBeatStart(): " << itr->getBeatStart() << std::endl;
		}
		if (itr->getBeatDuration() < 0){
			std::cerr << "ERROR: SongData.checkRep(): beat duration time is negative" << std::endl;
			std::cerr << "itr->getBeatDuration(): " << itr->getBeatDuration() << std::endl;
		}
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

SongData::SongData(const ChordContainer& input_chord_set){
	chord_set = input_chord_set;
	total_beat_duration = 0.0;
	for (ChordContainer::const_iterator itr = chord_set.begin();
		itr != chord_set.end(); itr++){
		double chord_end_time = itr->getBeatStart() + itr->getBeatDuration();
		if (total_beat_duration < chord_end_time){
			total_beat_duration = chord_end_time;
		}
	}
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
const ChordContainer& SongData::getChordsAtTime(double time) const {
	ChordContainer result;
	// iterate through every chord in the chord_set
	for (ChordContainer::const_iterator itr = chord_set.begin();
		itr != chord_set.end(); itr++){
		double chord_end_time = itr->getBeatStart() + itr->getBeatDuration();
		// if the specified time is between the start time and end time of this chord,
		// then this chord plays at this time.
		if (itr->getBeatStart() <= time && time <= chord_end_time){
			result.push_back(*itr);
		}
	}
	return result;
}  
