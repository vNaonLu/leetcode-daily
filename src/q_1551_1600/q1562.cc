// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Latest Group of Size M
//
// https://leetcode.com/problems/find-latest-group-of-size-m/
//
// Question ID: 1562
// Difficult  : Medium
// Solve Date : 2022/08/01 18:36

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1562. Find Latest Group of Size M|:
//
// Given an array |arr| that represents a permutation of numbers from |1| to
// |n|. You have a binary string of size |n| that initially has all its bits set
// to zero. At each step |i| (assuming both the binary string and |arr| are
// 1-indexed) from |1| to |n|, the bit at position |arr[i]| is set to |1|. You
// are also given an integer |m|. Find the latest step at which there exists a
// group of ones of length |m|. A group of ones is a contiguous substring of
// |1|'s such that it cannot be extended in either direction. Return the latest
// step at which there exists a group of ones of length exactly |m|. If no such
// group exists, return |-1|.
//

LEETCODE_BEGIN_RESOLVING(1562, FindLatestGroupOfSizeM, Solution);

class Solution {
public:
  int findLatestStep(vector<int> &arr, int m) {
    auto n   = int(arr.size());
    auto res = -1;
    auto cnt = vector<int>(n + 2), ind = vector<int>(n + 2);
    for (int i = 0; i < n; ++i) {
      int lo = ind[arr[i] - 1], hi = ind[arr[i] + 1], nl = lo + hi + 1;
      ind[arr[i]]      = nl;
      ind[arr[i] - lo] = nl;
      ind[arr[i] + hi] = nl;
      --cnt[lo];
      --cnt[hi];
      ++cnt[nl];
      if (cnt[m] > 0) {
        res = i + 1;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == arr.length|
// * |1 <= m <= n <= 10⁵|
// * |1 <= arr[i] <= n|
// * All integers in |arr| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [3,5,1,2,4], m = 1
// Output: 4
//
// Step 1: "00100", groups: ["1"]
// Step 2: "00101", groups: ["1", "1"]
// Step 3: "10101", groups: ["1", "1", "1"]
// Step 4: "11101", groups: ["111", "1"]
// Step 5: "11111", groups: ["11111"]
// The latest step at which there exists a group of size 1 is step 4.

LEETCODE_SOLUTION_UNITTEST(1562, FindLatestGroupOfSizeM, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 5, 1, 2, 4};
  int         m        = 1;
  int         expect   = 4;
  int         actual   = solution->findLatestStep(arr, m);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [3,1,5,4,2], m = 2
// Output: -1
//
// Step 1: "00100", groups: ["1"]
// Step 2: "10100", groups: ["1", "1"]
// Step 3: "10101", groups: ["1", "1", "1"]
// Step 4: "10111", groups: ["1", "111"]
// Step 5: "11111", groups: ["11111"]
// No group of size 2 exists during any step.

LEETCODE_SOLUTION_UNITTEST(1562, FindLatestGroupOfSizeM, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 1, 5, 4, 2};
  int         m        = 2;
  int         expect   = -1;
  int         actual   = solution->findLatestStep(arr, m);
  LCD_EXPECT_EQ(expect, actual);
}
