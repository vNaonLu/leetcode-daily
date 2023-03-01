// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Flatten Nested List Iterator
//
// https://leetcode.com/problems/flatten-nested-list-iterator/
//
// Question ID: 341
// Difficult  : Medium
// Solve Date : 2022/05/08 12:51

#include <iosfwd>
#include <list>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |341. Flatten Nested List Iterator|:
//
// You are given a nested list of integers |nestedList|. Each element is either
// an integer or a list whose elements may also be integers or other lists.
// Implement an iterator to flatten it. Implement the |NestedIterator| class:
//
//  • |NestedIterator(List<NestedInteger> nestedList)| Initializes the iterator
//  with the nested list |nestedList|.
//
//  • |int next()| Returns the next integer in the nested list.
//
//  • |boolean hasNext()| Returns |true| if there are still some integers in the
//  nested list and |false| otherwise.
// Your code will be tested with the following pseudocode:
// initialize iterator with nestedList
// res = []
// while iterator.hasNext()
//     append iterator.next() to the end of res
// return res
// If |res| matches the expected flattened list, then your code will be judged
// as correct.  
//

LEETCODE_BEGIN_RESOLVING(341, FlattenNestedListIterator, NestedIterator);

class NestedInteger {
public:
  // Return true if this NestedInteger holds a single integer, rather than a
  // nested list.
  bool isInteger() const;

  // Return the single integer that this NestedInteger holds, if it holds a
  // single integer The result is undefined if this NestedInteger holds a nested
  // list
  int getInteger() const;

  // Return the nested list that this NestedInteger holds, if it holds a nested
  // list The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger> &getList() const;
};

class NestedIterator {
private:
  vector<int>           expand_;
  vector<int>::iterator it_;

  void expand_integer(vector<int> &res, vector<NestedInteger> list) {
    for (auto &x : list) {
      if (x.isInteger()) {
        res.emplace_back(x.getInteger());
      } else {
        expand_integer(res, x.getList());
      }
    }
  }

public:
  NestedIterator(vector<NestedInteger> &nestedList) {
    expand_integer(expand_, nestedList);
    it_ = expand_.begin();
  }

  int next() { return *it_++; }

  bool hasNext() { return it_ != expand_.end(); }
};

LEETCODE_END_RESOLVING(NestedIterator);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nestedList.length <= 500|
// * The values of the integers in the nested list is in the range |[-10⁶,
// 10⁶]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nestedList = [[1,1],2,[1,1]]
// Output: [1,1,2,1,1]
//
// By calling next repeatedly until hasNext returns false, the order of elements
// returned by next should be: [1,1,2,1,1].

LEETCODE_SOLUTION_UNITTEST(341, FlattenNestedListIterator, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: nestedList = [1,[4,[6]]]
// Output: [1,4,6]
//
// By calling next repeatedly until hasNext returns false, the order of elements
// returned by next should be: [1,4,6].

LEETCODE_SOLUTION_UNITTEST(341, FlattenNestedListIterator, example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}
