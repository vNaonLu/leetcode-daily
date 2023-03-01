// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design Twitter
//
// https://leetcode.com/problems/design-twitter/
//
// Question ID: 355
// Difficult  : Medium
// Solve Date : 2022/08/23 19:17

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |355. Design Twitter|:
//
// Design a simplified version of Twitter where users can post tweets,
// follow/unfollow another user, and is able to see the |10| most recent tweets
// in the user's news feed. Implement the |Twitter| class:
//
//  • |Twitter()| Initializes your twitter object.
//
//  • |void postTweet(int userId, int tweetId)| Composes a new tweet with ID
//  |tweetId| by the user |userId|. Each call to this function will be made with
//  a unique |tweetId|.
//
//  • |List<Integer> getNewsFeed(int userId)| Retrieves the |10| most recent
//  tweet IDs in the user's news feed. Each item in the news feed must be posted
//  by users who the user followed or by the user themself. Tweets must be
//  ordered from most recent to least recent.
//
//  • |void follow(int followerId, int followeeId)| The user with ID
//  |followerId| started following the user with ID |followeeId|.
//
//  • |void unfollow(int followerId, int followeeId)| The user with ID
//  |followerId| started unfollowing the user with ID |followeeId|.
//

LEETCODE_BEGIN_RESOLVING(355, DesignTwitter, Twitter);

class Twitter {
private:
  int                                        timestamp;
  unordered_map<int, vector<pair<int, int>>> tweets;
  unordered_map<int, set<int>>               follows;

public:
  Twitter() : timestamp{0} {}

  void postTweet(int userId, int tweetId) {
    tweets[userId].emplace_back(++timestamp, tweetId);
  }

  vector<int> getNewsFeed(int userId) {
    /// init
    follows[userId].emplace(userId);
    vector<vector<pair<int, int>>::reverse_iterator> its;
    vector<int>                                      res;
    for (auto x : follows[userId]) {
      its.emplace_back(tweets[x].rbegin());
    }

    while (res.size() < 10) {
      vector<pair<int, int>>::reverse_iterator *cand = nullptr;
      auto                                      it   = its.begin();

      for (auto x : follows[userId]) {
        if ((*it) != tweets[x].rend()) {
          if (cand == nullptr || (**cand).first < (**it).first) {
            cand = &(*it);
          }
        }
        ++it;
      }

      if (cand == nullptr) {
        break;
      } else {
        res.emplace_back((**cand).second);
        ++(*cand);
      }
    }

    return res;
  }

  void follow(int followerId, int followeeId) {
    follows[followerId].emplace(followeeId);
  }

  void unfollow(int followerId, int followeeId) {
    follows[followerId].erase(followeeId);
  }
};

LEETCODE_END_RESOLVING(Twitter);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= userId, followerId, followeeId <= 500|
// * |0 <= tweetId <= 10⁴|
// * All the tweets have unique IDs.
// * At most |3 * 10⁴| calls will be made to |postTweet|, |getNewsFeed|,
// |follow|, and |unfollow|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet",
//  "getNewsFeed", "unfollow", "getNewsFeed"]
// [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
// Output: [null, null, [5], null, null, [6, 5], null, [5]]
//
// Twitter twitter = new Twitter();
// twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
// twitter.getNewsFeed(1); // User 1's news feed should return a list with 1
// tweet id -> [5]. return [5] twitter.follow(1, 2); // User 1 follows user 2.
// twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
// twitter.getNewsFeed(1); // User 1's news feed should return a list with 2
// tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is
// posted after tweet id 5. twitter.unfollow(1, 2); // User 1 unfollows user 2.
// twitter.getNewsFeed(1); // User 1's news feed should return a list with 1
// tweet id -> [5], since user 1 is no longer following user 2.

LEETCODE_SOLUTION_UNITTEST(355, DesignTwitter, example_1) {
  auto twitter    = MakeTwitter();
  int  s1_userId  = 1;
  int  s1_tweetId = 5;
  twitter->postTweet(s1_userId, s1_tweetId);
  int         s2_userId = 1;
  vector<int> s2_expect = {5};
  vector<int> s2_actual = twitter->getNewsFeed(s2_userId);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_followerId = 1;
  int s3_followeeId = 2;
  twitter->follow(s3_followerId, s3_followeeId);
  int s4_userId  = 2;
  int s4_tweetId = 6;
  twitter->postTweet(s4_userId, s4_tweetId);
  int         s5_userId = 1;
  vector<int> s5_expect = {6, 5};
  vector<int> s5_actual = twitter->getNewsFeed(s5_userId);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_followerId = 1;
  int s6_followeeId = 2;
  twitter->unfollow(s6_followerId, s6_followeeId);
  int         s7_userId = 1;
  vector<int> s7_expect = {5};
  vector<int> s7_actual = twitter->getNewsFeed(s7_userId);
  LCD_EXPECT_EQ(s7_expect, s7_actual);
}
