// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Simple Bank System
//
// https://leetcode.com/problems/simple-bank-system/
//
// Question ID: 2043
// Difficult  : Medium
// Solve Date : 2025/10/26 14:39

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2043. Simple Bank System|:
//
// You have been tasked with writing a program for a popular bank that will
// automate all its incoming transactions (transfer, deposit, and withdraw). The
// bank has |n| accounts numbered from |1| to |n|. The initial balance of each
// account is stored in a 0-indexed integer array |balance|, with the |(i +
// 1)ᵗʰ| account having an initial balance of |balance[i]|. Execute all the
// valid transactions. A transaction is valid if:
//
//  • The given account number(s) are between |1| and |n|, and
//
//  • The amount of money withdrawn or transferred from is less than or equal to
//  the balance of the account.
// Implement the |Bank| class:
//
//  • |Bank(long[] balance)| Initializes the object with the 0-indexed integer
//  array |balance|.
//
//  • |boolean transfer(int account1, int account2, long money)| Transfers
//  |money| dollars from the account numbered |account1| to the account numbered
//  |account2|. Return |true| if the transaction was successful, |false|
//  otherwise.
//
//  • |boolean deposit(int account, long money)| Deposit |money| dollars into
//  the account numbered |account|. Return |true| if the transaction was
//  successful, |false| otherwise.
//
//  • |boolean withdraw(int account, long money)| Withdraw |money| dollars from
//  the account numbered |account|. Return |true| if the transaction was
//  successful, |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(2043, SimpleBankSystem, Bank);

class Bank {
public:
  Bank(vector<long long> &balance) : acc_{std::move(balance)} {}

  bool transfer(int account1, int account2, long long money) {
    if (!isAccountValid(account1) || !isAccountValid(account2)) {
      return false;
    }
    // account is from 1 .. n
    --account1;
    --account2;
    if (acc_[account1] < money) {
      return false;
    }

    acc_[account1] -= money;
    acc_[account2] += money;
    return true;
  }

  bool deposit(int account, long long money) {
    if (!isAccountValid(account)) {
      return false;
    }
    acc_[--account] += money;
    return true;
  }

  bool withdraw(int account, long long money) {
    if (!isAccountValid(account) || acc_[--account] < money) {
      return false;
    }
    acc_[account] -= money;
    return true;
  }

private:
  bool isAccountValid(int a) { return a - 1 < acc_.size(); }

  vector<long long> acc_;
};

LEETCODE_END_RESOLVING(Bank);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == balance.length|
// * |1 <= n, account, account1, account2 <= 10⁵|
// * |0 <= balance[i], money <= 10¹²|
// * At most |10⁴| calls will be made to each function |transfer|, |deposit|,
// |withdraw|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Bank", "withdraw", "transfer", "deposit", "transfer", "withdraw"]
// [[[10, 100, 20, 50, 30]], [3, 10], [5, 1, 20], [5, 20], [3, 4, 15], [10, 50]]
// Output: [null, true, true, true, false, false]
//

LEETCODE_SOLUTION_UNITTEST(2043, SimpleBankSystem, example_1) {
  vector<long long> s0_balance = {10, 100, 20, 50, 30};
  auto              bank       = MakeBank(s0_balance);
  int               s1_account = 3;
  long long         s1_money   = 10;
  bool              s1_expect  = true;
  bool              s1_actual  = bank->withdraw(s1_account, s1_money);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int       s2_account1 = 5;
  int       s2_account2 = 1;
  long long s2_money    = 20;
  bool      s2_expect   = true;
  bool      s2_actual   = bank->transfer(s2_account1, s2_account2, s2_money);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int       s3_account = 5;
  long long s3_money   = 20;
  bool      s3_expect  = true;
  bool      s3_actual  = bank->deposit(s3_account, s3_money);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int       s4_account1 = 3;
  int       s4_account2 = 4;
  long long s4_money    = 15;
  bool      s4_expect   = false;
  bool      s4_actual   = bank->transfer(s4_account1, s4_account2, s4_money);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int       s5_account = 10;
  long long s5_money   = 50;
  bool      s5_expect  = false;
  bool      s5_actual  = bank->withdraw(s5_account, s5_money);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}
