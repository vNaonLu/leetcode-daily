// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Min Stack
//
// https://leetcode.com/problems/min-stack/
//
// Question ID: 155
// Difficult  : Medium
// Solve Date : 2021/10/02 14:34

#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |155. Min Stack|:
//
// Design a stack that supports push, pop, top, and retrieving the minimum
// element in constant time. Implement the |MinStack| class:
//
//  • |MinStack()| initializes the stack object.
//
//  • |void push(int val)| pushes the element |val| onto the stack.
//
//  • |void pop()| removes the element on the top of the stack.
//
//  • |int top()| gets the top element of the stack.
//
//  • |int getMin()| retrieves the minimum element in the stack.
// You must implement a solution with |O(1)| time complexity for each function.
//  
//

LEETCODE_BEGIN_RESOLVING(155, MinStack, MinStack);

class MinStack {
private:
  pair<int, int> data[30001];
  int            it;

public:
  MinStack() { it = -1; }
  inline void push(int val) {
    int m = numeric_limits<int>::max();
    if (it >= 0) {
      m = min(data[it].first, data[it].second);
    }
    data[++it] = make_pair(val, m);
  }
  inline void pop() { --it; }
  inline int  top() { return data[it].first; }
  inline int  getMin() { return min(data[it].first, data[it].second); }
};

LEETCODE_END_RESOLVING(MinStack);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= val <= 2³¹ - 1|
// * Methods |pop|, |top| and |getMin| operations will always be called on
// non-empty stacks.
// * At most |3 * 10⁴| calls will be made to |push|, |pop|, |top|, and |getMin|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MinStack","push","push","push","getMin","pop","top","getMin"]
// [[],[-2],[0],[-3],[],[],[],[]]
// Output: [null,null,null,null,-3,null,0,-2]
//
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.getMin(); // return -3
// minStack.pop();
// minStack.top(); // return 0
// minStack.getMin(); // return -2

LEETCODE_SOLUTION_UNITTEST(155, MinStack, example_1) {
  auto min_stack = MakeMinStack();
  int  s1_val    = -2;
  min_stack->push(s1_val);
  int s2_val = 0;
  min_stack->push(s2_val);
  int s3_val = -3;
  min_stack->push(s3_val);
  int s4_expect = -3;
  int s4_actual = min_stack->getMin();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  min_stack->pop();
  int s6_expect = 0;
  int s6_actual = min_stack->top();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_expect = -2;
  int s7_actual = min_stack->getMin();
  LCD_EXPECT_EQ(s7_expect, s7_actual);
}
