// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Insertion Sort List
//
// https://leetcode.com/problems/insertion-sort-list/
//
// Question ID: 147
// Difficult  : Medium
// Solve Date : 2021/12/15 18:04

#include "leetcode/list_node.h"
#include <algorithm>
#include <iosfwd>
#include <map>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |147. Insertion Sort List|:
//
// Given the |head| of a singly linked list, sort the list using insertion sort,
// and return the sorted list's head. The steps of the insertion sort algorithm:
//
//  1. Insertion sort iterates, consuming one input element each repetition and
//  growing a sorted output list.
//
//  2. At each iteration, insertion sort removes one element from the input
//  data, finds the location it belongs within the sorted list and inserts it
//  there.
//
//  3. It repeats until no input elements remain.
// The following is a graphical example of the insertion sort algorithm. The
// partially sorted list (black) initially contains only the first element in
// the list. One element (red) is removed from the input data and inserted
// in-place into the sorted list with each iteration.
// ![img](https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)
//  
//

LEETCODE_BEGIN_RESOLVING(147, InsertionSortList, Solution);

class Solution {
private:
  struct _compare {
    inline bool operator()(const ListNode *lhs,
                           const ListNode *rhs) const noexcept {
      return lhs->val < rhs->val;
    }
  };

public:
  ListNode *insertionSortList(ListNode *head) {
    if (nullptr == head)
      return nullptr;
    multiset<ListNode *, _compare> sort_map;
    while (head != nullptr) {
      auto p = head;
      sort_map.insert(new ListNode(p->val));
      head = head->next;
    }
    /// link
    for (auto it = sort_map.begin(); it != sort_map.end(); ++it) {
      auto next = it;
      if (++next != sort_map.end())
        (*it)->next = *(next);
    }
    return *(sort_map.begin());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[1, 5000]|.
// * |-5000 <= Node.val <= 5000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [4,2,1,3]
// Output: [1,2,3,4]
//

LEETCODE_SOLUTION_UNITTEST(147, InsertionSortList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({4, 2, 1, 3} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 2, 3, 4} /*, looped_index*/);
  ListNode *actual   = solution->insertionSortList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [-1,5,3,4,0]
// Output: [-1,0,3,4,5]
//

LEETCODE_SOLUTION_UNITTEST(147, InsertionSortList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head   = ListNode::FromVector({-1, 5, 3, 4, 0} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({-1, 0, 3, 4, 5} /*, looped_index*/);
  ListNode *actual = solution->insertionSortList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}
