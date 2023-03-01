// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Online Stock Span
//
// https://leetcode.com/problems/online-stock-span/
//
// Question ID: 901
// Difficult  : Medium
// Solve Date : 2022/11/09 18:41

#include <iosfwd>
#include <stack>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |901. Online Stock Span|:
//
// Design an algorithm that collects daily price quotes for some stock and
// returns the span of that stock's price for the current day. The span of the
// stock's price in one day is the maximum number of consecutive days (starting
// from that day and going backward) for which the stock price was less than or
// equal to the price of that day.
//
//  • For example, if the prices of the stock in the last four days is
//  |[7,2,1,2]| and the price of the stock today is |2|, then the span of today
//  is |4| because starting from today, the price of the stock was less than or
//  equal |2| for |4| consecutive days.
//
//  • Also, if the prices of the stock in the last four days is |[7,34,1,2]| and
//  the price of the stock today is |8|, then the span of today is |3| because
//  starting from today, the price of the stock was less than or equal |8| for
//  |3| consecutive days.
// Implement the |StockSpanner| class:
//
//  • |StockSpanner()| Initializes the object of the class.
//
//  • |int next(int price)| Returns the span of the stock's price given that
//  today's price is |price|.
//

LEETCODE_BEGIN_RESOLVING(901, OnlineStockSpan, StockSpanner);

class StockSpanner {
private:
  stack<pair<int, int>> stk_;

public:
  StockSpanner() {}

  int next(int price) {
    int res = 1;
    while (!stk_.empty() && price >= stk_.top().first) {
      res += stk_.top().second;
      stk_.pop();
    }
    stk_.emplace(price, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(StockSpanner);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= price <= 10⁵|
// * At most |10⁴| calls will be made to |next|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["StockSpanner", "next", "next", "next", "next", "next", "next",
//  "next"]
// [[], [100], [80], [60], [70], [60], [75], [85]]
// Output: [null, 1, 1, 1, 2, 1, 4, 6]
//
// StockSpanner stockSpanner = new StockSpanner();
// stockSpanner.next(100); // return 1
// stockSpanner.next(80); // return 1
// stockSpanner.next(60); // return 1
// stockSpanner.next(70); // return 2
// stockSpanner.next(60); // return 1
// stockSpanner.next(75); // return 4, because the last 4 prices (including
// today's price of 75) were less than or equal to today's price.
// stockSpanner.next(85); // return 6

LEETCODE_SOLUTION_UNITTEST(901, OnlineStockSpan, example_1) {
  auto stock_spanner = MakeStockSpanner();
  int  s1_price      = 100;
  int  s1_expect     = 1;
  int  s1_actual     = stock_spanner->next(s1_price);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_price  = 80;
  int s2_expect = 1;
  int s2_actual = stock_spanner->next(s2_price);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_price  = 60;
  int s3_expect = 1;
  int s3_actual = stock_spanner->next(s3_price);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_price  = 70;
  int s4_expect = 2;
  int s4_actual = stock_spanner->next(s4_price);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_price  = 60;
  int s5_expect = 1;
  int s5_actual = stock_spanner->next(s5_price);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_price  = 75;
  int s6_expect = 4;
  int s6_actual = stock_spanner->next(s6_price);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_price  = 85;
  int s7_expect = 6;
  int s7_actual = stock_spanner->next(s7_price);
  LCD_EXPECT_EQ(s7_expect, s7_actual);
}
