// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Partition Labels
//
// https://leetcode.com/problems/partition-labels/
//
// Question ID: 763
// Difficult  : Medium
// Solve Date : 2021/09/25 16:47

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |763. Partition Labels|:
//
// You are given a string |s|. We want to partition the string into as many
// parts as possible so that each letter appears in at most one part. Note that
// the partition is done so that after concatenating all the parts in order, the
// resultant string should be |s|. Return a list of integers representing the
// size of these parts.  
//

LEETCODE_BEGIN_RESOLVING(763, PartitionLabels, Solution);

class Solution {
public:
  vector<int> partitionLabels(string s) {
    vector<int> letter_last_appear(26, s.size());
    for (int i = 0; i < s.size(); ++i)
      letter_last_appear[s[i] - 'a'] = i;
    int         last = 0, l = 0;
    vector<int> res;
    for (int i = 0; i < s.size(); ++i) {
      last = max(last, letter_last_appear[s[i] - 'a']);
      if (i == last) {
        res.push_back(i - l + 1);
        l = i + 1;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 500|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ababcbacadefegdehijhklij"
// Output: [9,7,8]
//
// The partition is "ababcbaca", "defegde", "hijhklij".
// This is a partition so that each letter appears in at most one part.
// A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it
// splits s into less parts.

LEETCODE_SOLUTION_UNITTEST(763, PartitionLabels, example_1) {
  auto        solution = MakeSolution();
  string      s        = "ababcbacadefegdehijhklij";
  vector<int> expect   = {9, 7, 8};
  vector<int> actual   = solution->partitionLabels(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "eccbbbbdec"
// Output: [10]
//

LEETCODE_SOLUTION_UNITTEST(763, PartitionLabels, example_2) {
  auto        solution = MakeSolution();
  string      s        = "eccbbbbdec";
  vector<int> expect   = {10};
  vector<int> actual   = solution->partitionLabels(s);
  LCD_EXPECT_EQ(expect, actual);
}
