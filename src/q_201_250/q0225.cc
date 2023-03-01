// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Implement Stack using Queues
//
// https://leetcode.com/problems/implement-stack-using-queues/
//
// Question ID: 225
// Difficult  : Easy
// Solve Date : 2022/05/05 18:12

#include <iosfwd>
#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |225. Implement Stack using Queues|:
//
// Implement a last-in-first-out (LIFO) stack using only two queues. The
// implemented stack should support all the functions of a normal stack (
// |push|, |top|, |pop|, and |empty|). Implement the |MyStack| class:
//
//  • |void push(int x)| Pushes element x to the top of the stack.
//
//  • |int pop()| Removes the element on the top of the stack and returns it.
//
//  • |int top()| Returns the element on the top of the stack.
//
//  • |boolean empty()| Returns |true| if the stack is empty, |false| otherwise.
// Notes:
//
//  • You must use only standard operations of a queue, which means that only
//  |push to back|, |peek/pop from front|, |size| and |is empty| operations are
//  valid.
//
//  • Depending on your language, the queue may not be supported natively. You
//  may simulate a queue using a list or deque (double-ended queue) as long as
//  you use only a queue's standard operations.
//  
//

LEETCODE_BEGIN_RESOLVING(225, ImplementStackUsingQueues, MyStack);

class MyStack {
private:
  queue<int> q;
  int        peek = -1;

public:
  MyStack() {}

  void push(int x) {
    peek = x;
    q.push(x);
  }

  int pop() {
    int n = q.size() - 1;
    while (n--) {
      peek = q.front();
      q.push(peek);
      q.pop();
    }

    int res = q.front();
    q.pop();

    return res;
  }

  int top() { return peek; }

  bool empty() { return q.size() == 0; }
};

LEETCODE_END_RESOLVING(MyStack);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= x <= 9|
// * At most |100| calls will be made to |push|, |pop|, |top|, and |empty|.
// * All the calls to |pop| and |top| are valid.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyStack", "push", "push", "top", "pop", "empty"]
// [[], [1], [2], [], [], []]
// Output: [null, null, null, 2, 2, false]
//
// MyStack myStack = new MyStack();
// myStack.push(1);
// myStack.push(2);
// myStack.top(); // return 2
// myStack.pop(); // return 2
// myStack.empty(); // return False

LEETCODE_SOLUTION_UNITTEST(225, ImplementStackUsingQueues, example_1) {
  auto my_stack = MakeMyStack();
  int  s1_x     = 1;
  my_stack->push(s1_x);
  int s2_x = 2;
  my_stack->push(s2_x);
  int s3_expect = 2;
  int s3_actual = my_stack->top();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_expect = 2;
  int s4_actual = my_stack->pop();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  bool s5_expect = false;
  bool s5_actual = my_stack->empty();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}
