#include "piano_chord.h"
#include <iostream>
#include <vector>

int main()
{
  std::cout << "Type a chord in the format \"<root note> <chord type>/<inversion>\" (the \"/inversion\" is optional)" << std::endl << "Type \"end\" to mark the end of the input, or \"quit\" to exit." << std::endl;
  std::vector<PianoChord> chord_sequence;
  std::string chord;
  std::getline(std::cin, chord);
  while(chord != "quit" && chord != "end")
  {
    chord_sequence.push_back(PianoChord(chord));
    //PianoChord chord1 = PianoChord(chord);
    //chord1.print_base_chord();
    std::getline(std::cin, chord);
  }
  if (chord == "quit") return 0;

  for (int i = 0; i < chord_sequence.size(); i++)
  {
    chord_sequence[i].print_base_chord();
  }

  return 0;
}
