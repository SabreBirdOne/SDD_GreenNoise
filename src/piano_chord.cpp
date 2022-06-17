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
   *
   *    "<root_note> <chord_type>/<bass note for inversions(OPTIONAL)>"
   *
   * and sets the base_chord values to the corresponding integer-note values
   * for the input chord.
   *
   * If the chord is given with a slash-inversion, the base note cannot be changed.
   * In this case, PianoChord::static_bass_note (bool) is set to true, and the
   * bass note is the first note in the vector. For all other notes, order does
   * not matter.
   * However, if no slash-inversion is notated, the base note can be changed.
   * In this casem PianoChord::static_bass_note (bool) is set to false, and the
   * order of all notes in the PianoChord::base_chord (vector) does not matter.
   */
  std::string root_note; // root_note is the 1st interval of the chord
  std::string bass_note = ""; // bass_note stores the bass note for inversions, otherwise is ""
  int space_index = name_.find(" ");
  root_note = name_.substr(0, space_index);
  name_ = name_.substr(space_index + 1, name_.size() - space_index - 1);
  if (name_.find("/"))
  {
    /* This section executes when the chord is in slash-inversion notation
     */
    space_index = name_.find("/");
    bass_note = name_.substr(space_index + 1, name_.size() - space_index - 1);
    name_ = name_.substr(0, space_index);
  }
  std::cout << "|" << bass_note << "|" << std::endl;
  
  if (bass_note == "")
  {
    /* This section executes if there is no inversion
     */
    static_bass_note = false;
    base_chord.push_back(noteToInt(bass_note));
  }
  base_chord.push_back(noteToInt(root_note));
}
