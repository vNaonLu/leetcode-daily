// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Filling Bookcase Shelves
//
// https://leetcode.com/problems/filling-bookcase-shelves/
//
// Question ID: 1105
// Difficult  : Medium
// Solve Date : 2024/07/31 23:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1105. Filling Bookcase Shelves|:
//
// You are given an array |books| where |books[i] = [thicknessᵢ, heightᵢ]|
// indicates the thickness and height of the |iᵗʰ| book. You are also given an
// integer |shelfWidth|. We want to place these books in order onto bookcase
// shelves that have a total width |shelfWidth|. We choose some of the books to
// place on this shelf such that the sum of their thickness is less than or
// equal to |shelfWidth|, then build another level of the shelf of the bookcase
// so that the total height of the bookcase has increased by the maximum height
// of the books we just put down. We repeat this process until there are no more
// books to place. Note that at each step of the above process, the order of the
// books we place is the same order as the given sequence of books.
//
//  • For example, if we have an ordered list of |5| books, we might place the
//  first and second book onto the first shelf, the third book on the second
//  shelf, and the fourth and fifth book on the last shelf.
// Return the minimum possible height that the total bookshelf can be after
// placing shelves in this manner.
//
//

LEETCODE_BEGIN_RESOLVING(1105, FillingBookcaseShelves, Solution);

class Solution {
public:
  int minHeightShelves(vector<vector<int>> &books, int shelfWidth) {
    int         n = books.size();
    vector<int> f(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      int w = books[i - 1][0];
      int h = books[i - 1][1];
      f[i]  = f[i - 1] + h;
      for (int j = i - 1; j > 0; --j) {
        w += books[j - 1][0];
        if (w > shelfWidth) {
          break;
        }

        h    = max(h, books[j - 1][1]);
        f[i] = min(f[i], f[j - 1] + h);
      }
    }
    return f[n];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= books.length <= 1000|
// * |1 <= thicknessᵢ <= shelfWidth <= 1000|
// * |1 <= heightᵢ <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelfWidth = 4
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(1105, FillingBookcaseShelves, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> books    = {
      {1, 1},
      {2, 3},
      {2, 3},
      {1, 1},
      {1, 1},
      {1, 1},
      {1, 2}
  };
  int shelfWidth = 4;
  int expect     = 6;
  int actual     = solution->minHeightShelves(books, shelfWidth);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: books = [[1,3],[2,4],[3,2]], shelfWidth = 6
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1105, FillingBookcaseShelves, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> books    = {
      {1, 3},
      {2, 4},
      {3, 2}
  };
  int shelfWidth = 6;
  int expect     = 4;
  int actual     = solution->minHeightShelves(books, shelfWidth);
  LCD_EXPECT_EQ(expect, actual);
}
