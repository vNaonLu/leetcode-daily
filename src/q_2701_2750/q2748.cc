// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Beautiful Pairs
//
// https://leetcode.com/problems/number-of-beautiful-pairs/
//
// Question ID: 2748
// Difficult  : Easy
// Solve Date : 2023/12/24 12:21

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2748. Number of Beautiful Pairs|:
//
// You are given a 0-indexed integer array |nums|. A pair of indices |i|, |j|
// where |0 <= i < j < nums.length| is called beautiful if the first digit of
// |nums[i]| and the last digit of |nums[j]| are coprime. Return the total
// number of beautiful pairs in |nums|. Two integers |x| and |y| are coprime if
// there is no integer greater than 1 that divides both of them. In other words,
// |x| and |y| are coprime if |gcd(x, y) == 1|, where |gcd(x, y)| is the
// greatest common divisor of |x| and |y|.
//
//

LEETCODE_BEGIN_RESOLVING(2748, NumberOfBeautifulPairs, Solution);

class Solution {
public:
  int countBeautifulPairs(vector<int> &nums) {
    int res = 0;
    int n   = nums.size();
    int first;
    int last;
    for (int i = 0; i < n; ++i) {
      first = nums[i];
      while (first > 9) {
        first /= 10;
      }

      for (int j = i + 1; j < n; ++j) {
        last = nums[j] % 10;
        if (gcd(first, last) == 1) {
          ++res;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 100|
// * |1 <= nums[i] <= 9999|
// * |nums[i] % 10 != 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,5,1,4]
// Output: 5
//
// There are 5 beautiful pairs in nums:
// When i = 0 and j = 1: the first digit of nums[0] is 2, and the last digit of
// nums[1] is 5. We can confirm that 2 and 5 are coprime, since gcd(2,5) == 1.
// When i = 0 and j = 2: the first digit of nums[0] is 2, and the last digit of
// nums[2] is 1. Indeed, gcd(2,1) == 1. When i = 1 and j = 2: the first digit of
// nums[1] is 5, and the last digit of nums[2] is 1. Indeed, gcd(5,1) == 1. When
// i = 1 and j = 3: the first digit of nums[1] is 5, and the last digit of
// nums[3] is 4. Indeed, gcd(5,4) == 1. When i = 2 and j = 3: the first digit of
// nums[2] is 1, and the last digit of nums[3] is 4. Indeed, gcd(1,4) == 1.
// Thus, we return 5.

LEETCODE_SOLUTION_UNITTEST(2748, NumberOfBeautifulPairs, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 1, 4};
  int         expect   = 5;
  int         actual   = solution->countBeautifulPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [11,21,12]
// Output: 2
//
// There are 2 beautiful pairs:
// When i = 0 and j = 1: the first digit of nums[0] is 1, and the last digit of
// nums[1] is 1. Indeed, gcd(1,1) == 1. When i = 0 and j = 2: the first digit of
// nums[0] is 1, and the last digit of nums[2] is 2. Indeed, gcd(1,2) == 1.
// Thus, we return 2.

LEETCODE_SOLUTION_UNITTEST(2748, NumberOfBeautifulPairs, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {11, 21, 12};
  int         expect   = 2;
  int         actual   = solution->countBeautifulPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}
