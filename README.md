# CS1_PA4
 Sorting

Problem Scenario: Nearest Stadium
The soccer tournament is in full swing, and fans are eager to experience the excitement live from the
stadiums. With a tournament pass in hand, you can attend any match at any stadium. However, the host city
of Monster country is massive, and with multiple stadiums spread across different locations, finding the closest
stadium can be a challenge.

To help fans quickly locate the nearest stadium, an efficient search system is needed. The city can be
represented on a Cartesian plane, with your current location at the point (x, y). You also have the coordinates
of all stadiums hosting matches. Your task is to sort these stadiums by their distance from your position so
you can decide where to go next.

Additionally, fans may have specific stadiums in mind. Your program should handle queries about particular
locations—checking whether a stadium exists there and, if so, identifying its position in the sorted list. If no
stadium is found at the queried location, the program should clearly indicate this.
Now, get ready to navigate the city, find the best stadium, and enjoy the beautiful game!

Note: This assignment comes with several important implementation restrictions. To ensure everyone is fully
aware of them, we will list these restrictions first, deviating from the usual section order used in previous
assignments.

Implementation Restrictions
1. You must implement a hybrid sorting algorithm that combines Merge Sort and Insertion Sort to sort the
point data. Each input case will include a threshold value, t. Within the mergeSort function, if a subsection
of the array contains t or fewer elements, you should apply Insertion Sort instead of continuing with
Merge Sort. For larger sections, use the standard Merge Sort approach.
This optimization helps improve sorting efficiency by leveraging Insertion Sort for small arrays rather than
waiting until the array size reduces to one. The reasoning behind this approach will be briefly discussed in
class. Additional details on the sorting comparison method are provided below.

2. You must store your coordinates in a struct that contains two integer fields. You can add more fields if
needed.

3. You must implement a ReadData() function that reads the required data from the inputs and return the
array of points to be sorted.

4. While comparing points during sorting, you need to use a compareTo function to decide which point should
come first out of the two points you are comparing. So, you must write a function compareTo which
takes in two pointers, ptrPt1 and ptrPt2, to coordinate structs and returns:
   a. a negative integer if the point pointed by ptrPt1 is closer to you than the point pointed to by ptrPt2
   b. 0 if the two locations pointed to by both are identical locations,
   c. a positive integer if the point pointed to by ptrPt1 is farther from you than the point pointed to by ptrPt2.
   d. Exceptions to this will be when the two pointers are pointing to points that are the same distance
      from you, but are distinct points.
         i. In these cases, if ptrPt1's x coordinate is lower than ptrPt2's x coordinate, a negative integer
            must be returned.
         ii. Alternatively, if ptrPt1's x coordinate is greater than ptrPt2's x coordinate a positive integer
             must be returned.
         iii. Finally, if the x coordinate of both points is the same, if ptrPt1's y coordinate is lower than
              ptrPt2's y coordinate, a negative integer must be returned. If ptrPt1's y coordinate is greater
              than ptrPt2's y coordinate, a positive integer must be returned.

5. Since your location must be used for sorting, please make the variable that stores your x and y coordinates
global. Your program should have no other global variables.

6. A Binary Search function must be used when answering queries. As you are searching points, using
compareTo function would help you during this process.

7. You need to write a wrapper sort function that serves as the entry point for sorting. This function should:
   • Take in the array to be sorted, its length, and the threshold value (t).
   • Not be recursive itself. Instead, it should simply call the appropriate sorting function.
   • Pass the array and relevant parameters to the Merge Sort function, which will internally decide when
     to switch to Insertion Sort based on the threshold value t.
     This wrapper function ensures a clean and structured approach to sorting by handling the initial function
     call and keeping the main sorting logic separate.

8. The recursive mergeSort function should:
   • Take in the array, a starting index, an ending index, and the threshold value (t).
   • Recursively divide the array and apply Merge Sort if the subsection size is greater than t.
   • Switch to Insertion Sort instead of further recursion when the subsection size becomes t or smaller.
     In this function, you should either make recursive calls to mergeSort or call Insertion Sort, but
     never both for the same subsection. This ensures efficient sorting by leveraging the strengths of
     each algorithm appropriately.

9. Make sure to write the insertion sort function that takes the array, starting and ending index from the array
that you want to sort. Make sure you sort only from the starting and ending index of the array. Do not sort
the entire array by mistake in this function, which will increase the run-time a lot instead of optimizing!

10. Make sure there is no memory leak.

The Problem
Given your location and the coordinates of each stadium, sort the list in ascending order of distance from
you. If two stadiums are equidistant, break ties by x-coordinate (lower value comes first). If there is still a tie,
use the y-coordinate (lower value comes first).

After sorting, answer several fan queries about specific locations on the coordinate plane:
   • Determine if a queried point contains a stadium.
   • If a stadium exists at the queried location, find its ranking in the sorted list based on its distance from you.
   • If no stadium is present, indicate this clearly.

The Input (to be read from standard input. Using file i/o on any submission (either latest or history of
submissions while grading) will result in zero in this assignment and 0 in another past assignment)
The first line of the input contains 5 integers separated by spaces. The first two of these values are x and y (|x|,
|y| ≤ 10000), representing your location. The third integer is n (2 ≤ n ≤ 106), representing the number of
stadiums. The fourth integer is s (1 ≤ s ≤ 2x105), representing the number of points to search for. The last
integer, t (1 ≤ t ≤ 30), represents the threshold to be used for determining whether you run Merge Sort of
Insertion Sort.

The next n lines of the input contain x and y coordinate values, respectively, separated by spaces, representing
the locations of stadiums. Each of these values will be integers and the points will be distinct (and also different
from your location) and the absolute value of x and y for all of these coordinates will not exceed 10,000.
Then the next s lines of the input contain x and y coordinate values for searching. Both values on each line
will be integers with an absolute value less than or equal to 10,000.

The Output (to be printed to standard console output)
The first n lines of output should list the coordinates of the stadiums, sorted according to the specified criteria.
Each line should be formatted as:
x-coordinate y-coordinate
with a single space separating the values.
The last s lines of output should contain the results for each of the s queries from the input. Each answer
should be printed on a separate line. If the point queried contains a stadium, output a line with the following
format:
x y: stadium found at rank R in the sorted order
where (x, y) is the query point, and R is the one-based position of that stadium in the sorted list. (Thus, R will
be 1 more than the array index in which (x, y) is located, after sorting.)
If the point queried does NOT contain a stadium, output a line with the following format:
x y: no stadium found at this location

Additional Requirement:
   • You have to use Merge sort, insertion sort, and binary search for your solution based on the
     requirement. Without using them, you will get zero. The output must match with the sample output
     format. Do not add additional space, extra characters or words with the output as we will use diff
     command to check whether your result matches with our result. Next, you must write a well structure
     code. There will be a deduction of 10% points if the code is not well indented and 5% for not
     commenting important blocks.
   • As always, all the programming submission will be graded base on the result from codegrade. If your
     code does not work on codegrade, we will conclude that your code has an error even if it works in your
     computer.
   • Your code should contain no memory leak for full credit
   • Note that you can use <math.h> library if you need. In that case you have to use –lm option while
     compiling your code.
        For example: $gcc filename.c -lm
