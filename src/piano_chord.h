#ifndef piano_chord_h
#define piano_chord_h

#include <string>
#include <vector>
#include <iostream>
#include "piano_chord_specific.h"

/*----------------------------------------------------------------------------------------*\
 * In each octave, there are 12 notes:
 *    Ab A Bb B C C# D Eb E F F# G
 *
 *                       One octave on a piano keyboard:
 *   _____________________________________________________________________
 *    |     |     |   |     |     |     |     |   |     |   |     |     |
 *    |     |     |   |     |     |     |     |   |     |   |     |     |
 *    |     |     |   |     |     |     |     |   |     |   |     |     |
 *    |     |     |   |     |     |     |     |   |     |   |     |     |
 *    |     |     |   |     |     |     |     |   |     |   |     |     |
 *    |     | C#  |   | Eb  |     |     | F#  |   | Ab  |   | Bb  |     |
 *    |     |     |   |     |     |     |     |   |     |   |     |     |
 *    |     |_____|   |_____|     |     |_____|   |_____|   |_____|     |
 *    |        |         |        |        |         |         |        |
 *    |        |         |        |        |         |         |        |
 *    |        |         |        |        |         |         |        |
 *    |        |         |        |        |         |         |        |
 *    |        |         |        |        |         |         |        |
 *    |        |         |        |        |         |         |        |
 *    |        |         |        |        |         |         |        |
 *    |   C    |    D    |   E    |   F    |   G     |    A    |   B    |
 *    |        |         |        |        |         |         |        |
 *    |________|_________|________|________|_________|_________|________|
 *
 * In our implementation, to make things simpler (and faster), each base note will
 * correspond to an integer value:
 *
 *    +----+----+----+----+----+----+----+----+----+----+----+----+
 *    | A  | Bb | B  | C  | C# | D  | Eb | E  | F  | F# | G  | Ab |
 *    +----+----+----+----+----+----+----+----+----+----+----+----+
 *    | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 | 11 |
 *    +----+----+----+----+----+----+----+----+----+----+----+----+
 *    
 * Additionally, a standard piano has 88 keys, with the first key being A. At the end of
 * each octave, a new octave starts (from C). To account for different octaves, notes
 * are notated as follows:
 *
 *    C4 -> C in the 4th octave
 *
 * Using the updated notation above, the entire keyboard would look as such:
 *
 *    +-----+-----+-----+-       -+-----+-----+-----+-       -+-----+-----+-----+
 *    | A0  | Bb0 | B0  |         | Ab1 | A2  | Bb2 |         | Bb8 | B8  | C9  |
 *    +-----+-----+-----+-  ...  -+-----+-----+-----+-  ...  -+-----+-----+-----+
 *    |  0  |  1  |  2  |         | 11  | 12  | 13  |         | 85  | 86  | 87  |
 *    +-----+-----+-----+-       -+-----+-----+-----+-       -+-----+-----+-----+
 *
 * This gives us the two integer values we need to define each note: there is a base note
 * value (0 - 11) and a specific note value (0 - 87). Every possible specific note can be
 * defined by:
 *    
 *    <base note> + 12 * <current octave - 1>
 *
 * so for F# in the 6th octave, the integer value would be:
 *
 *    9 + 12 * (6 - 1) = 69
 *
 *                      --------------------------------------------
 *
 * One chord is a set of notes played at the same time. This is stored as a vector of
 * integer values, each entry corresponding to a note. At the time of creation, there is
 * only a base chord, which tells the user the type of notes that must be played (consists
 * of only base notes 1 - 12). Specific chords will be created by external algorithms.
\*----------------------------------------------------------------------------------------*/

class PianoChord
{
public:
  PianoChord(std::string name_);
  void makeChordList(int min_note, int max_note, int max_distance);
  void print_base_chord(std::ostream &ostr);
  void print_chord(std::ostream &ostr);
  void print_chord_list(std::ostream &ostr);
  std::vector<PianoChordSpecific> chord_list;
  std::string name;
  void setSpecificChord(int index) { specific_chord = index; }
  PianoChordSpecific getSpecificChord() { return chord_list[specific_chord]; }


private:
  std::vector<int> base_chord;
  int specific_chord = 0;
  bool static_bass_note;

  double beat_start;    // the start time of a chord in beats
  double beat_duration; // measure of duration of chord in beats

  void parseChord(std::string name_);
  void addNotes(std::vector<int> notes);
};

std::string intToNote(int note);
#endif
