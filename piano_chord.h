#ifndef PIANO_CHORD_H
#define PIANO_CHORD_H


#include <string>
#include <vector>
#include <iostream>
#include "piano_chord_specific.h"

class piano_chordData;
class PianoChord
{
public:
       PianoChord(std::string name_) : name(name_) { parseChord(name_); }
      void makeChordList(int min_note, int max_note, int max_distance);
      void print_base_chord(std::ostream &ostr);
      void print_chord(std::ostream &ostr);
      void print_chord_list(std::ostream &ostr);
      std::vector<PianoChordSpecific> chord_list;
      std::string name;
      void setSpecificChord(int index) { specific_chord = index; }
      PianoChordSpecific getSpecificChord() { return chord_list[specific_chord]; }
private:

    std::vector<int> base_chord;
    int specific_chord = 0;
    bool static_bass_note;
    void parseChord(std::string name_);
    void addNotes(std::vector<int> notes);
};

std::string intToNote(int note);

#endif // PIANO_CHORD_H
