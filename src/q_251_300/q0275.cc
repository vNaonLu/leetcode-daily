// Copyright 2023 Naon Lu
//
// This file describes the solution of
// H-Index II
//
// https://leetcode.com/problems/h-index-ii/
//
// Question ID: 275
// Difficult  : Medium
// Solve Date : 2022/07/21 19:57

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |275. H-Index II|:
//
// Given an array of integers |citations| where |citations[i]| is the number of
// citations a researcher received for their |iᵗʰ| paper and |citations|is
// sorted in an ascending order, return compute the researcher's |h|-index.
// According to the [definition of h-index on Wikipedia]: A scientist has an
// index |h| if |h| of their |n| papers have at least |h| citations each, and
// the other |n − h| papers have no more than |h| citations each. If there are
// several possible values for |h|, the maximum one is taken as the |h|-index.
// You must write an algorithm that runs in logarithmic time.
//

LEETCODE_BEGIN_RESOLVING(275, HIndexII, Solution);

class Solution {
public:
  int hIndex(vector<int> &citations) {
    int n  = citations.size();
    int lo = 0, hi = n - 1, res = 0;

    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;

      if (citations[mid] >= n - mid) {
        res = n - mid;
        hi  = mid - 1;
      } else {
        lo = mid + 1;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == citations.length|
// * |1 <= n <= 10⁵|
// * |0 <= citations[i] <= 1000|
// * |citations| is sorted in ascending order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: citations = [0,1,3,5,6]
// Output: 3
//
// [0,1,3,5,6] means the researcher has 5 papers in total and each of them had
// received 0, 1, 3, 5, 6 citations respectively. Since the researcher has 3
// papers with at least 3 citations each and the remaining two with no more than
// 3 citations each, their h-index is 3.

LEETCODE_SOLUTION_UNITTEST(275, HIndexII, example_1) {
  auto        solution  = MakeSolution();
  vector<int> citations = {0, 1, 3, 5, 6};
  int         expect    = 3;
  int         actual    = solution->hIndex(citations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: citations = [1,2,100]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(275, HIndexII, example_2) {
  auto        solution  = MakeSolution();
  vector<int> citations = {1, 2, 100};
  int         expect    = 2;
  int         actual    = solution->hIndex(citations);
  LCD_EXPECT_EQ(expect, actual);
}
