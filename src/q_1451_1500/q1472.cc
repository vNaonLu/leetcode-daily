// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design Browser History
//
// https://leetcode.com/problems/design-browser-history/
//
// Question ID: 1472
// Difficult  : Medium
// Solve Date : 2023/03/18 14:48

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1472. Design Browser History|:
//
// You have a browser of one tab where you start on the |homepage| and you can
// visit another |url|, get back in the history number of |steps| or move
// forward in the history number of |steps|. Implement the |BrowserHistory|
// class:
//
//  • |BrowserHistory(string homepage)| Initializes the object with the
//  |homepage| of the browser.
//
//  • |void visit(string url)| Visits |url| from the current page. It clears up
//  all the forward history.
//
//  • |string back(int steps)| Move |steps| back in history. If you can only
//  return |x| steps in the history and |steps > x|, you will return only |x|
//  steps. Return the current |url| after moving back in history at most
//  |steps|.
//
//  • |string forward(int steps)| Move |steps| forward in history. If you can
//  only forward |x| steps in the history and |steps > x|, you will forward only
//  |x| steps. Return the current |url| after forwarding in history at most
//  |steps|.
//
//

LEETCODE_BEGIN_RESOLVING(1472, DesignBrowserHistory, BrowserHistory);

class BrowserHistory {
private:
  stack<string> backward_urls_;
  stack<string> foreward_urls_;
  string        current_;

public:
  BrowserHistory(string homepage) : current_{std::move(homepage)} {}

  void visit(string url) {
    backward_urls_.emplace(std::move(current_));
    current_ = std::move(url);
    for (; !foreward_urls_.empty(); foreward_urls_.pop())
      ;
  }

  string back(int steps) {
    while (steps > 0 && !backward_urls_.empty()) {
      auto tmp = std::move(backward_urls_.top());
      backward_urls_.pop();
      foreward_urls_.emplace(std::move(current_));
      current_ = std::move(tmp);
      --steps;
    }
    return current_;
  }

  string forward(int steps) {
    while (steps > 0 && !foreward_urls_.empty()) {
      auto tmp = std::move(foreward_urls_.top());
      foreward_urls_.pop();
      backward_urls_.emplace(std::move(current_));
      current_ = std::move(tmp);
      --steps;
    }
    return current_;
  }
};

LEETCODE_END_RESOLVING(BrowserHistory);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= homepage.length <= 20|
// * |1 <= url.length <= 20|
// * |1 <= steps <= 100|
// * |homepage| and |url| consist of  '.' or lower case English letters.
// * At most |5000| calls will be made to |visit|, |back|, and |forward|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input:
//  ["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
// [["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]
// Output:
// [null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]
//
// BrowserHistory browserHistory = new BrowserHistory("leetcode.com");
// browserHistory.visit("google.com"); // You are in "leetcode.com". Visit
// "google.com" browserHistory.visit("facebook.com"); // You are in
// "google.com". Visit "facebook.com" browserHistory.visit("youtube.com"); //
// You are in "facebook.com". Visit "youtube.com" browserHistory.back(1); // You
// are in "youtube.com", move back to "facebook.com" return "facebook.com"
// browserHistory.back(1); // You are in "facebook.com", move back to
// "google.com" return "google.com" browserHistory.forward(1); // You are in
// "google.com", move forward to "facebook.com" return "facebook.com"
// browserHistory.visit("linkedin.com"); // You are in "facebook.com". Visit
// "linkedin.com" browserHistory.forward(2); // You are in "linkedin.com", you
// cannot move forward any steps. browserHistory.back(2); // You are in
// "linkedin.com", move back two steps to "facebook.com" then to "google.com".
// return "google.com" browserHistory.back(7); // You are in "google.com", you
// can move back only one step to "leetcode.com". return "leetcode.com"

LEETCODE_SOLUTION_UNITTEST(1472, DesignBrowserHistory, example_1) {
  string s0_homepage     = "leetcode.com";
  auto   browser_history = MakeBrowserHistory(s0_homepage);
  string s1_url          = "google.com";
  browser_history->visit(s1_url);
  string s2_url = "facebook.com";
  browser_history->visit(s2_url);
  string s3_url = "youtube.com";
  browser_history->visit(s3_url);
  int    s4_steps  = 1;
  string s4_expect = "facebook.com";
  string s4_actual = browser_history->back(s4_steps);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int    s5_steps  = 1;
  string s5_expect = "google.com";
  string s5_actual = browser_history->back(s5_steps);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int    s6_steps  = 1;
  string s6_expect = "facebook.com";
  string s6_actual = browser_history->forward(s6_steps);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  string s7_url = "linkedin.com";
  browser_history->visit(s7_url);
  int    s8_steps  = 2;
  string s8_expect = "linkedin.com";
  string s8_actual = browser_history->forward(s8_steps);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  int    s9_steps  = 2;
  string s9_expect = "google.com";
  string s9_actual = browser_history->back(s9_steps);
  LCD_EXPECT_EQ(s9_expect, s9_actual);
  int    s10_steps  = 7;
  string s10_expect = "leetcode.com";
  string s10_actual = browser_history->back(s10_steps);
  LCD_EXPECT_EQ(s10_expect, s10_actual);
}
