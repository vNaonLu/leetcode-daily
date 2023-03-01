// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Linked List Random Node
//
// https://leetcode.com/problems/linked-list-random-node/
//
// Question ID: 382
// Difficult  : Medium
// Solve Date : 2022/01/07 18:11

#include "leetcode/list_node.h"
#include <iosfwd>
#include <random>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |382. Linked List Random Node|:
//
// Given a singly linked list, return a random node's value from the linked
// list. Each node must have the same probability of being chosen. Implement the
// |Solution| class:
//
//  • |Solution(ListNode head)| Initializes the object with the head of the
//  singly-linked list |head|.
//
//  • |int getRandom()| Chooses a node randomly from the list and returns its
//  value. All the nodes of the list should be equally likely to be chosen.
//  
//

LEETCODE_BEGIN_RESOLVING(382, LinkedListRandomNode, Solution);

class Solution {
private:
  random_device rd;
  vector<int>   dataset_;

public:
  Solution(ListNode *head) {
    while (nullptr != head) {
      dataset_.emplace_back(head->val);
      head = head->next;
    }
  }

  int getRandom() {
    mt19937_64                 rng(rd());
    uniform_int_distribution<> dist(0, dataset_.size() - 1);
    return dataset_.at(dist(rng));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the linked list will be in the range |[1, 10⁴]|.
// * |-10⁴ <= Node.val <= 10⁴|
// * At most |10⁴| calls will be made to |getRandom|.
// * What if the linked list is extremely large and its length is unknown to
// you?
// * Could you solve this efficiently without using extra space?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Solution", "getRandom", "getRandom", "getRandom", "getRandom",
//  "getRandom"]
// [[[1, 2, 3]], [], [], [], [], []]
// Output: [null, 1, 3, 2, 2, 3]
//
// Solution solution = new Solution([1, 2, 3]);
// solution.getRandom(); // return 1
// solution.getRandom(); // return 3
// solution.getRandom(); // return 2
// solution.getRandom(); // return 2
// solution.getRandom(); // return 3
// // getRandom() should return either 1, 2, or 3 randomly. Each element should
// have equal probability of returning.

LEETCODE_SOLUTION_UNITTEST(382, LinkedListRandomNode, example_1) {
  GTEST_SKIP() << "Random Output";
  ListNode *s0_head   = ListNode::FromVector({1, 2, 3} /*, looped_index*/);
  auto      solution  = MakeSolution(s0_head);
  int       s1_expect = 1;
  int       s1_actual = solution->getRandom();
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_expect = 3;
  int s2_actual = solution->getRandom();
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_expect = 2;
  int s3_actual = solution->getRandom();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_expect = 2;
  int s4_actual = solution->getRandom();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_expect = 3;
  int s5_actual = solution->getRandom();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  ListNode::Release(s0_head);
}
