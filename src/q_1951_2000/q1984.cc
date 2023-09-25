// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Difference Between Highest and Lowest of K Scores
//
// https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/
//
// Question ID: 1984
// Difficult  : Easy
// Solve Date : 2023/09/19 18:54

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1984. Minimum Difference Between Highest and Lowest of K
// Scores|:
//
// You are given a 0-indexed integer array |nums|, where |nums[i]| represents
// the score of the |iᵗʰ| student. You are also given an integer |k|. Pick the
// scores of any |k| students from the array so that the difference between the
// highest and the lowest of the |k| scores is minimized. Return the minimum
// possible difference.
//
//

LEETCODE_BEGIN_RESOLVING(1984,
                         MinimumDifferenceBetweenHighestAndLowestOfKScores,
                         Solution);

class Solution {
public:
  int minimumDifference(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int res = numeric_limits<int>::max();
    for (int i = 0; i + k <= nums.size(); ++i) {
      res = min(res, nums[i + k - 1] - nums[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= nums.length <= 1000|
// * |0 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [90], k = 1
// Output: 0
//
// There is one way to pick score(s) of one student:
// - [90]. The difference between the highest and lowest score is 90 - 90 = 0.
// The minimum possible difference is 0.

LEETCODE_SOLUTION_UNITTEST(1984,
                           MinimumDifferenceBetweenHighestAndLowestOfKScores,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {90};
  int         k        = 1;
  int         expect   = 0;
  int         actual   = solution->minimumDifference(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [9,4,1,7], k = 2
// Output: 2
//
// There are six ways to pick score(s) of two students:
// - [9,4,1,7]. The difference between the highest and lowest score is 9 - 4
// = 5.
// - [9,4,1,7]. The difference between the highest and lowest score is 9 - 1
// = 8.
// - [9,4,1,7]. The difference between the highest and lowest score is 9 - 7
// = 2.
// - [9,4,1,7]. The difference between the highest and lowest score is 4 - 1
// = 3.
// - [9,4,1,7]. The difference between the highest and lowest score is 7 - 4
// = 3.
// - [9,4,1,7]. The difference between the highest and lowest score is 7 - 1
// = 6. The minimum possible difference is 2.

LEETCODE_SOLUTION_UNITTEST(1984,
                           MinimumDifferenceBetweenHighestAndLowestOfKScores,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 4, 1, 7};
  int         k        = 2;
  int         expect   = 2;
  int         actual   = solution->minimumDifference(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input:
//  [41900,69441,94407,37498,20299,10856,36221,2231,54526,79072,84309,76765,92282,13401,44698,17586,98455,47895,98889,65298,32271,23801,83153,12186,7453,79460,67209,54576,87785,47738,40750,31265,77990,93502,50364,75098,11712,80013,24193,35209,56300,85735,3590,24858,6780,50086,87549,7413,90444,12284,44970,39274,81201,43353,75808,14508,17389,10313,90055,43102,18659,20802,70315,48843,12273,78876,36638,17051,20478]
// 5
// Output: 1428
//

LEETCODE_SOLUTION_UNITTEST(1984,
                           MinimumDifferenceBetweenHighestAndLowestOfKScores,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {
      41900, 69441, 94407, 37498, 20299, 10856, 36221, 2231,  54526, 79072,
      84309, 76765, 92282, 13401, 44698, 17586, 98455, 47895, 98889, 65298,
      32271, 23801, 83153, 12186, 7453,  79460, 67209, 54576, 87785, 47738,
      40750, 31265, 77990, 93502, 50364, 75098, 11712, 80013, 24193, 35209,
      56300, 85735, 3590,  24858, 6780,  50086, 87549, 7413,  90444, 12284,
      44970, 39274, 81201, 43353, 75808, 14508, 17389, 10313, 90055, 43102,
      18659, 20802, 70315, 48843, 12273, 78876, 36638, 17051, 20478};
  int k      = 5;
  int expect = 1428;
  int actual = solution->minimumDifference(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
