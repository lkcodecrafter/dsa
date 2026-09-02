/*
    QUESTION    : First non-repeating character in a stream of characters (Queue Method)
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/first-non-repeating-character-in-a-stream1216/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear pass through string
// S.C : O(26) = O(1) - Queue and frequency vector
class Solution {
public:
    string FirstNonRepeating(string A) {
        vector<int> freq(26, 0);
        queue<char> q;
        string result = "";

        for (char ch : A) {
            freq[ch - 'a']++;
            q.push(ch);

            while (!q.empty() && freq[q.front() - 'a'] > 1) {
                q.pop();
            }

            if (q.empty()) {
                result.push_back('#');
            } else {
                result.push_back(q.front());
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `freq[ch - 'a']++; q.push(ch);`
 * - `while (!q.empty() && freq[q.front() - 'a'] > 1) q.pop();`
 * - `result += (q.empty() ? '#' : q.front());`
 * - Time: O(N), Space: O(1).
 */
