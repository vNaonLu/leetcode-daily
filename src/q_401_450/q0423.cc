// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Reconstruct Original Digits from English
//
// https://leetcode.com/problems/reconstruct-original-digits-from-english/
//
// Question ID: 423
// Difficult  : Medium
// Solve Date : 2024/03/26 20:56

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |423. Reconstruct Original Digits from English|:
//
// Given a string |s| containing an out-of-order English representation of
// digits |0-9|, return the digits in ascending order.
//
//

LEETCODE_BEGIN_RESOLVING(423, ReconstructOriginalDigitsFromEnglish, Solution);

class Solution {
public:
  string originalDigits(string s) {
    vector<int> mp(10, 0);
    string      res;
    for (auto c : s) {
      switch (c) {
      case 'z':
        ++mp[0];
        break;
      case 'x':
        ++mp[6];
        break;
      case 'w':
        ++mp[2];
        break;
      case 'u':
        ++mp[4];
        break;
      case 'g':
        ++mp[8];
        break;
      case 'h':
        ++mp[3]; // 3, 8
        break;
      case 'f':
        ++mp[5]; // 4, 5
        break;
      case 's':
        ++mp[7]; // 6, 7
        break;
      case 'i':
        ++mp[9]; // 5, 6, 8, 9
        break;
      case 'o':
        ++mp[1]; // 0, 1, 2, 4
        break;
      default:
        break;
      }
    }
    mp[3] = mp[3] - mp[8];
    mp[5] = mp[5] - mp[4];
    mp[7] = mp[7] - mp[6];
    mp[9] = mp[9] - (mp[5] + mp[6] + mp[8]);
    mp[1] = mp[1] - (mp[0] + mp[2] + mp[4]);
    for (int i = 0; i < mp.size(); ++i) {
      while (mp[i]-- > 0) {
        res.push_back('0' + i);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s[i]| is one of the characters
// |["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"]|.
// * |s| is guaranteed to be valid.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "owoztneoer"
// Output: "012"
//

LEETCODE_SOLUTION_UNITTEST(423, ReconstructOriginalDigitsFromEnglish,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "owoztneoer";
  string expect   = "012";
  string actual   = solution->originalDigits(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "fviefuro"
// Output: "45"
//

LEETCODE_SOLUTION_UNITTEST(423, ReconstructOriginalDigitsFromEnglish,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "fviefuro";
  string expect   = "45";
  string actual   = solution->originalDigits(s);
  LCD_EXPECT_EQ(expect, actual);
}
