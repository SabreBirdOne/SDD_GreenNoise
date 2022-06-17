#include "piano_chord.h"
#include <iostream>

int main()
{
  std::cout << "Type a chord in the format \"<root note> <chord type>/<inversion>\" (the \"/inversion\" is optional)" << std::endl << "Type \"quit\" to exit." << std::endl;
  std::string chord;
  std::getline(std::cin, chord);
  while(chord != "quit")
  {
    PianoChord chord1 = PianoChord(chord);
    chord1.print_base_chord();
    std::getline(std::cin, chord);
  }
  return 0;
}
