// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Divide a String Into Groups of Size k
//
// https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/
//
// Question ID: 2138
// Difficult  : Easy
// Solve Date : 2023/10/04 21:16

#include <cmath>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2138. Divide a String Into Groups of Size k|:
//
// A string |s| can be partitioned into groups of size |k| using the following
// procedure:
//
//  • The first group consists of the first |k| characters of the string, the
//  second group consists of the next |k| characters of the string, and so on.
//  Each character can be a part of exactly one group.
//
//  • For the last group, if the string does not have |k| characters remaining,
//  a character |fill| is used to complete the group.
// Note that the partition is done so that after removing the |fill| character
// from the last group (if it exists) and concatenating all the groups in order,
// the resultant string should be |s|. Given the string |s|, the size of each
// group |k| and the character |fill|, return a string array denoting the
// composition of every group |s| has been divided into, using the above
// procedure.
//
//

LEETCODE_BEGIN_RESOLVING(2138, DivideAStringIntoGroupsOfSizeK, Solution);

class Solution {
public:
  vector<string> divideString(string s, int k, char fill) {
    vector<string> res;
    if (s.size() % k) {
      int nxt = ceil(float(s.size()) / float(k));
      int rem = (nxt * k) - s.size();
      for (int i = 0; i < rem; ++i) {
        s += fill;
      }
    }

    int i = 0;
    while (i < s.size()) {
      res.emplace_back(s.substr(i, k));
      i += k;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists of lowercase English letters only.
// * |1 <= k <= 100|
// * |fill| is a lowercase English letter.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcdefghi", k = 3, fill = "x"
// Output: ["abc","def","ghi"]
//
// The first 3 characters "abc" form the first group.
// The next 3 characters "def" form the second group.
// The last 3 characters "ghi" form the third group.
// Since all groups can be completely filled by characters from the string, we
// do not need to use fill. Thus, the groups formed are "abc", "def", and "ghi".

LEETCODE_SOLUTION_UNITTEST(2138, DivideAStringIntoGroupsOfSizeK, example_1) {
  auto           solution = MakeSolution();
  string         s        = "abcdefghi";
  int            k        = 3;
  char           fill     = 'x';
  vector<string> expect   = {"abc", "def", "ghi"};
  vector<string> actual   = solution->divideString(s, k, fill);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcdefghij", k = 3, fill = "x"
// Output: ["abc","def","ghi","jxx"]
//
// Similar to the previous example, we are forming the first three groups "abc",
// "def", and "ghi". For the last group, we can only use the character 'j' from
// the string. To complete this group, we add 'x' twice. Thus, the 4 groups
// formed are "abc", "def", "ghi", and "jxx".

LEETCODE_SOLUTION_UNITTEST(2138, DivideAStringIntoGroupsOfSizeK, example_2) {
  auto           solution = MakeSolution();
  string         s        = "abcdefghij";
  int            k        = 3;
  char           fill     = 'x';
  vector<string> expect   = {"abc", "def", "ghi", "jxx"};
  vector<string> actual   = solution->divideString(s, k, fill);
  LCD_EXPECT_EQ(expect, actual);
}
