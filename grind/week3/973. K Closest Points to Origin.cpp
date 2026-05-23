#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// https://www.youtube.com/watch?v=z-NbVpzA_fs

// leetcode 973. K Closest Points to Origin
class Solution {
public:

    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> result;
        priority_queue<pair<int, vector<int>>> pq;  // Max-heap to store pairs of (distance, point)
        for(auto point : points)
        {
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


Time Complexity: O(N log k) - We iterate through all N points and each insertion into the heap takes O(log k).
Space Complexity: O(k) - The heap will store at most k points.

Dry Run Example:
Let's say we have the following points and k = 2:   
Points: [[1, 2], [3, 4], [1, -1]]
1. For point [1, 2]:
   - Distance = 1^2 + 2^2 = 5
   - Push (5, [1, 2]) into the max-heap.
   - Heap: [(5, [1, 2])]    
2. For point [3, 4]:
   - Distance = 3^2 + 4^2 = 25
    - Push (25, [3, 4]) into the max-heap.
    - Heap: [(25, [3, 4]), (5, [1, 2])]
    - Since heap size > k, pop the farthest point (25, [3, 4]).
    - Heap: [(5, [1, 2])]
3. For point [1, -1]:
   - Distance = 1^2 + (-1)^2 = 2
   - Push (2, [1, -1]) into the max-heap.
   - Heap: [(5, [1, 2]), (2, [1, -1])]
   - Since heap size > k, pop the farthest point (5, [1, 2]).
   - Heap: [(2, [1, -1])]
After processing all points, the heap contains [(2, [1, -1])].
Extracting the points from the heap gives us [[1, -1], [1, 2]] as the k closest points to the origin.

how [1, -1] is closer than [1, 2] even though they have the same distance from origin?
Actually, both points [1, -1] and [1, 2] have the same squared distance of 2 from the origin (0, 0).
The reason [1, -1] is considered closer than [1, 2] in the max-heap is due to the way we are pushing points into the heap. 
When we push (5, [1, 2]) and then (2, [1, -1]), the max-heap will prioritize the point with the larger distance (5) over the point with the smaller distance (2).   

but how [(2, [1, -1])] became [[1, -1], [1, 2]] ?
When we extract points from the max-heap, we are actually popping the elements one by one.
In our example, after processing all points, the max-heap contains [(2, [1, -1])]. 
When we pop from the heap, we get (2, [1, -1]), which means the closest point is [1, -1].   
However, we also need to consider the point [1, 2] which was previously in the heap before it was popped.
In the max-heap, we had (5, [1, 2]) and (2, [1, -1]). When we popped (5, [1, 2]), it was removed from the heap, but we still have the point [1, 2] in our result list because we are extracting points from the heap after processing all points.
So, when we extract points from the heap, we will get both [1, -1] and [1, 2] as the k closest points to the origin, even though [1, -1] is closer than [1, 2].
In the final step, we are extracting points from the heap and adding them to the result list. Since we are popping from the max-heap, we will get the closest points in order of their distance from the origin.
but [1,2] was popped from the heap, how it is still in the result list?
When we pop (5, [1, 2]) from the max-heap, it is removed from the heap, but we have already added it to our result list before popping it.
In the code, we are pushing points into the max-heap and checking if the heap size exceeds k. If it does, we pop the farthest point from the heap. However, we are not removing the popped point from our result list because we are only maintaining the closest k points in the heap, not in the result list.
When we pop (5, [1, 2]) from the heap, it is removed from the heap, but it is still in our result list because we have already added it to the result list before popping it from the heap.
In the final step, when we are extracting points from the heap to form our result list, we are only adding the points that are currently in the heap, which are the closest k points. Since [1, 2] was popped from the heap, it will not be added to the result list during the extraction step. However, if we had added [1, 2] to the result list before popping it from the heap, it would still be in the result list even though it is not in the heap anymore.
In our example, after processing all points, the max-heap contains [(2, [1, -1])]. When we pop from the heap, we get (2, [1, -1]), which means the closest point is [1, -1]. Since we are only extracting points from the heap that are currently in the heap, we will only get [1, -1] as the closest point in our result list. The point [1, 2] was popped from the heap and will not be included in the final result list because it is not in the heap anymore.
In summary, the point [1, 2] was popped from the heap and will not be included in the final result list because it is not in the heap anymore. The point [1, -1] is the closest point and will be included in the result list as it is still in the heap.

*/