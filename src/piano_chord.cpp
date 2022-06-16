#include "piano_chord.h"
#include <string>

#include <iostream>

int noteToInt(std::string note)
{
  if (note == "A") return 1;
  if (note == "Bb" || note == "A#") return 2;
  if (note == "B") return 3;
  if (note == "C") return 4;
  if (note == "C#" || note == "Db") return 5;
  if (note == "D") return 6;
  if (note == "Eb" || note == "D#") return 7;
  if (note == "E") return 8;
  if (note == "F") return 9;
  if (note == "F#" || note == "Gb") return 10;
  if (note == "G") return 11;
  if (note == "Ab" || note == "G#") return 12;
  return 0;
}


void PianoChord::parseChord(std::string name_)
{
  /* This function expects a string in the format:
   *    "<root_note> <chord_type>/<bass note for inversions(OPTIONAL)>"
   * and sets the base_chord values to the corresponding integer-note values
   * for the input chord.
   */
  std::string root_note; // root_note is the 1st interval of the chord
  std::string bass_note = ""; // bass_note stores the bass note for inversions, otherwise is ""
  int first_space_index = name_.find(" ");
  root_note = name_.substr(0, first_space_index);
  name_ = name_.substr(first_space_index + 1, name_.size() - first_space_index - 1);
  if (name_.find("/"))
  {
  }
  else
  {
    std::cout << "|" << name_ << "|" << std::endl;
  }
}
