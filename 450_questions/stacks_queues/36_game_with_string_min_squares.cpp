/*
    QUESTION    : Game with String (Minimum sum of squares of character counts after removing k chars)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/game-with-string4102/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N + K log(Alphabet)) = O(N) since alphabet size <= 26
// S.C : O(26) = O(1) - Max-Heap storing character frequencies
class Solution {
public:
    int minValue(string s, int k) {
        vector<int> freq(26, 0);
        for (char ch : s) {
            freq[ch - 'a']++;
        }

        // Max-Heap stores character frequencies
        priority_queue<int> maxHeap;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                maxHeap.push(freq[i]);
            }
        }

        // Greedily reduce the highest frequency k times
        while (k > 0 && !maxHeap.empty()) {
            int topFreq = maxHeap.top();
            maxHeap.pop();

            topFreq--;
            k--;

            if (topFreq > 0) {
                maxHeap.push(topFreq);
            }
        }

        // Calculate sum of squares of remaining frequencies
        int sumOfSquares = 0;
        while (!maxHeap.empty()) {
            int f = maxHeap.top();
            maxHeap.pop();
            sumOfSquares += (f * f);
        }

        return sumOfSquares;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store frequencies in Max-Heap.
 * - Greedily pop max frequency, decrement by 1, and push back, repeated `k` times.
 * - Compute sum of `f * f` for all remaining elements.
 * - Time: O(N), Space: O(1).
 */
