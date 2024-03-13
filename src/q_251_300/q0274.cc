// Copyright 2024 Naon Lu
//
// This file describes the solution of
// H-Index
//
// https://leetcode.com/problems/h-index/
//
// Question ID: 274
// Difficult  : Medium
// Solve Date : 2024/03/13 19:56

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |274. H-Index|:
//
// Given an array of integers |citations| where |citations[i]| is the number of
// citations a researcher received for their |iᵗʰ| paper, return the
// researcher's h-index. According to the [definition of h-index on Wikipedia]:
// The h-index is defined as the maximum value of |h| such that the given
// researcher has published at least |h| papers that have each been cited at
// least |h| times.
//
//

LEETCODE_BEGIN_RESOLVING(274, HIndex, Solution);

class Solution {
public:
  int hIndex(vector<int> &citations) {
    int lo = 0;
    int hi = citations.size();
    while (lo < hi) {
      int mid = lo + (hi - lo + 1) / 2;
      int cnt = count_if(citations.begin(), citations.end(),
                         [mid](auto c) { return c >= mid; });
      if (cnt >= mid) {
        lo = mid;
      } else {
        hi = mid - 1;
      }
    }
    return lo;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == citations.length|
// * |1 <= n <= 5000|
// * |0 <= citations[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: citations = [3,0,6,1,5]
// Output: 3
//
// [3,0,6,1,5] means the researcher has 5 papers in total and each of them had
// received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3
// papers with at least 3 citations each and the remaining two with no more than
// 3 citations each, their h-index is 3.

LEETCODE_SOLUTION_UNITTEST(274, HIndex, example_1) {
  auto        solution  = MakeSolution();
  vector<int> citations = {3, 0, 6, 1, 5};
  int         expect    = 3;
  int         actual    = solution->hIndex(citations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: citations = [1,3,1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(274, HIndex, example_2) {
  auto        solution  = MakeSolution();
  vector<int> citations = {1, 3, 1};
  int         expect    = 1;
  int         actual    = solution->hIndex(citations);
  LCD_EXPECT_EQ(expect, actual);
}
