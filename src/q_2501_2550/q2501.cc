// Copyright 2024 Naon Lu //
// This file describes the solution of
// Longest Square Streak in an Array
//
// https://leetcode.com/problems/longest-square-streak-in-an-array/
//
// Question ID: 2501
// Difficult  : Medium
// Solve Date : 2024/10/28 18:56

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2501. Longest Square Streak in an Array|:
//
// You are given an integer array |nums|. A subsequence of |nums| is called a
// square streak if:
//
//  • The length of the subsequence is at least |2|, and
//
//  • after sorting the subsequence, each element (except the first element) is
//  the square of the previous number.
// Return the length of the longest square streak in |nums|, or return |-1| if
// there is no square streak. A subsequence is an array that can be derived from
// another array by deleting some or no elements without changing the order of
// the remaining elements.
//
//

LEETCODE_BEGIN_RESOLVING(2501, LongestSquareStreakInAnArray, Solution);

class Solution {
public:
  int longestSquareStreak(vector<int> &nums) {
    set<int64_t> s(nums.begin(), nums.end());
    int          res = -1;
    auto         it  = s.begin();
    while (it != s.end()) {
      int  cnt  = 1;
      auto find = s.find(*it * *it);

      while (find != s.end()) {
        auto sqr = find;
        find     = s.find(*sqr * *sqr);
        s.erase(sqr);
        ++cnt;
      }
      cout << *it << " " << cnt << endl;

      if (cnt > 1) {
        res = max(res, cnt);
      }

      s.erase(it++);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁵|
// * |2 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,3,6,16,8,2]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2501, LongestSquareStreakInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 6, 16, 8, 2};
  int         expect   = 3;
  int         actual   = solution->longestSquareStreak(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,5,6,7]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2501, LongestSquareStreakInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 5, 6, 7};
  int         expect   = -1;
  int         actual   = solution->longestSquareStreak(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [2,4]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2501, LongestSquareStreakInAnArray,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 4};
  int         expect   = 2;
  int         actual   = solution->longestSquareStreak(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: [4,16,256,65536]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2501, LongestSquareStreakInAnArray,
                           extra_testcase_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 16, 256, 65536};
  int         expect   = 4;
  int         actual   = solution->longestSquareStreak(nums);
  LCD_EXPECT_EQ(expect, actual);
}
