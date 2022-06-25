#ifndef piano_chord_specific_h
#define piano_chord_specific_h

#include <string>
#include <vector>
#include <iostream>

class PianoChordSpecific
{
public:
  PianoChordSpecific(std::vector<int> notes_) : notes(notes_) {};
  std::vector<int> notes;
  //std::vector<int> fingerings;
private:
};

#endif
