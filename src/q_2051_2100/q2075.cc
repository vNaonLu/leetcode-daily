// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Decode the Slanted Ciphertext
//
// https://leetcode.com/problems/decode-the-slanted-ciphertext/
//
// Question ID: 2075
// Difficult  : Medium
// Solve Date : 2026/04/04 18:28

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2075. Decode the Slanted Ciphertext|:
//
// A string |originalText| is encoded using a slanted transposition cipher to a
// string |encodedText| with the help of a matrix having a fixed number of rows
// |rows|. |originalText| is placed first in a top-left to bottom-right manner.
// ![img](https://assets.leetcode.com/uploads/2021/11/07/exa11.png)
// The blue cells are filled first, followed by the red cells, then the yellow
// cells, and so on, until we reach the end of |originalText|. The arrow
// indicates the order in which the cells are filled. All empty cells are filled
// with |' '|. The number of columns is chosen such that the rightmost column
// will not be empty after filling in |originalText|. |encodedText| is then
// formed by appending all characters of the matrix in a row-wise fashion.
// ![img](https://assets.leetcode.com/uploads/2021/11/07/exa12.png)
// The characters in the blue cells are appended first to |encodedText|, then
// the red cells, and so on, and finally the yellow cells. The arrow indicates
// the order in which the cells are accessed. For example, if |originalText =
// "cipher"| and |rows = 3|, then we encode it in the following manner:
// ![img](https://assets.leetcode.com/uploads/2021/10/25/desc2.png)
// The blue arrows depict how |originalText| is placed in the matrix, and the
// red arrows denote the order in which |encodedText| is formed. In the above
// example, |encodedText = "ch ie pr"|. Given the encoded string |encodedText|
// and number of rows |rows|, return the original string |originalText|. Note:
// |originalText| does not have any trailing spaces |' '|. The test cases are
// generated such that there is only one possible |originalText|.
//
//

LEETCODE_BEGIN_RESOLVING(2075, DecodeTheSlantedCiphertext, Solution);

class Solution {
public:
  string decodeCiphertext(string s, int rows) {
    if (s.empty())
      return s;

    int n    = s.size();
    int cols = (n + rows - 1) / rows;

    string res;

    for (int start = 0; start < cols; start++) {
      int r = 0, c = start;
      while (r < rows && c < cols) {
        res += s[r * cols + c];
        r++;
        c++;
      }
    }

    while (!res.empty() && res.back() == ' ')
      res.pop_back();
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= encodedText.length <= 10⁶|
// * |encodedText| consists of lowercase English letters and |' '| only.
// * |encodedText| is a valid encoding of some |originalText| that does not have
// trailing spaces.
// * |1 <= rows <= 1000|
// * The testcases are generated such that there is only one possible
// |originalText|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: encodedText = "ch ie pr", rows = 3
// Output: "cipher"
//

LEETCODE_SOLUTION_UNITTEST(2075, DecodeTheSlantedCiphertext, example_1) {
  auto   solution    = MakeSolution();
  string encodedText = "ch   ie   pr";
  int    rows        = 3;
  string expect      = "cipher";
  string actual      = solution->decodeCiphertext(encodedText, rows);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: encodedText = "iveo eed l te olc", rows = 4
// Output: "i love leetcode"
//

LEETCODE_SOLUTION_UNITTEST(2075, DecodeTheSlantedCiphertext, example_2) {
  auto   solution    = MakeSolution();
  string encodedText = "iveo    eed   l te   olc";
  int    rows        = 4;
  string expect      = "i love leetcode";
  string actual      = solution->decodeCiphertext(encodedText, rows);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: encodedText = "coding", rows = 1
// Output: "coding"
//

LEETCODE_SOLUTION_UNITTEST(2075, DecodeTheSlantedCiphertext, example_3) {
  auto   solution    = MakeSolution();
  string encodedText = "coding";
  int    rows        = 1;
  string expect      = "coding";
  string actual      = solution->decodeCiphertext(encodedText, rows);
  LCD_EXPECT_EQ(expect, actual);
}
