// Interim release main.cpp
#include "piano_chord.h"
#include "song_data.h"
#include "song_list_entry.h"
#include "song_list_data_parser_txt.h"
#include "song_list_data_writer_txt.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <utility>
#include <math.h>
#include <list>
#include <unordered_map>

typedef std::list<PianoChord> ChordContainer;
typedef std::unordered_map<std::string, std::string> MetaDataContainer; 

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
    std::cout << "Creating chord list for " << chord_sequence[i].getName() << "..." << std::endl;
    chord_sequence[i].makeChordList(10, 44, MAX_REACH);
    std::cout << chord_sequence[i].getName() << ": Chord list created!" << std::endl;
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
        ostr << "Chord: " << chord_sequence[i].getName() << std::endl;
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
        ostr << chord_sequence[i].getName() << ": ";
        chord_sequence[i].print_chord(ostr);
      }
    }
    else if (input == "change_specific_chord")
    {
      ostr << "All chords:" << std::endl;
      for (unsigned int i = 0; i < chord_sequence.size(); i++)
      {
        ostr << i << ": " << chord_sequence[i].getName() << std::endl;
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
      ostr << "Chord " << chord_sequence[chord_selection].getName() << " now set to option " << specific_chord_selection << std::endl;
    }

    if (input != "") ostr << std::endl << "Enter Next Command: ";
    std::getline(istr, input);
  }
  
  ostr << std::endl;
  ostr << "Testing song_list_entry and song_data" << std::endl;
  
  std::list<PianoChord> chords (chord_sequence.begin(), chord_sequence.end());
  SongData song_data (chords);

  ostr << std::endl;
  ostr << "Chord set inside SongData: " << std::endl;
  for (ChordContainer::const_iterator itr = song_data.getChordSet().begin();
    itr != song_data.getChordSet().end(); itr++){
    
    for (unsigned int i = 0; i < (itr->getBaseChord()).size(); i++)
    {
      std::string note = intToNote((itr->getBaseChord())[i]);
      note = note.substr(0, note.size() - 1);
      note += (note.size() == 1) ? " " : "";
      ostr << "| " << note << " ";
    }
    ostr << "|" << std::endl;
  }

  SongListEntry sle (song_data);

  ostr << std::endl;
  ostr << "Chord set inside SongListEntry: " << std::endl;
  for (ChordContainer::const_iterator itr = sle.getSongData().getChordSet().begin();
    itr != sle.getSongData().getChordSet().end(); itr++){
    
    for (unsigned int i = 0; i < (itr->getBaseChord()).size(); i++)
    {
      std::string note = intToNote((itr->getBaseChord())[i]);
      note = note.substr(0, note.size() - 1);
      note += (note.size() == 1) ? " " : "";
      ostr << "| " << note << " ";
    }
    ostr << "|" << std::endl;
  }
  
  ostr << std::endl;
  ostr << "SongListEntry metadata (print method):" << std::endl;
  sle.printMetaData(ostr);
  
  ostr << std::endl;
  ostr << "SongListEntry: testing editMetaData" << std::endl;
  sle.editMetaData("SONG NAME", "Never gonna give you up");
  sle.editMetaData("COMPOSER", "Rick Astley");
  sle.editMetaData("ALBUM", "Operation Carnate Medallion playlist");
  sle.editMetaData("DATE ADDED TO LIST", "Since the end of time~~");
  sle.editMetaData("EXTRA INFO", "LET\'S MAKE SOME NOISE");
  
  sle.printMetaData(ostr);

  ostr << std::endl;
  ostr << "SongListEntry: testing getSpecificMetaData" << std::endl;
  ostr << "SONG NAME: " << sle.getSpecificMetaData("SONG NAME") << std::endl;
  ostr << "EXTRA INFO: " << sle.getSpecificMetaData("EXTRA INFO") << std::endl;

  ostr << std::endl;
  ostr << "Testing SongListEntry and SongListDataParserTxt" << std::endl;
  ostr << "parsing..." << std::endl;
  SongListDataParserTxt parser;
  SongListEntry parsed_sle = parser.parse("../AppData/EXAMPLE - For Parsing - SongForMyFather.txt");
  ostr << "printing metadata:" << std::endl;
  parsed_sle.printMetaData(ostr);

  ostr << std::endl;
  ostr << "Testing SongListEntry and SongListDataWriterTxt" << std::endl;
  ostr << "creating new SongListEntry: " << std::endl;
  sle.editMetaData("SONG NAME", "Blue Skies (Infinity remix)");
  sle.editMetaData("COMPOSER", "Project Aces");
  sle.editMetaData("ALBUM", "Ace Combat Infinity Original Soundtrack");
  sle.editMetaData("DATE ADDED TO LIST", "Right now");
  sle.editMetaData("EXTRA INFO", "For Post Stall Maneuver addicts"); 
  sle.printMetaData(ostr);
  
  ostr << std::endl;
  ostr << "writing data to blue_skies.txt" << std::endl;
  SongListDataWriterTxt writer;
  writer.writeData("../AppData/blue_skies.txt", sle);

  ostr << "contents has been written in blue_skies.txt" << std::endl;
  return 0;
}


std::pair<int, std::vector<PianoChord>> findEasiestPath(std::vector<PianoChord> chord_sequence, int starting_chord)
{
  //center the leftmost note of the last chord around C3
  int center_note = 27;
  int best = chord_sequence[0].chord_list[0].notes[0];
  int best_index = 0;
  for (unsigned int i = 1; i < chord_sequence[starting_chord].chord_list.size(); i++)
  {
    if (abs(chord_sequence[0].chord_list[i].notes[0] - center_note) < abs(best - center_note))
    {
      best = chord_sequence[0].chord_list[i].notes[0];
      best_index = i;
    }
  }
  int prev_specific_chord_index = chord_sequence[0].getSpecificChordIndex();
  chord_sequence[0].setSpecificChord(best_index);
  for (unsigned int i = 1; i < chord_sequence.size(); i++)
  {
    chord_sequence[i].setSpecificChord(0);
    int min_difficulty = difficulty(chord_sequence[i-1].getSpecificChord(), chord_sequence[i].getSpecificChord());
    int min_difficulty_index = 0;
    for (unsigned int j = 1; j < chord_sequence[i].chord_list.size(); j++)
    {
      chord_sequence[i].setSpecificChord(j);
      int new_difficulty = difficulty(chord_sequence[i-1].getSpecificChord(), chord_sequence[i].getSpecificChord());
      if (new_difficulty < min_difficulty)
      {
        min_difficulty = difficulty(chord_sequence[i-1].getSpecificChord(), chord_sequence[i].getSpecificChord());
        min_difficulty_index = j;
      }
    }
    chord_sequence[i].setSpecificChord(min_difficulty_index);
    chord_sequence[i-1].setSpecificChord(prev_specific_chord_index);
    prev_specific_chord_index = chord_sequence[i].getSpecificChordIndex();
  }
  chord_sequence[chord_sequence.size()-1].setSpecificChord(prev_specific_chord_index);
  return std::make_pair(0, chord_sequence);
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
