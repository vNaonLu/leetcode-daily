#ifndef ANYORDER_H__
#define ANYORDER_H__

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#ifdef EXPECT_EQ
// only thought as vector<T>
#define EXPECT_EQ_ANY_ORDER(val1, val2) \
  auto actual = val1;                   \
  sort(actual.begin(), actual.end());   \
  sort(val2.begin(), val2.end());       \
  EXPECT_EQ(actual, val2);
#endif

#ifdef EXPECT_EQ
// only thought as vector<vector<T>>
#define EXPECT_EQ_ANY_ORDER_RECURSIVE(val1, val2) \
  auto actual = val1;                             \
  for (auto &elm : actual)                        \
    sort(elm.begin(), elm.end());                 \
  for (auto &elm : val2)                          \
    sort(elm.begin(), elm.end());                 \
  sort(actual.begin(), actual.end());             \
  sort(val2.begin(), val2.end());                 \
  EXPECT_EQ(actual, val2);
#endif

#endif