#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{

public:
    // print the count of frequence in sorted order
    void countFre(string s)
    {
        int c[26] = {0};
        for (int i = 0; i < s.length(); i++)
        {
            c[s[i] - 'a']++;
        }
        for (int i = 0; i < 26; i++)
        {
            if (c[i] > 0)
            {
                cout << (char)(i + 'a') << " : " << c[i] << "\n";
            }
        }
    }
    void countFreq2(string str)
    {
        int count[26] = {0};
        for (int i = 0; i < str.length(); i++)
        {

            char ch = str[i];
            // Convert uppercase to lowercase
            if (ch >= 'A' && ch <= 'Z')
            {
                ch = ch - 'A' + 'a';
            }

            // Count only alphabets
            if (ch >= 'a' && ch <= 'z')
                count[ch - 'a']++;
        }
        for (int i = 0; i < 26; i++)
        {
            if (count[i] > 0)
                cout << (char)(i + 'a') << " : " << count[i] << "\n";
        }
    }
    
    // Anagram of each other
    // Every character in the first string should be present in the second and the
    // frequency must also be same.
    // Naive approach
    void isAnagram(string str, string str2){
        sort(str.begin(), str.end());
        sort(str2.begin(), str2.end());
        cout<< "is Anagram " << (str == str2);
    }

    // Efficient approach
    bool isAnagram2(string str, string str2){
        int count[26]={0};

        if (str.length() != str2.length()) return false;
        for(int i=0;i<str.length();i++){
          char ch1 = tolower(str[i]); // normalize to lowercase
          char ch2 = tolower(str2[i]);
        
          if (ch1 >= 'a' && ch1 <= 'z') count[ch1 - 'a']++;
          if (ch2 >= 'a' && ch2 <= 'z') count[ch2 - 'a']--;
        }
        for(int i=0;i<26;i++){
            if (count[i]!=0)
            {
                return false;
            } 
        }
        return true;
    }
};
main()
{
    Solution sol;
    //sol.countFreq2("Lalit kumar ayar");
    string str = "silent";
    //cout<<str.find("bite");
    string str2 = "liddd";
    bool isAnagram = sol.isAnagram2(str, str2);
    cout<<isAnagram;
}