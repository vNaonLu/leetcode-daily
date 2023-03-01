// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count of Smaller Numbers After Self
//
// https://leetcode.com/problems/count-of-smaller-numbers-after-self/
//
// Question ID: 315
// Difficult  : Hard
// Solve Date : 2022/02/15 18:25

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |315. Count of Smaller Numbers After Self|:
//
// Given an integer array |nums|, return an integer array |counts| where
// |counts[i]| is the number of smaller elements to the right of |nums[i]|.  
//

LEETCODE_BEGIN_RESOLVING(315, CountOfSmallerNumbersAfterSelf, Solution);

class Solution {
private:
  void merge_sort(vector<pair<int, int>> &a, int beg, int end,
                  vector<int> &res) {
    if (beg >= end)
      return;

    int mid = beg + (end - beg) / 2;

    merge_sort(a, beg, mid, res);
    merge_sort(a, mid + 1, end, res);

    vector<pair<int, int>> temp;

    int left = beg, right = mid + 1, count = 0;
    while (left <= mid && right <= end) {
      if (a[left].first > a[right].first) {
        temp.emplace_back(a[right++]);
        ++count;
      } else {
        res[a[left].second] += count;
        temp.emplace_back(a[left++]);
      }
    }

    while (left <= mid) {
      res[a[left].second] += count;
      temp.emplace_back(a[left++]);
    }

    while (right <= end) {
      temp.emplace_back(a[right++]);
    }

    for (const auto &x : temp) {
      a[beg++] = x;
    }
  }

public:
  vector<int> countSmaller(vector<int> &nums) {
    vector<int>            res(nums.size(), 0);
    vector<pair<int, int>> nums_pair;
    for (int i = 0; i < nums.size(); ++i) {
      nums_pair.emplace_back(nums[i], i);
    }
    merge_sort(nums_pair, 0, nums.size() - 1, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁴ <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,2,6,1]
// Output: [2,1,1,0]
//
// To the right of 5 there are 2 smaller elements (2 and 1).
// To the right of 2 there is only 1 smaller element (1).
// To the right of 6 there is 1 smaller element (1).
// To the right of 1 there is 0 smaller element.

LEETCODE_SOLUTION_UNITTEST(315, CountOfSmallerNumbersAfterSelf, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 2, 6, 1};
  vector<int> expect   = {2, 1, 1, 0};
  vector<int> actual   = solution->countSmaller(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(315, CountOfSmallerNumbersAfterSelf, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1};
  vector<int> expect   = {0};
  vector<int> actual   = solution->countSmaller(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [-1,-1]
// Output: [0,0]
//

LEETCODE_SOLUTION_UNITTEST(315, CountOfSmallerNumbersAfterSelf, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, -1};
  vector<int> expect   = {0, 0};
  vector<int> actual   = solution->countSmaller(nums);
  LCD_EXPECT_EQ(expect, actual);
}
