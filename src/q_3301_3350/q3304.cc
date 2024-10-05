// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the K-th Character in String Game I
//
// https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/
//
// Question ID: 3304
// Difficult  : Easy
// Solve Date : 2024/10/05 16:33

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3304. Find the K-th Character in String Game I|:
//
// Alice and Bob are playing a game. Initially, Alice has a string |word = "a"|.
// You are given a positive integer |k|.
// Now Bob will ask Alice to perform the following operation forever:
//
//  • Generate a new string by changing each character in |word| to its next
//  character in the English alphabet, and append it to the original |word|.
// For example, performing the operation on |"c"| generates |"cd"| and
// performing the operation on |"zb"| generates |"zbac"|. Return the value of
// the |kᵗʰ| character in |word|, after enough operations have been done for
// |word| to have at least |k| characters. Note that the character |'z'| can be
// changed to |'a'| in the operation.
//
//

LEETCODE_BEGIN_RESOLVING(3304, FindTheKThCharacterInStringGameI, Solution);

class Solution {
public:
  char kthCharacter(int k) { return 'a' + __builtin_popcount(k - 1); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= 500|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: k = 5
// Output: "b"
//

LEETCODE_SOLUTION_UNITTEST(3304, FindTheKThCharacterInStringGameI, example_1) {
  auto solution = MakeSolution();
  int  k        = 5;
  char expect   = 'b';
  char actual   = solution->kthCharacter(k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: k = 10
// Output: "c"
//

LEETCODE_SOLUTION_UNITTEST(3304, FindTheKThCharacterInStringGameI, example_2) {
  auto solution = MakeSolution();
  int  k        = 10;
  char expect   = 'c';
  char actual   = solution->kthCharacter(k);
  LCD_EXPECT_EQ(expect, actual);
}
