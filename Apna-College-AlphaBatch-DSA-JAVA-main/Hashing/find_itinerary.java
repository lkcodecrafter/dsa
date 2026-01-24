import java.util.*;

/*
🧠 What is this program trying to do?

You are given flight tickets in the form:

source -> destination


Example:

Mumbai -> Delhi
Delhi  -> Goa
Goa    -> Chennai
Chennai-> Bengaluru


The goal is to:

Find the starting city (the city that never appears as a destination)

Print the full travel itinerary in order

🔍 Method: getStart(HashMap<String, String> tickets)
Step 1: Create a reverse map
HashMap<String,String> revMap = new HashMap<>();


This will store:

destination -> source

Step 2: Fill the reverse map
for(String i : tickets.keySet()){
    revMap.put(tickets.get(i), i);
}

Given tickets:
Source	    Destination
chennai	    bengluru
Mumbai	    delhi
goa	        chennai
delhi   	goa

revMap becomes:
Destination 	Source
bengluru	    chennai
delhi	        Mumbai
chennai     	goa
goa         	delhi


Step 3: Find the starting city
for(String i : tickets.keySet()){
    if(!revMap.containsKey(i)){
        return i;
    }
}


We check:

A starting city will never appear as a destination

Check each key:
City	Is it in revMap?
chennai	✅ yes
Mumbai	❌ no
goa	✅ yes
delhi	✅ yes

✔ Starting city = "Mumbai"

🚀 main() method execution
Step 1: Call getStart
String start = getStart(tickets);


✔ start = "Mumbai"

Step 2: Print starting city
System.out.print(start);


Output so far:

Mumbai

Step 3: Print full itinerary
for(String key : tickets.keySet()){
    System.out.print("-->"+tickets.get(start));
    start = tickets.get(start);
}


⚠ Note: key is NOT used in the loop — the loop just runs n times.

🧪 Dry Run of the Loop

Initial:

start = "Mumbai"

Iteration	start	tickets.get(start)	Output Printed	New start
1	Mumbai	delhi	→ delhi	delhi
2	delhi	goa	→ goa	goa
3	goa	chennai	→ chennai	chennai
4	chennai	bengluru	→ bengluru	bengluru
✅ Final Output
Mumbai
-->delhi-->goa-->chennai-->bengluru

⚠ Important Improvement (Best Practice)

Your loop:

for(String key : tickets.keySet())


Better written as:

while(tickets.containsKey(start)){
    System.out.print("-->" + tickets.get(start));
    start = tickets.get(start);
}


This avoids unnecessary looping and is cleaner and safer.

🧩 Summary

✔ Uses a reverse map to find the starting point
✔ Starting city = one that never appears as destination
✔ Then follows the chain using start = tickets.get(start)
✔ Prints itinerary in correct order

*/

public class find_itinerary {

    public static String getStart(HashMap<String,String> tickets){

        //we will make a reverse hashMap
        HashMap<String,String> revMap = new HashMap<>();

        for(String i : tickets.keySet()){
            System.out.println("value " +tickets.get(i) + " key " + i);
            revMap.put(tickets.get(i), i);
        }

        for(String i : tickets.keySet()){
            if(!revMap.containsKey(i)){
                return i; //starting point
            }
        }

        return null;
    }
    public static void main(String args[]){
        HashMap<String,String> tickets = new HashMap<>();

        tickets.put("chennai","bengluru");
        tickets.put("Mumbai","delhi");
        tickets.put("goa","chennai");
        tickets.put("delhi","goa");

        String start = getStart(tickets);

        System.out.print(start); //printing intial starting point
        System.out.println();
        for(String key : tickets.keySet()){
            System.out.print("-->"+tickets.get(start)); // printing the value 
            start = tickets.get(start);
        }
    }
}

/*

### Purpose
The code reconstructs the correct order of a travel itinerary from a set of flight tickets, where each ticket is a (source, destination) pair. The goal is to print the full path in order, starting from the initial departure city.

### How it works

1. **getStart Function**:
   - It finds the starting city of the journey.
   - It creates a reverse map (`revMap`) where each destination points to its source.
   - Then, it checks for a city in the original tickets that is not present as a destination in `revMap`. This city is the starting point (since no ticket arrives there).

2. **main Function**:
   - It creates a `HashMap` of tickets (source → destination).
   - Calls `getStart` to find the starting city.
   - Prints the starting city.
   - Then, it follows the tickets from the starting city, printing each destination in order, thus reconstructing the full itinerary.

### Example
Given the tickets:
- chennai → bengluru
- Mumbai → delhi
- goa → chennai
- delhi → goa
{chennai -> bengluru, mumbai -> delhi, goa-> channai, delhi->goa}

The itinerary is:
Mumbai → delhi → goa → chennai → bengluru

### Summary
- The code finds the starting city (not a destination in any ticket).
- Then, it prints the full travel path by following the tickets from start to end.

Let me know if you want a step-by-step trace or further explanation!

*/