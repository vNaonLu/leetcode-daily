// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shuffle an Array
//
// https://leetcode.com/problems/shuffle-an-array/
//
// Question ID: 384
// Difficult  : Medium
// Solve Date : 2021/10/08 12:48

#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |384. Shuffle an Array|:
//
// Given an integer array |nums|, design an algorithm to randomly shuffle the
// array. All permutations of the array should be equally likely as a result of
// the shuffling. Implement the |Solution| class:
//
//  • |Solution(int[] nums)| Initializes the object with the integer array
//  |nums|.
//
//  • |int[] reset()| Resets the array to its original configuration and returns
//  it.
//
//  • |int[] shuffle()| Returns a random shuffling of the array.
//  
//

LEETCODE_BEGIN_RESOLVING(384, ShuffleAnArray, Solution);

class Solution {
private:
  vector<int> m_set;

public:
  Solution(vector<int> &nums) { m_set = nums; }
  vector<int> reset() { return m_set; }
  vector<int> shuffle() {
    vector<int> res = m_set;
    for (int i = 0; i < res.size(); ++i) {
      int idx = rand() % res.size();
      swap(res[i], res[idx]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |-10⁶ <= nums[i] <= 10⁶|
// * All the elements of |nums| are unique.
// * At most |10⁴| calls in total will be made to |reset| and |shuffle|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Solution", "shuffle", "reset", "shuffle"]
// [[[1, 2, 3]], [], [], []]
// Output: [null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]
//
// Solution solution = new Solution([1, 2, 3]);
// solution.shuffle(); // Shuffle the array [1,2,3] and return its result.
//  // Any permutation of [1,2,3] must be equally likely to be returned.
//  // Example: return [3, 1, 2]
// solution.reset(); // Resets the array back to its original configuration
// [1,2,3]. Return [1, 2, 3] solution.shuffle(); // Returns the random shuffling
// of array [1,2,3]. Example: return [1, 3, 2]

LEETCODE_SOLUTION_UNITTEST(384, ShuffleAnArray, example_1) {
  vector<int> nums     = {1, 2, 3};
  auto        solution = MakeSolution(nums);
  vector<int> expect   = {1, 2, 3};
  EXPECT_ANYORDER_EQ(expect, solution->shuffle());
  LCD_EXPECT_EQ(expect, solution->reset());
  EXPECT_ANYORDER_EQ(expect, solution->shuffle());
}
