// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Pair Removal to Sort Array II
//
// https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/
//
// Question ID: 3510
// Difficult  : Hard
// Solve Date : 2026/01/23 13:14

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3510. Minimum Pair Removal to Sort Array II|:
//
// Given an array |nums|, you can perform the following operation any number of
// times:
//
//  • Select the adjacent pair with the minimum sum in |nums|. If multiple such
//  pairs exist, choose the leftmost one.
//
//  • Replace the pair with their sum.
// Return the minimum number of operations needed to make the array
// non-decreasing. An array is said to be non-decreasing if each element is
// greater than or equal to its previous element (if it exists).
//
//

LEETCODE_BEGIN_RESOLVING(3510, MinimumPairRemovalToSortArrayII, Solution);

class Solution {

public:
  int minimumPairRemoval(vector<int> &nums) {
    int N = nums.size();
    if (N < 2)
      return 0;

    vector<long long> array(nums.begin(), nums.end());
    flipped = 0;
    left.assign(N, 0);
    right.assign(N, 0);
    pairSum.clear();

    for (int i = 0; i < N; ++i) {
      left[i]  = i - 1;
      right[i] = i + 1;
    }

    for (int i = 0; i < N - 1; ++i) {
      if (array[i] > array[i + 1])
        flipped++;

      pairSum.insert({array[i] + array[i + 1], i});
    }

    int op = 0;
    while (flipped > 0 && !pairSum.empty()) {
      auto it = pairSum.begin();
      int  i  = it->second;
      pairSum.erase(it);

      int j = right[i];
      int h = left[i];
      int k = right[j];

      remove(h, N, array);
      if (array[i] > array[j])
        flipped--;
      remove(j, N, array);

      array[i] += array[j];

      op++;
      right[i] = k;
      if (k < N)
        left[k] = i;

      add(h, N, array);
      add(i, N, array);
    }

    return op;
  }

private:
  long long getVal(int i, const vector<long long> &array) { return array[i]; }

  void add(int i, int N, const vector<long long> &array) {
    if (i >= 0 && i < N) {
      int j = right[i];
      if (j < N) {
        pairSum.insert({array[i] + array[j], i});
        if (array[i] > array[j])
          flipped++;
      }
    }
  }

  void remove(int i, int N, const vector<long long> &array) {
    if (i >= 0 && i < N) {
      int j = right[i];
      if (j < N) {
        auto it = pairSum.find({array[i] + array[j], i});
        if (it != pairSum.end()) {
          if (array[i] > array[j])
            flipped--;
          pairSum.erase(it);
        }
      }
    }
  }
  long long                 flipped;
  vector<int>               left;
  vector<int>               right;
  set<pair<long long, int>> pairSum;
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,2,3,1]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3510, MinimumPairRemovalToSortArrayII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 2, 3, 1};
  int         expect   = 2;
  int         actual   = solution->minimumPairRemoval(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,2]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3510, MinimumPairRemovalToSortArrayII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2};
  int         expect   = 0;
  int         actual   = solution->minimumPairRemoval(nums);
  LCD_EXPECT_EQ(expect, actual);
}
