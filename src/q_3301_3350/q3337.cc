// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Total Characters in String After Transformations II
//
// https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/
//
// Question ID: 3337
// Difficult  : Hard
// Solve Date : 2025/05/14 19:15

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3337. Total Characters in String After Transformations II|:
//
// You are given a string |s| consisting of lowercase English letters, an
// integer |t| representing the number of transformations to perform, and an
// array |nums| of size 26. In one transformation, every character in |s| is
// replaced according to the following rules:
//
//  • Replace |s[i]| with the next |nums[s[i] - 'a']| consecutive characters in
//  the alphabet. For example, if |s[i] = 'a'| and |nums[0] = 3|, the character
//  |'a'| transforms into the next 3 consecutive characters ahead of it, which
//  results in |"bcd"|.
//
//  • The transformation wraps around the alphabet if it exceeds |'z'|. For
//  example, if |s[i] = 'y'| and |nums[24] = 3|, the character |'y'| transforms
//  into the next 3 consecutive characters ahead of it, which results in
//  |"zab"|.
// Return the length of the resulting string after exactly |t| transformations.
// Since the answer may be very large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(3337, TotalCharactersInStringAfterTransformationsII,
                         Solution);

class Solution {
public:
  using ll                  = int64_t;
  constexpr static int kMod = 1e9 + 7;

  int lengthAfterTransformations(string s, int t, vector<int> &nums) {
    vector<vector<ll>> transform(26, vector<ll>(26, 0));

    for (int i = 0; i < 26; i++) {
      for (int shift = 0; shift < nums[i]; shift++) {
        transform[i][(i + 1 + shift) % 26]++;
      }
    }

    transform = powerMatrix(transform, t);
    vector<vector<ll>> freq(1, vector<ll>(26, 0));
    for (char ch : s) {
      freq[0][ch - 'a']++;
    }

    freq            = multiplyMatrices(freq, transform);
    int totalLength = 0;
    for (int count : freq[0]) {
      totalLength += count;
      if (totalLength >= kMod)
        totalLength -= kMod;
    }

    return totalLength;
  }

private:
  vector<vector<ll>> multiplyMatrices(const vector<vector<ll>> &A,
                                      const vector<vector<ll>> &B) {
    int rowsA = A.size(), colsA = A[0].size(), colsB = B[0].size();
    vector<vector<__int128_t>> temp(rowsA, vector<__int128_t>(colsB, 0));
    vector<vector<ll>>         result(rowsA, vector<ll>(colsB, 0));

    for (int i = 0; i < rowsA; i++) {
      for (int j = 0; j < colsB; j++) {
        for (int k = 0; k < colsA; k++) {
          temp[i][j] += A[i][k] * B[k][j];
        }
        result[i][j] = temp[i][j] % kMod;
      }
    }
    return result;
  }

  vector<vector<ll>> powerMatrix(vector<vector<ll>> matrix, ll exponent) {
    vector<vector<ll>> result(matrix.size(), vector<ll>(matrix.size(), 0));

    for (int i = 0; i < matrix.size(); i++)
      result[i][i] = 1;

    while (exponent > 0) {
      if (exponent % 2 == 1)
        result = multiplyMatrices(result, matrix);
      matrix = multiplyMatrices(matrix, matrix);
      exponent /= 2;
    }
    return result;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists only of lowercase English letters.
// * |1 <= t <= 10⁹|
// * |nums.length == 26|
// * |1 <= nums[i] <= 25|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcyy", t = 2, nums =
//  [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(3337, TotalCharactersInStringAfterTransformationsII,
                           example_1) {
  auto        solution = MakeSolution();
  string      s        = "abcyy";
  int         t        = 2;
  vector<int> nums     = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2};
  int         expect   = 7;
  int         actual   = solution->lengthAfterTransformations(s, t, nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "azbk", t = 1, nums =
//  [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(3337, TotalCharactersInStringAfterTransformationsII,
                           example_2) {
  auto        solution = MakeSolution();
  string      s        = "azbk";
  int         t        = 1;
  vector<int> nums     = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                          2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
  int         expect   = 8;
  int         actual   = solution->lengthAfterTransformations(s, t, nums);
  LCD_EXPECT_EQ(expect, actual);
}
