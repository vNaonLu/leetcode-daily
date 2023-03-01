// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Encode and Decode TinyURL
//
// https://leetcode.com/problems/encode-and-decode-tinyurl/
//
// Question ID: 535
// Difficult  : Medium
// Solve Date : 2022/04/23 14:52

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |535. Encode and Decode TinyURL|:
//
// Note: This is a companion problem to the [System Design] problem: [Design
// TinyURL]. TinyURL is a URL shortening service where you enter a URL such as
// |https://leetcode.com/problems/design-tinyurl| and it returns a short URL
// such as |http://tinyurl.com/4e9iAk|. Design a class to encode a URL and
// decode a tiny URL. There is no restriction on how your encode/decode
// algorithm should work. You just need to ensure that a URL can be encoded to a
// tiny URL and the tiny URL can be decoded to the original URL. Implement the
// |Solution| class:
//
//  • |Solution()| Initializes the object of the system.
//
//  • |String encode(String longUrl)| Returns a tiny URL for the given
//  |longUrl|.
//
//  • |String decode(String shortUrl)| Returns the original long URL for the
//  given |shortUrl|. It is guaranteed that the given |shortUrl| was encoded by
//  the same object.
//  
//

LEETCODE_BEGIN_RESOLVING(535, EncodeAndDecodeTinyURL, Solution);

class Solution {
public:
  // Encodes a URL to a shortened URL.
  string encode(string longUrl) { return longUrl; }

  // Decodes a shortened URL to its original URL.
  string decode(string shortUrl) { return shortUrl; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= url.length <= 10⁴|
// * |url| is guranteed to be a valid URL.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: url = "https://leetcode.com/problems/design-tinyurl"
// Output: "https://leetcode.com/problems/design-tinyurl"
//
// Solution obj = new Solution();
// string tiny = obj.encode(url); // returns the encoded tiny url.
// string ans = obj.decode(tiny); // returns the original url after deconding
// it.

LEETCODE_SOLUTION_UNITTEST(535, EncodeAndDecodeTinyURL, example_1) {
  auto   solution = MakeSolution();
  string longUrl  = "https://leetcode.com/problems/design-tinyurl";
  string expect   = "https://leetcode.com/problems/design-tinyurl";
  string actual   = solution->encode(longUrl);
  LCD_EXPECT_EQ(expect, actual);
}
