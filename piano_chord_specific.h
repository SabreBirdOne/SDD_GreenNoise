#ifndef PIANO_CHORD_SPECIFIC_H
#define PIANO_CHORD_SPECIFIC_H

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

#endif // PIANO_CHORD_SPECIFIC_H
