
#ifndef Q155_UNITTEST_H__
#define Q155_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0155.hpp"
using namespace std;

/**
  * This file is generated by leetcode_add.py
  *
  * 155.
  *      Min Stack
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   Design a stack that supports push, pop, top, and retrieving the
  *   minimum element in constant time.
  *   
  *   Implement the ‘MinStack’.
  *   
  *   - ‘MinStack()’ initializes the stack object.
  *   
  *   - ‘void push(int val)’ pushes the element ‘val’ onto the stack.
  *   
  *   - ‘void pop()’ removes the element on the top of the stack.
  *   
  *   - ‘int top()’ gets the top element of the stack.
  *   
  *   - ‘int getMin()’ retrieves the minimum element in the stack.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘-2³¹ ≤ val ≤ 2³¹ - 1’
  *   • Methods ‘pop’ , ‘top’ and ‘getMin’ operations will always be called on “non-empty” stacks.
  *   • At most ‘3 × 10⁴’ calls will be made to ‘push’ , ‘pop’ , ‘top’ , and ‘getMin’ .
  *
*/

TEST(q155, sample_input01) {
  l155::MinStack solver;
  solver.push(-2);
  solver.push(0);
  solver.push(-3);
  EXPECT_EQ(solver.getMin(), -3);
  solver.pop();
  EXPECT_EQ(solver.top(), 0);
  EXPECT_EQ(solver.getMin(), -2);
}

#endif