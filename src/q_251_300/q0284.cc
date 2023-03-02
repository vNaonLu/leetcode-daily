// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Peeking Iterator
//
// https://leetcode.com/problems/peeking-iterator/
//
// Question ID: 284
// Difficult  : Medium
// Solve Date : 2022/04/25 18:32

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |284. Peeking Iterator|:
//
// Design an iterator that supports the |peek| operation on an existing iterator
// in addition to the |hasNext| and the |next| operations. Implement the
// |PeekingIterator| class:
//
//  • |PeekingIterator(Iterator<int> nums)| Initializes the object with the
//  given integer iterator |iterator|.
//
//  • |int next()| Returns the next element in the array and moves the pointer
//  to the next element.
//
//  • |boolean hasNext()| Returns |true| if there are still elements in the
//  array.
//
//  • |int peek()| Returns the next element in the array without moving the
//  pointer.
// Note: Each language may have a different implementation of the constructor
// and |Iterator|, but they all support the |int next()| and |boolean hasNext()|
// functions.  
//

LEETCODE_BEGIN_RESOLVING(284, PeekingIterator, PeekingIterator);

class Iterator {
public:
  Iterator([[maybe_unused]] const vector<int> &nums) {}
  Iterator([[maybe_unused]] const Iterator &iter) {}

  // Returns the next element in the iteration.
  int next() { return -1; }

  // Returns true if the iteration has more elements.
  bool hasNext() const { return false; }
};

class PeekingIterator : public Iterator {
private:
  vector<int>           d_;
  vector<int>::iterator it;

public:
  PeekingIterator(const vector<int> &nums)
      : Iterator(nums), d_{nums}, it{d_.begin()} {
    // Initialize any member here.
    // **DO NOT** save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.
  }

  // Returns the next element in the iteration without advancing the iterator.
  int peek() { return *it; }

  // hasNext() and next() should behave the same as in the Iterator interface.
  // Override them if needed.
  int next() { return *it++; }

  bool hasNext() const { return it != d_.end(); }
};

LEETCODE_END_RESOLVING(PeekingIterator);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 1000|
// * All the calls to |next| and |peek| are valid.
// * At most |1000| calls will be made to |next|, |hasNext|, and |peek|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["PeekingIterator", "next", "peek", "next", "next", "hasNext"]
// [[[1, 2, 3]], [], [], [], [], []]
// Output: [null, 1, 2, 2, 3, false]
//
// PeekingIterator peekingIterator = new PeekingIterator([1, 2, 3]); // [1,2,3]
// peekingIterator.next(); // return 1, the pointer moves to the next element
// [1,2,3]. peekingIterator.peek(); // return 2, the pointer does not move
// [1,2,3]. peekingIterator.next(); // return 2, the pointer moves to the next
// element [1,2,3] peekingIterator.next(); // return 3, the pointer moves to the
// next element [1,2,3] peekingIterator.hasNext(); // return False

LEETCODE_SOLUTION_UNITTEST(284, PeekingIterator, example_1) {
  const vector<int> s0_nums          = {1, 2, 3};
  auto              peeking_iterator = MakePeekingIterator(s0_nums);
  int               s1_expect        = 1;
  int               s1_actual        = peeking_iterator->next();
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_expect = 2;
  int s2_actual = peeking_iterator->peek();
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_expect = 2;
  int s3_actual = peeking_iterator->next();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_expect = 3;
  int s4_actual = peeking_iterator->next();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  bool s5_expect = false;
  bool s5_actual = peeking_iterator->hasNext();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}
