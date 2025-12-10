# Two Pointers Pattern -- 21 Lessons

## 📌 Introduction

The **Two Pointers** pattern is used for problems involving sorted
arrays, string comparisons, window expansions, and pair/triplet
finding.\
It reduces time complexity and improves efficiency.

------------------------------------------------------------------------

## 1. Introduction to Two Pointers Pattern

Two pointers move from either ends or at different speeds to solve
problems faster.

------------------------------------------------------------------------

## 2. Pair with Target Sum (Easy)

``` cpp
vector<int> pairWithTargetSum(vector<int>& arr, int target) {
    int l=0, r=arr.size()-1;
    while(l<r){
        int sum = arr[l] + arr[r];
        if(sum == target) return {l, r};
        else if(sum < target) l++;
        else r--;
    }
    return {-1,-1};
}
```

------------------------------------------------------------------------

## 3. Find Non-Duplicate Number Instances (Easy)

``` cpp
int singleNonDuplicate(vector<int>& nums) {
    int x = 0;
    for(int n : nums) x ^= n;
    return x;
}
```

------------------------------------------------------------------------

## 4. Squaring a Sorted Array (Easy)

Example Input
nums = {-7, -3, 2, 3, 11}

🔹 Initial Setup
l = 0
r = 4
k = 4
ans = [?, ?, ?, ?, ?]

⭐ Dry Run Step-by-Step
Iteration 1

abs(nums[l]) = abs(-7) = 7

abs(nums[r]) = abs(11) = 11

7 > 11? → No, so use nums[r].

ans[4] = 11 * 11 = 121
r = 3
k = 3


ans = [?, ?, ?, ?, 121]

Iteration 2

abs(nums[l]) = 7

abs(nums[r]) = abs(3) = 3

7 > 3? → Yes, so use nums[l].

ans[3] = (-7)*(-7) = 49
l = 1
k = 2


ans = [?, ?, ?, 49, 121]

Iteration 3

abs(nums[l]) = abs(-3) = 3

abs(nums[r]) = 3

3 > 3? → No, so use nums[r].

ans[2] = 3*3 = 9
r = 2
k = 1


ans = [?, ?, 9, 49, 121]

Iteration 4

Now:

l = 1

r = 2

Check:

abs(nums[l]) = 3

abs(nums[r]) = abs(2) = 2

3 > 2? → Yes

ans[1] = (-3)*(-3) = 9
l = 2
k = 0


ans = [?, 9, 9, 49, 121]

Iteration 5

Now:

l = 2

r = 2

Check:

abs(nums[l]) = 2

abs(nums[r]) = 2

2 > 2? → No

ans[0] = 2*2 = 4
r = 1
k = -1


ans = [4, 9, 9, 49, 121]

Loop ends because l > r.

✅ Final Output
[4, 9, 9, 49, 121]



``` cpp
vector<int> sortedSquares(vector<int>& nums) {
    int l=0, r=nums.size()-1;
    vector<int> ans(nums.size());
    int k=r;
    while(l<=r){
        if(abs(nums[l]) > abs(nums[r])) ans[k--] = nums[l]*nums[l++];
        else ans[k--] = nums[r]*nums[r--];
    }
    return ans;
}
```

------------------------------------------------------------------------

## 5. Triplet Sum to Zero (Medium)

nums = {-1, 0, 1, 2, -1, -4}
If you want a different input, tell me and I’ll redo the run.

🔹 Step 1 — Sort the array
css
Copy code
nums → [-4, -1, -1, 0, 1, 2]
Initialize:

ini
Copy code
res = []
🔹 Step 2 — Main loop (i from 0 to end)
⭐ i = 0
makefile
Copy code
nums[i] = -4
l = 1, r = 5
Check sums:
sum = -4 + (-1) + 2 = -3 → < 0 → l++

sum = -4 + (-1) + 2 = -3 → < 0 → l++

sum = -4 + 0 + 2 = -2 → < 0 → l++

sum = -4 + 1 + 2 = -1 → < 0 → l++
Now l = r → stop.

No triplets for i = 0.

⭐ i = 1
makefile
Copy code
nums[i] = -1
l = 2, r = 5
Check sums:
sum = -1 + (-1) + 2 = 0 → found triplet

