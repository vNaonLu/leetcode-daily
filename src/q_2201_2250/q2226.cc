// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Candies Allocated to K Children
//
// https://leetcode.com/problems/maximum-candies-allocated-to-k-children/
//
// Question ID: 2226
// Difficult  : Medium
// Solve Date : 2025/03/14 19:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2226. Maximum Candies Allocated to K Children|:
//
// You are given a 0-indexed integer array |candies|. Each element in the array
// denotes a pile of candies of size |candies[i]|. You can divide each pile into
// any number of sub piles, but you cannot merge two piles together. You are
// also given an integer |k|. You should allocate piles of candies to |k|
// children such that each child gets the same number of candies. Each child can
// be allocated candies from only one pile of candies and some piles of candies
// may go unused. Return the maximum number of candies each child can get.
//
//

LEETCODE_BEGIN_RESOLVING(2226, MaximumCandiesAllocatedToKChildren, Solution);

class Solution {
public:
  int maximumCandies(vector<int> &candies, long long k) {
    int64_t lo  = 1;
    int64_t hi  = *max_element(candies.begin(), candies.end());
    int     res = 0;
    while (lo <= hi) {
      int64_t mi  = lo + (hi - lo) / 2;
      int64_t cnt = 0;
      for (auto p : candies) {
        cnt += p / mi;
      }

      if (cnt >= k) {
        res = mi;
        lo  = mi + 1;
      } else {
        hi = mi - 1;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= candies.length <= 10⁵|
// * |1 <= candies[i] <= 10⁷|
// * |1 <= k <= 10¹²|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: candies = [5,8,6], k = 3
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2226, MaximumCandiesAllocatedToKChildren,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> candies  = {5, 8, 6};
  long long   k        = 3;
  int         expect   = 5;
  int         actual   = solution->maximumCandies(candies, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: candies = [2,5], k = 11
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2226, MaximumCandiesAllocatedToKChildren,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> candies  = {2, 5};
  long long   k        = 11;
  int         expect   = 0;
  int         actual   = solution->maximumCandies(candies, k);
  LCD_EXPECT_EQ(expect, actual);
}
