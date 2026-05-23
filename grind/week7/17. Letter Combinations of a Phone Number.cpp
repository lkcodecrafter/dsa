#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        string temp = "";
        vector<string> res;
        backtrack(digits, 0, temp, res, mapping);
        return res;
    }
    void backtrack(string &digits, int index, string temp, vector<string> &res, vector<string> &mapping)
    {
        if (index == digits.size())
        {
            res.push_back(temp);
            return;
        }

        int k = digits[index] - '0'; // value is 2 for '2', 3 for '3' and so on
        // digits[index] - '0' is used to convert the character representation of a digit (e.g., '2') into its corresponding integer value (e.g., 2). This is done by subtracting the ASCII value of '0' from the ASCII value of the character at digits[index]. For example, if digits[index] is '2', then '2' - '0' will give you 2, which can be used to access the correct string in the mapping vector.
        string &letters = mapping[k]; // mapping[2] will give you "abc", mapping[3] will give you "def" and so on
        for (char l : letters)
        {
            temp.push_back(l);
            backtrack(digits, index + 1, temp, res, mapping);
            temp.pop_back();
        }
    }
};
