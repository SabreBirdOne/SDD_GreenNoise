#include "piano_chord.h"
#include <string>
#include <math.h>
#include <stdio.h>

#include <iostream>

int noteToInt(std::string note)
{
  if (note == "A") return 0;
  if (note == "Bb" || note == "A#") return 1;
  if (note == "B") return 2;
  if (note == "C") return 3;
  if (note == "C#" || note == "Db") return 4;
  if (note == "D") return 5;
  if (note == "Eb" || note == "D#") return 6;
  if (note == "E") return 7;
  if (note == "F") return 8;
  if (note == "F#" || note == "Gb") return 9;
  if (note == "G") return 10;
  if (note == "Ab" || note == "G#") return 11;
  return 0;
}


std::string intToNote(int note)
{
  std::string return_string;
  if (note % 12 == 0) return_string = "A";
  if (note % 12 == 1) return_string = "Bb";
  if (note % 12 == 2) return_string = "B";
  if (note % 12 == 3) return_string = "C";
  if (note % 12 == 4) return_string = "C#";
  if (note % 12 == 5) return_string = "D";
  if (note % 12 == 6) return_string = "Eb";
  if (note % 12 == 7) return_string = "E";
  if (note % 12 == 8) return_string = "F";
  if (note % 12 == 9) return_string = "F#";
  if (note % 12 == 10) return_string = "G";
  if (note % 12 == 11) return_string = "Ab";
  note -= 3;
  return_string += std::to_string((int)(floor((float)note / 12) + 1));
  return return_string;
}

PianoChord::PianoChord(std::string name_){
  name = name_;
  parseChord(name_);
}

void PianoChord::addNotes(std::vector<int> notes)
{
  bool add_extra_bass_note = false;
  int new_note;
  if (static_bass_note)
  {
    for (unsigned int i = 0; i < notes.size(); i++)
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
    for (unsigned int i = 0; i < notes.size(); i++)
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
  //int notes_file = open("chord_types.json", O_RDONLY);
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


std::vector<std::vector<int>> makeChordListHelper(int next_note, int max_note, std::vector<int> notes)
{
  std::vector<std::vector<int>> return_vector;
  for (; next_note <= max_note; next_note++)
  {
    for (unsigned int i = 0; i < notes.size(); i++)
    {
      if (next_note % 12 == notes[i])
      {
        std::vector<int> new_notes = notes;
        new_notes.erase(new_notes.begin() + i);
        std::vector<std::vector<int>> sub_chords = makeChordListHelper(next_note + 1, max_note, new_notes);
        for (unsigned int j = 0; j < sub_chords.size(); j++)
        {
          sub_chords[j].push_back(next_note);
          return_vector.push_back(sub_chords[j]);
        }
        if (new_notes.size() == 0)
        {
          std::vector<int> sub_chord = {next_note};
          return_vector.push_back(sub_chord);
        }
      }
    }
  }
  return return_vector;
}


void PianoChord::makeChordList(int min_note, int max_note, int max_distance)
{
  std::vector<std::vector<int>> chord_list_vector;
  if (static_bass_note)
  {
  }
  else
  {
    while (min_note + max_distance <= max_note)
    {
      std::vector<std::vector<int>> new_chord_list_vector = makeChordListHelper(min_note, 
                  min_note + max_distance, base_chord);
      for (unsigned int i = 0; i < new_chord_list_vector.size(); i++)
      {
        for (unsigned int j = 0; j < chord_list_vector.size(); j++)
        {
          if (new_chord_list_vector[i] == chord_list_vector[j])
          {
            new_chord_list_vector.erase(new_chord_list_vector.begin() + i);
            i--;
            break;
          }
        }
        //chord_list_vector.push_back(new_chord_list_vector[i]);
      }
      chord_list_vector.insert(chord_list_vector.end(), new_chord_list_vector.begin(), new_chord_list_vector.end());
      min_note++;
    }
  }
  for (unsigned int i = 0; i < chord_list_vector.size(); i++)
  {
    // reverse the order of the notes in each set of notes and add to PianoChord::chord_list
    std::vector<int> new_chord(chord_list_vector[i].size());
    for (int j = chord_list_vector[i].size(); j > 0; j--)
    {
      new_chord[chord_list_vector[i].size() - j] = chord_list_vector[i][j - 1];
    }
    chord_list.push_back(PianoChordSpecific(new_chord, max_distance));
  }
  return;
}


void PianoChord::print_base_chord(std::ostream &ostr)
{
  for (unsigned int i = 0; i < base_chord.size(); i++)
  {
    std::string note = intToNote(base_chord[i]);
    note = note.substr(0, note.size() - 1);
    note += (note.size() == 1) ? " " : "";
    ostr << "| " << note << " ";
  }
  ostr << "|" << std::endl;
}


void PianoChord::print_chord(std::ostream &ostr)
{
  PianoChordSpecific *chord = &chord_list[specific_chord];
  for (unsigned int i = 0; i < chord->notes.size(); i++)
  {
    ostr << "|" << intToNote(chord->notes[i]);
  }
  /*
  ostr << "| ";
  for (int i = 0; i < chord->fingerings.size(); i++)
  {
    ostr << "|" << chord->fingerings[i];
  }
  */
  ostr << "|" << std::endl;
}


void PianoChord::print_chord_list(std::ostream &ostr)
{
  for (unsigned int i = 0; i < chord_list.size(); i++)
  {
    PianoChordSpecific *chord = &chord_list[i];
    for (unsigned int j = 0; j < chord->notes.size(); j++)
    {
      std::string note = intToNote(chord->notes[j]);
      note += (note.size() == 2) ? " " : "";
      ostr << "| " << note << " ";
    }
    ostr << "|" << std::endl;
  }
}
