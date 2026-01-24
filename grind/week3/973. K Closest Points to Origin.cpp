#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// https://www.youtube.com/watch?v=z-NbVpzA_fs

class Solution {
public:

    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> result;
        priority_queue<pair<int, vector<int>>> pq;
        for(auto point : points){
            int dist = point[0]*point[0] + point[1]*point[1];
            pq.push({dist, point});
            if(pq.size() > k){
                pq.pop();
            }
        }
        while(!pq.empty()){
            result.push_back(pq.top().second);
            pq.pop();
        }
        return result;
    }
};

/*

Your thinking

Help me write a detailed reasoning process for how to solve the problem.
To solve the problem of finding the k closest points to the origin (0, 0) from a 
list of points in a 2D plane, we can use a max-heap (priority queue) to efficiently
keep track of the closest points as we iterate through the list. 
 Here's a step-by-step breakdown of the approach: 

1. **Distance Calculation**: For each point, 
calculate the squared Euclidean distance from the origin (0, 0). 
Since we only need to compare distances, we can avoid computing square roots.
2. **Max-Heap Usage**: Use a max-heap to maintain the k closest points seen so far. 
The heap stores pairs of (distance, point).
3. **Iterate Through Points**: For each point:
   - Calculate its squared distance.
   - Push it into the max-heap.
   - If the heap size exceeds k, remove the farthest point (top of max-heap).
4. **Extract Results**: After processing all points, extract all elements from the heap to form the final result.

This approach ensures that we always keep only the k closest points in our priority queue and efficiently
manage them without sorting all points.

*/