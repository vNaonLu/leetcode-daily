// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Partition Array Into Three Parts With Equal Sum
//
// https://leetcode.com/problems/partition-array-into-three-parts-with-equal-sum/
//
// Question ID: 1013
// Difficult  : Easy
// Solve Date : 2023/07/24 13:49

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1013. Partition Array Into Three Parts With Equal Sum|:
//
// Given an array of integers |arr|, return |true| if we can partition the array
// into three non-empty parts with equal sums. Formally, we can partition the
// array if we can find indexes |i + 1 < j| with |(arr[0] + arr[1] + ... +
// arr[i] == arr[i + 1] + arr[i + 2] + ... + arr[j - 1] == arr[j] + arr[j + 1] +
// ... + arr[arr.length - 1])|
//
//

LEETCODE_BEGIN_RESOLVING(1013, PartitionArrayIntoThreePartsWithEqualSum,
                         Solution);

class Solution {
public:
  bool canThreePartsEqualSum(vector<int> &arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 3 != 0) {
      return false;
    }
    sum /= 3;
    int partition = 0;
    int cur       = 0;
    for (auto x : arr) {
      cur += x;
      if (cur == sum) {
        ++partition;
        cur = 0;
      }
    }
    return partition >= 3;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= arr.length <= 5 * 10⁴|
// * |-10⁴ <= arr[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [0,2,1,-6,6,-7,9,1,2,0,1]
// Output: true
//
// 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1

LEETCODE_SOLUTION_UNITTEST(1013, PartitionArrayIntoThreePartsWithEqualSum,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {0, 2, 1, -6, 6, -7, 9, 1, 2, 0, 1};
  bool        expect   = true;
  bool        actual   = solution->canThreePartsEqualSum(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [0,2,1,-6,6,7,9,-1,2,0,1]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1013, PartitionArrayIntoThreePartsWithEqualSum,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1};
  bool        expect   = false;
  bool        actual   = solution->canThreePartsEqualSum(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [3,3,6,5,-2,2,5,1,-9,4]
// Output: true
//
// 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4

LEETCODE_SOLUTION_UNITTEST(1013, PartitionArrayIntoThreePartsWithEqualSum,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 3, 6, 5, -2, 2, 5, 1, -9, 4};
  bool        expect   = true;
  bool        actual   = solution->canThreePartsEqualSum(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [0,0,0,0]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1013, PartitionArrayIntoThreePartsWithEqualSum,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {0, 0, 0, 0};
  bool        expect   = true;
  bool        actual   = solution->canThreePartsEqualSum(arr);
  LCD_EXPECT_EQ(expect, actual);
}
