// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Distribute Candies to People
//
// https://leetcode.com/problems/distribute-candies-to-people/
//
// Question ID: 1103
// Difficult  : Easy
// Solve Date : 2023/07/26 22:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1103. Distribute Candies to People|:
//
// We distribute some number of |candies|, to a row of |n = num_people| people
// in the following way: We then give 1 candy to the first person, 2 candies to
// the second person, and so on until we give |n| candies to the last person.
// Then, we go back to the start of the row, giving |n + 1| candies to the first
// person, |n + 2| candies to the second person, and so on until we give |2 * n|
// candies to the last person. This process repeats (with us giving one more
// candy each time, and moving to the start of the row after we reach the end)
// until we run out of candies.  The last person will receive all of our
// remaining candies (not necessarily one more than the previous gift). Return
// an array (of length |num_people| and sum |candies|) that represents the final
// distribution of candies.
//
//

LEETCODE_BEGIN_RESOLVING(1103, DistributeCandiesToPeople, Solution);

class Solution {
public:
  vector<int> distributeCandies(int candies, int num_people) {
    vector<int> res(num_people);
    for (int i = 0; candies > 0; ++i) {
      res[i % num_people] += min(candies, i + 1);
      candies -= i + 1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * 1 <= candies <= 10^9
// * 1 <= num_people <= 1000
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: candies = 7, num_people = 4
// Output: [1,2,3,1]
//
// On the first turn, ans[0] += 1, and the array is [1,0,0,0].
// On the second turn, ans[1] += 2, and the array is [1,2,0,0].
// On the third turn, ans[2] += 3, and the array is [1,2,3,0].
// On the fourth turn, ans[3] += 1 (because there is only one candy left), and
// the final array is [1,2,3,1].

LEETCODE_SOLUTION_UNITTEST(1103, DistributeCandiesToPeople, example_1) {
  auto        solution   = MakeSolution();
  int         candies    = 7;
  int         num_people = 4;
  vector<int> expect     = {1, 2, 3, 1};
  vector<int> actual     = solution->distributeCandies(candies, num_people);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: candies = 10, num_people = 3
// Output: [5,2,3]
//
// On the first turn, ans[0] += 1, and the array is [1,0,0].
// On the second turn, ans[1] += 2, and the array is [1,2,0].
// On the third turn, ans[2] += 3, and the array is [1,2,3].
// On the fourth turn, ans[0] += 4, and the final array is [5,2,3].

LEETCODE_SOLUTION_UNITTEST(1103, DistributeCandiesToPeople, example_2) {
  auto        solution   = MakeSolution();
  int         candies    = 10;
  int         num_people = 3;
  vector<int> expect     = {5, 2, 3};
  vector<int> actual     = solution->distributeCandies(candies, num_people);
  LCD_EXPECT_EQ(expect, actual);
}
