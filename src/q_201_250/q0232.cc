// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Implement Queue using Stacks
//
// https://leetcode.com/problems/implement-queue-using-stacks/
//
// Question ID: 232
// Difficult  : Easy
// Solve Date : 2022/09/23 17:38

#include <iosfwd>
#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |232. Implement Queue using Stacks|:
//
// Implement a first in first out (FIFO) queue using only two stacks. The
// implemented queue should support all the functions of a normal queue (
// |push|, |peek|, |pop|, and |empty|). Implement the |MyQueue| class:
//
//  • |void push(int x)| Pushes element x to the back of the queue.
//
//  • |int pop()| Removes the element from the front of the queue and returns
//  it.
//
//  • |int peek()| Returns the element at the front of the queue.
//
//  • |boolean empty()| Returns |true| if the queue is empty, |false| otherwise.
// Notes:
//
//  • You must use only standard operations of a stack, which means only |push
//  to top|, |peek/pop from top|, |size|, and |is empty| operations are valid.
//
//  • Depending on your language, the stack may not be supported natively. You
//  may simulate a stack using a list or deque (double-ended queue) as long as
//  you use only a stack's standard operations.
//

LEETCODE_BEGIN_RESOLVING(232, ImplementQueueUsingStacks, MyQueue);

class MyQueue {
private:
  queue<int> stk;

public:
  MyQueue() {}

  void push(int x) {
    auto tmp = queue<int>();
    while (!stk.empty()) {
      tmp.emplace(stk.front());
      stk.pop();
    }
    tmp.emplace(x);
    while (!tmp.empty()) {
      stk.emplace(tmp.front());
      tmp.pop();
    }
  }

  int pop() {
    auto res = stk.front();
    stk.pop();
    return res;
  }

  int peek() { return stk.front(); }

  bool empty() { return stk.empty(); }
};

LEETCODE_END_RESOLVING(MyQueue);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= x <= 9|
// * At most |100|calls will be made to |push|, |pop|, |peek|, and |empty|.
// * All the calls to |pop| and |peek| are valid.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyQueue", "push", "push", "peek", "pop", "empty"]
// [[], [1], [2], [], [], []]
// Output: [null, null, null, 1, 1, false]
//
// MyQueue myQueue = new MyQueue();
// myQueue.push(1); // queue is: [1]
// myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
// myQueue.peek(); // return 1
// myQueue.pop(); // return 1, queue is [2]
// myQueue.empty(); // return false

LEETCODE_SOLUTION_UNITTEST(232, ImplementQueueUsingStacks, example_1) {
  auto my_queue = MakeMyQueue();
  int  s1_x     = 1;
  my_queue->push(s1_x);
  int s2_x = 2;
  my_queue->push(s2_x);
  int s3_expect = 1;
  int s3_actual = my_queue->peek();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_expect = 1;
  int s4_actual = my_queue->pop();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  bool s5_expect = false;
  bool s5_actual = my_queue->empty();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}
