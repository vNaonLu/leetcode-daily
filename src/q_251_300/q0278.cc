// Copyright 2023 Naon Lu
//
// This file describes the solution of
// First Bad Version
//
// https://leetcode.com/problems/first-bad-version/
//
// Question ID: 278
// Difficult  : Easy
// Solve Date : 2022/04/07 18:35

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |278. First Bad Version|:
//
// You are a product manager and currently leading a team to develop a new
// product. Unfortunately, the latest version of your product fails the quality
// check. Since each version is developed based on the previous version, all the
// versions after a bad version are also bad. Suppose you have |n| versions |[1,
// 2, ..., n]| and you want to find out the first bad one, which causes all the
// following ones to be bad. You are given an API |bool isBadVersion(version)|
// which returns whether |version| is bad. Implement a function to find the
// first bad version. You should minimize the number of calls to the API.  
//

int  bad;
bool isBadVersion(int x) { return x >= bad; }

LEETCODE_BEGIN_RESOLVING(278, FirstBadVersion, Solution);

class Solution {
public:
  int firstBadVersion(int n) {
    int l = 1, r = n;
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (isBadVersion(mid))
        r = mid;
      else
        l = mid + 1;
    }
    return l;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= bad <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, bad = 4
// Output: 4
//
// call isBadVersion(3) -> false
// call isBadVersion(5) -> true
// call isBadVersion(4) -> true
// Then 4 is the first bad version.

LEETCODE_SOLUTION_UNITTEST(278, FirstBadVersion, example_1) {
  bad           = 4;
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 4;
  int  actual   = solution->firstBadVersion(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, bad = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(278, FirstBadVersion, example_2) {
  bad           = 1;
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->firstBadVersion(n);
  LCD_EXPECT_EQ(expect, actual);
}
