// Copyright 2023 Naon Lu
//
// This file describes the solution of
// 3Sum With Multiplicity
//
// https://leetcode.com/problems/3sum-with-multiplicity/
//
// Question ID: 923
// Difficult  : Medium
// Solve Date : 2022/04/06 18:10

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |923. 3Sum With Multiplicity|:
//
// Given an integer array |arr|, and an integer |target|, return the number of
// tuples |i, j, k| such that |i < j < k| and |arr[i] + arr[j] + arr[k] ==
// target|. As the answer can be very large, return it modulo |10⁹ + 7|.  
//

LEETCODE_BEGIN_RESOLVING(923, 3SumWithMultiplicity, Solution);

class Solution {
private:
  constexpr static size_t kMod = 1e9 + 7;

public:
  int threeSumMulti(vector<int> &arr, int target) {
    vector<long> count(101, 0);
    for (auto &x : arr) {
      ++count[x];
    }

    long res = 0;
    for (int x = 0; x <= 100; ++x) {
      if (count[x] == 0)
        continue;
      for (int y = x + 1; y <= 100; ++y) {
        if (count[y] == 0)
          continue;
        int z = target - x - y;
        if (y < z && z <= 100) {
          res += count[x] * count[y] * count[z];
          res %= kMod;
        }
      }
    }

    for (int x = 0; x <= 100; ++x) {
      if (count[x] == 0)
        continue;
      int z = target - 2 * x;
      if (x < z && z <= 100) {
        res += count[x] * (count[x] - 1) / 2 * count[z];
        res %= kMod;
      }
    }

    for (int x = 0; x <= 100; ++x) {
      if (count[x] == 0)
        continue;
      if (target % 2 == x % 2) {
        int z = (target - x) / 2;
        if (x < z && z <= 100) {
          res += count[x] * count[z] * (count[z] - 1) / 2;
          res %= kMod;
        }
      }
    }

    if (target % 3 == 0) {
      int x = target / 3;
      if (x >= 0 && x <= 100) {
        res += count[x] * (count[x] - 1) * (count[x] - 2) / 6;
        res %= kMod;
      }
    }
    return (int)res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= arr.length <= 3000|
// * |0 <= arr[i] <= 100|
// * |0 <= target <= 300|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,1,2,2,3,3,4,4,5,5], target = 8
// Output: 20
//
// Enumerating by the values (arr[i], arr[j], arr[k]):
// (1, 2, 5) occurs 8 times;
// (1, 3, 4) occurs 8 times;
// (2, 2, 4) occurs 2 times;
// (2, 3, 3) occurs 2 times.

LEETCODE_SOLUTION_UNITTEST(923, 3SumWithMultiplicity, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  int         target   = 8;
  int         expect   = 20;
  int         actual   = solution->threeSumMulti(arr, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,1,2,2,2,2], target = 5
// Output: 12
//
// arr[i] = 1, arr[j] = arr[k] = 2 occurs 12 times:
// We choose one 1 from [1,1] in 2 ways,
// and two 2s from [2,2,2,2] in 6 ways.

LEETCODE_SOLUTION_UNITTEST(923, 3SumWithMultiplicity, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 1, 2, 2, 2, 2};
  int         target   = 5;
  int         expect   = 12;
  int         actual   = solution->threeSumMulti(arr, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [2,1,3], target = 6
// Output: 1
//
// (1, 2, 3) occured one time in the array so we return 1.

LEETCODE_SOLUTION_UNITTEST(923, 3SumWithMultiplicity, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 1, 3};
  int         target   = 6;
  int         expect   = 1;
  int         actual   = solution->threeSumMulti(arr, target);
  LCD_EXPECT_EQ(expect, actual);
}
