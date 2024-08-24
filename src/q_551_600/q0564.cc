// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Closest Palindrome
//
// https://leetcode.com/problems/find-the-closest-palindrome/
//
// Question ID: 564
// Difficult  : Hard
// Solve Date : 2024/08/24 16:28

#include <cmath>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |564. Find the Closest Palindrome|:
//
// Given a string |n| representing an integer, return the closest integer (not
// including itself), which is a palindrome. If there is a tie, return the
// smaller one. The closest is defined as the absolute difference minimized
// between two integers.
//
//

LEETCODE_BEGIN_RESOLVING(564, FindTheClosestPalindrome, Solution);

class Solution {
public:
  string nearestPalindromic(string numberStr) {
    int64_t number = stoll(numberStr);

    // Edge cases for small numbers
    if (number <= 10)
      return to_string(number - 1);
    if (number == 11)
      return "9";

    // Special case for 18-digit number with all 9s, thanks to dcodeDV for
    // pointing this out
    if (numberStr == "999999999999999999") {
      return "1000000000000000001";
    }

    int     length   = numberStr.length();
    int64_t leftHalf = stoll(numberStr.substr(0, (length + 1) / 2));

    vector<int64_t> palindromeCandidates(5);
    palindromeCandidates[0] =
        generatePalindromeFromLeft(leftHalf - 1, length % 2 == 0);
    palindromeCandidates[1] =
        generatePalindromeFromLeft(leftHalf, length % 2 == 0);

    // Handle potential overflow for leftHalf + 1
    if (leftHalf < 999999999) {
      palindromeCandidates[2] =
          generatePalindromeFromLeft(leftHalf + 1, length % 2 == 0);
    } else {
      palindromeCandidates[2] = stoll("1" + string(length - 1, '0') + "1");
    }

    palindromeCandidates[3] = pow(10, length - 1) - 1;
    palindromeCandidates[4] = pow(10, length) + 1;

    int64_t nearestPalindrome = 0;
    int64_t minDifference     = numeric_limits<int64_t>::max();

    for (int64_t candidate : palindromeCandidates) {
      if (candidate == number)
        continue;
      int64_t difference = abs(candidate - number);
      if (difference < minDifference ||
          (difference == minDifference && candidate < nearestPalindrome)) {
        minDifference     = difference;
        nearestPalindrome = candidate;
      }
    }

    return to_string(nearestPalindrome);
  }

private:
  int64_t generatePalindromeFromLeft(int64_t leftHalf, bool isEvenLength) {
    int64_t palindrome = leftHalf;
    if (!isEvenLength)
      leftHalf /= 10;
    while (leftHalf > 0) {
      palindrome = palindrome * 10 + leftHalf % 10;
      leftHalf /= 10;
    }
    return palindrome;
  }
};

// https://leetcode.com/problems/find-the-closest-palindrome/submissions/1366449944/

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n.length <= 18|
// * |n| consists of only digits.
// * |n| does not have leading zeros.
// * |n| is representing an integer in the range |[1, 10¹⁸ - 1]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = "123"
// Output: "121"
//

LEETCODE_SOLUTION_UNITTEST(564, FindTheClosestPalindrome, example_1) {
  auto   solution = MakeSolution();
  string n        = "123";
  string expect   = "121";
  string actual   = solution->nearestPalindromic(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = "1"
// Output: "0"
//

LEETCODE_SOLUTION_UNITTEST(564, FindTheClosestPalindrome, example_2) {
  auto   solution = MakeSolution();
  string n        = "1";
  string expect   = "0";
  string actual   = solution->nearestPalindromic(n);
  LCD_EXPECT_EQ(expect, actual);
}
