#include "piano_chord.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

#define MAX_REACH 17

int findEasiestPath(std::vector<PianoChord>* chord_sequence, int starting_chord);
int difficulty(PianoChordSpecific chord1, PianoChordSpecific chord2);

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
  std::cout << "Chord Sequence Saved!" << std::endl;
  for (int i = 0; i < chord_sequence.size(); i++)
  {
    std::cout << "Creating chord list for " << chord_sequence[i].name << "..." << std::endl;
    usleep(50000);
    chord_sequence[i].makeChordList(10, 44, MAX_REACH);
    std::cout << chord_sequence[i].name << ": Chord list created!" << std::endl;
  }
  std::cout << "Generating specific chord path..." << std::endl;
  findEasiestPath(&chord_sequence, 0);
  std::cout << "Done!" << std::endl;



  std::string input;
  std::cout << std::endl << "Enter Next Command: ";
  std::getline(istr, input);
  while (input != "quit")
  {
    if (input == "show_all_chords")
    {
      for (int i = 0; i < chord_sequence.size(); i++)
      {
        ostr << "Chord: " << chord_sequence[i].name << std::endl;
        chord_sequence[i].print_base_chord(ostr);
        ostr << "Possible Chord Permutations:" << std::endl;
        chord_sequence[i].print_chord_list(ostr);
        ostr << std::endl;
      }
    }
    else if (input == ("show_specific_chords"))
    {
      for (int i = 0; i < chord_sequence.size(); i++)
      {
        ostr << chord_sequence[i].name << ": ";
        chord_sequence[i].print_chord(ostr);
      }
    }
    if (input != "") std::cout << std::endl << "Enter Next Command: ";
    std::getline(istr, input);
  }

  return 0;
}


int findEasiestPath(std::vector<PianoChord>* chord_sequence, int starting_chord)
{
  if (starting_chord >= (int)(*chord_sequence).size()-2)
  {
    return 0;
  }
    int min_difficulty = findEasiestPath(chord_sequence, starting_chord+1) + difficulty((*chord_sequence)[starting_chord].getSpecificChord(), (*chord_sequence)[starting_chord+1].getSpecificChord());
  int min_difficulty_index = 0;
  for (int i = 1; i < (*chord_sequence)[starting_chord].chord_list.size(); i++)
  {
    (*chord_sequence)[starting_chord].setSpecificChord(i);
    int new_difficulty = findEasiestPath(chord_sequence, starting_chord+1) + difficulty((*chord_sequence)[starting_chord].getSpecificChord(), (*chord_sequence)[starting_chord+1].getSpecificChord());
    if (new_difficulty < min_difficulty)
    {
      min_difficulty = new_difficulty;
      min_difficulty_index = i;
    }
  }
  (*chord_sequence)[starting_chord].setSpecificChord(min_difficulty_index);
  return min_difficulty;
}


int difficulty(PianoChordSpecific chord1, PianoChordSpecific chord2)
{
  int difficulty = abs(chord1.notes[0] - chord2.notes[0]);
  return difficulty;
}
