#include "piano_chord_specific.h"
#include <stdlib.h>
#include <string>

#define THUMB_INDEX_MAX 0.57
#define THUMB_MIDDLE_MAX 0.79
#define THUMB_RING_MAX 0.91
#define THUMB_PINKY_MAX 1.0
#define INDEX_MIDDLE_MAX 0.33
#define INDEX_RING_MAX 0.52
#define INDEX_PINKY_MAX 0.71
#define MIDDLE_RING_MAX 0.33
#define MIDDLE_PINKY_MAX 0.57
#define RING_PINKY_MAX 0.33


std::string fingerType(int finger)
{
  /*
   * finger is expected to be a number 0 - 9 (inclusive)
   */
  if (finger == 0 || finger == 9) return "pinky";
  if (finger == 1 || finger == 8) return "ring";
  if (finger == 2 || finger == 7) return "middle";
  if (finger == 3 || finger == 6) return "index";
  if (finger == 4 || finger == 5) return "thumb";
  return "";
}

float PianoChordSpecific::difficulty(std::vector<int> fingerings)
{
  float difficulty = 0.0;
  int finger1 = fingerings[0];
  for (int i = 1; i < fingerings.size(); i++)
  {
    int finger2 = fingerings[i];
    int distance = abs(finger2 - finger1);
    std::string f1 = fingerType(finger1);
    std::string f2 = fingerType(finger2);
    int max_distance;
    if ((finger1 == 0 && finger2 == 1) || (finger1 == 8 && finger2 == 9))
    {
      max_distance = RING_PINKY_MAX * max_reach;
    }
    else if ((finger1 == 0 && finger2 == 2) || (finger1 == 7 && finger2 == 9))
    {
      max_distance = MIDDLE_PINKY_MAX * max_reach;
    }
    else if ((finger1 == 0 && finger2 == 3) || (finger1 == 6 && finger2 == 9))
    {
      max_distance = INDEX_PINKY_MAX * max_reach;
    }
    else if ((finger1 == 0 && finger2 == 4) || (finger1 == 5 && finger2 == 9))
    {
      max_distance = THUMB_PINKY_MAX * max_reach;
    }
    else if ((finger1 == 1 && finger2 == 2) || (finger1 == 7 && finger2 == 8))
    {
      max_distance = MIDDLE_RING_MAX * max_reach;
    }
    else if ((finger1 == 1 && finger2 == 3) || (finger1 == 6 && finger2 == 8))
    {
      max_distance = INDEX_RING_MAX * max_reach;
    }
    else if ((finger1 == 1 && finger2 == 4) || (finger1 == 5 && finger2 == 8))
    {
      max_distance = THUMB_RING_MAX * max_reach;
    }
    else if ((finger1 == 2 && finger2 == 3) || (finger1 == 6 && finger2 == 7))
    {
      max_distance = INDEX_MIDDLE_MAX * max_reach;
    }
    else if ((finger1 == 2 && finger2 == 4) || (finger1 == 5 && finger2 == 7))
    {
      max_distance = THUMB_MIDDLE_MAX * max_reach;
    }
    else if ((finger1 == 3 && finger2 == 4) || (finger1 == 5 && finger2 == 6))
    {
      max_distance = THUMB_INDEX_MAX * max_reach;
    }

    if (distance > max_distance) return 0.0; // this means the chord is impossible to play
    difficulty += distance / max_distance;
    finger1 = finger2;
  }
  return difficulty;
}


/*
std::vector<std::vector<int>> makeFingeringListHelper(int size)
{
  return NULL;
}
*/

/*
void PianoChordSpecific::makeFingeringList()
{
  for (int i = 0; i < notes.size(); i++)
  {
    
  }
}
*/
