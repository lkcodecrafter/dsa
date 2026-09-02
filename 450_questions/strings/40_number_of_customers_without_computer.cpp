/*
    QUESTION    : Function to find Number of customers who could not get a computer
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/function-to-find-number-of-customers-who-could-not-get-a-computer/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Single pass state tracking
// S.C : O(26) = O(1) - State arrays (0: not arrived, 1: got computer, 2: left without computer)
class Solution {
public:
    int countCustomers(int n, string seq) {
        vector<int> state(26, 0); // 0 = absent, 1 = using computer, 2 = left unattended
        int occupied = 0;
        int unattendedCount = 0;

        for (char ch : seq) {
            int idx = ch - 'A';

            // Customer arrives for the first time
            if (state[idx] == 0) {
                if (occupied < n) {
                    occupied++;
                    state[idx] = 1; // Got a computer
                } else {
                    unattendedCount++;
                    state[idx] = 2; // No computer available; will leave
                }
            }
            // Customer is leaving
            else {
                if (state[idx] == 1) {
                    occupied--; // Frees up a computer
                }
                state[idx] = 0;
            }
        }

        return unattendedCount;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - On arrival: if `occupied < n` `occupied++; state=1;` else `unattended++; state=2;`.
 * - On departure: if `state == 1` `occupied--;`.
 * - Time: O(N), Space: O(1).
 */
