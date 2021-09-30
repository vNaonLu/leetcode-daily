
#ifndef Q707_UNITTEST_H__
#define Q707_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0707.hpp"
using namespace std;

/**
  * prompt test
  *
  * 707.
  *      Design Linked List
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   Design your implementation of the linked list. You can choose to use a
  *   singly or doubly linked list.<br.
  *   
  *   A node in a singly linked list should have two attributes: ‘val’ and
  *   ‘next’ . ‘val’ is the value of the current node, and ‘next’ is a
  *   pointer/reference to the next node.<br.
  *   
  *   If you want to use the doubly linked list, you will need one more
  *   attribute ‘prev’ to indicate the previous node in the linked list.
  *   Assume all nodes in the linked list are “0-indexed”.
  *   
  *   Implement the ‘MyLinkedList’.
  *   
  *   - ‘MyLinkedList()’ Initializes the ‘MyLinkedList’ object.
  *   
  *   - ‘int get(int index)’ Get the value of the ‘indexᵗʰ’ node in the
  *   linked list. If the index is invalid, return ‘-1’.
  *   
  *   - ‘void addAtHead(int val)’ Add a node of value ‘val’ before the
  *   first element of the linked list. After the insertion, the new node
  *   will be the first node of the linked list.
  *   
  *   - ‘void addAtTail(int val)’ Append a node of value ‘val’ as the last
  *   element of the linked list.
  *   
  *   - ‘void addAtIndex(int index, int val)’ Add a node of value ‘val’
  *   before the ‘indexᵗʰ’ node in the linked list. If ‘index’ equals the
  *   length of the linked list, the node will be appended to the end of the
  *   linked list. If ‘index’ is greater than the length, the node “will not
  *   be inserted”.
  *   
  *   - ‘void deleteAtIndex(int index)’ Delete the ‘indexᵗʰ’ node in the
  *   linked list, if the index is valid.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘0 ≤ index, val ≤ 1000’
  *   • Please do not use the built-in LinkedList library.
  *   • At most ‘2000’ calls will be made to ‘get’ , ‘addAtHead’ , ‘addAtTail’ , ‘addAtIndex’ and ‘deleteAtIndex’ .
  *
*/

TEST(q707, sample_input01) {
  l707::MyLinkedList solver;
  solver.addAtHead(1);
  solver.addAtTail(3);
  solver.addAtIndex(1, 2);
  EXPECT_EQ(solver.get(1), 2);
  solver.deleteAtIndex(1);
  EXPECT_EQ(solver.get(1), 3);
}

#endif