// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Slowest Key
//
// https://leetcode.com/problems/slowest-key/
//
// Question ID: 1629
// Difficult  : Easy
// Solve Date : 2021/09/06 08:00

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1629. Slowest Key|:
//
// A newly designed keypad was tested, where a tester pressed a sequence of |n|
// keys, one at a time. You are given a string |keysPressed| of length |n|,
// where |keysPressed[i]| was the |iᵗʰ| key pressed in the testing sequence, and
// a sorted list |releaseTimes|, where |releaseTimes[i]| was the time the |iᵗʰ|
// key was released. Both arrays are 0-indexed. The |0ᵗʰ| key was pressed at the
// time |0|, and every subsequent key was pressed at the exact time the previous
// key was released. The tester wants to know the key of the keypress that had
// the longest duration. The |iᵗʰ|^{ }keypress had a duration of
// |releaseTimes[i] - releaseTimes[i - 1]|, and the |0ᵗʰ| keypress had a
// duration of |releaseTimes[0]|. Note that the same key could have been pressed
// multiple times during the test, and these multiple presses of the same key
// may not have had the same duration. Return the key of the keypress that had
// the longest duration. If there are multiple such keypresses, return the
// lexicographically largest key of the keypresses.  
//

LEETCODE_BEGIN_RESOLVING(1629, SlowestKey, Solution);

class Solution {
public:
  char slowestKey(vector<int> &releaseTimes, string keysPressed) {
    if (keysPressed.size() < 1)
      return '\0';
    char res     = keysPressed[0];
    int  longest = releaseTimes[0];
    for (int i = 1; i < releaseTimes.size(); ++i) {
      int cur = releaseTimes[i] - releaseTimes[i - 1];
      if (cur > longest) {
        longest = cur;
        res     = keysPressed[i];
      } else if (cur == longest) {
        res = max(res, keysPressed[i]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |releaseTimes.length == n|
// * |keysPressed.length == n|
// * |2 <= n <= 1000|
// * |1 <= releaseTimes[i] <= 10⁹|
// * |releaseTimes[i] < releaseTimes[i+1]|
// * |keysPressed| contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: releaseTimes = [9,29,49,50], keysPressed = "cbcd"
// Output: "c"
//
// The keypresses were as follows:
// Keypress for 'c' had a duration of 9 (pressed at time 0 and released at time
// 9). Keypress for 'b' had a duration of 29 - 9 = 20 (pressed at time 9 right
// after the release of the previous character and released at time 29).
// Keypress for 'c' had a duration of 49 - 29 = 20 (pressed at time 29 right
// after the release of the previous character and released at time 49).
// Keypress for 'd' had a duration of 50 - 49 = 1 (pressed at time 49 right
// after the release of the previous character and released at time 50). The
// longest of these was the keypress for 'b' and the second keypress for 'c',
// both with duration 20. 'c' is lexicographically larger than 'b', so the
// answer is 'c'.

LEETCODE_SOLUTION_UNITTEST(1629, SlowestKey, example_1) {
  auto        solution     = MakeSolution();
  vector<int> releaseTimes = {9, 29, 49, 50};
  string      keysPressed  = "cbcd";
  char        expect       = 'c';
  char        actual       = solution->slowestKey(releaseTimes, keysPressed);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: releaseTimes = [12,23,36,46,62], keysPressed = "spuda"
// Output: "a"
//
// The keypresses were as follows:
// Keypress for 's' had a duration of 12.
// Keypress for 'p' had a duration of 23 - 12 = 11.
// Keypress for 'u' had a duration of 36 - 23 = 13.
// Keypress for 'd' had a duration of 46 - 36 = 10.
// Keypress for 'a' had a duration of 62 - 46 = 16.
// The longest of these was the keypress for 'a' with duration 16.

LEETCODE_SOLUTION_UNITTEST(1629, SlowestKey, example_2) {
  auto        solution     = MakeSolution();
  vector<int> releaseTimes = {12, 23, 36, 46, 62};
  string      keysPressed  = "spuda";
  char        expect       = 'a';
  char        actual       = solution->slowestKey(releaseTimes, keysPressed);
  EXPECT_EQ(expect, actual);
}
