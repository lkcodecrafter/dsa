# Merge Intervals Pattern – 15 Lessons (With Dry Runs & Visualizations)

## 📌 Introduction to Merge Intervals Pattern
The **Merge Intervals** pattern is used to handle overlapping intervals.
Common in calendars, meeting rooms, CPU scheduling, and timelines.

### General Rule
1. Sort intervals by start time
2. Compare with last merged interval
3. Merge if overlapping

---

## 1. Merge Intervals (Medium)

### C++ Code
```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> res;
    for(auto &in : intervals){
        if(res.empty() || res.back()[1] < in[0])
            res.push_back(in);
        else
            res.back()[1] = max(res.back()[1], in[1]);
    }
    return res;
}
```

### Dry Run
Input: `[[1,3],[2,6],[8,10],[15,18]]`
```
[1,3] + [2,6] => [1,6]
[8,10], [15,18]
```

### Visualization
```
[1---3]
   [2------6]  => [1------6]
```

---

## 2. Insert Interval (Medium)

```cpp
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newI) {
    vector<vector<int>> res;
    int i=0;
    while(i<intervals.size() && intervals[i][1] < newI[0])
        res.push_back(intervals[i++]);
    while(i<intervals.size() && intervals[i][0] <= newI[1]){
        newI[0]=min(newI[0],intervals[i][0]);
        newI[1]=max(newI[1],intervals[i][1]);
        i++;
    }
    res.push_back(newI);
    while(i<intervals.size()) res.push_back(intervals[i++]);
    return res;
}
```

---

## 3. Intervals Intersection (Medium)

```cpp
vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
    int i=0,j=0;
    vector<vector<int>> res;
    while(i<A.size() && j<B.size()){
        int s=max(A[i][0],B[j][0]);
        int e=min(A[i][1],B[j][1]);
        if(s<=e) res.push_back({s,e});
        if(A[i][1]<B[j][1]) i++; else j++;
    }
    return res;
}
```

---

## 4. Conflicting Appointments (Medium)

```cpp
bool canAttendMeetings(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    for(int i=1;i<intervals.size();i++)
        if(intervals[i][0] < intervals[i-1][1])
            return false;
    return true;
}
```

---

## 5. Minimum Meeting Rooms (Hard)

```cpp
int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<int> s,e;
    for(auto &i:intervals){ s.push_back(i[0]); e.push_back(i[1]); }
    sort(s.begin(),s.end());
    sort(e.begin(),e.end());
    int rooms=0,j=0;
    for(int i=0;i<s.size();i++){
        if(s[i] < e[j]) rooms++;
        else j++;
    }
    return rooms;
}
```

---

## 6. Maximum CPU Load (Hard)

```cpp
int maxCPULoad(vector<vector<int>>& jobs) {
    sort(jobs.begin(),jobs.end());
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    int load=0,maxLoad=0;
    for(auto &j:jobs){
        while(!pq.empty() && pq.top().first<=j[0]){
            load-=pq.top().second; pq.pop();
        }
        pq.push({j[1],j[2]});
        load+=j[2];
        maxLoad=max(maxLoad,load);
    }
    return maxLoad;
}
```

---

## 7. Employee Free Time (Hard)

```cpp
vector<vector<int>> employeeFreeTime(vector<vector<vector<int>>>& schedule) {
    vector<vector<int>> all;
    for(auto &e:schedule)
        for(auto &i:e)
            all.push_back(i);
    sort(all.begin(),all.end());
    vector<vector<int>> res;
    auto prev=all[0];
    for(int i=1;i<all.size();i++){
        if(all[i][0]>prev[1])
            res.push_back({prev[1],all[i][0]});
        else
            prev[1]=max(prev[1],all[i][1]);
    }
    return res;
}
```

---

## ✅ Summary
- Sort first
- Merge overlaps
- Widely used in scheduling problems
