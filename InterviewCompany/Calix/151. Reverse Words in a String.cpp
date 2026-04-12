#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        string ans = "";

        reverse(s.begin(), s.end());
        for (int i = 0; i < s.length(); i++) {
            string words = "";
            while (i < s.length() && s[i] != ' ') {
                words += s[i];
                i++;
            }

            reverse(words.begin(), words.end());
            if (words.length() > 0) {
                ans += " " + words;
            }
        }

        return ans.substr(1);
    }
};