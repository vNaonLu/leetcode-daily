// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Range Sum Query - Mutable
//
// https://leetcode.com/problems/range-sum-query-mutable/
//
// Question ID: 307
// Difficult  : Medium
// Solve Date : 2022/07/31 12:40

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |307. Range Sum Query - Mutable|:
//
// Given an integer array |nums|, handle multiple queries of the following
// types:
//
//  1. Update the value of an element in |nums|.
//
//  2. Calculate the sum of the elements of |nums| between indices |left| and
//  |right| inclusive where |left <= right|.
// Implement the |NumArray| class:
//
//  • |NumArray(int[] nums)| Initializes the object with the integer array
//  |nums|.
//
//  • |void update(int index, int val)| Updates the value of |nums[index]| to be
//  |val|.
//
//  • |int sumRange(int left, int right)| Returns the sum of the elements of
//  |nums| between indices |left| and |right| inclusive (i.e. |nums[left] +
//  nums[left + 1] + ... + nums[right]|).
//

LEETCODE_BEGIN_RESOLVING(307, RangeSumQueryMutable, NumArray);

class NumArray {
private:
  size_t      n = 0;
  vector<int> tree;

  static vector<int> buildTree(vector<int> &nums) {
    vector<int> res(nums.size() * 2);
    for (int i = nums.size(), j = 0; i < 2 * nums.size(); ++i, ++j) {
      res[i] = nums[j];
    }

    for (int i = nums.size() - 1; i > 0; --i) {
      res[i] = res[i * 2 + 1] + res[i * 2];
    }

    return res;
  }

public:
  NumArray(vector<int> &nums) : n{nums.size()}, tree{buildTree(nums)} {}

  void update(int index, int val) {
    index += n;
    tree[index] = val;

    while (index > 0) {
      int left  = index;
      int right = index;
      if (index & 1) {
        left = index - 1;
      } else {
        right = index + 1;
      }

      tree[index / 2] = tree[left] + tree[right];
      index /= 2;
    }
  }

  int sumRange(int left, int right) {
    int lo  = left + n;
    int hi  = right + n;
    int res = 0;
    while (lo <= hi) {
      if (lo & 1) {
        res += tree[lo++];
      }
      if (!(hi & 1)) {
        res += tree[hi--];
      }

      lo /= 2;
      hi /= 2;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(NumArray);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 3 * 10⁴|
// * |-100 <= nums[i] <= 100|
// * |0 <= index < nums.length|
// * |-100 <= val <= 100|
// * |0 <= left <= right < nums.length|
// * At most |3 * 10⁴| calls will be made to |update| and |sumRange|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["NumArray", "sumRange", "update", "sumRange"]
// [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
// Output: [null, 9, null, 8]
//
// NumArray numArray = new NumArray([1, 3, 5]);
// numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
// numArray.update(1, 2); // nums = [1, 2, 5]
// numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8

LEETCODE_SOLUTION_UNITTEST(307, RangeSumQueryMutable, example_1) {
  vector<int> s0_nums   = {1, 3, 5};
  auto        num_array = MakeNumArray(s0_nums);
  int         s1_left   = 0;
  int         s1_right  = 2;
  int         s1_expect = 9;
  int         s1_actual = num_array->sumRange(s1_left, s1_right);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_index = 1;
  int s2_val   = 2;
  num_array->update(s2_index, s2_val);
  int s3_left   = 0;
  int s3_right  = 2;
  int s3_expect = 8;
  int s3_actual = num_array->sumRange(s3_left, s3_right);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
}
