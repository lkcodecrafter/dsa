# Cyclic Sort Pattern – 17 Lessons (With Dry Runs & Visualizations)

## 📌 Introduction to Cyclic Sort Pattern

Cyclic Sort works when numbers are in range 1 to N (or 0 to N).
Correct index of number x = x - 1

We swap elements until every number is at its correct index.

------------------------------------------------------------
```cpp
1️⃣ Cyclic Sort (Easy)

C++ Code:

void cyclicSort(vector<int>& nums) {
    int i = 0;
    while (i < nums.size()) {
        int correct = nums[i] - 1;
        if (nums[i] != nums[correct])
            swap(nums[i], nums[correct]);
        else
            i++;
    }
}

Dry Run:
Input: [3,1,5,4,2]

Step 1:
3 should be at index 2 → swap
[5,1,3,4,2]

Step 2:
5 should be at index 4 → swap
[2,1,3,4,5]

Step 3:
2 should be at index 1 → swap
[1,2,3,4,5]

Sorted ✔

Visualization:

Index : 0 1 2 3 4
Value : 3 1 5 4 2
Final : 1 2 3 4 5

------------------------------------------------------------

2️⃣ Find Missing Number (Easy)

int missingNumber(vector<int>& nums) {
    int i=0;
    while(i<nums.size()){
        if(nums[i]<nums.size() && nums[i]!=nums[nums[i]]) // nums[nums[i]] means the value at the index of the current number example: if nums[i] is 3, then nums[nums[i]] means nums[3] which is the value at index 3
            swap(nums[i],nums[nums[i]]);
        else i++;
    }
    for(int i=0;i<nums.size();i++)
        if(nums[i]!=i) return i;
    return nums.size();
}

------------------------------------------------------------

3️⃣ Find All Missing Numbers (Easy)

vector<int> findDisappearedNumbers(vector<int>& nums) {
    int i=0;
    while(i<nums.size()){
        int correct=nums[i]-1;
        if(nums[i]!=nums[correct])
            swap(nums[i],nums[correct]);
        else i++;
    }
    vector<int> res;
    for(int i=0;i<nums.size();i++)
        if(nums[i]!=i+1) res.push_back(i+1);
    return res;
}

------------------------------------------------------------

4️⃣ Find the Duplicate Number (Easy)

int findDuplicate(vector<int>& nums) {
    int i=0;
    while(i<nums.size()){
        if(nums[i]!=i+1){
            int correct=nums[i]-1;
            if(nums[i]!=nums[correct])
                swap(nums[i],nums[correct]);
            else return nums[i];
        } else i++;
    }
    return -1;
}

------------------------------------------------------------

5️⃣ Find All Duplicate Numbers (Easy)

vector<int> findDuplicates(vector<int>& nums) {
    int i=0;
    while(i<nums.size()){
        int correct=nums[i]-1;
        if(nums[i]!=nums[correct])
            swap(nums[i],nums[correct]);
        else i++;
    }
    vector<int> res;
    for(int i=0;i<nums.size();i++)
        if(nums[i]!=i+1) res.push_back(nums[i]);
    return res;
}

------------------------------------------------------------

6️⃣ Find the Corrupt Pair (Easy)

vector<int> findCorruptPair(vector<int>& nums) {
    int i=0;
    while(i<nums.size()){
        int correct=nums[i]-1;
        if(nums[i]!=nums[correct])
            swap(nums[i],nums[correct]);
        else i++;
    }
    for(int i=0;i<nums.size();i++)
        if(nums[i]!=i+1)
            return {nums[i], i+1};
    return {};
}

------------------------------------------------------------

7️⃣ Smallest Missing Positive (Medium)
```cpp
int firstMissingPositive(vector<int>& nums) {
    int i=0;
    while(i<nums.size()){
        int correct=nums[i]-1;
        if(nums[i]>0 && nums[i]<=nums.size() && nums[i]!=nums[correct])
            swap(nums[i],nums[correct]);
        else i++;
    }
    for(int i=0;i<nums.size();i++)
        if(nums[i]!=i+1) return i+1;
    return nums.size()+1;
}

------------------------------------------------------------

8️⃣ First K Missing Positive (Hard)

vector<int> findKMissing(vector<int>& nums, int k) {
    int i=0;
    while(i<nums.size()){
        int correct=nums[i]-1;
        if(nums[i]>0 && nums[i]<=nums.size() && nums[i]!=nums[correct])
            swap(nums[i],nums[correct]);
        else i++;
    }
    vector<int> res;
    unordered_set<int> extra;
    for(int i=0;i<nums.size() && res.size()<k;i++){
        if(nums[i]!=i+1){
            res.push_back(i+1);
            extra.insert(nums[i]);
        }
    }
    int next=nums.size()+1;
    while(res.size()<k){
        if(!extra.count(next)) res.push_back(next);
        next++;
    }
    return res;
}

------------------------------------------------------------

Pattern Summary:

✔ Works when numbers are in fixed range  
✔ Place number x at index x-1  
✔ Time: O(N)  
✔ Space: O(1)  

Memory Trick:
Think of arranging students in roll-number order.
Keep swapping until everyone sits correctly.
