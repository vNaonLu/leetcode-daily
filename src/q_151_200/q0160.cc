// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Intersection of Two Linked Lists
//
// https://leetcode.com/problems/intersection-of-two-linked-lists/
//
// Question ID: 160
// Difficult  : Easy
// Solve Date : 2021/09/29 14:18

#include "leetcode/list_node.h"
#include <iosfwd>
#include <set>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |160. Intersection of Two Linked Lists|:
//
// Given the heads of two singly linked-lists |headA| and |headB|, return the
// node at which the two lists intersect. If the two linked lists have no
// intersection at all, return |null|. For example, the following two linked
// lists begin to intersect at node |c1|:
// ![img](https://assets.leetcode.com/uploads/2021/03/05/160_statement.png)
// The test cases are generated such that there are no cycles anywhere in the
// entire linked structure. Note that the linked lists must retain their
// original structure after the function returns. Custom Judge: The inputs to
// the judge are given as follows (your program is not given these inputs):
//
//  • |intersectVal| - The value of the node where the intersection occurs. This
//  is |0| if there is no intersected node.
//
//  • |listA| - The first linked list.
//
//  • |listB| - The second linked list.
//
//  • |skipA| - The number of nodes to skip ahead in |listA| (starting from the
//  head) to get to the intersected node.
//
//  • |skipB| - The number of nodes to skip ahead in |listB| (starting from the
//  head) to get to the intersected node.
// The judge will then create the linked structure based on these inputs and
// pass the two heads, |headA| and |headB| to your program. If you correctly
// return the intersected node, then your solution will be accepted.  
//

LEETCODE_BEGIN_RESOLVING(160, IntersectionOfTwoLinkedLists, Solution);

class Solution {
public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    unordered_set<ListNode *> setA;
    ListNode                 *p = headA;
    while (p != nullptr) {
      setA.insert(p);
      p = p->next;
    }
    p = headB;
    while (p != nullptr) {
      if (setA.count(p))
        return p;
      p = p->next;
    }
    return nullptr;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes of |listA| is in the |m|.
// * The number of nodes of |listB| is in the |n|.
// * |1 <= m, n <= 3 * 10⁴|
// * |1 <= Node.val <= 10⁵|
// * |0 <= skipA < m|
// * |0 <= skipB < n|
// * |intersectVal| is |0| if |listA| and |listB| do not intersect.
// * |intersectVal == listA[skipA] == listB[skipB]| if |listA| and |listB|
// intersect.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA =
//  2, skipB = 3
// Output: Intersected at '8'
//
// The intersected node's value is 8 (note that this must not be 0 if the two
// lists intersect). From the head of A, it reads as [4,1,8,4,5]. From the head
// of B, it reads as [5,6,1,8,4,5]. There are 2 nodes before the intersected
// node in A; There are 3 nodes before the intersected node in B.
// - Note that the intersected node's value is not 1 because the nodes with
// value 1 in A and B (2ⁿᵈ node in A and 3ʳᵈ node in B) are different node
// references. In other words, they point to two different locations in memory,
// while the nodes with value 8 in A and B (3ʳᵈ node in A and 4ᵗʰ node in B)
// point to the same location in memory.

LEETCODE_SOLUTION_UNITTEST(160, IntersectionOfTwoLinkedLists, example_1) {
  auto      solution       = MakeSolution();
  ListNode *headA          = ListNode::FromVector({4, 1, 8, 4, 5});
  ListNode *headB          = ListNode::FromVector({5, 6, 1});
  ListNode *expect         = headA->GetChild(2);
  headB->GetChild(2)->next = expect;
  ListNode *actual         = solution->getIntersectionNode(headA, headB);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(headA, headB, expect, actual);
}

// [Example #2]
//  Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3,
//  skipB = 1
// Output: Intersected at '2'
//
// The intersected node's value is 2 (note that this must not be 0 if the two
// lists intersect). From the head of A, it reads as [1,9,1,2,4]. From the head
// of B, it reads as [3,2,4]. There are 3 nodes before the intersected node in
// A; There are 1 node before the intersected node in B.

LEETCODE_SOLUTION_UNITTEST(160, IntersectionOfTwoLinkedLists, example_2) {
  auto      solution       = MakeSolution();
  ListNode *headA          = ListNode::FromVector({1, 9, 1, 2, 4});
  ListNode *headB          = ListNode::FromVector({3});
  ListNode *expect         = headA->GetChild(3);
  headB->GetChild(0)->next = expect;
  ListNode *actual         = solution->getIntersectionNode(headA, headB);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(headA, headB, expect, actual);
}

// [Example #3]
//  Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB =
//  2
// Output: No intersection
//
// From the head of A, it reads as [2,6,4]. From the head of B, it reads as
// [1,5]. Since the two lists do not intersect, intersectVal must be 0, while
// skipA and skipB can be arbitrary values. Explanation: The two lists do not
// intersect, so return null.

LEETCODE_SOLUTION_UNITTEST(160, IntersectionOfTwoLinkedLists, example_3) {
  auto      solution = MakeSolution();
  ListNode *headA    = ListNode::FromVector({2, 6, 3});
  ListNode *headB    = ListNode::FromVector({1, 5});
  ListNode *expect   = nullptr;
  ListNode *actual   = solution->getIntersectionNode(headA, headB);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(headA, headB, expect, actual);
}
