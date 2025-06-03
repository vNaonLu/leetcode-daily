// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Candies You Can Get from Boxes
//
// https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/
//
// Question ID: 1298
// Difficult  : Hard
// Solve Date : 2025/06/03 19:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1298. Maximum Candies You Can Get from Boxes|:
//
// You have |n| boxes labeled from |0| to |n - 1|. You are given four arrays:
// |status|, |candies|, |keys|, and |containedBoxes| where:
//
//  • |status[i]| is |1| if the |iᵗʰ| box is open and |0| if the |iᵗʰ| box is
//  closed,
//
//  • |candies[i]| is the number of candies in the |iᵗʰ| box,
//
//  • |keys[i]| is a list of the labels of the boxes you can open after opening
//  the |iᵗʰ| box.
//
//  • |containedBoxes[i]| is a list of the boxes you found inside the |iᵗʰ| box.
// You are given an integer array |initialBoxes| that contains the labels of the
// boxes you initially have. You can take all the candies in any open box and
// you can use the keys in it to open new boxes and you also can use the boxes
// you find in it. Return the maximum number of candies you can get following
// the rules above.
//
//

LEETCODE_BEGIN_RESOLVING(1298, MaximumCandiesYouCanGetFromBoxes, Solution);

class Solution {
public:
  int maxCandies(vector<int> &status, vector<int> &candies,
                 vector<vector<int>> &keys, vector<vector<int>> &containedBoxes,
                 vector<int> &initialBoxes) {
    bool found_op = true;
    int  res      = 0;
    while (!initialBoxes.empty() && found_op) {
      found_op = false;
      vector<int> next;
      for (auto id : initialBoxes) {
        if (status[id]) {
          found_op = true;
          next.insert(next.end(), containedBoxes[id].begin(),
                      containedBoxes[id].end());
          for (auto _id : keys[id]) {
            status[_id] = 1;
          }
          res += candies[id];
        } else {
          next.emplace_back(id);
        }
      }
      swap(initialBoxes, next);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == status.length == candies.length == keys.length ==
// containedBoxes.length|
// * |1 <= n <= 1000|
// * |status[i]| is either |0| or |1|.
// * |1 <= candies[i] <= 1000|
// * |0 <= keys[i].length <= n|
// * |0 <= keys[i][j] < n|
// * All values of |keys[i]| are unique.
// * |0 <= containedBoxes[i].length <= n|
// * |0 <= containedBoxes[i][j] < n|
// * All values of |containedBoxes[i]| are unique.
// * Each box is contained in one box at most.
// * |0 <= initialBoxes.length <= n|
// * |0 <= initialBoxes[i] < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]],
//  containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(1298, MaximumCandiesYouCanGetFromBoxes, example_1) {
  auto                solution       = MakeSolution();
  vector<int>         status         = {1, 0, 1, 0};
  vector<int>         candies        = {7, 5, 4, 100};
  vector<vector<int>> keys           = {{}, {}, {1}, {}};
  vector<vector<int>> containedBoxes = {
      {1, 2},
      {3},
      {},
      {}
  };
  vector<int> initialBoxes = {0};
  int         expect       = 16;
  int         actual =
      solution->maxCandies(status, candies, keys, containedBoxes, initialBoxes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: status = [1,0,0,0,0,0], candies = [1,1,1,1,1,1], keys =
//  [[1,2,3,4,5],[],[],[],[],[]], containedBoxes = [[1,2,3,4,5],[],[],[],[],[]],
//  initialBoxes = [0]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(1298, MaximumCandiesYouCanGetFromBoxes, example_2) {
  auto                solution = MakeSolution();
  vector<int>         status   = {1, 0, 0, 0, 0, 0};
  vector<int>         candies  = {1, 1, 1, 1, 1, 1};
  vector<vector<int>> keys     = {
      {1, 2, 3, 4, 5},
      {},
      {},
      {},
      {},
      {}
  };
  vector<vector<int>> containedBoxes = {
      {1, 2, 3, 4, 5},
      {},
      {},
      {},
      {},
      {}
  };
  vector<int> initialBoxes = {0};
  int         expect       = 6;
  int         actual =
      solution->maxCandies(status, candies, keys, containedBoxes, initialBoxes);
  LCD_EXPECT_EQ(expect, actual);
}
