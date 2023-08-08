// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Generate a String With Characters That Have Odd Counts
//
// https://leetcode.com/problems/generate-a-string-with-characters-that-have-odd-counts/
//
// Question ID: 1374
// Difficult  : Easy
// Solve Date : 2023/08/08 19:39

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1374. Generate a String With Characters That Have Odd
// Counts|:
//
// Given an integer |n|, return a string with |n| characters such that each
// character in such string occurs an odd number of times. The returned string
// must contain only lowercase English letters. If there are multiples valid
// strings, return any of them.
//
//

LEETCODE_BEGIN_RESOLVING(1374, GenerateAStringWithCharactersThatHaveOddCounts,
                         Solution);

class Solution {
public:
  string generateTheString(int n) {
    string res;
    if (n & 1) {
      res.assign(n, 'a');
    } else {
      res.assign(n - 1, 'a');
      res.push_back('b');
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 500|
///////////////////////////////////////////////////////////////////////////////

namespace {
bool IsAllOdd(const string &s) {
  unordered_map<char, int> freq;
  for (auto c : s) {
    ++freq[c];
  }
  for (auto [c, cnt] : freq) {
    if ((cnt & 1) == 0) {
      return false;
    }
  }
  return true;
}
} // namespace

// [Example #1]
//  Input: n = 4
// Output: "pppz"
//
// "pppz" is a valid string since the character 'p' occurs three times and the
// character 'z' occurs once. Note that there are many other valid strings such
// as "ohhh" and "love".

LEETCODE_SOLUTION_UNITTEST(1374, GenerateAStringWithCharactersThatHaveOddCounts,
                           example_1) {
  auto   solution = MakeSolution();
  int    n        = 4;
  string actual   = solution->generateTheString(n);
  EXPECT_TRUE(IsAllOdd(actual));
}

// [Example #2]
//  Input: n = 2
// Output: "xy"
//
// "xy" is a valid string since the characters 'x' and 'y' occur once. Note that
// there are many other valid strings such as "ag" and "ur".

LEETCODE_SOLUTION_UNITTEST(1374, GenerateAStringWithCharactersThatHaveOddCounts,
                           example_2) {
  auto   solution = MakeSolution();
  int    n        = 2;
  string actual   = solution->generateTheString(n);
  EXPECT_TRUE(IsAllOdd(actual));
}

// [Example #3]
//  Input: n = 7
// Output: "holasss"
//

LEETCODE_SOLUTION_UNITTEST(1374, GenerateAStringWithCharactersThatHaveOddCounts,
                           example_3) {
  auto   solution = MakeSolution();
  int    n        = 7;
  string actual   = solution->generateTheString(n);
  EXPECT_TRUE(IsAllOdd(actual));
}
