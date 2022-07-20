#ifndef piano_chord_specific_h
#define piano_chord_specific_h

#include <string>
#include <vector>
#include <iostream>

class PianoChordSpecific
{
public:
  PianoChordSpecific(std::vector<int> notes_, int max_reach_) : notes(notes_), max_reach(max_reach_) {};
  std::vector<int> notes;
  std::vector<std::vector<int>> fingerings;
  float difficulty(std::vector<int> fingerings);
private:
  int max_reach;
};

#endif
