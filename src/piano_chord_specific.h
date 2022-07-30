#ifndef piano_chord_specific_h
#define piano_chord_specific_h

#include <string>
#include <vector>
#include <iostream>

class PianoChordSpecific
{
public:
  std::vector<int> notes;
  std::vector<std::vector<int>> fingerings;

  PianoChordSpecific(std::vector<int> notes_, int max_reach_) : notes(notes_), max_reach(max_reach_) {};
  
  float difficulty(std::vector<int> fingerings);
  int getMaxReach() const { return max_reach; }
private:
  int max_reach;
};

#endif
