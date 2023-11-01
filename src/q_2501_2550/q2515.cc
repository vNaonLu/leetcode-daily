// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Distance to Target String in a Circular Array
//
// https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/
//
// Question ID: 2515
// Difficult  : Easy
// Solve Date : 2023/11/01 20:39

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2515. Shortest Distance to Target String in a Circular
// Array|:
//
// You are given a 0-indexed circular string array |words| and a string
// |target|. A circular array means that the array's end connects to the array's
// beginning.
//
//  • Formally, the next element of |words[i]| is |words[(i + 1) % n]| and the
//  previous element of |words[i]| is |words[(i - 1 + n) % n]|, where |n| is the
//  length of |words|.
// Starting from |startIndex|, you can move to either the next word or the
// previous word with |1| step at a time. Return the shortest distance needed to
// reach the string |target|. If the string |target| does not exist in |words|,
// return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2515, ShortestDistanceToTargetStringInACircularArray,
                         Solution);

class Solution {
public:
  int closetTarget(vector<string> &words, string target, int startIndex) {
    int res = words.size();
    for (int i = 0; i < words.size(); ++i) {
      if (words[i] == target) {
        res =
            min({res, abs(startIndex - i), (int)(i + words.size() - startIndex),
                 (int)(startIndex + words.size() - i)});
      }
    }
    return res == words.size() ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 100|
// * |words[i]| and |target| consist of only lowercase English letters.
// * |0 <= startIndex < words.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["hello","i","am","leetcode","hello"], target = "hello",
//  startIndex = 1
// Output: 1
//
// We start from index 1 and can reach "hello" by
// - moving 3 units to the right to reach index 4.
// - moving 2 units to the left to reach index 4.
// - moving 4 units to the right to reach index 0.
// - moving 1 unit to the left to reach index 0.
// The shortest distance to reach "hello" is 1.

LEETCODE_SOLUTION_UNITTEST(2515, ShortestDistanceToTargetStringInACircularArray,
                           example_1) {
  auto           solution   = MakeSolution();
  vector<string> words      = {"hello", "i", "am", "leetcode", "hello"};
  string         target     = "hello";
  int            startIndex = 1;
  int            expect     = 1;
  int            actual     = solution->closetTarget(words, target, startIndex);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["a","b","leetcode"], target = "leetcode", startIndex = 0
// Output: 1
//
// We start from index 0 and can reach "leetcode" by
// - moving 2 units to the right to reach index 3.
// - moving 1 unit to the left to reach index 3.
// The shortest distance to reach "leetcode" is 1.

LEETCODE_SOLUTION_UNITTEST(2515, ShortestDistanceToTargetStringInACircularArray,
                           example_2) {
  auto           solution   = MakeSolution();
  vector<string> words      = {"a", "b", "leetcode"};
  string         target     = "leetcode";
  int            startIndex = 0;
  int            expect     = 1;
  int            actual     = solution->closetTarget(words, target, startIndex);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["i","eat","leetcode"], target = "ate", startIndex = 0
// Output: -1
//
// Since "ate" does not exist in |words|, we return -1.

LEETCODE_SOLUTION_UNITTEST(2515, ShortestDistanceToTargetStringInACircularArray,
                           example_3) {
  auto           solution   = MakeSolution();
  vector<string> words      = {"i", "eat", "leetcode"};
  string         target     = "ate";
  int            startIndex = 0;
  int            expect     = -1;
  int            actual     = solution->closetTarget(words, target, startIndex);
  LCD_EXPECT_EQ(expect, actual);
}
