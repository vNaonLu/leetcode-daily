// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse String
//
// https://leetcode.com/problems/reverse-string/
//
// Question ID: 344
// Difficult  : Easy
// Solve Date : 2021/09/08 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |344. Reverse String|:
//
// Write a function that reverses a string. The input string is given as an
// array of characters |s|. You must do this by modifying the input array
// [in-place] with |O(1)| extra memory.  
//

LEETCODE_BEGIN_RESOLVING(344, ReverseString, Solution);

class Solution {
public:
  void reverseString(vector<char> &s) {
    int  l = 0, r = s.size() - 1;
    char tmp = ' ';
    while (l <= r) {
      tmp    = s[r];
      s[r--] = s[l];
      s[l++] = tmp;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s[i]| is a [printable ascii character].
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = ["h","e","l","l","o"]
// Output: ["o","l","l","e","h"]
//

LEETCODE_SOLUTION_UNITTEST(344, ReverseString, example_1) {
  auto         solution = MakeSolution();
  vector<char> s        = {'h', 'e', 'l', 'l', 'o'};
  vector<char> expect   = {'o', 'l', 'l', 'e', 'h'};
  solution->reverseString(s);
  EXPECT_EQ(expect, s);
}

// [Example #2]
//  Input: s = ["H","a","n","n","a","h"]
// Output: ["h","a","n","n","a","H"]
//

LEETCODE_SOLUTION_UNITTEST(344, ReverseString, example_2) {
  auto         solution = MakeSolution();
  vector<char> s        = {'H', 'a', 'n', 'n', 'a', 'h'};
  vector<char> expect   = {'h', 'a', 'n', 'n', 'a', 'H'};
  solution->reverseString(s);
  EXPECT_EQ(expect, s);
}