lua
Copy code
res = [[-1, -1, 2]]
Skip duplicates:

nums[l]==nums[l+1]? (-1 == -1) → yes → l=3

nums[r]==nums[r-1]? (2 == 1) → no
Then move both:

ini
Copy code
l = 4, r = 4
Loop ends.

⭐ i = 2
Copy code
nums[i] = -1
But nums[i] == nums[i-1] → duplicate, so skip.

⭐ i = 3
makefile
Copy code
nums[i] = 0
l = 4, r = 5
sum = 0 + 1 + 2 = 3 → >0 → r--

Now r = 4 → l == r → stop

No new triplets.

⭐ i = 4
makefile
Copy code
nums[i] = 1
l = 5, r = 5
Impossible (l >= r). Skip.

⭐ i = 5
Copy code
nums[i] = 2
Can't form a triplet (needs 2 more elements). Loop ends.

🎉 Final Result
ini
Copy code
res = [
  [-1, -1, 2],
  [-1, 0, 1]
]
✔ FINAL OUTPUT
cpp
Copy code
[[-1, -1, 2], [-1, 0, 1]]


``` cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;

    for(int i=0;i<nums.size();i++){
        if(i>0 && nums[i]==nums[i-1]) continue;
        int l=i+1, r=nums.size()-1;

        while(l<r){
            int sum = nums[i]+nums[l]+nums[r];
            if(sum==0){
                res.push_back({nums[i], nums[l], nums[r]});
                while(l<r && nums[l]==nums[l+1]) l++;
                while(l<r && nums[r]==nums[r-1]) r--;
                l++; r--;
            }
            else if(sum<0) l++;
            else r--;
        }
    }
    return res;
}
```

------------------------------------------------------------------------

## 6. Triplet Sum Close to Target (Medium)
🔹 Example Input
nums = [-1, 2, 1, -4]
target = 1

🔹 Step 1 — Sort
nums → [-4, -1, 1, 2]


Initialize:

best = 1e9   (a very large number)

⭐ MAIN LOOP
▶ i = 0 (nums[i] = -4)
l = 1 → -1
r = 3 →  2

1️⃣ sum = -4 + -1 + 2 = -3

Compare closeness to target=1:

current diff = |1 - (-3)| = 4

best diff = |1 - 1e9| = huge → so update

best = -3


sum < target → move left pointer:

l = 2

2️⃣ sum = -4 + 1 + 2 = -1

Check closeness:

diff = |1 - (-1)| = 2

best diff = |1 - (-3)| = 4 → update

best = -1


sum < target → move l:

l = 3


Now l == r → stop.

▶ i = 1 (nums[i] = -1)
l = 2 → 1
r = 3 → 2

1️⃣ sum = -1 + 1 + 2 = 2

Check closeness:

diff = |1 - 2| = 1

best diff = |1 - (-1)| = 2 → update

best = 2


sum > target → move r left:

r = 2


Now l == r → stop.

▶ i = 2
l = 3, r = 3 → stop

▶ i = 3

Same → stop.

🎉 FINAL RESULT
best = 2


This means:
👉 the triplet closest to target = 1 is (-1, 1, 2) which sums to 2.

⭐ Summary of best updates
i	l	r	triplet	   sum	  diff     	best
0	1	3	-4,-1, 2	-3	    4	     -3
0	2	3	-4, 1, 2	-1	    2	     -1
1	2	3	-1, 1, 2	2	    1	      2 

Final answer → 2



``` cpp
int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int best = 1e9;

    for(int i=0;i<nums.size();i++){
        int l=i+1, r=nums.size()-1;

        while(l<r){
            int sum = nums[i]+nums[l]+nums[r];
            if(abs(target-sum) < abs(target-best)) best = sum;
            if(sum < target) l++;
            else r--;
        }
    }
    return best;
}
```

------------------------------------------------------------------------

## 7. Triplets with Smaller Sum (Medium)

🔹 Example Input

Let’s use a common example:

nums = [-2, 0, 1, 3]
target = 2

🔹 Step 1 — Sort
nums → [-2, 0, 1, 3]


count = 0

