#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
public:

        priority_queue<int> maxHeap; // to store the smaller half of the numbers
        priority_queue<int, vector<int>, greater<int>> minHeap; // to store the larger half of the numbers
    MedianFinder() {
        // Initialize the heaps
        // maxHeap will store the smaller half of the numbers, and minHeap will store the larger half. This way, we can easily find the median by looking at the tops of both heaps.    
        maxHeap.push(INT_MIN); // to avoid empty heap issues
        minHeap.push(INT_MAX); // to avoid empty heap issues
    }
    
    void addNum(int num) {
        if(num <= maxHeap.top()){
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }

        // Balance the heaps
        if(maxHeap.size() > minHeap.size() + 1){
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if(minHeap.size() > maxHeap.size()){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }   
    }
    
    double findMedian() {
        if(maxHeap.size() > minHeap.size()){
            return maxHeap.top();
        } else {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */