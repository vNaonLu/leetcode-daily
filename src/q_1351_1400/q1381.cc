// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Design a Stack With Increment Operation
//
// https://leetcode.com/problems/design-a-stack-with-increment-operation/
//
// Question ID: 1381
// Difficult  : Medium
// Solve Date : 2024/09/30 21:10

#include <deque>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1381. Design a Stack With Increment Operation|:
//
// Design a stack that supports increment operations on its elements.
// Implement the |CustomStack| class:
//
//  • |CustomStack(int maxSize)| Initializes the object with |maxSize| which is
//  the maximum number of elements in the stack.
//
//  • |void push(int x)| Adds |x| to the top of the stack if the stack has not
//  reached the |maxSize|.
//
//  • |int pop()| Pops and returns the top of the stack or |-1| if the stack is
//  empty.
//
//  • |void inc(int k, int val)| Increments the bottom |k| elements of the stack
//  by |val|. If there are less than |k| elements in the stack, increment all
//  the elements in the stack.
//
//

LEETCODE_BEGIN_RESOLVING(1381, DesignAStackWithIncrementOperation, CustomStack);

class CustomStack {
public:
  CustomStack(int maxSize) : max_{(size_t)maxSize} {}

  void push(int x) {
    if (data_.size() == max_) {
      return;
    }

    data_.emplace_back(x);
  }

  int pop() {
    if (data_.empty()) {
      return -1;
    }
    auto x = data_.back();
    data_.pop_back();
    return x;
  }

  void increment(int k, int val) {
    auto beg = data_.begin();
    while (k && beg != data_.end()) {
      *beg += val;
      --k;
      ++beg;
    }
  }

private:
  const size_t max_;
  deque<int>   data_;
};

LEETCODE_END_RESOLVING(CustomStack);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= maxSize, x, k <= 1000|
// * |0 <= val <= 100|
// * At most |1000| calls will be made to each method of |increment|, |push| and
// |pop| each separately.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input:
//  ["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
// [[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
// Output: [null,null,null,2,null,null,null,null,null,103,202,201,-1]
//

LEETCODE_SOLUTION_UNITTEST(1381, DesignAStackWithIncrementOperation,
                           example_1) {
  int  s0_maxSize   = 3;
  auto custom_stack = MakeCustomStack(s0_maxSize);
  int  s1_x         = 1;
  custom_stack->push(s1_x);
  int s2_x = 2;
  custom_stack->push(s2_x);
  int s3_expect = 2;
  int s3_actual = custom_stack->pop();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_x = 2;
  custom_stack->push(s4_x);
  int s5_x = 3;
  custom_stack->push(s5_x);
  int s6_x = 4;
  custom_stack->push(s6_x);
  int s7_k   = 5;
  int s7_val = 100;
  custom_stack->increment(s7_k, s7_val);
  int s8_k   = 2;
  int s8_val = 100;
  custom_stack->increment(s8_k, s8_val);
  int s9_expect = 103;
  int s9_actual = custom_stack->pop();
  LCD_EXPECT_EQ(s9_expect, s9_actual);
  int s10_expect = 202;
  int s10_actual = custom_stack->pop();
  LCD_EXPECT_EQ(s10_expect, s10_actual);
  int s11_expect = 201;
  int s11_actual = custom_stack->pop();
  LCD_EXPECT_EQ(s11_expect, s11_actual);
  int s12_expect = -1;
  int s12_actual = custom_stack->pop();
  LCD_EXPECT_EQ(s12_expect, s12_actual);
}
