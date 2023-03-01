// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Frequency of the Most Frequent Element
//
// https://leetcode.com/problems/frequency-of-the-most-frequent-element/
//
// Question ID: 1838
// Difficult  : Medium
// Solve Date : 2022/02/24 18:19

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1838. Frequency of the Most Frequent Element|:
//
// The frequency of an element is the number of times it occurs in an array.
// You are given an integer array |nums| and an integer |k|. In one operation,
// you can choose an index of |nums| and increment the element at that index by
// |1|. Return the maximum possible frequency of an element after performing at
// most |k| operations.  
//

LEETCODE_BEGIN_RESOLVING(1838, FrequencyOfTheMostFrequentElement, Solution);

class Solution {
public:
  int maxFrequency(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int       res = 1;
    long long sum = 0;
    for (int i = 0, left = 0; i < nums.size(); ++i) {
      sum += nums[i];
      while (sum < (long long)nums[i] * (i - left + 1) - k) {
        sum -= nums[left++];
      }
      res = max(res, i - left + 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
// * |1 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,4], k = 5
// Output: 3
// Explanation: Increment the first element three times and the second element
// two times to make nums = [4,4,4]. 4 has a frequency of 3.
//

LEETCODE_SOLUTION_UNITTEST(1838, FrequencyOfTheMostFrequentElement, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 4};
  int         k        = 5;
  int         expect   = 3;
  int         actual   = solution->maxFrequency(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,4,8,13], k = 5
// Output: 2
//
// There are multiple optimal solutions:
// - Increment the first element three times to make nums = [4,4,8,13]. 4 has a
// frequency of 2.
// - Increment the second element four times to make nums = [1,8,8,13]. 8 has a
// frequency of 2.
// - Increment the third element five times to make nums = [1,4,13,13]. 13 has a
// frequency of 2.

LEETCODE_SOLUTION_UNITTEST(1838, FrequencyOfTheMostFrequentElement, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 4, 8, 13};
  int         k        = 5;
  int         expect   = 2;
  int         actual   = solution->maxFrequency(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,9,6], k = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1838, FrequencyOfTheMostFrequentElement, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 9, 6};
  int         k        = 2;
  int         expect   = 1;
  int         actual   = solution->maxFrequency(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
