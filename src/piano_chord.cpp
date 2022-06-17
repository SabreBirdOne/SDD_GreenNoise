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


std::string intToNote(int note)
{
  if (note == 1) return "A";
  if (note == 2) return "Bb";
  if (note == 3) return "B";
  if (note == 4) return "C";
  if (note == 5) return "C#";
  if (note == 6) return "D";
  if (note == 7) return "Eb";
  if (note == 8) return "E";
  if (note == 9) return "F";
  if (note == 10) return "F#";
  if (note == 11) return "G";
  if (note == 12) return "Ab";
  return "";
}

void PianoChord::addNotes(std::vector<int> notes)
{
  bool add_extra_bass_note = false;
  int new_note;
  if (static_bass_note)
  {
    for (int i = 0; i < notes.size(); i++)
    {
      new_note = base_chord[1] + notes[i] - 1;
      if (new_note > 12) new_note %= 12;
      
      if (new_note == base_chord[0])
      {
        if (add_extra_bass_note) base_chord.push_back(new_note);
        add_extra_bass_note = true;
      }
      else
      {
        base_chord.push_back(new_note);
      }
    }
  }
  else
  {
    for (int i = 0; i < notes.size(); i++)
    {
      new_note = base_chord[0] + notes[i] - 1;
      if (new_note > 12) new_note %= 12;
      base_chord.push_back(new_note);
    }
  }
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
  base_chord.clear();
  std::string root_note; // root_note is the 1st interval of the chord
  std::string bass_note = ""; // bass_note stores the bass note for inversions, otherwise is ""
  int space_index = name_.find(" ");
  root_note = name_.substr(0, space_index);
  name_ = name_.substr(space_index + 1, name_.size() - space_index - 1);
  if (name_.find("/") != std::string::npos)
  {
    /* This section executes when the chord is in slash-inversion notation
     */
    static_bass_note = true;
    space_index = name_.find("/");
    bass_note = name_.substr(space_index + 1, name_.size() - space_index - 1);
    name_ = name_.substr(0, space_index);
    base_chord.push_back(noteToInt(bass_note));
  }
  
  if (bass_note == "")
  {
    /* This section executes if there is no inversion
     */
    static_bass_note = false;
  }
  base_chord.push_back(noteToInt(root_note));


  std::vector<int> notes;
  if (name_ == "augmented")
  {
    addNotes({5, 9});
  }
  else if (name_ == "augmented-seventh")
  {
    addNotes({5, 9, 12});
  }
  else if (name_ == "diminished")
  {
    addNotes({4, 7});
  }
  else if (name_ == "diminished-seventh")
  {
    addNotes({4, 7, 10});
  }
  else if (name_ == "dominant")
  {
    addNotes({5, 8, 11});
  }
  else if (name_ == "dominant-11th")
  {
    addNotes({5, 8, 11, 15, 18});
  }
  else if (name_ == "dominant-13th")
  {
    addNotes({5, 8, 11, 15, 18, 22});
  }
  else if (name_ == "dominant-ninth")
  {
    addNotes({5, 8, 11, 15});
  }
  else if (name_ == "French")
  {
  }
  else if (name_ == "German")
  {
  }
  else if (name_ == "half-diminished")
  {
    addNotes({4, 7, 11});
  }
  else if (name_ == "Italian")
  {
  }
  else if (name_ == "major")
  {
    addNotes({5, 8});
  }
  else if (name_ == "major-11th")
  {
    addNotes({5, 8, 12, 15, 18});
  }
  else if (name_ == "major-13th")
  {
    addNotes({5, 8, 12, 15, 18, 22});
  }
  else if (name_ == "major-minor")
  {
    addNotes({4, 8, 12});
  }
  else if (name_ == "major-ninth")
  {
    addNotes({5, 8, 12, 15});
  }
  else if (name_ == "major-seventh")
  {
    addNotes({5, 8, 12});
  }
  else if (name_ == "major-sixth")
  {
  }
  else if (name_ == "minor")
  {
    addNotes({4, 8});
  }
  else if (name_ == "minor-11th")
  {
  }
  else if (name_ == "minor-13th")
  {
  }
  else if (name_ == "minor-ninth")
  {
    addNotes({4, 8, 11, 15});
  }
  else if (name_ == "minor-seventh")
  {
    addNotes({4, 8, 11});
  }
  else if (name_ == "minor-sixth")
  {
  }
  else if (name_ == "Neapolitan")
  {
  }
  else if (name_ == "none")
  {
  }
  else if (name_ == "other")
  {
  }
  else if (name_ == "pedal")
  {
  }
  else if (name_ == "power")
  {
  }
  else if (name_ == "suspended-fourth")
  {
  }
  else if (name_ == "suspended-second")
  {
  }
  else if (name_ == "Tristan")
  {
  }
  else
  {
  }
}


void PianoChord::print_base_chord()
{
  for (int i = 0; i < base_chord.size(); i++)
  {
    std::cout << "|" << intToNote(base_chord[i]);
  }
  std::cout << "|" << std::endl;
}
