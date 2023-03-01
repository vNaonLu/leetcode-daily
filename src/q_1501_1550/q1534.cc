// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Good Triplets
//
// https://leetcode.com/problems/count-good-triplets/
//
// Question ID: 1534
// Difficult  : Easy
// Solve Date : 2021/10/13 12:39

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1534. Count Good Triplets|:
//
// Given an array of integers |arr|, and three integers  |a|,  |b| and  |c|. You
// need to find the number of good triplets.
//
// A triplet |(arr[i], arr[j], arr[k])| is good if the following conditions are
// true:
//
//
//
//  • |0 <= i < j < k < arr.length|
//
//  • ||arr[i] - arr[j]| <= a|
//
//  • ||arr[j] - arr[k]| <= b|
//
//  • ||arr[i] - arr[k]| <= c|
//
//
// Where ||x|| denotes the absolute value of |x|.
//
// Return the number of good triplets.
//
//  
//

LEETCODE_BEGIN_RESOLVING(1534, CountGoodTriplets, Solution);

class Solution {
public:
  int countGoodTriplets(vector<int> &arr, int a, int b, int c) {
    int res = 0;
    for (int i = 0; i < arr.size(); ++i) {
      for (int j = i + 1; j < arr.size(); ++j) {
        if (abs(arr[j] - arr[i]) <= a) {
          for (int k = j + 1; k < arr.size(); k++) {
            if (abs(arr[k] - arr[j]) <= b && abs(arr[k] - arr[i]) <= c)
              ++res;
          }
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= arr.length <= 100|
// * |0 <= arr[i] <= 1000|
// * |0 <= a, b, c <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
// Output: 4
//
//  There are 4 good triplets: [(3,0,1), (3,0,1), (3,1,1), (0,1,1)].

LEETCODE_SOLUTION_UNITTEST(1534, CountGoodTriplets, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 0, 1, 1, 9, 7};
  int         a        = 7;
  int         b        = 2;
  int         c        = 3;
  int         expect   = 4;
  int         actual   = solution->countGoodTriplets(arr, a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,1,2,2,3], a = 0, b = 0, c = 1
// Output: 0
//
// No triplet satisfies all conditions.

LEETCODE_SOLUTION_UNITTEST(1534, CountGoodTriplets, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 1, 2, 2, 3};
  int         a        = 0;
  int         b        = 0;
  int         c        = 1;
  int         expect   = 0;
  int         actual   = solution->countGoodTriplets(arr, a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}
