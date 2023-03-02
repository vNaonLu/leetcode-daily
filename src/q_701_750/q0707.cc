// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design Linked List
//
// https://leetcode.com/problems/design-linked-list/
//
// Question ID: 707
// Difficult  : Medium
// Solve Date : 2021/09/30 14:17

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |707. Design Linked List|:
//
// Design your implementation of the linked list. You can choose to use a singly
// or doubly linked list. A node in a singly linked list should have two
// attributes: |val| and |next|. |val| is the value of the current node, and
// |next| is a pointer/reference to the next node. If you want to use the doubly
// linked list, you will need one more attribute |prev| to indicate the previous
// node in the linked list. Assume all nodes in the linked list are 0-indexed.
// Implement the |MyLinkedList| class:
//
//  • |MyLinkedList()| Initializes the |MyLinkedList| object.
//
//  • |int get(int index)| Get the value of the |indexᵗʰ| node in the linked
//  list. If the index is invalid, return |-1|.
//
//  • |void addAtHead(int val)| Add a node of value |val| before the first
//  element of the linked list. After the insertion, the new node will be the
//  first node of the linked list.
//
//  • |void addAtTail(int val)| Append a node of value |val| as the last element
//  of the linked list.
//
//  • |void addAtIndex(int index, int val)| Add a node of value |val| before the
//  |indexᵗʰ| node in the linked list. If |index| equals the length of the
//  linked list, the node will be appended to the end of the linked list. If
//  |index| is greater than the length, the node will not be inserted.
//
//  • |void deleteAtIndex(int index)| Delete the |indexᵗʰ| node in the linked
//  list, if the index is valid.
//  
//

LEETCODE_BEGIN_RESOLVING(707, DesignLinkedList, MyLinkedList);

class MyLinkedList {
private:
  struct node {
    node *next;
    int   val;
    node(int val) : next(nullptr), val(val) {}
  }     *m_node;
  size_t m_size;

public:
  MyLinkedList() {
    m_node = nullptr;
    m_size = 0;
  }
  void print(string pmt) {
    node *p = m_node;
    cout << "after " << pmt << ", size: " << m_size << "  ";
    while (p != nullptr) {
      cout << p->val << " ";
      p = p->next;
    }
    cout << endl;
  }
  int get(int index) {
    if (index >= m_size)
      return -1;
    node *p = m_node;
    while (index > 0) {
      --index;
      p = p->next;
    }
    return p->val;
  }
  void addAtHead(int val) {
    node *p = new node(val);
    if (m_node == nullptr) {
      m_node = p;
    } else {
      p->next = m_node;
      m_node  = p;
    }
    ++m_size;
  }
  void addAtTail(int val) {
    node *lead = m_node;
    while (lead != nullptr && lead->next != nullptr) {
      lead = lead->next;
    }
    if (lead == nullptr) {
      m_node = new node(val);
    } else {
      lead->next = new node(val);
    }
    ++m_size;
  }
  void addAtIndex(int index, int val) {
    if (index > m_size)
      return;
    if (index == 0) {
      addAtHead(val);
    } else {
      node *p    = new node(val);
      node *lead = m_node;
      while (--index > 0) {
        lead = lead->next;
      }
      p->next    = lead->next;
      lead->next = p;
    }
    ++m_size;
  }
  void deleteAtIndex(int index) {
    if (index >= m_size)
      return;
    if (index == 0) {
      node *p = m_node;
      m_node  = m_node->next;
      delete p;
    } else {
      node *lead = m_node;
      while (--index > 0) {
        lead = lead->next;
      }
      node *p    = lead->next;
      lead->next = p->next;
      delete p;
    }
    --m_size;
  }
};

LEETCODE_END_RESOLVING(MyLinkedList);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= index, val <= 1000|
// * Please do not use the built-in LinkedList library.
// * At most |2000| calls will be made to |get|, |addAtHead|, |addAtTail|,
// |addAtIndex| and |deleteAtIndex|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get",
//  "deleteAtIndex", "get"]
// [[], [1], [3], [1, 2], [1], [1], [1]]
// Output: [null, null, null, null, 2, null, 3]
//
// MyLinkedList myLinkedList = new MyLinkedList();
// myLinkedList.addAtHead(1);
// myLinkedList.addAtTail(3);
// myLinkedList.addAtIndex(1, 2); // linked list becomes 1->2->3
// myLinkedList.get(1); // return 2
// myLinkedList.deleteAtIndex(1); // now the linked list is 1->3
// myLinkedList.get(1); // return 3

LEETCODE_SOLUTION_UNITTEST(707, DesignLinkedList, example_1) {
  auto my_linked_list = MakeMyLinkedList();
  int  s1_val         = 1;
  my_linked_list->addAtHead(s1_val);
  int s2_val = 3;
  my_linked_list->addAtTail(s2_val);
  int s3_index = 1;
  int s3_val   = 2;
  my_linked_list->addAtIndex(s3_index, s3_val);
  int s4_index  = 1;
  int s4_expect = 2;
  int s4_actual = my_linked_list->get(s4_index);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_index = 1;
  my_linked_list->deleteAtIndex(s5_index);
  int s6_index  = 1;
  int s6_expect = 3;
  int s6_actual = my_linked_list->get(s6_index);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}
