#include "piano_chord.h"
#include <iostream>
#include <vector>

int main()
{
  std::ostream &ostr = std::cout;
  std::istream &istr = std::cin;
  ostr << "Type a chord in the format \"<root note> <chord type>/<inversion>\" (the \"/inversion\" is optional)" << std::endl << "Type \"end\" to mark the end of the input, or \"quit\" to exit." << std::endl;
  std::vector<PianoChord> chord_sequence;
  std::string chord;
  std::getline(istr, chord);
  while(chord != "quit" && chord != "end")
  {
    chord_sequence.push_back(PianoChord(chord));
    //PianoChord chord1 = PianoChord(chord);
    //chord1.print_base_chord();
    std::getline(istr, chord);
  }
  if (chord == "quit") return 0;

  for (int i = 0; i < chord_sequence.size(); i++)
  {
    ostr << "Chord: " << chord_sequence[i].name << std::endl;
    chord_sequence[i].print_base_chord(ostr);
    chord_sequence[i].makeChordList(0, 87, 19);
    ostr << "Possible Chord Permutations:" << std::endl;
    chord_sequence[i].print_chord_list(ostr);
    ostr << std::endl;
  }

  return 0;
}
