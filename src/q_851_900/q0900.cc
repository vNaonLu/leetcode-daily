// Copyright 2024 Naon Lu
//
// This file describes the solution of
// RLE Iterator
//
// https://leetcode.com/problems/rle-iterator/
//
// Question ID: 900
// Difficult  : Medium
// Solve Date : 2024/09/12 20:44

#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |900. RLE Iterator|:
//
// We can use run-length encoding (i.e., RLE) to encode a sequence of integers.
// In a run-length encoded array of even length |encoding| (0-indexed), for all
// even |i|, |encoding[i]| tells us the number of times that the non-negative
// integer value |encoding[i + 1]| is repeated in the sequence.
//
//  • For example, the sequence |arr = [8,8,8,5,5]| can be encoded to be
//  |encoding = [3,8,2,5]|. |encoding = [3,8,0,9,2,5]| and |encoding =
//  [2,8,1,8,2,5]| are also valid RLE of |arr|.
// Given a run-length encoded array, design an iterator that iterates through
// it. Implement the |RLEIterator| class:
//
//  • |RLEIterator(int[] encoded)| Initializes the object with the encoded array
//  |encoded|.
//
//  • |int next(int n)| Exhausts the next |n| elements and returns the last
//  element exhausted in this way. If there is no element left to exhaust,
//  return |-1| instead.
//
//

LEETCODE_BEGIN_RESOLVING(900, RLEIterator, RLEIterator);

class RLEIterator {
public:
  RLEIterator(vector<int> &encoding) {
    auto beg = encoding.begin();
    while (beg != encoding.end()) {
      v_.emplace_back(*(beg + 1), *beg);
      beg += 2;
    }
  }

  int next(int n) {
    while (n && v_.size()) {
      auto sub = min(n, v_.front().second);
      v_.front().second -= sub;
      n -= sub;

      if (n != 0 && v_.front().second == 0) {
        v_.pop_front();
      }
    }

    return v_.empty() ? -1 : v_.front().first;
  }

private:
  deque<pair<int, int>> v_;
};

LEETCODE_END_RESOLVING(RLEIterator);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= encoding.length <= 1000|
// * |encoding.length| is even.
// * |0 <= encoding[i] <= 10⁹|
// * |1 <= n <= 10⁹|
// * At most |1000| calls will be made to |next|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["RLEIterator", "next", "next", "next", "next"]
// [[[3, 8, 0, 9, 2, 5]], [2], [1], [1], [2]]
// Output: [null, 8, 8, 5, -1]
//

LEETCODE_SOLUTION_UNITTEST(900, RLEIterator, example_1) {
  vector<int> s0_encoding  = {3, 8, 0, 9, 2, 5};
  auto        rle_iterator = MakeRLEIterator(s0_encoding);
  int         s1_n         = 2;
  int         s1_expect    = 8;
  int         s1_actual    = rle_iterator->next(s1_n);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_n      = 1;
  int s2_expect = 8;
  int s2_actual = rle_iterator->next(s2_n);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_n      = 1;
  int s3_expect = 5;
  int s3_actual = rle_iterator->next(s3_n);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_n      = 2;
  int s4_expect = -1;
  int s4_actual = rle_iterator->next(s4_n);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
}
