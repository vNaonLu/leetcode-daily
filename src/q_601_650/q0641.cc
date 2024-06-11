// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Design Circular Deque
//
// https://leetcode.com/problems/design-circular-deque/
//
// Question ID: 641
// Difficult  : Medium
// Solve Date : 2024/06/08 10:17

#include <deque>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |641. Design Circular Deque|:
//
// Design your implementation of the circular double-ended queue (deque).
// Implement the |MyCircularDeque| class:
//
//  • |MyCircularDeque(int k)| Initializes the deque with a maximum size of |k|.
//
//  • |boolean insertFront()| Adds an item at the front of Deque. Returns |true|
//  if the operation is successful, or |false| otherwise.
//
//  • |boolean insertLast()| Adds an item at the rear of Deque. Returns |true|
//  if the operation is successful, or |false| otherwise.
//
//  • |boolean deleteFront()| Deletes an item from the front of Deque. Returns
//  |true| if the operation is successful, or |false| otherwise.
//
//  • |boolean deleteLast()| Deletes an item from the rear of Deque. Returns
//  |true| if the operation is successful, or |false| otherwise.
//
//  • |int getFront()| Returns the front item from the Deque. Returns |-1| if
//  the deque is empty.
//
//  • |int getRear()| Returns the last item from Deque. Returns |-1| if the
//  deque is empty.
//
//  • |boolean isEmpty()| Returns |true| if the deque is empty, or |false|
//  otherwise.
//
//  • |boolean isFull()| Returns |true| if the deque is full, or |false|
//  otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(641, DesignCircularDeque, MyCircularDeque);

class MyCircularDeque {
public:
  MyCircularDeque(int k) : size_{k} {}

  bool insertFront(int value) {
    if (isFull()) {
      return false;
    }
    content_.push_front(value);
    return true;
  }

  bool insertLast(int value) {
    if (isFull()) {
      return false;
    }
    content_.push_back(value);
    return true;
  }

  bool deleteFront() {
    if (isEmpty()) {
      return false;
    }
    content_.pop_front();
    return true;
  }

  bool deleteLast() {
    if (isEmpty()) {
      return false;
    }
    content_.pop_back();
    return true;
  }

  int getFront() {
    if (isEmpty()) {
      return -1;
    }
    return content_.front();
  }

  int getRear() {
    if (isEmpty()) {
      return -1;
    }
    return content_.back();
  }

  bool isEmpty() { return content_.empty(); }

  bool isFull() { return content_.size() >= size_; }

private:
  int        size_ = 0;
  deque<int> content_;
};

LEETCODE_END_RESOLVING(MyCircularDeque);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= 1000|
// * |0 <= value <= 1000|
// * At most |2000| calls will be made to |insertFront|, |insertLast|,
// |deleteFront|, |deleteLast|, |getFront|, |getRear|, |isEmpty|, |isFull|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyCircularDeque", "insertLast", "insertLast", "insertFront",
//  "insertFront", "getRear", "isFull", "deleteLast", "insertFront", "getFront"]
// [[3], [1], [2], [3], [4], [], [], [], [4], []]
// Output: [null, true, true, true, false, 2, true, true, true, 4]
//

LEETCODE_SOLUTION_UNITTEST(641, DesignCircularDeque, example_1) {
  int  s0_k              = 3;
  auto my_circular_deque = MakeMyCircularDeque(s0_k);
  int  s1_value          = 1;
  bool s1_expect         = true;
  bool s1_actual         = my_circular_deque->insertLast(s1_value);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int  s2_value  = 2;
  bool s2_expect = true;
  bool s2_actual = my_circular_deque->insertLast(s2_value);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int  s3_value  = 3;
  bool s3_expect = true;
  bool s3_actual = my_circular_deque->insertFront(s3_value);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int  s4_value  = 4;
  bool s4_expect = false;
  bool s4_actual = my_circular_deque->insertFront(s4_value);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_expect = 2;
  int s5_actual = my_circular_deque->getRear();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  bool s6_expect = true;
  bool s6_actual = my_circular_deque->isFull();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  bool s7_expect = true;
  bool s7_actual = my_circular_deque->deleteLast();
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  int  s8_value  = 4;
  bool s8_expect = true;
  bool s8_actual = my_circular_deque->insertFront(s8_value);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  int s9_expect = 4;
  int s9_actual = my_circular_deque->getFront();
  LCD_EXPECT_EQ(s9_expect, s9_actual);
}
