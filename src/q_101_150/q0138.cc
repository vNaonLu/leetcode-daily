// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Copy List with Random Pointer
//
// https://leetcode.com/problems/copy-list-with-random-pointer/
//
// Question ID: 138
// Difficult  : Medium
// Solve Date : 2022/03/12 13:26

#include <iosfwd>
#include <map>
#include <queue>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |138. Copy List with Random Pointer|:
//
// A linked list of length |n| is given such that each node contains an
// additional random pointer, which could point to any node in the list, or
// |null|. Construct a deep copy of the list. The deep copy should consist of
// exactly |n| brand new nodes, where each new node has its value set to the
// value of its corresponding original node. Both the |next| and |random|
// pointer of the new nodes should point to new nodes in the copied list such
// that the pointers in the original list and copied list represent the same
// list state. None of the pointers in the new list should point to nodes in the
// original list. For example, if there are two nodes |X| and |Y| in the
// original list, where |X.random --> Y|, then for the corresponding two nodes
// |x| and |y| in the copied list, |x.random --> y|. Return the head of the
// copied linked list. The linked list is represented in the input/output as a
// list of |n| nodes. Each node is represented as a pair of |[val,
// random_index]| where:
//
//  • |val|: an integer representing |Node.val|
//
//  • |random_index|: the index of the node (range from |0| to |n-1|) that the
//  |random| pointer points to, or |null| if it does not point to any node.
// Your code will only be given the |head| of the original linked list.
//  
//

LEETCODE_BEGIN_RESOLVING(138, CopyListWithRandomPointer, Solution);

class Node {
public:
  int   val;
  Node *next;
  Node *random;

  Node(int _val) {
    val    = _val;
    next   = NULL;
    random = NULL;
  }
};

class Solution {
public:
  Node *copyRandomList(Node *head) {
    unordered_map<Node *, pair<int, int>> pos_rdpos;
    queue<Node *>                         nodes;
    vector<Node *>                        res;
    int                                   idx = 0;
    Node                                 *p   = head;
    while (nullptr != p) {
      pos_rdpos[p].first = idx++;
      res.emplace_back(new Node(p->val));
      p = p->next;
    }
    res.emplace_back(nullptr);
    pos_rdpos[nullptr] = make_pair(idx, -1);
    p                  = head;
    while (nullptr != p) {
      pos_rdpos[p].second = pos_rdpos[p->random].first;
      nodes.emplace(p);
      p = p->next;
    }

    for (int i = 0; i < res.size() - 1; ++i) {
      auto curr    = res[i];
      curr->next   = res[i + 1];
      curr->random = res[pos_rdpos[head].second];
      head         = head->next;
    }

    return res.front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n <= 1000|
// * |-10⁴ <= Node.val <= 10⁴|
// * |Node.random| is |null| or is pointing to some node in the linked list.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
// Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
//

LEETCODE_SOLUTION_UNITTEST(138, CopyListWithRandomPointer, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: head = [[1,1],[2,1]]
// Output: [[1,1],[2,1]]
//

LEETCODE_SOLUTION_UNITTEST(138, CopyListWithRandomPointer, example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #3]
//  Input: head = [[3,null],[3,0],[3,null]]
// Output: [[3,null],[3,0],[3,null]]
//

LEETCODE_SOLUTION_UNITTEST(138, CopyListWithRandomPointer, example_3) {
  GTEST_SKIP() << "Unittest Not Implemented";
}
