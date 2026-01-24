import java.util.*;

public class Activity_selection {
    public static void main(String args[]){
        int start [] = {1,3,0,5,8,5};
        int end [] = {2,4,6,7,9,9};
        
        //sorting end time wise
        /*here we are using a 2D array sort */

        // a table of 3 coloums 
        /* 
         1st coloum will save the index of the number
         2nd coloum Will save start 
         3rd will save the end so
         we will sort by 3rd coloum
         */
        int activities[][] = new int[start.length][3];
        for(int i = 0; i< start.length; i++){
            activities[i][0] = i; //index
            activities[i][1] = start[i];
            activities[i][2] = end[i];
        }
        
        //lambda function -> sortform
        Arrays.sort(activities, Comparator.comparingDouble(o -> o[2])); //here 2 is showing coloum no. three

        //end time basis soted

        int maxAct = 0;
        ArrayList <Integer> ans = new ArrayList<>();

        //1at activity
        maxAct = 1;//because at list one activity will be performed
        ans.add(activities[0][0]);
        int lastEnd = activities[0][2];
        for(int i = 0; i<end.length; i++){
            if(activities[i][1]>= lastEnd){
                maxAct++;
                ans.add(activities[i][0]);
                lastEnd = activities[i][2];
            }
        }
        
        System.out.println("Max actvity = "+maxAct);
        for(int i = 0; i< ans.size(); i++){
            System.out.print("A"+ans.get(i)+" ");
        }
    }
    
}


/*

lkcodecrafter: Can you help me to understand this code and dry run also?

GitHub Copilot: Certainly! Here’s an explanation and a dry run of your code in `Activity_selection.java`:

## What does this code do?
This code solves the classic "Activity Selection Problem" using a greedy algorithm. The goal is to select the maximum number of non-overlapping activities from a list, where each activity has a start and end time.

### Steps in the code:
1. **Input:** Arrays `start` and `end` represent the start and end times of activities.
2. **Preparation:** A 2D array `activities` is created, where each row contains:
   - The activity index
   - The start time
   - The end time
3. **Sorting:** The activities are sorted by their end times (greedy step).
4. **Selection:** The first activity is always selected. Then, for each subsequent activity, if its start time is after or equal to the last selected activity’s end time, it is selected.
5. **Output:** The code prints the maximum number of activities and their indices.

---

## Dry Run (Step-by-step Example)

Given:
- `start = {1, 3, 0, 5, 8, 5}`
- `end = {2, 4, 6, 7, 9, 9}`

### Step 1: Build `activities` array
| Index | Start | End |
|-------|-------|-----|
| 0     | 1     | 2   |
| 1     | 3     | 4   |
| 2     | 0     | 6   |
| 3     | 5     | 7   |
| 4     | 8     | 9   |
| 5     | 5     | 9   |

### Step 2: Sort by end time
After sorting by end time (column 2):
| Index | Start | End |
|-------|-------|-----|
| 0     | 1     | 2   |
| 1     | 3     | 4   |
| 2     | 0     | 6   |
| 3     | 5     | 7   |
| 4     | 8     | 9   |
| 5     | 5     | 9   |

(Sorting doesn't change the order here, but in general, it will.)

### Step 3: Select activities
- Select activity 0 (index 0): lastEnd = 2
- Check activity 1: start=3 >= lastEnd=2 → select, lastEnd=4
- Check activity 2: start=0 < lastEnd=4 → skip
- Check activity 3: start=5 >= lastEnd=4 → select, lastEnd=7
- Check activity 4: start=8 >= lastEnd=7 → select, lastEnd=9
- Check activity 5: start=5 < lastEnd=9 → skip

### Step 4: Output
- Max activities: 4
- Selected indices: 0, 1, 3, 4

So, the output will be:
```
Max actvity = 4
A0 A1 A3 A4 
```

---

## Summary
- The code finds the maximum set of non-overlapping activities.
- It sorts by end time, always picks the earliest finishing activity next.
- The dry run shows that activities 0, 1, 3, and 4 are selected.

Let me know if you want a line-by-line explanation or have any other questions!

*/