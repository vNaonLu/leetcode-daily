// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Wiggle Sort II
//
// https://leetcode.com/problems/wiggle-sort-ii/
//
// Question ID: 324
// Difficult  : Medium
// Solve Date : 2024/03/09 14:51

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |324. Wiggle Sort II|:
//
// Given an integer array |nums|, reorder it such that |nums[0] < nums[1] >
// nums[2] < nums[3]...|. You may assume the input array always has a valid
// answer.
//
//

LEETCODE_BEGIN_RESOLVING(324, WiggleSortII, Solution);

class Solution {
public:
  void wiggleSort(vector<int> &nums) {
    int n = nums.size();

    auto midptr = nums.begin() + n / 2;
    nth_element(nums.begin(), midptr, nums.end());
    int mid = *midptr;

#define A(i) nums[(1 + 2 * (i)) % (n | 1)]

    int i = 0, j = 0, k = n - 1;
    while (j <= k) {
      if (A(j) > mid)
        swap(A(i++), A(j++));
      else if (A(j) < mid)
        swap(A(j), A(k--));
      else
        j++;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5 * 10⁴|
// * |0 <= nums[i] <= 5000|
// * It is guaranteed that there will be an answer for the given input |nums|.
///////////////////////////////////////////////////////////////////////////////

bool isWiggleSort(vector<int> const &v) {
  for (int i = 1; i < v.size(); ++i) {
    if (i & 1) {
      if (v[i] <= v[i - 1]) {
        return false;
      } else if (i + 1 < v.size() && v[i + 1] >= v[i]) {
        return false;
      }
    } else {
      if (v[i] >= v[i - 1]) {
        return false;
      } else if (i + 1 < v.size() && v[i + 1] <= v[i]) {
        return false;
      }
    }
  }
  return true;
}

// [Example #1]
//  Input: nums = [1,5,1,1,6,4]
// Output: [1,6,1,5,1,4]
//
// [1,4,1,5,1,6] is also accepted.

LEETCODE_SOLUTION_UNITTEST(324, WiggleSortII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 1, 1, 6, 4};
  solution->wiggleSort(nums);
  EXPECT_TRUE(isWiggleSort(nums));
}

// [Example #2]
//  Input: nums = [1,3,2,2,3,1]
// Output: [2,3,1,3,1,2]
//

LEETCODE_SOLUTION_UNITTEST(324, WiggleSortII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 2, 2, 3, 1};
  vector<int> expect   = {2, 3, 1, 3, 1, 2};
  solution->wiggleSort(nums);
  EXPECT_TRUE(isWiggleSort(nums));
}
