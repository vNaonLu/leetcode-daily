
#ifndef CONDITION_H__
#define CONDITION_H__

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

#ifdef EXPECT_TRUE
#define EXPECT_TRUE_IF(val1, val2) \
  EXPECT_TRUE(val2(val1));
#endif

#endif