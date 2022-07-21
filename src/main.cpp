#include "piano_chord.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <utility>
#include <math.h>

#define MAX_REACH 17


std::pair<int, std::vector<PianoChord>> findEasiestPath(std::vector<PianoChord> chord_sequence, int starting_chord);
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
  for (unsigned int i = 0; i < chord_sequence.size(); i++)
  {
    std::cout << "Creating chord list for " << chord_sequence[i].name << "..." << std::endl;
    usleep(30000);
    chord_sequence[i].makeChordList(10, 44, MAX_REACH);
    std::cout << chord_sequence[i].name << ": Chord list created!" << std::endl;
  }
  std::cout << "Generating specific chord path..." << std::endl;
  std::pair<int, std::vector<PianoChord>> result = findEasiestPath(chord_sequence, 0);
  chord_sequence = result.second;
  std::cout << "Done!" << std::endl;



  std::string input;
  std::cout << std::endl << "Enter Next Command: ";
  std::getline(istr, input);
  while (input != "quit")
  {
    if (input == "show_all_chords")
    {
      for (unsigned int i = 0; i < chord_sequence.size(); i++)
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
      for (unsigned int i = 0; i < chord_sequence.size(); i++)
      {
        ostr << chord_sequence[i].name << ": ";
        chord_sequence[i].print_chord(ostr);
      }
    }
    else if (input == "change_specific_chord")
    {
      ostr << "All chords:" << std::endl;
      for (unsigned int i = 0; i < chord_sequence.size(); i++)
      {
        ostr << i << ": " << chord_sequence[i].name << std::endl;
      }
      int chord_selection;
      ostr << "Select a chord: ";
      istr >> chord_selection;
      ostr << "Choose from the following list of chord permutations:" << std::endl;
      for (unsigned int i = 0; i < chord_sequence[chord_selection].chord_list.size(); i++)
      {
        PianoChordSpecific *chord = &(chord_sequence[chord_selection].chord_list[i]);
        ostr << i << ": ";
        for (unsigned int j = 0; j < chord->notes.size(); j++)
        {
          std::string note = intToNote(chord->notes[j]);
          note += (note.size() == 2) ? " " : "";
          ostr << "| " << note << " ";
        }
        ostr << "|" << std::endl;
      }
      int specific_chord_selection;
      ostr << "Select a permutation: ";
      std::cin >> specific_chord_selection;
      chord_sequence[chord_selection].setSpecificChord(specific_chord_selection);
      ostr << "Chord " << chord_sequence[chord_selection].name << " now set to option " << specific_chord_selection << std::endl;
    }

    if (input != "") ostr << std::endl << "Enter Next Command: ";
    std::getline(istr, input);
  }

  return 0;
}


std::pair<int, std::vector<PianoChord>> findEasiestPath(std::vector<PianoChord> chord_sequence, int starting_chord)
{
  //base case
  if (starting_chord >= (int)chord_sequence.size()-1)
  {
    //center the leftmost note of the last chord around C3
    int center_note = 27;
    int best = chord_sequence[starting_chord].chord_list[0].notes[0];
    int best_index = 0;
    for (unsigned int i = 1; i < chord_sequence[starting_chord].chord_list.size(); i++)
    {
      if (abs(chord_sequence[starting_chord].chord_list[i].notes[0] - center_note) < abs(best - center_note))
      {
        best = chord_sequence[starting_chord].chord_list[i].notes[0];
        best_index = i;
      }
    }
    chord_sequence[starting_chord].setSpecificChord(best_index);
    return std::make_pair(0, chord_sequence);
  }
  //recursion
  std::pair<int, std::vector<PianoChord>> min_difficulty = findEasiestPath(chord_sequence, starting_chord+1);
  min_difficulty.first += difficulty(chord_sequence[starting_chord].getSpecificChord(), min_difficulty.second[starting_chord+1].getSpecificChord());
  int min_difficulty_index = 0;
  for (unsigned int i = 1; i < chord_sequence[starting_chord].chord_list.size(); i++)
  {
    chord_sequence[starting_chord].setSpecificChord(i);
    std::pair<int, std::vector<PianoChord>> new_difficulty = findEasiestPath(chord_sequence, starting_chord+1);
    new_difficulty.first += difficulty(chord_sequence[starting_chord].getSpecificChord(), new_difficulty.second[starting_chord+1].getSpecificChord());
    if (new_difficulty.first < min_difficulty.first)
    {
      min_difficulty = new_difficulty;
      min_difficulty_index = i;
    }
  }
  return min_difficulty;
}


int difficulty(PianoChordSpecific chord1, PianoChordSpecific chord2)
{
  int difficulty = 0;
  int num_iterations = (chord1.notes.size() < chord2.notes.size()) ? chord1.notes.size() : chord2.notes.size();
  for (int i = 0; i < num_iterations; i++)
  {
    difficulty += pow(2, abs(chord1.notes[i] - chord2.notes[i]));
  }
  difficulty += abs((int)chord1.notes.size() - (int)chord2.notes.size());
  return difficulty;
}
