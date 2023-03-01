// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Poor Pigs
//
// https://leetcode.com/problems/poor-pigs/
//
// Question ID: 458
// Difficult  : Hard
// Solve Date : 2022/08/06 15:12

#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |458. Poor Pigs|:
//
// There are |buckets| buckets of liquid, where exactly one of the buckets is
// poisonous. To figure out which one is poisonous, you feed some number of
// (poor) pigs the liquid to see whether they will die or not. Unfortunately,
// you only have |minutesToTest| minutes to determine which bucket is poisonous.
// You can feed the pigs according to these steps:
//
//  1. Choose some live pigs to feed.
//
//  2. For each pig, choose which buckets to feed it. The pig will consume all
//  the chosen buckets simultaneously and will take no time. Each pig can feed
//  from any number of buckets, and each bucket can be fed from by any number of
//  pigs.
//
//  3. Wait for |minutesToDie| minutes. You may not feed any other pigs during
//  this time.
//
//  4. After |minutesToDie| minutes have passed, any pigs that have been fed the
//  poisonous bucket will die, and all others will survive.
//
//  5. Repeat this process until you run out of time.
// Given |buckets|, |minutesToDie|, and |minutesToTest|, return the minimum
// number of pigs needed to figure out which bucket is poisonous within the
// allotted time.
//

LEETCODE_BEGIN_RESOLVING(458, PoorPigs, Solution);

class Solution {
public:
  int poorPigs(int buckets, int minutesToDie, int minutesToTest) {

    return ceil(log(buckets) / log(minutesToTest / minutesToDie + 1));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= buckets <= 1000|
// * |1 <=minutesToDie <=minutesToTest <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
// Output: 2
//
// We can determine the poisonous bucket as follows:
// At time 0, feed the first pig buckets 1 and 2, and feed the second pig
// buckets 2 and 3. At time 15, there are 4 possible outcomes:
// - If only the first pig dies, then bucket 1 must be poisonous.
// - If only the second pig dies, then bucket 3 must be poisonous.
// - If both pigs die, then bucket 2 must be poisonous.
// - If neither pig dies, then bucket 4 must be poisonous.

LEETCODE_SOLUTION_UNITTEST(458, PoorPigs, example_1) {
  auto solution      = MakeSolution();
  int  buckets       = 4;
  int  minutesToDie  = 15;
  int  minutesToTest = 15;
  int  expect        = 2;
  int  actual        = solution->poorPigs(buckets, minutesToDie, minutesToTest);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
// Output: 2
//
// We can determine the poisonous bucket as follows:
// At time 0, feed the first pig bucket 1, and feed the second pig bucket 2.
// At time 15, there are 2 possible outcomes:
// - If either pig dies, then the poisonous bucket is the one it was fed.
// - If neither pig dies, then feed the first pig bucket 3, and feed the second
// pig bucket 4. At time 30, one of the two pigs must die, and the poisonous
// bucket is the one it was fed.

LEETCODE_SOLUTION_UNITTEST(458, PoorPigs, example_2) {
  auto solution      = MakeSolution();
  int  buckets       = 4;
  int  minutesToDie  = 15;
  int  minutesToTest = 30;
  int  expect        = 2;
  int  actual        = solution->poorPigs(buckets, minutesToDie, minutesToTest);
  LCD_EXPECT_EQ(expect, actual);
}
