// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Distance Value Between Two Arrays
//
// https://leetcode.com/problems/find-the-distance-value-between-two-arrays/
//
// Question ID: 1385
// Difficult  : Easy
// Solve Date : 2022/04/06 18:57

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1385. Find the Distance Value Between Two Arrays|:
//
// Given two integer arrays |arr1| and |arr2|, and the integer |d|, return the
// distance value between the two arrays. The distance value is defined as the
// number of elements |arr1[i]| such that there is not any element |arr2[j]|
// where ||arr1[i]-arr2[j]| <= d|.  
//

LEETCODE_BEGIN_RESOLVING(1385, FindTheDistanceValueBetweenTwoArrays, Solution);

class Solution {
public:
  int findTheDistanceValue(vector<int> &arr1, vector<int> &arr2, int d) {
    int m = arr1.size(), n = arr2.size();
    int res = m;
    sort(arr2.begin(), arr2.end());
    for (auto &x : arr1) {
      int l = 0, r = n - 1;
      int lb = x - d, rb = x + d;

      while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr2[m] < lb) {
          l = m + 1;
        } else if (arr2[m] > rb) {
          r = m - 1;
        } else {
          --res;
          break;
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
// * |1 <= arr1.length, arr2.length <= 500|
// * |-1000 <= arr1[i], arr2[j] <= 1000|
// * |0 <= d <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
// Output: 2
//
// For arr1[0]=4 we have:
// |4-10|=6 > d=2
// |4-9|=5 > d=2
// |4-1|=3 > d=2
// |4-8|=4 > d=2
// For arr1[1]=5 we have:
// |5-10|=5 > d=2
// |5-9|=4 > d=2
// |5-1|=4 > d=2
// |5-8|=3 > d=2
// For arr1[2]=8 we have:
// |8-10|=2 <= d=2
// |8-9|=1 <= d=2
// |8-1|=7 > d=2
// |8-8|=0 <= d=2

LEETCODE_SOLUTION_UNITTEST(1385, FindTheDistanceValueBetweenTwoArrays,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {4, 5, 8};
  vector<int> arr2     = {10, 9, 1, 8};
  int         d        = 2;
  int         expect   = 2;
  int         actual   = solution->findTheDistanceValue(arr1, arr2, d);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1385, FindTheDistanceValueBetweenTwoArrays,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {1, 4, 2, 3};
  vector<int> arr2     = {-4, -3, 6, 10, 20, 30};
  int         d        = 3;
  int         expect   = 2;
  int         actual   = solution->findTheDistanceValue(arr1, arr2, d);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr1 = [2,1,100,3], arr2 = [-5,-2,10,-3,7], d = 6
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1385, FindTheDistanceValueBetweenTwoArrays,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {2, 1, 100, 3};
  vector<int> arr2     = {-5, -2, 10, -3, 7};
  int         d        = 6;
  int         expect   = 1;
  int         actual   = solution->findTheDistanceValue(arr1, arr2, d);
  LCD_EXPECT_EQ(expect, actual);
}
