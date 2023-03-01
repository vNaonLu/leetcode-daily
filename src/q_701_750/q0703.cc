// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Kth Largest Element in a Stream
//
// https://leetcode.com/problems/kth-largest-element-in-a-stream/
//
// Question ID: 703
// Difficult  : Easy
// Solve Date : 2022/04/08 20:15

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |703. Kth Largest Element in a Stream|:
//
// Design a class to find the |kᵗʰ| largest element in a stream. Note that it is
// the |kᵗʰ| largest element in the sorted order, not the |kᵗʰ| distinct
// element. Implement |KthLargest| class:
//
//  • |KthLargest(int k, int[] nums)| Initializes the object with the integer
//  |k| and the stream of integers |nums|.
//
//  • |int add(int val)| Appends the integer |val| to the stream and returns the
//  element representing the |kᵗʰ| largest element in the stream.
//  
//

LEETCODE_BEGIN_RESOLVING(703, KthLargestElementInAStream, KthLargest);

class KthLargest {
private:
  priority_queue<int, vector<int>, greater<int>> data_;
  int                                            target_;

  void adjust() {
    while (data_.size() > target_) {
      data_.pop();
    }
  }

public:
  KthLargest(int k, vector<int> &nums) : target_{k} {
    for (auto &x : nums) {
      data_.emplace(x);
      adjust();
    }
  }

  int add(int val) {
    data_.emplace(val);
    adjust();
    return data_.top();
  }
};

LEETCODE_END_RESOLVING(KthLargest);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= 10⁴|
// * |0 <= nums.length <= 10⁴|
// * |-10⁴ <= nums[i] <= 10⁴|
// * |-10⁴ <= val <= 10⁴|
// * At most |10⁴| calls will be made to |add|.
// * It is guaranteed that there will be at least |k| elements in the array when
// you search for the |kᵗʰ| element.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["KthLargest", "add", "add", "add", "add", "add"]
// [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
// Output: [null, 4, 5, 5, 8, 8]
//
// KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
// kthLargest.add(3); // return 4
// kthLargest.add(5); // return 5
// kthLargest.add(10); // return 5
// kthLargest.add(9); // return 8
// kthLargest.add(4); // return 8

LEETCODE_SOLUTION_UNITTEST(703, KthLargestElementInAStream, example_1) {
  int         s0_k        = 3;
  vector<int> s0_nums     = {4, 5, 8, 2};
  auto        kth_largest = MakeKthLargest(s0_k, s0_nums);
  int         s1_val      = 3;
  int         s1_expect   = 4;
  int         s1_actual   = kth_largest->add(s1_val);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_val    = 5;
  int s2_expect = 5;
  int s2_actual = kth_largest->add(s2_val);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_val    = 10;
  int s3_expect = 5;
  int s3_actual = kth_largest->add(s3_val);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_val    = 9;
  int s4_expect = 8;
  int s4_actual = kth_largest->add(s4_val);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_val    = 4;
  int s5_expect = 8;
  int s5_actual = kth_largest->add(s5_val);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}
