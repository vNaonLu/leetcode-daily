// Copyright 2023 Naon Lu
//
// This file describes the solution of
// UTF-8 Validation
//
// https://leetcode.com/problems/utf-8-validation/
//
// Question ID: 393
// Difficult  : Medium
// Solve Date : 2022/02/11 18:48

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |393. UTF-8 Validation|:
//
// Given an integer array |data| representing the data, return whether it is a
// valid UTF-8 encoding (i.e. it translates to a sequence of valid UTF-8 encoded
// characters). A character in UTF8 can be from 1 to 4 bytes long, subjected to
// the following rules:
//
//  1. For a 1-byte character, the first bit is a |0|, followed by its Unicode
//  code.
//
//  2. For an n-bytes character, the first |n| bits are all one's, the |n + 1|
//  bit is |0|, followed by |n - 1| bytes with the most significant |2| bits
//  being |10|.
// This is how the UTF-8 encoding would work:
//      Number of Bytes   |        UTF-8 Octet Sequence
//                        |              (binary)
//    --------------------+-----------------------------------------
//             1          |   0xxxxxxx
//             2          |   110xxxxx 10xxxxxx
//             3          |   1110xxxx 10xxxxxx 10xxxxxx
//             4          |   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
// |x| denotes a bit in the binary form of a byte that may be either |0| or |1|.
// Note: The input is an array of integers. Only the least significant 8 bits of
// each integer is used to store the data. This means each integer represents
// only 1 byte of data.  
//

LEETCODE_BEGIN_RESOLVING(393, UTF8Validation, Solution);

class Solution {
private:
  int verifyFirst(int n) {
    constexpr static int mask = 1 << 7;
    int                  res  = 0;
    while (n & mask) {
      ++res;
      n <<= 1;
    }
    return res;
  }
  bool verifyBelow(int n) {
    constexpr static int maskf = 1 << 7;
    constexpr static int masks = 1 << 6;
    return (n & maskf) && !(n & masks);
  }

public:
  bool validUtf8(vector<int> &data) {
    for (int i = 0; i < data.size();) {
      int first = verifyFirst(data[i++]);
      switch (first) {
      case 4:
        if (i == data.size() || verifyBelow(data[i++]) == false)
          return false;
        [[fallthrough]];
      case 3:
        if (i == data.size() || verifyBelow(data[i++]) == false)
          return false;
        [[fallthrough]];
      case 2:
        if (i == data.size() || verifyBelow(data[i++]) == false)
          return false;
        [[fallthrough]];
      case 0:
        break;
      default:
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= data.length <= 2 * 10⁴|
// * |0 <= data[i] <= 255|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: data = [197,130,1]
// Output: true
//
// data represents the octet sequence: 11000101 10000010 00000001.
// It is a valid utf-8 encoding for a 2-bytes character followed by a 1-byte
// character.

LEETCODE_SOLUTION_UNITTEST(393, UTF8Validation, example_1) {
  auto        solution = MakeSolution();
  vector<int> data     = {197, 130, 1};
  bool        expect   = true;
  bool        actual   = solution->validUtf8(data);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: data = [235,140,4]
// Output: false
//
// data represented the octet sequence: 11101011 10001100 00000100.
// The first 3 bits are all one's and the 4th bit is 0 means it is a 3-bytes
// character. The next byte is a continuation byte which starts with 10 and
// that's correct. But the second continuation byte does not start with 10, so
// it is invalid.

LEETCODE_SOLUTION_UNITTEST(393, UTF8Validation, example_2) {
  auto        solution = MakeSolution();
  vector<int> data     = {235, 140, 4};
  bool        expect   = false;
  bool        actual   = solution->validUtf8(data);
  LCD_EXPECT_EQ(expect, actual);
}
