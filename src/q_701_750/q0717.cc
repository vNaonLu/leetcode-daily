// Copyright 2023 Naon Lu
//
// This file describes the solution of
// 1-bit and 2-bit Characters
//
// https://leetcode.com/problems/1-bit-and-2-bit-characters/
//
// Question ID: 717
// Difficult  : Easy
// Solve Date : 2021/10/06 00:01

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |717. 1-bit and 2-bit Characters|:
//
// We have two special characters:
//
//  • The first character can be represented by one bit |0|.
//
//  • The second character can be represented by two bits ( |10| or |11|).
// Given a binary array |bits| that ends with |0|, return |true| if the last
// character must be a one-bit character.  
//

LEETCODE_BEGIN_RESOLVING(717, 1BitAnd2BitCharacters, Solution);

class Solution {
public:
  bool isOneBitCharacter(vector<int> &bits) {
    for (int i = 0; i < bits.size();) {
      if (i == bits.size() - 1)
        return true;
      i = bits[i] ? i + 2 : i + 1;
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= bits.length <= 1000|
// * |bits[i]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: bits = [1,0,0]
// Output: true
//
// The only way to decode it is two-bit character and one-bit character.
// So the last character is one-bit character.

LEETCODE_SOLUTION_UNITTEST(717, 1BitAnd2BitCharacters, example_1) {
  auto        solution = MakeSolution();
  vector<int> bits     = {1, 0, 0};
  bool        expect   = true;
  bool        actual   = solution->isOneBitCharacter(bits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: bits = [1,1,1,0]
// Output: false
//
// The only way to decode it is two-bit character and two-bit character.
// So the last character is not one-bit character.

LEETCODE_SOLUTION_UNITTEST(717, 1BitAnd2BitCharacters, example_2) {
  auto        solution = MakeSolution();
  vector<int> bits     = {1, 1, 1, 0};
  bool        expect   = false;
  bool        actual   = solution->isOneBitCharacter(bits);
  LCD_EXPECT_EQ(expect, actual);
}
