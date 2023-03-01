// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Bag of Tokens
//
// https://leetcode.com/problems/bag-of-tokens/
//
// Question ID: 948
// Difficult  : Medium
// Solve Date : 2022/09/12 17:51

#include <algorithm>
#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |948. Bag of Tokens|:
//
// You have an initial power of |power|, an initial score of |0|, and a bag of
// |tokens| where |tokens[i]| is the value of the |iᵗʰ| token (0-indexed). Your
// goal is to maximize your total score by potentially playing each token in one
// of two ways:
//
//  • If your current power is at least |tokens[i]|, you may play the |iᵗʰ|
//  token face up, losing |tokens[i]| power and gaining |1| score.
//
//  • If your current score is at least |1|, you may play the |iᵗʰ| token face
//  down, gaining |tokens[i]| power and losing |1| score.
// Each token may be played at most once and in any order. You do not have to
// play all the tokens. Return the largest possible score you can achieve after
// playing any number of tokens.
//

LEETCODE_BEGIN_RESOLVING(948, BagOfTokens, Solution);

class Solution {
public:
  int bagOfTokensScore(vector<int> &tokens, int power) {
    sort(tokens.begin(), tokens.end());
    auto lo    = (int)0;
    auto hi    = (int)tokens.size() - 1;
    auto res   = (int)0;
    auto score = (int)0;
    while (lo <= hi && (power >= tokens[lo] || score > 0)) {
      while (lo <= hi && power >= tokens[lo]) {
        power -= tokens[lo++];
        ++score;
      }
      res = max(res, score);
      if (lo <= hi && score > 0) {
        power += tokens[hi--];
        --score;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= tokens.length <= 1000|
// * |0 <= tokens[i],power < 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tokens = [100], power = 50
// Output: 0
//
// : Playing the only token in the bag is impossible because you either have too
// little power or too little score.

LEETCODE_SOLUTION_UNITTEST(948, BagOfTokens, example_1) {
  auto        solution = MakeSolution();
  vector<int> tokens   = {100};
  int         power    = 50;
  int         expect   = 0;
  int         actual   = solution->bagOfTokensScore(tokens, power);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tokens = [100,200], power = 150
// Output: 1
//
// Play the 0ᵗʰ token (100) face up, your power becomes 50 and score becomes 1.
// There is no need to play the 1ˢᵗ token since you cannot play it face up to
// add to your score.

LEETCODE_SOLUTION_UNITTEST(948, BagOfTokens, example_2) {
  auto        solution = MakeSolution();
  vector<int> tokens   = {100, 200};
  int         power    = 150;
  int         expect   = 1;
  int         actual   = solution->bagOfTokensScore(tokens, power);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: tokens = [100,200,300,400], power = 200
// Output: 2
//
// Play the tokens in this order to get a score of 2:
// 1. Play the 0ᵗʰ token (100) face up, your power becomes 100 and score
// becomes 1.
// 2. Play the 3ʳᵈ token (400) face down, your power becomes 500 and score
// becomes 0.
// 3. Play the 1ˢᵗ token (200) face up, your power becomes 300 and score
// becomes 1.
// 4. Play the 2^{nd }token (300) face up, your power becomes 0 and score
// becomes 2.

LEETCODE_SOLUTION_UNITTEST(948, BagOfTokens, example_3) {
  auto        solution = MakeSolution();
  vector<int> tokens   = {100, 200, 300, 400};
  int         power    = 200;
  int         expect   = 2;
  int         actual   = solution->bagOfTokensScore(tokens, power);
  LCD_EXPECT_EQ(expect, actual);
}
