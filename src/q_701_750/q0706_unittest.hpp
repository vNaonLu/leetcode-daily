
#ifndef Q706_UNITTEST_H__
#define Q706_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0706.hpp"
using namespace std;

/**
  * prompt test
  *
  * 706.
  *      Design HashMap
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   Design a HashMap without using any built-in hash table libraries.
  *   
  *   Implement the ‘MyHashMap’.
  *   
  *   - ‘MyHashMap()’ initializes the object with an empty map.
  *   
  *   - ‘void put(int key, int value)’ inserts a ‘(key, value)’ pair into
  *   the HashMap. If the ‘key’ already exists in the map, update the
  *   corresponding ‘value’.
  *   
  *   - ‘int get(int key)’ returns the ‘value’ to which the specified ‘key’
  *   is mapped, or ‘-1’ if this map contains no mapping for the ‘key’.
  *   
  *   - ‘void remove(key)’ removes the ‘key’ and its corresponding ‘value’
  *   if the map contains the mapping for the ‘key’.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘0 ≤ key, value ≤ 10⁶’
  *   • At most ‘10⁴’ calls will be made to ‘put’ , ‘get’ , and ‘remove’ .
  *
*/

TEST(q706, sample_input01) {
  l706::MyHashMap solver;
  solver.put(1, 1);
  solver.put(2, 2);
  EXPECT_EQ(solver.get(1), 1);
  EXPECT_EQ(solver.get(3), -1);
  solver.put(2, 1);
  EXPECT_EQ(solver.get(2), 1);
  solver.remove(2);
  EXPECT_EQ(solver.get(2), -1);
}

#endif