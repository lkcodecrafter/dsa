/*
    QUESTION    : Find the first non-repeating character from a stream of characters
    Company Tags: Amazon, Flipkart, Yahoo
    GfG Link    : https://practice.geeksforgeeks.org/problems/first-non-repeating-character-in-a-stream/0
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Each character is pushed and popped from queue at most once
// S.C : O(26) = O(1) - Queue and frequency array of alphabet size
class Solution {
public:
    string FirstNonRepeating(string A) {
        string result = "";
        vector<int> freq(26, 0);
        queue<char> q;

        for (char ch : A) {
            // Increment frequency of current character
            freq[ch - 'a']++;
            q.push(ch);

            // Pop characters that have repeated (frequency > 1) from the front of queue
            while (!q.empty() && freq[q.front() - 'a'] > 1) {
                q.pop();
            }

            // The front of the queue is the first non-repeating character so far
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
 * - `result.push_back(q.empty() ? '#' : q.front());`
 * - Time: O(N), Space: O(1).
 */