⭐ MAIN LOOP
▶ i = 0 (nums[i] = -2)
l = 1  (0)
r = 3  (3)

1️⃣ sum = -2 + 0 + 3 = 1

Compare with target = 2:

1 < 2 → valid


👉 All pairs between l and r are valid: (l,r) = (1,3) and (2,3)
Count += (r - l) = (3 - 1) = 2

count = 2
l = 2

2️⃣ l = 2, r = 3

sum = -2 + 1 + 3 = 2

2 < 2 ?  NO


So move r left:

r = 2


Now l == r → stop inner loop.

▶ i = 1 (nums[i] = 0)
l = 2  (1)
r = 3  (3)

sum = 0 + 1 + 3 = 4
4 < 2 ? NO


Move r left:

r = 2


l == r → stop.

▶ i = 2
l = 3, r = 3 → l >= r → stop immediately

▶ i = 3
l = 4 → outside array → stop

🎉 Final Answer
count = 2

✔ Valid triplets

Specifically, these two triplets have sum < 2:

(-2, 0, 3) → 1

(-2, 1, 3) → 2 (⚠ but equal to target, so not counted!)

Oops—check again! The second one is not counted because its sum = 2.

The correct 2 valid triplets are:

(-2, 0, 1) → -1

(-2, 0, 3) → 1

These are the two counted in the algorithm.


``` cpp
int threeSumSmaller(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int count=0;

    for(int i=0;i<nums.size();i++){
        int l=i+1, r=nums.size()-1;
        while(l<r){
            int sum = nums[i]+nums[l]+nums[r];
            if(sum < target){
                count += r-l;
                l++;
            } else r--;
        }
    }
    return count;
}
```

------------------------------------------------------------------------

## 8. Dutch National Flag Problem (Medium)

🔹 Example Input

This is the typical input for this algorithm:

nums = [2, 0, 2, 1, 1, 0]

🔹 Initial State
l = 0
m = 0
r = nums.size() - 1 = 5

nums = [2, 0, 2, 1, 1, 0]

⭐ MAIN LOOP (while m <= r)
▶ Step 1
m = 0 → nums[m] = 2


Condition:

else → swap(nums[m], nums[r--])


Swap(nums[0], nums[5]):

nums = [0, 0, 2, 1, 1, 2]
r = 4
m = 0   (does NOT increase!)

▶ Step 2
m = 0 → nums[m] = 0


Condition:

nums[m] == 0 → swap(nums[l++], nums[m++])


Swap(nums[0], nums[0]):

nums = [0, 0, 2, 1, 1, 2]
l = 1
m = 1

▶ Step 3
m = 1 → nums[m] = 0


Again nums[m] == 0 → swap(nums[l], nums[m]):

Swap(nums[1], nums[1]):

nums = [0, 0, 2, 1, 1, 2]
l = 2
m = 2

▶ Step 4
m = 2 → nums[m] = 2


Swap(nums[m], nums[r]):

Swap(nums[2], nums[4]):

nums = [0, 0, 1, 1, 2, 2]
r = 3
m = 2   (m does NOT move!)

▶ Step 5
m = 2 → nums[m] = 1


Condition:

nums[m] == 1 → m++

m = 3

▶ Step 6
m = 3 → nums[m] = 1


nums[m] == 1 → m++

m = 4


Now:

m = 4
r = 3


m > r → STOP

🎉 FINAL ARRAY
[0, 0, 1, 1, 2, 2]


Sorted in Dutch National Flag order.

⭐ Summary Table
Step	l	m	r	Operation	Array
1	0	0	5→4	swap(0,5)	[0,0,2,1,1,2]
2	0→1	0→1	4	swap(0,0)	[0,0,2,1,1,2]
3	1→2	1→2	4	swap(1,1)	[0,0,2,1,1,2]
4	2	2	4→3	swap(2,4)	[0,0,1,1,2,2]
5	2	2→3	3	m++	[0,0,1,1,2,2]
6	2	3→4	3	m++	[0,0,1,1,2,2]

If you want, I can explain why this algorithm works, or dry run another example!

You said:

Dutch National Flag algorithm

what is this?
ChatGPT said:

