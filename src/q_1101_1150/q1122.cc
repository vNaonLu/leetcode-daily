// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Relative Sort Array
//
// https://leetcode.com/problems/relative-sort-array/
//
// Question ID: 1122
// Difficult  : Easy
// Solve Date : 2022/02/15 18:15

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1122. Relative Sort Array|:
//
// Given two arrays |arr1| and |arr2|, the elements of |arr2| are distinct, and
// all elements in |arr2| are also in |arr1|. Sort the elements of |arr1| such
// that the relative ordering of items in |arr1| are the same as in |arr2|.
// Elements that do not appear in |arr2| should be placed at the end of |arr1|
// in ascending order.  
//

LEETCODE_BEGIN_RESOLVING(1122, RelativeSortArray, Solution);

class Solution {
public:
  vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
    vector<int> res(arr1.size());
    vector<int> count(1001, 0);
    for (const auto &x : arr1)
      ++count[x];
    int idx = 0;
    for (const auto &x : arr2) {
      while (count[x]--) {
        res[idx++] = x;
      }
    }
    for (int i = 0; i < count.size(); ++i) {
      while (count[i]-- > 0) {
        res[idx++] = i;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr1.length, arr2.length <= 1000|
// * |0 <= arr1[i], arr2[i] <= 1000|
// * All the elements of |arr2| are distinct.
// * Each  |arr2[i]| is in |arr1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
// Output: [2,2,2,1,4,3,3,9,6,7,19]
//

LEETCODE_SOLUTION_UNITTEST(1122, RelativeSortArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19};
  vector<int> arr2     = {2, 1, 4, 3, 9, 6};
  vector<int> expect   = {2, 2, 2, 1, 4, 3, 3, 9, 6, 7, 19};
  vector<int> actual   = solution->relativeSortArray(arr1, arr2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
// Output: [22,28,8,6,17,44]
//

LEETCODE_SOLUTION_UNITTEST(1122, RelativeSortArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {28, 6, 22, 8, 44, 17};
  vector<int> arr2     = {22, 28, 8, 6};
  vector<int> expect   = {22, 28, 8, 6, 17, 44};
  vector<int> actual   = solution->relativeSortArray(arr1, arr2);
  LCD_EXPECT_EQ(expect, actual);
}
