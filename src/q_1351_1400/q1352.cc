// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Product of the Last K Numbers
//
// https://leetcode.com/problems/product-of-the-last-k-numbers/
//
// Question ID: 1352
// Difficult  : Medium
// Solve Date : 2025/02/14 22:32

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1352. Product of the Last K Numbers|:
//
// Design an algorithm that accepts a stream of integers and retrieves the
// product of the last |k| integers of the stream. Implement the
// |ProductOfNumbers| class:
//
//  • |ProductOfNumbers()| Initializes the object with an empty stream.
//
//  • |void add(int num)| Appends the integer |num| to the stream.
//
//  • |int getProduct(int k)| Returns the product of the last |k| numbers in the
//  current list. You can assume that always the current list has at least |k|
//  numbers.
// The test cases are generated so that, at any time, the product of any
// contiguous sequence of numbers will fit into a single 32-bit integer without
// overflowing.
//
//

LEETCODE_BEGIN_RESOLVING(1352, ProductOfTheLastKNumbers, ProductOfNumbers);

class ProductOfNumbers {
public:
  ProductOfNumbers() : pre_{1} {}

  void add(int num) {
    if (num == 0) {
      pre_ = {1};
    } else {
      pre_.emplace_back(pre_.back() * num);
    }
  }

  int getProduct(int k) {
    if (k > pre_.size() - 1) {
      return 0;
    }

    return pre_.back() / pre_[pre_.size() - 1 - k];
  }

private:
  vector<int> pre_;
};

LEETCODE_END_RESOLVING(ProductOfNumbers);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= num <= 100|
// * |1 <= k <= 4 * 10⁴|
// * At most |4 * 10⁴| calls will be made to |add| and |getProduct|.
// * The product of the stream at any point in time will fit in a 32-bit
// integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input:
//  ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
// [[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]
// Output: [null,null,null,null,null,null,20,40,0,null,32]
//

LEETCODE_SOLUTION_UNITTEST(1352, ProductOfTheLastKNumbers, example_1) {
  auto product_of_numbers = MakeProductOfNumbers();
  int  s1_num             = 3;
  product_of_numbers->add(s1_num);
  int s2_num = 0;
  product_of_numbers->add(s2_num);
  int s3_num = 2;
  product_of_numbers->add(s3_num);
  int s4_num = 5;
  product_of_numbers->add(s4_num);
  int s5_num = 4;
  product_of_numbers->add(s5_num);
  int s6_k      = 2;
  int s6_expect = 20;
  int s6_actual = product_of_numbers->getProduct(s6_k);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_k      = 3;
  int s7_expect = 40;
  int s7_actual = product_of_numbers->getProduct(s7_k);
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  int s8_k      = 4;
  int s8_expect = 0;
  int s8_actual = product_of_numbers->getProduct(s8_k);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  int s9_num = 8;
  product_of_numbers->add(s9_num);
  int s10_k      = 2;
  int s10_expect = 32;
  int s10_actual = product_of_numbers->getProduct(s10_k);
  LCD_EXPECT_EQ(s10_expect, s10_actual);
}
