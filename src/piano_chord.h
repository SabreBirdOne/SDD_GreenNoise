#ifndef piano_chord_h
#define piano_chord_h

#include <string>
#include <vector>

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
 *    | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 | 11 | 12 |
 *    +----+----+----+----+----+----+----+----+----+----+----+----+
 *    
 * Additionally, a standard piano has 88 keys, with the first key being A. At the end of
 * each octave, a new octave starts (from A). To account for different octaves, notes
 * are notated as follows:
 *
 *    C4 -> C in the 4th octave
 *
 * Using the updated notation above, the entire keyboard would look as such:
 *
 *    +-----+-----+-----+-       -+-----+-----+-----+-       -+-----+-----+-----+
 *    | A1  | Bb1 | B1  |         | Ab1 | A2  | Bb2 |         | Bb8 | B8  | C8  |
 *    +-----+-----+-----+-  ...  -+-----+-----+-----+-  ...  -+-----+-----+-----+
 *    |  1  |  2  |  3  |         | 12  | 13  | 14  |         | 86  | 87  | 88  |
 *    +-----+-----+-----+-       -+-----+-----+-----+-       -+-----+-----+-----+
 *
 * This gives us the two integer values we need to define each note: there is a base note
 * value (1 - 12) and a specific note value (1 - 88). Every possible specific note can be
 * defined by:
 *    
 *    <base note> + 12 * <current octave - 1>
 *
 * so for F# in the 6th octave, the integer value would be:
 *
 *    10 + 12 * (6 - 1) = 70
 *
 *                      --------------------------------------------
 *
 * One chord is a set of notes played at the same time. This is stored as a vector of
 * integer values, each entry corresponding to a note. At the time of creation, there is
 * only a base chord, which tells the user the type of notes that must be played (consists
 * of only base notes 1 - 12). Specific chords will be created by external algorithms.
\*----------------------------------------------------------------------------------------*/

class PianoChord {
public:
  PianoChord(std::string name_) { parseChord(name_); }
private:
  std::string name;
  std::vector<int> base_chord;
  std::vector<int> specific_chord;
  bool static_bass_note;
  void parseChord(std::string name_);
  void addNotes(std::vector<int> notes);
};

#endif
