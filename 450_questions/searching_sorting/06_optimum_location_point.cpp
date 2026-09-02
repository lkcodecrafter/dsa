/*
    QUESTION    : Optimum location of point to minimize total distance
    Company Tags: Google
    GfG Link    : https://www.geeksforgeeks.org/optimum-location-point-minimize-total-distance/
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Point struct
struct Point {
    double x, y;
};

// Line: ax + by + c = 0
struct Line {
    double a, b, c;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N * log(Range / EPS)) - Ternary Search on unimodal convex distance function
// S.C : O(1)                    - Constant auxiliary space
class Solution {
private:
    double dist(double x1, double y1, Point p) {
        return sqrt((x1 - p.x) * (x1 - p.x) + (y1 - p.y) * (y1 - p.y));
    }

    // Calculates total distance from point (x, y) on the line to all points
    double totalDistance(double x, Line l, const vector<Point>& points) {
        // y = -(a*x + c) / b
        double y = -(l.a * x + l.c) / l.b;
        double sum = 0;
        for (const Point& p : points) {
            sum += dist(x, y, p);
        }
        return sum;
    }

public:
    double findOptimumCost(Line l, const vector<Point>& points) {
        double low = -1e6, high = 1e6;
        double eps = 1e-6;

        // Ternary search for global minimum of convex function
        while ((high - low) > eps) {
            double mid1 = low + (high - low) / 3;
            double mid2 = high - (high - low) / 3;

            double dist1 = totalDistance(mid1, l, points);
            double dist2 = totalDistance(mid2, l, points);

            if (dist1 < dist2) {
                high = mid2;
            } else {
                low = mid1;
            }
        }

        return totalDistance((low + high) / 2, l, points);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Distance function on line is unimodal $\rightarrow$ use Ternary Search on `x` coordinate.
 * - Calculate `y = -(a*x + c)/b` and total distance to all points.
 * - Time: O(N log(1/eps)), Space: O(1).
 */
