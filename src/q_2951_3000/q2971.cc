// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Polygon With the Largest Perimeter
//
// https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/
//
// Question ID: 2971
// Difficult  : Medium
// Solve Date : 2024/02/15 18:03

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2971. Find Polygon With the Largest Perimeter|:
//
// You are given an array of positive integers |nums| of length |n|.
// A polygon is a closed plane figure that has at least |3| sides. The longest
// side of a polygon is smaller than the sum of its other sides. Conversely, if
// you have |k| ( |k >= 3|) positive real numbers |a₁|, |a₂|, |a₃|, ..., |aₖ|
// where |a₁ <= a₂ <= a₃ <= ... <= aₖ| and |a₁ + a₂ + a₃ + ... + aₖ₋₁ > aₖ|,
// then there always exists a polygon with |k| sides whose lengths are |a₁|,
// |a₂|, |a₃|, ..., |aₖ|. The perimeter of a polygon is the sum of lengths of
// its sides. Return the largest possible perimeter of a polygon whose sides can
// be formed from |nums|, or |-1| if it is not possible to create a polygon.
//
//

LEETCODE_BEGIN_RESOLVING(2971, FindPolygonWithTheLargestPerimeter, Solution);

class Solution {
public:
  long long largestPerimeter(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    int64_t sides = nums.size();
    int64_t res   = accumulate(nums.begin(), nums.end(), 0ll);
    for (int i = nums.size() - 1; i >= 2; --i) {
      // sum <= lagest
      // i.e. sum - lagest <= lagest
      // i.e. sum <= 2 * lagest
      if (res <= 2 * nums[i]) {
        res -= nums[i];
        --sides;
      } else {
        break;
      }
    }
    return sides == 2 ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= n <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,5,5]
// Output: 15
//
// The only possible polygon that can be made from nums has 3 sides: 5, 5,
// and 5. The perimeter is 5 + 5 + 5 = 15.

LEETCODE_SOLUTION_UNITTEST(2971, FindPolygonWithTheLargestPerimeter,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 5, 5};
  long long   expect   = 15;
  long long   actual   = solution->largestPerimeter(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,12,1,2,5,50,3]
// Output: 12
//
// The polygon with the largest perimeter which can be made from nums has 5
// sides: 1, 1, 2, 3, and 5. The perimeter is 1 + 1 + 2 + 3 + 5 = 12. We cannot
// have a polygon with either 12 or 50 as the longest side because it is not
// possible to include 2 or more smaller sides that have a greater sum than
// either of them. It can be shown that the largest possible perimeter is 12.

LEETCODE_SOLUTION_UNITTEST(2971, FindPolygonWithTheLargestPerimeter,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 12, 1, 2, 5, 50, 3};
  long long   expect   = 12;
  long long   actual   = solution->largestPerimeter(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [5,5,50]
// Output: -1
//
// There is no possible way to form a polygon from nums, as a polygon has at
// least 3 sides and 50 > 5 + 5.

LEETCODE_SOLUTION_UNITTEST(2971, FindPolygonWithTheLargestPerimeter,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 5, 50};
  long long   expect   = -1;
  long long   actual   = solution->largestPerimeter(nums);
  LCD_EXPECT_EQ(expect, actual);
}
