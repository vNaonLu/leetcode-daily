// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Optimal Partition of String
//
// https://leetcode.com/problems/optimal-partition-of-string/
//
// Question ID: 2405
// Difficult  : Medium
// Solve Date : 2023/04/04 14:57

#include <iosfwd>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2405. Optimal Partition of String|:
//
// Given a string |s|, partition the string into one or more substrings such
// that the characters in each substring are unique. That is, no letter appears
// in a single substring more than once. Return the minimum number of substrings
// in such a partition. Note that each character should belong to exactly one
// substring in a partition.
//
//

LEETCODE_BEGIN_RESOLVING(2405, OptimalPartitionOfString, Solution);

class Solution {
public:
  int partitionString(string s) {
    int                 res = 1;
    unordered_set<char> memo;
    for (auto c : s) {
      if (!memo.emplace(c).second) {
        ++res;
        memo.clear();
        memo.emplace(c);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of only English lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abacaba"
// Output: 4
//
// Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
// It can be shown that 4 is the minimum number of substrings needed.

LEETCODE_SOLUTION_UNITTEST(2405, OptimalPartitionOfString, example_1) {
  auto   solution = MakeSolution();
  string s        = "abacaba";
  int    expect   = 4;
  int    actual   = solution->partitionString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "ssssss"
// Output: 6
// Explanation:
// The only valid partition is ("s","s","s","s","s","s").
//

LEETCODE_SOLUTION_UNITTEST(2405, OptimalPartitionOfString, example_2) {
  auto   solution = MakeSolution();
  string s        = "ssssss";
  int    expect   = 6;
  int    actual   = solution->partitionString(s);
  LCD_EXPECT_EQ(expect, actual);
}