Ah — you’re asking “What is this?” meaning:
👉 What is the Dutch National Flag algorithm?

Let me explain it very simply.

🇳🇱 Dutch National Flag Algorithm — Simple Explanation

This algorithm sorts an array that contains only 0, 1, and 2
(like colors: Red = 0, White = 1, Blue = 2)

Example:

[2, 0, 1, 2, 1, 0]


The goal is to turn it into:

[0, 0, 1, 1, 2, 2]


But do this in one single pass (O(n)), and without extra space.

⭐ Why is it called “Dutch National Flag”?

Because the Dutch flag has three horizontal stripes:

⬆ Red
⬆ White
⬆ Blue

Just like your array has:

0 → Red

1 → White

2 → Blue

So the algorithm groups them like the flag.

⭐ How it works

We use three pointers:

l → boundary for 0s
m → current element we examine
r → boundary for 2s


Rules:

1️⃣ If nums[m] == 0

→ swap with left side
→ move l and m forward

2️⃣ If nums[m] == 1

→ correct position
→ move m forward

3️⃣ If nums[m] == 2

→ swap with right side
→ move r backward
(m does NOT move)

⭐ Visual Example

Start:

[2, 0, 1, 2, 1, 0]
 l  m           r


See 2 → swap with r

See 0 → swap with l

See 1 → just move m

Repeat until m > r

You end with:

[0, 0, 1, 1, 2, 2]

⭐ Why is it good?

✔ Very fast (O(n))
✔ Only one pass
✔ No extra memory (in-place)
✔ Elegant logic


``` cpp
void sortColors(vector<int>& nums) {
    int l=0, m=0, r=nums.size()-1;

    while(m<=r){
        if(nums[m]==0) swap(nums[l++], nums[m++]);
        else if(nums[m]==1) m++;
        else swap(nums[m], nums[r--]);
    }
}
```

------------------------------------------------------------------------

## 9. Quadruple Sum to Target (Medium)

``` cpp
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;

    for(int i=0;i<nums.size();i++){
        if(i>0 && nums[i]==nums[i-1]) continue;
        for(int j=i+1;j<nums.size();j++){
            if(j>i+1 && nums[j]==nums[j-1]) continue;

            int l=j+1, r=nums.size()-1;

            while(l<r){
                long long sum = 1LL*nums[i]+nums[j]+nums[l]+nums[r];
                if(sum==target){
                    res.push_back({nums[i],nums[j],nums[l],nums[r]});
                    while(l<r && nums[l]==nums[l+1]) l++;
                    while(l<r && nums[r]==nums[r-1]) r--;
                    l++; r--;
                }
                else if(sum < target) l++;
                else r--;
            }
        }
    }
    return res;
}
```

------------------------------------------------------------------------

## 10. Comparing Strings with Backspaces (Medium)

``` cpp
bool backspaceCompare(string s, string t) {
    int i=s.size()-1, j=t.size()-1;
    int skipS=0, skipT=0;

    while(i>=0 || j>=0){
        while(i>=0){
            if(s[i]=='#') skipS++, i--;
            else if(skipS>0) skipS--, i--;
            else break;
        }
        while(j>=0){
            if(t[j]=='#') skipT++, j--;
            else if(skipT>0) skipT--, j--;
            else break;
        }

        if(i>=0 && j>=0 && s[i]!=t[j]) return false;
        if((i>=0) != (j>=0)) return false;

        i--; j--;
    }
    return true;
}
```

------------------------------------------------------------------------

## 11. Minimum Window Sort (Medium)

``` cpp
int findUnsortedSubarray(vector<int>& nums) {
    int n = nums.size();
    int l=0, r=n-1;

    while(l<n-1 && nums[l]<=nums[l+1]) l++;
    if(l==n-1) return 0;
 
    while(r>0 && nums[r]>=nums[r-1]) r--;

    int mn=1e9, mx=-1e9;
    for(int i=l;i<=r;i++){
        mn=min(mn, nums[i]);
        mx=max(mx, nums[i]);
    }

    while(l>0 && nums[l-1] > mn) l--;
    while(r<n-1 && nums[r+1] < mx) r++;

    return r-l+1;
}
```
