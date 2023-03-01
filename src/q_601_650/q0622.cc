// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design Circular Queue
//
// https://leetcode.com/problems/design-circular-queue/
//
// Question ID: 622
// Difficult  : Medium
// Solve Date : 2022/05/15 13:35

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |622. Design Circular Queue|:
//
// Design your implementation of the circular queue. The circular queue is a
// linear data structure in which the operations are performed based on FIFO
// (First In First Out) principle, and the last position is connected back to
// the first position to make a circle. It is also called "Ring Buffer". One of
// the benefits of the circular queue is that we can make use of the spaces in
// front of the queue. In a normal queue, once the queue becomes full, we cannot
// insert the next element even if there is a space in front of the queue. But
// using the circular queue, we can use the space to store new values. Implement
// the |MyCircularQueue| class:
//
//  • |MyCircularQueue(k)| Initializes the object with the size of the queue to
//  be |k|.
//
//  • |int Front()| Gets the front item from the queue. If the queue is empty,
//  return |-1|.
//
//  • |int Rear()| Gets the last item from the queue. If the queue is empty,
//  return |-1|.
//
//  • |boolean enQueue(int value)| Inserts an element into the circular queue.
//  Return |true| if the operation is successful.
//
//  • |boolean deQueue()| Deletes an element from the circular queue. Return
//  |true| if the operation is successful.
//
//  • |boolean isEmpty()| Checks whether the circular queue is empty or not.
//
//  • |boolean isFull()| Checks whether the circular queue is full or not.
// You must solve the problem without using the built-in queue data structure in
// your programming language.
//

LEETCODE_BEGIN_RESOLVING(622, DesignCircularQueue, MyCircularQueue);

class MyCircularQueue {
private:
  vector<int> data;
  int         head, tail;

public:
  MyCircularQueue(int k) : data(k), head{0}, tail{0} {}

  bool enQueue(int value) {
    if (isFull()) {
      return false;
    }
    data[head++ % data.size()] = value;

    return true;
  }

  bool deQueue() {
    if (isEmpty()) {
      return false;
    }

    ++tail;
    return true;
  }

  int Front() {
    if (isEmpty()) {
      return -1;
    }

    return data[tail % data.size()];
  }

  int Rear() {
    if (isEmpty()) {
      return -1;
    }

    return data[(head - 1) % data.size()];
  }

  bool isEmpty() { return head == tail; }

  bool isFull() { return head == tail + data.size(); }
};

LEETCODE_END_RESOLVING(MyCircularQueue);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= 1000|
// * |0 <= value <= 1000|
// * At most |3000| calls will be made to |enQueue|, |deQueue|, |Front|, |Rear|,
// |isEmpty|, and |isFull|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue",
//  "Rear", "isFull", "deQueue", "enQueue", "Rear"]
// [[3], [1], [2], [3], [4], [], [], [], [4], []]
// Output: [null, true, true, true, false, 3, true, true, true, 4]
//
// MyCircularQueue myCircularQueue = new MyCircularQueue(3);
// myCircularQueue.enQueue(1); // return True
// myCircularQueue.enQueue(2); // return True
// myCircularQueue.enQueue(3); // return True
// myCircularQueue.enQueue(4); // return False
// myCircularQueue.Rear(); // return 3
// myCircularQueue.isFull(); // return True
// myCircularQueue.deQueue(); // return True
// myCircularQueue.enQueue(4); // return True
// myCircularQueue.Rear(); // return 4

LEETCODE_SOLUTION_UNITTEST(622, DesignCircularQueue, example_1) {
  int  s0_k              = 3;
  auto my_circular_queue = MakeMyCircularQueue(s0_k);
  int  s1_value          = 1;
  bool s1_expect         = true;
  bool s1_actual         = my_circular_queue->enQueue(s1_value);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int  s2_value  = 2;
  bool s2_expect = true;
  bool s2_actual = my_circular_queue->enQueue(s2_value);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int  s3_value  = 3;
  bool s3_expect = true;
  bool s3_actual = my_circular_queue->enQueue(s3_value);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int  s4_value  = 4;
  bool s4_expect = false;
  bool s4_actual = my_circular_queue->enQueue(s4_value);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_expect = 3;
  int s5_actual = my_circular_queue->Rear();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  bool s6_expect = true;
  bool s6_actual = my_circular_queue->isFull();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  bool s7_expect = true;
  bool s7_actual = my_circular_queue->deQueue();
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  int  s8_value  = 4;
  bool s8_expect = true;
  bool s8_actual = my_circular_queue->enQueue(s8_value);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  int s9_expect = 4;
  int s9_actual = my_circular_queue->Rear();
  LCD_EXPECT_EQ(s9_expect, s9_actual);
}
