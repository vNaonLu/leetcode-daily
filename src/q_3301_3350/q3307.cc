// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the K-th Character in String Game II
//
// https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/
//
// Question ID: 3307
// Difficult  : Hard
// Solve Date : 2025/07/04 19:17

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3307. Find the K-th Character in String Game II|:
//
// Alice and Bob are playing a game. Initially, Alice has a string |word = "a"|.
// You are given a positive integer |k|. You are also given an integer array
// |operations|, where |operations[i]| represents the type of the |iᵗʰ|
// operation. Now Bob will ask Alice to perform all operations in sequence:
//
//  • If |operations[i] == 0|, append a copy of |word| to itself.
//
//  • If |operations[i] == 1|, generate a new string by changing each character
//  in |word| to its next character in the English alphabet, and append it to
//  the original |word|. For example, performing the operation on |"c"|
//  generates |"cd"| and performing the operation on |"zb"| generates |"zbac"|.
// Return the value of the |kᵗʰ| character in |word| after performing all the
// operations. Note that the character |'z'| can be changed to |'a'| in the
// second type of operation.
//
//

LEETCODE_BEGIN_RESOLVING(3307, FindTheKThCharacterInStringGameII, Solution);

class Solution {
public:
  char kthCharacter(long long k, vector<int> &operations) {
    int             shift = 0;
    vector<int64_t> lengths;
    int64_t         len = 1;

    for (int op : operations) {
      (void)op;
      len *= 2;
      lengths.push_back(len);
      if (len >= k)
        break;
    }

    for (int i = lengths.size() - 1; i >= 0; --i) {
      int64_t half = lengths[i] / 2;
      int     op   = operations[i];
      if (k > half) {
        k -= half;
        if (op == 1)
          shift++;
      }
    }

    return (char)((('a' - 'a' + shift) % 26) + 'a');
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= 10¹⁴|
// * |1 <= operations.length <= 100|
// * |operations[i]| is either 0 or 1.
// * The input is generated such that |word| has at least |k| characters after
// all operations.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: k = 5, operations = [0,0,0]
// Output: "a"
//

LEETCODE_SOLUTION_UNITTEST(3307, FindTheKThCharacterInStringGameII, example_1) {
  auto        solution   = MakeSolution();
  long long   k          = 5;
  vector<int> operations = {0, 0, 0};
  char        expect     = 'a';
  char        actual     = solution->kthCharacter(k, operations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: k = 10, operations = [0,1,0,1]
// Output: "b"
//

LEETCODE_SOLUTION_UNITTEST(3307, FindTheKThCharacterInStringGameII, example_2) {
  auto        solution   = MakeSolution();
  long long   k          = 10;
  vector<int> operations = {0, 1, 0, 1};
  char        expect     = 'b';
  char        actual     = solution->kthCharacter(k, operations);
  LCD_EXPECT_EQ(expect, actual);
}
