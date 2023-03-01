// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Merge k Sorted Lists
//
// https://leetcode.com/problems/merge-k-sorted-lists/
//
// Question ID: 23
// Difficult  : Hard
// Solve Date : 2021/11/17 18:43

#include "leetcode/list_node.h"
#include <iosfwd>
#include <list>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |23. Merge k Sorted Lists|:
//
// You are given an array of |k| linked-lists |lists|, each linked-list is
// sorted in ascending order. Merge all the linked-lists into one sorted
// linked-list and return it.  
//

LEETCODE_BEGIN_RESOLVING(23, MergeKSortedLists, Solution);

class Solution {
private:
  ListNode *mergeHelper(ListNode *p, ListNode *q) {
    ListNode  dummy;
    ListNode *t = &dummy;
    while (p != nullptr && q != nullptr) {
      if (p->val > q->val) {
        t->next = q;
        q       = q->next;
      } else {
        t->next = p;
        p       = p->next;
      }
      t = t->next;
    }
    if (p != nullptr)
      t->next = p;
    if (q != nullptr)
      t->next = q;
    return dummy.next;
  }

public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    if (lists.empty())
      return nullptr;
    for (int i = 1; i < lists.size(); ++i)
      lists[0] = mergeHelper(lists[0], lists[i]);
    return lists.front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |k == lists.length|
// * |0 <= k <= 10⁴|
// * |0 <= lists[i].length <= 500|
// * |-10⁴ <= lists[i][j] <= 10⁴|
// * |lists[i]| is sorted in ascending order.
// * The sum of |lists[i].length| will not exceed |10⁴|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: lists = [[1,4,5],[1,3,4],[2,6]]
// Output: [1,1,2,3,4,4,5,6]
//
// The linked-lists are:
// [
//  1->4->5,
//  1->3->4,
//  2->6
// ]
// merging them into one sorted list:
// 1->1->2->3->4->4->5->6

LEETCODE_SOLUTION_UNITTEST(23, MergeKSortedLists, example_1) {
  auto               solution = MakeSolution();
  vector<ListNode *> lists    = {
      ListNode::FromVector({1, 4, 5} /*, looped_index*/),
      ListNode::FromVector({1, 3, 4} /*, looped_index*/),
      ListNode::FromVector({2, 6} /*, looped_index*/)};
  ListNode *expect =
      ListNode::FromVector({1, 1, 2, 3, 4, 4, 5, 6} /*, looped_index*/);
  ListNode *actual = solution->mergeKLists(lists);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(expect, actual);
}

// [Example #2]
//  Input: lists = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(23, MergeKSortedLists, example_2) {
  auto               solution = MakeSolution();
  vector<ListNode *> lists    = {};
  ListNode          *expect   = ListNode::FromVector({} /*, looped_index*/);
  ListNode          *actual   = solution->mergeKLists(lists);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(expect, actual);
}

// [Example #3]
//  Input: lists = [[]]
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(23, MergeKSortedLists, example_3) {
  auto               solution = MakeSolution();
  vector<ListNode *> lists    = {ListNode::FromVector({} /*, looped_index*/)};
  ListNode          *expect   = ListNode::FromVector({} /*, looped_index*/);
  ListNode          *actual   = solution->mergeKLists(lists);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(expect, actual);
}
