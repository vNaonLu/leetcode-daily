// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Validate IP Address
//
// https://leetcode.com/problems/validate-ip-address/
//
// Question ID: 468
// Difficult  : Medium
// Solve Date : 2022/08/24 18:50

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |468. Validate IP Address|:
//
// Given a string |queryIP|, return |"IPv4"| if IP is a valid IPv4 address,
// |"IPv6"| if IP is a valid IPv6 address or |"Neither"| if IP is not a correct
// IP of any type. A valid IPv4 address is an IP in the form |"x₁.x₂.x₃.x₄"|
// where |0 <= xᵢ <= 255| and |xᵢ| cannot contain leading zeros. For example,
// |"192.168.1.1"| and |"192.168.1.0"| are valid IPv4 addresses while
// |"192.168.01.1"|, |"192.168.1.00"|, and |"192.168@1.1"| are invalid IPv4
// addresses. A valid IPv6 address is an IP in the form
// |"x₁:x₂:x₃:x₄:x₅:x₆:x₇:x₈"| where:
//
//  • |1 <= xᵢ.length <= 4|
//
//  • |xᵢ| is a hexadecimal string which may contain digits, lowercase English
//  letter ( |'a'| to |'f'|) and upper-case English letters ( |'A'| to |'F'|).
//
//  • Leading zeros are allowed in |xᵢ|.
// For example, " |2001:0db8:85a3:0000:0000:8a2e:0370:7334"| and "
// |2001:db8:85a3:0:0:8A2E:0370:7334"| are valid IPv6 addresses, while "
// |2001:0db8:85a3::8A2E:037j:7334"| and "
// |02001:0db8:85a3:0000:0000:8a2e:0370:7334"| are invalid IPv6 addresses.
//

LEETCODE_BEGIN_RESOLVING(468, ValidateIPAddress, Solution);

class Solution {
private:
  template <typename Iterator>
  int toInt(Iterator beg, Iterator end) {
    auto res = 0;
    while (beg != end) {
      res *= 10;
      res += *beg++ - '0';
    }
    return res;
  }

  bool isValidIpv4(char x) { return (x >= '0' && x <= '9'); }

  bool isIpv4(string_view s) {
    auto find = 0;
    auto l    = s.begin();
    auto len  = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
      if (len > 3) {
        return false;
      }

      if (*it == '.') {
        auto x = toInt(l, it);
        if (x > 255 || (*l == '0' && len > 1) || it == l) {
          return false;
        }
        l   = it + 1;
        len = 0;
        ++find;
      } else if (it + 1 == s.end()) {
        auto x = toInt(l, s.end());
        if (x > 255 || (*l == '0' && (len + 1) > 1)) {
          return false;
        }
      } else if (!isValidIpv4(*it)) {
        return false;
      } else {
        ++len;
      }
    }

    return find == 3 && l != s.end();
  }

  bool isValidIpv6(char x) {
    return (x >= '0' && x <= '9') || (x >= 'a' && x <= 'f') ||
           (x >= 'A' && x <= 'F');
  }

  bool isIpv6(string_view s) {
    auto find = 0;
    auto l    = s.begin();
    auto len  = 0;

    for (auto it = s.begin(); it != s.end(); ++it) {
      if (len > 4) {
        return false;
      }

      if (*it == ':') {
        if (len == 0) {
          return false;
        }
        l = it + 1;
        ++find;
        len = 0;
      } else if (it + 1 == s.end()) {
        if ((len + 1) > 4) {
          return false;
        }
      } else if (!isValidIpv6(*it)) {
        return false;
      } else {
        ++len;
      }
    }

    return find == 7 && l != s.end();
  }

public:
  string validIPAddress(string queryIP) {
    return isIpv4(queryIP) ? "IPv4" : isIpv6(queryIP) ? "IPv6" : "Neither";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |queryIP| consists only of English letters, digits and the characters |'.'|
// and |':'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: queryIP = "172.16.254.1"
// Output: "IPv4"
//
// This is a valid IPv4 address, return "IPv4".

LEETCODE_SOLUTION_UNITTEST(468, ValidateIPAddress, example_1) {
  auto   solution = MakeSolution();
  string queryIP  = "172.16.254.1";
  string expect   = "IPv4";
  string actual   = solution->validIPAddress(queryIP);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: queryIP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
// Output: "IPv6"
//
// This is a valid IPv6 address, return "IPv6".

LEETCODE_SOLUTION_UNITTEST(468, ValidateIPAddress, example_2) {
  auto   solution = MakeSolution();
  string queryIP  = "2001:0db8:85a3:0:0:8A2E:0370:7334";
  string expect   = "IPv6";
  string actual   = solution->validIPAddress(queryIP);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: queryIP = "256.256.256.256"
// Output: "Neither"
//
// This is neither a IPv4 address nor a IPv6 address.

LEETCODE_SOLUTION_UNITTEST(468, ValidateIPAddress, example_3) {
  auto   solution = MakeSolution();
  string queryIP  = "256.256.256.256";
  string expect   = "Neither";
  string actual   = solution->validIPAddress(queryIP);
  LCD_EXPECT_EQ(expect, actual);
}
