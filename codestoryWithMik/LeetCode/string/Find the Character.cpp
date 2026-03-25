#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// LeetCode 1160. Find Words That Can Be Formed by Characters
// You are given an array of strings words and a string chars.
// You are given an array of strings words and a string chars.

/*
A string is good if it can be formed by characters from chars
(each character can only be used once for each word in words).

Return the sum of lengths of all good strings in words.

Example 1:

Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation: The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
*/

class Solution
{
public:
    int countCharacters(vector<string> &words, string chars)
    {
        vector<int> ch(26, 0);
        for (char c : chars)
        {
            ch[c - 'a']++;
        }

        int result = 0;

        for (string &word : words)
        {
            vector<int> wc(26, 0);
            for (int i = 0; i < word.length(); i++)
            {
                wc[word[i] - 'a']++;
            }

            bool isOk = true;
            for (int i = 0; i < 26; i++)
            {
                if (wc[i] > ch[i])
                {
                    isOk = false;
                    break;
                }
            }

            if (isOk)
            {
                result+=word.length();
            }
            
        }
        return result;
    }
};

int main(){

    vector<string>words = {"cat","bt","hat","tree"};
    string chars = "atach";
    Solution sol;
    cout<<sol.countCharacters(words, chars);
    return 0;
}

/*
Performance BreakdownTime Complexity: O(n + m . k), where n is the length of chars,
m is the number of words, and $k is the average length of a word (
or 26, whichever is the bottleneck in your loop).
Space Complexity: O(1) (since the alphabet size is constant at 26).

*/