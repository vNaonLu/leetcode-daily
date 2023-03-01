// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Champagne Tower
//
// https://leetcode.com/problems/champagne-tower/
//
// Question ID: 799
// Difficult  : Medium
// Solve Date : 2022/03/04 18:09

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |799. Champagne Tower|:
//
// We stack glasses in a pyramid, where the first row has |1| glass, the second
// row has |2| glasses, and so on until the 100ᵗʰ row.  Each glass holds one
// cup of champagne.
//
// Then, some champagne is poured into the first glass at the top.  When the
// topmost glass is full, any excess liquid poured will fall equally to the
// glass immediately to the left and right of it.  When those glasses become
// full, any excess champagne will fall equally to the left and right of those
// glasses, and so on.  (A glass at the bottom row has its excess champagne fall
// on the floor.)
//
// For example, after one cup of champagne is poured, the top most glass is
// full.  After two cups of champagne are poured, the two glasses on the second
// row are half full.  After three cups of champagne are poured, those two cups
// become full - there are 3 full glasses total now.  After four cups of
// champagne are poured, the third row has the middle glass half full, and the
// two outside glasses are a quarter full, as pictured below.
//
// ![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/03/09/tower.png)
//
// Now after pouring some non-negative integer cups of champagne, return how
// full the |jᵗʰ| glass in the |iᵗʰ| row is (both |i| and |j| are 0-indexed.)
//
//  
//

LEETCODE_BEGIN_RESOLVING(799, ChampagneTower, Solution);

class Solution {
public:
  double champagneTower(int poured, int query_row, int query_glass) {
    vector<vector<double>> tower(101, vector<double>(101, 0.));
    tower.front().front() = poured;
    for (int i = 0; i <= query_row; ++i) {
      for (int j = 0; j <= i; ++j) {
        double liq = (tower[i][j] - 1.0) / 2.0;
        if (liq > 0) {
          tower[i + 1][j] += liq;
          tower[i + 1][j + 1] += liq;
        }
      }
    }
    return min(1.0, tower[query_row][query_glass]);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= poured <= 10⁹|
// * |0 <= query_glass <= query_row < 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: poured = 1, query_row = 1, query_glass = 1
// Output: 0.00000
//
// We poured 1 cup of champange to the top glass of the tower (which is indexed
// as (0, 0)). There will be no excess liquid so all the glasses under the top
// glass will remain empty.

LEETCODE_SOLUTION_UNITTEST(799, ChampagneTower, example_1) {
  auto   solution    = MakeSolution();
  int    poured      = 1;
  int    query_row   = 1;
  int    query_glass = 1;
  double expect      = 0.00000;
  double actual      = solution->champagneTower(poured, query_row, query_glass);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: poured = 2, query_row = 1, query_glass = 1
// Output: 0.50000
//
// We poured 2 cups of champange to the top glass of the tower (which is indexed
// as (0, 0)). There is one cup of excess liquid. The glass indexed as (1, 0)
// and the glass indexed as (1, 1) will share the excess liquid equally, and
// each will get half cup of champange.

LEETCODE_SOLUTION_UNITTEST(799, ChampagneTower, example_2) {
  auto   solution    = MakeSolution();
  int    poured      = 2;
  int    query_row   = 1;
  int    query_glass = 1;
  double expect      = 0.50000;
  double actual      = solution->champagneTower(poured, query_row, query_glass);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: poured = 100000009, query_row = 33, query_glass = 17
// Output: 1.00000
//

LEETCODE_SOLUTION_UNITTEST(799, ChampagneTower, example_3) {
  auto   solution    = MakeSolution();
  int    poured      = 100000009;
  int    query_row   = 33;
  int    query_glass = 17;
  double expect      = 1.00000;
  double actual      = solution->champagneTower(poured, query_row, query_glass);
  LCD_EXPECT_EQ(expect, actual);
}
