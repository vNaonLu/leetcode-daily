// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reformat Phone Number
//
// https://leetcode.com/problems/reformat-phone-number/
//
// Question ID: 1694
// Difficult  : Easy
// Solve Date : 2023/03/22 20:05

#include <cctype>
#include <iosfwd>
#include <queue>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1694. Reformat Phone Number|:
//
// You are given a phone number as a string |number|. |number| consists of
// digits, spaces |' '|, and/or dashes |'-'|. You would like to reformat the
// phone number in a certain manner. Firstly, remove all spaces and dashes.
// Then, group the digits from left to right into blocks of length 3 until there
// are 4 or fewer digits. The final digits are then grouped as follows:
//
//  • 2 digits: A single block of length 2.
//
//  • 3 digits: A single block of length 3.
//
//  • 4 digits: Two blocks of length 2 each.
// The blocks are then joined by dashes. Notice that the reformatting process
// should never produce any blocks of length 1 and produce at most two blocks of
// length 2. Return the phone number after formatting.
//
//

LEETCODE_BEGIN_RESOLVING(1694, ReformatPhoneNumber, Solution);

class Solution {
private:
  string popOut(queue<char> &q, size_t cnt) {
    string res;
    while (cnt-- > 0) {
      res += q.front();
      q.pop();
    }
    return res;
  }

public:
  string reformatNumber(string number) {
    string      res;
    queue<char> nums;
    for (auto c : number) {
      if (isdigit(c)) {
        nums.emplace(c);
      }
    }
    while (!nums.empty()) {
      if (nums.size() > 4) {
        res += std::move(popOut(nums, 3));
      } else if (nums.size() == 4) {
        res += std::move(popOut(nums, 2));
        res += '-';
        res += std::move(popOut(nums, 2));
      } else {
        res += std::move(popOut(nums, nums.size()));
      }
      res += '-';
    }
    res.pop_back();
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= number.length <= 100|
// * |number| consists of digits and the characters |'-'| and |' '|.
// * There are at least two digits in |number|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: number = "1-23-45 6"
// Output: "123-456"
//
// The digits are "123456".
// Step 1: There are more than 4 digits, so group the next 3 digits. The 1st
// block is "123". Step 2: There are 3 digits remaining, so put them in a single
// block of length 3. The 2nd block is "456". Joining the blocks gives
// "123-456".

LEETCODE_SOLUTION_UNITTEST(1694, ReformatPhoneNumber, example_1) {
  auto   solution = MakeSolution();
  string number   = "1-23-45 6";
  string expect   = "123-456";
  string actual   = solution->reformatNumber(number);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: number = "123 4-567"
// Output: "123-45-67"
//
// The digits are "1234567".
// Step 1: There are more than 4 digits, so group the next 3 digits. The 1st
// block is "123". Step 2: There are 4 digits left, so split them into two
// blocks of length 2. The blocks are "45" and "67". Joining the blocks gives
// "123-45-67".

LEETCODE_SOLUTION_UNITTEST(1694, ReformatPhoneNumber, example_2) {
  auto   solution = MakeSolution();
  string number   = "123 4-567";
  string expect   = "123-45-67";
  string actual   = solution->reformatNumber(number);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: number = "123 4-5678"
// Output: "123-456-78"
//
// The digits are "12345678".
// Step 1: The 1st block is "123".
// Step 2: The 2nd block is "456".
// Step 3: There are 2 digits left, so put them in a single block of length 2.
// The 3rd block is "78". Joining the blocks gives "123-456-78".

LEETCODE_SOLUTION_UNITTEST(1694, ReformatPhoneNumber, example_3) {
  auto   solution = MakeSolution();
  string number   = "123 4-5678";
  string expect   = "123-456-78";
  string actual   = solution->reformatNumber(number);
  LCD_EXPECT_EQ(expect, actual);
}
