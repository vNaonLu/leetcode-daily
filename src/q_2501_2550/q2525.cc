// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Categorize Box According to Criteria
//
// https://leetcode.com/problems/categorize-box-according-to-criteria/
//
// Question ID: 2525
// Difficult  : Easy
// Solve Date : 2023/11/06 21:24

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2525. Categorize Box According to Criteria|:
//
// Given four integers |length|, |width|, |height|, and |mass|, representing the
// dimensions and mass of a box, respectively, return a string representing the
// category of the box.
//
//  • The box is |"Bulky"| if:
//
//
//    • Any of the dimensions of the box is greater or equal to |10⁴|.
//
//    • Or, the volume of the box is greater or equal to |10⁹|.
//
//
//
//  • If the mass of the box is greater or equal to |100|, it is |"Heavy".|
//
//  • If the box is both |"Bulky"| and |"Heavy"|, then its category is |"Both"|.
//
//  • If the box is neither |"Bulky"| nor |"Heavy"|, then its category is
//  |"Neither"|.
//
//  • If the box is |"Bulky"| but not |"Heavy"|, then its category is |"Bulky"|.
//
//  • If the box is |"Heavy"| but not |"Bulky"|, then its category is |"Heavy"|.
// Note that the volume of the box is the product of its length, width and
// height.
//
//

LEETCODE_BEGIN_RESOLVING(2525, CategorizeBoxAccordingToCriteria, Solution);

class Solution {
public:
  string categorizeBox(int length, int width, int height, int mass) {
    bool is_bulky = (length >= 1e+4) || (width >= 1e+4) || (height >= 1e+4) ||
                    (1e+9 / length / width / height <= 1);
    bool is_heavy = mass >= 100;

    return is_bulky && is_heavy
               ? "Both"
               : (is_bulky ? "Bulky" : (is_heavy ? "Heavy" : "Neither"));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= length, width, height <= 10⁵|
// * |1 <= mass <= 10³|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: length = 1000, width = 35, height = 700, mass = 300
// Output: "Heavy"
//
// None of the dimensions of the box is greater or equal to 10⁴.
// Its volume = 24500000 <= 10⁹. So it cannot be categorized as "Bulky".
// However mass >= 100, so the box is "Heavy".
// Since the box is not "Bulky" but "Heavy", we return "Heavy".

LEETCODE_SOLUTION_UNITTEST(2525, CategorizeBoxAccordingToCriteria, example_1) {
  auto   solution = MakeSolution();
  int    length   = 1000;
  int    width    = 35;
  int    height   = 700;
  int    mass     = 300;
  string expect   = "Heavy";
  string actual   = solution->categorizeBox(length, width, height, mass);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: length = 200, width = 50, height = 800, mass = 50
// Output: "Neither"
//
// None of the dimensions of the box is greater or equal to 10⁴.
// Its volume = 8 * 10⁶ <= 10⁹. So it cannot be categorized as "Bulky".
// Its mass is also less than 100, so it cannot be categorized as "Heavy"
// either. Since its neither of the two above categories, we return "Neither".

LEETCODE_SOLUTION_UNITTEST(2525, CategorizeBoxAccordingToCriteria, example_2) {
  auto   solution = MakeSolution();
  int    length   = 200;
  int    width    = 50;
  int    height   = 800;
  int    mass     = 50;
  string expect   = "Neither";
  string actual   = solution->categorizeBox(length, width, height, mass);
  LCD_EXPECT_EQ(expect, actual);
}
