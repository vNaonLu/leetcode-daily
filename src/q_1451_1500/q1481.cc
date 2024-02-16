// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Least Number of Unique Integers after K Removals
//
// https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/
//
// Question ID: 1481
// Difficult  : Medium
// Solve Date : 2024/02/16 17:35

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1481. Least Number of Unique Integers after K Removals|:
//
// Given an array of integers |arr| and an integer |k|. Find the least number of
// unique integers after removing exactly |k| elements.
//
//
//
//
//
//

LEETCODE_BEGIN_RESOLVING(1481, LeastNumberOfUniqueIntegersAfterKRemovals,
                         Solution);

class Solution {
public:
  int findLeastNumOfUniqueInts(vector<int> &arr, int k) {
    unordered_map<int, int> freq;
    for (auto x : arr) {
      ++freq[x];
    }

    int  res    = freq.size();
    auto cnt_mp = remap(freq);
    for (auto &[c, v] : cnt_mp) {
      if (k >= c) {
        res -= min<int>(v.size(), k / c);
        k -= min<int>(v.size(), k / c) * c;
      } else {
        break;
      }
    }
    return res;
  }

private:
  map<int, vector<int>> remap(unordered_map<int, int> const &mp) {
    map<int, vector<int>> res;
    for (auto [k, c] : mp) {
      res[c].emplace_back(k);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10^5|
// * |1 <= arr[i] <= 10^9|
// * |0 <= k <= arr.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [5,5,4], k = 1
// Output: 1
//
// : Remove the single 4, only 5 is left.

LEETCODE_SOLUTION_UNITTEST(1481, LeastNumberOfUniqueIntegersAfterKRemovals,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {5, 5, 4};
  int         k        = 1;
  int         expect   = 1;
  int         actual   = solution->findLeastNumOfUniqueInts(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [4,3,1,1,3,3,2], k = 3
// Output: 2
//
// : Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.

LEETCODE_SOLUTION_UNITTEST(1481, LeastNumberOfUniqueIntegersAfterKRemovals,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {4, 3, 1, 1, 3, 3, 2};
  int         k        = 3;
  int         expect   = 2;
  int         actual   = solution->findLeastNumOfUniqueInts(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}
