// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Replace Elements with Greatest Element on Right Side
//
// https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/
//
// Question ID: 1299
// Difficult  : Easy
// Solve Date : 2023/03/27 12:58

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1299. Replace Elements with Greatest Element on Right Side|:
//
// Given an array |arr|, replace every element in that array with the greatest
// element among the elements to its right, and replace the last element with
// |-1|. After doing so, return the array.
//
//

LEETCODE_BEGIN_RESOLVING(1299, ReplaceElementsWithGreatestElementOnRightSide,
                         Solution);

class Solution {
public:
  vector<int> replaceElements(vector<int> &arr) {
    vector<int> res(arr.size(), 0);
    int         mx = -1;
    for (int i = arr.size() - 1; i >= 0; --i) {
      res[i] = mx;
      mx     = max(arr[i], mx);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁴|
// * |1 <= arr[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [17,18,5,4,6,1]
// Output: [18,6,6,6,1,-1]
//
// - index 0 --> the greatest element to the right of index 0 is index 1 (18).
// - index 1 --> the greatest element to the right of index 1 is index 4 (6).
// - index 2 --> the greatest element to the right of index 2 is index 4 (6).
// - index 3 --> the greatest element to the right of index 3 is index 4 (6).
// - index 4 --> the greatest element to the right of index 4 is index 5 (1).
// - index 5 --> there are no elements to the right of index 5, so we put -1.

LEETCODE_SOLUTION_UNITTEST(1299, ReplaceElementsWithGreatestElementOnRightSide,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {17, 18, 5, 4, 6, 1};
  vector<int> expect   = {18, 6, 6, 6, 1, -1};
  vector<int> actual   = solution->replaceElements(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [400]
// Output: [-1]
//
// There are no elements to the right of index 0.

LEETCODE_SOLUTION_UNITTEST(1299, ReplaceElementsWithGreatestElementOnRightSide,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {400};
  vector<int> expect   = {-1};
  vector<int> actual   = solution->replaceElements(arr);
  LCD_EXPECT_EQ(expect, actual);
}
