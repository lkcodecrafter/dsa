#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// https://www.youtube.com/watch?v=z-NbVpzA_fs

class Solution {
public:

    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> result;
        priority_queue<pair<int, vector<int>>> pq;  // Max-heap to store pairs of (distance, point)
        for(auto point : points){
            int dist = point[0]*point[0] + point[1]*point[1];
            pq.push({dist, point}); // value of q now is (distance, point) example : (5, [1,2])
            // why taken pq as max-heap → because we want to remove the farthest point when size exceeds k
            // example : if we have k=2 and we have points with distances 1, 2, 3 in the heap
            // when we add the point with distance 3, the heap will have (1, point1), (2, point2), (3, point3)
            // since it's a max-heap, the top will be (3, point3)
            // when we check if pq.size() > k, it will be true (3 > 2)
            // so we will pop the top element which is (3, point3) and it will be removed from the heap
            // this way we ensure that we always keep the closest k points in the heap
            if(pq.size() > k){
                pq.pop();
            }
        }
        while(!pq.empty()){
            result.push_back(pq.top().second); // pq.top().second value is example : [1,2] and first value is example : 5 which is the distance
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