// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design Authentication Manager
//
// https://leetcode.com/problems/design-authentication-manager/
//
// Question ID: 1797
// Difficult  : Medium
// Solve Date : 2022/05/14 12:59

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1797. Design Authentication Manager|:
//
// There is an authentication system that works with authentication tokens. For
// each session, the user will receive a new authentication token that will
// expire |timeToLive| seconds after the |currentTime|. If the token is renewed,
// the expiry time will be extended to expire |timeToLive| seconds after the
// (potentially different) |currentTime|. Implement the |AuthenticationManager|
// class:
//
//  • |AuthenticationManager(int timeToLive)| constructs the
//  |AuthenticationManager| and sets the |timeToLive|.
//
//  • |generate(string tokenId, int currentTime)| generates a new token with the
//  given |tokenId| at the given |currentTime| in seconds.
//
//  • |renew(string tokenId, int currentTime)| renews the unexpired token with
//  the given |tokenId| at the given |currentTime| in seconds. If there are no
//  unexpired tokens with the given |tokenId|, the request is ignored, and
//  nothing happens.
//
//  • |countUnexpiredTokens(int currentTime)| returns the number of unexpired
//  tokens at the given currentTime.
// Note that if a token expires at time |t|, and another action happens on time
// |t| ( |renew| or |countUnexpiredTokens|), the expiration takes place before
// the other actions.
//

LEETCODE_BEGIN_RESOLVING(1797, DesignAuthenticationManager,
                         AuthenticationManager);

class AuthenticationManager {
private:
  int                        live_time;
  unordered_map<string, int> tokens_expire;

public:
  AuthenticationManager(int timeToLive) : live_time{timeToLive} {}

  void generate(string tokenId, int currentTime) {
    tokens_expire[tokenId] = currentTime + live_time;
  }

  void renew(string tokenId, int currentTime) {
    auto &expire = tokens_expire[tokenId];

    if (expire > currentTime) {
      expire = currentTime + live_time;
    }
  }

  int countUnexpiredTokens(int currentTime) {
    int expired = 0;
    for (auto &[token, expire] : tokens_expire) {
      if (expire > currentTime) {
        ++expired;
      }
    }

    return expired;
  }
};

LEETCODE_END_RESOLVING(AuthenticationManager);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= timeToLive <= 10⁸|
// * |1 <= currentTime <= 10⁸|
// * |1 <= tokenId.length <= 5|
// * |tokenId| consists only of lowercase letters.
// * All calls to |generate| will contain unique values of |tokenId|.
// * The values of |currentTime| across all the function calls will be strictly
// increasing.
// * At most |2000| calls will be made to all functions combined.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["AuthenticationManager", " renew", "generate", "
//  countUnexpiredTokens", "generate", " renew", " renew", "
//  countUnexpiredTokens"]
// [[5], ["aaa", 1], ["aaa", 2], [6], ["bbb", 7], ["aaa", 8], ["bbb", 10], [15]]
// Output: [null, null, null, 1, null, null, null, 0]
//
// AuthenticationManager authenticationManager = new AuthenticationManager(5);
// // Constructs the AuthenticationManager with |timeToLive| = 5 seconds.
// authenticationManager. |renew|("aaa", 1); // No token exists with tokenId
// "aaa" at time 1, so nothing happens. authenticationManager.generate("aaa",
// 2); // Generates a new token with tokenId "aaa" at time 2.
// authenticationManager. |countUnexpiredTokens|(6); // The token with tokenId
// "aaa" is the only unexpired one at time 6, so return 1.
// authenticationManager.generate("bbb", 7); // Generates a new token with
// tokenId "bbb" at time 7. authenticationManager. |renew|("aaa", 8); // The
// token with tokenId "aaa" expired at time 7, and 8 >= 7, so at time 8 the
// |renew| request is ignored, and nothing happens. authenticationManager.
// |renew|("bbb", 10); // The token with tokenId "bbb" is unexpired at time 10,
// so the |renew| request is fulfilled and now the token will expire at time 15.
// authenticationManager. |countUnexpiredTokens|(15); // The token with tokenId
// "bbb" expires at time 15, and the token with tokenId "aaa" expired at time 7,
// so currently no token is unexpired, so return 0.

LEETCODE_SOLUTION_UNITTEST(1797, DesignAuthenticationManager, example_1) {
  int    s0_timeToLive          = 5;
  auto   authentication_manager = MakeAuthenticationManager(s0_timeToLive);
  string s1_tokenId             = "aaa";
  int    s1_currentTime         = 1;
  authentication_manager->renew(s1_tokenId, s1_currentTime);
  string s2_tokenId     = "aaa";
  int    s2_currentTime = 2;
  authentication_manager->generate(s2_tokenId, s2_currentTime);
  int s3_currentTime = 6;
  int s3_expect      = 1;
  int s3_actual = authentication_manager->countUnexpiredTokens(s3_currentTime);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  string s4_tokenId     = "bbb";
  int    s4_currentTime = 7;
  authentication_manager->generate(s4_tokenId, s4_currentTime);
  string s5_tokenId     = "aaa";
  int    s5_currentTime = 8;
  authentication_manager->renew(s5_tokenId, s5_currentTime);
  string s6_tokenId     = "bbb";
  int    s6_currentTime = 10;
  authentication_manager->renew(s6_tokenId, s6_currentTime);
  int s7_currentTime = 15;
  int s7_expect      = 0;
  int s7_actual = authentication_manager->countUnexpiredTokens(s7_currentTime);
  LCD_EXPECT_EQ(s7_expect, s7_actual);
}
