/*
 * COP 3502C Programming Assignment 4
 * This program is written by: Aaron Burgess
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct coordinates {
    int x;
    int y;
    double dist;
}Coordinates;

//function prototypes
void wrapperSort(Coordinates *arr, int length, int t);
void merge(Coordinates *arr, int l, int m, int r);
void mergeInsertionSort(Coordinates *arr, int l, int r, int t);
void insertionSort(Coordinates *arr, int l, int r);
int binarySearch(Coordinates *list, int length, Coordinates key);
Coordinates* readData(int num);
int compareTo(Coordinates *a, Coordinates *b);

//global variables
int initX;
int initY;

int main(void) {
    int numStadiums, queries, t; //t is the threshold for the insertionSort call
    scanf("%d %d %d %d %d", &initX, &initY, &numStadiums, &queries, &t); //scan the first line

    Coordinates* map_queries = readData(numStadiums + queries); //read the stadiums and the queries in the same array
    if (map_queries == NULL) { //check if failure
        printf("Memory allocation failed for map_queries\n");
        return 1;
    }

    for (int i = 0; i<numStadiums+queries; i++) { //calculate the distance of the stadiums to (initX, initY)
        map_queries[i].dist = sqrt(pow((map_queries[i].x - initX),2) + pow((map_queries[i].y - initY),2));
    }

    //sorting and printing the sorted stadiums
    wrapperSort(map_queries, numStadiums, t);

    for (int i = 0; i<numStadiums; i++) {
        printf("%d %d\n", map_queries[i].x, map_queries[i].y);
    }

    //checking the queries
    for (int i = 0; i<queries; i++) {
        int index = binarySearch(map_queries, numStadiums, map_queries[numStadiums + i]);

        if (index == -1) { //query not in list of stadiums
            printf("%d %d: no stadium found at this location\n", map_queries[numStadiums + i].x, map_queries[numStadiums + i].y);
        }
        else { //print off where the stadium was found in the sorted list
            printf("%d %d: stadium found at rank %d in the sorted order\n", map_queries[numStadiums + i].x, map_queries[numStadiums + i].y, index + 1);
        }
    }

    //freeing the memory allocated for the Coordinates*
    free(map_queries);
}

Coordinates* readData(int num) {
    Coordinates *arr = (Coordinates *)malloc(sizeof(Coordinates) * num); //allocate space for the array of coordinates (stadiums and queries)
    if (arr == NULL) { //check if failure
        printf("Memory allocation failed!");
        return NULL;
    }
    for (int i = 0; i < num; i++) { //fill the array
        scanf("%d %d", &arr[i].x, &arr[i].y);
    }
    return arr;
}
int compareTo(Coordinates *a, Coordinates *b) { //comparing how far they are from you to sort the arr properly
    if (a->x == b->x && a->y == b->y) { //same point
        return 0;
    }

    if (a->dist < b->dist) { //a is closer
        return -1;
    }
    else if (a->dist > b->dist) { //b is closer
        return 1;
    }
    else { //same distance so compare x and then y
        if (a->x < b->x) { //a has a smaller x coordinate
            return -1;
        }
        else if (a->x > b->x) { //b has a smaller x coordinate
            return 1;
        }
        else {
            if (a->y < b->y) { //a has a smaller y coordinate
                return -1;
            }
            if (a->y > b->y) { //b has a smaller y coordinate
                return 1;
            }
        }
    }
}

void wrapperSort(Coordinates *arr, int length, int t) { //wrapperSort calls mergeSort which internally decides when to call insertionSort
    mergeInsertionSort(arr, 0, length - 1, t);
}

//merge-insertion hybrid sorting algorithm
void mergeInsertionSort(Coordinates *arr, int l, int r, int t) {
    int length = r - l + 1;
    if (length <= t) { //base case
        insertionSort(arr, l, r);
        return;
    }
    else if (r > l) { //do recursive calls with the array split down the middle
        int middle = (l + r)/2;
        mergeInsertionSort(arr, l, middle, t);
        mergeInsertionSort(arr, middle+1, r, t);
        merge(arr, l, middle, r);
    }
}

void insertionSort(Coordinates *arr, int l, int r){
    int j;
    for (int i = l; i < r+1; i++) {
        Coordinates item = arr[i];
        for (j = i - 1; j >= l; j--) { //j <= l for efficiency
            if (compareTo(&arr[j], &item) == 1) {
                arr[j+1] = arr[j];
            }
            else { //found where it goes
                break;
            }
        }
        arr[j+1] = item;
    }
}

void merge(Coordinates *arr, int l, int m, int r){
    int sizeLeft = m - l + 1;
    int sizeRight = r - m;

    Coordinates *L = (Coordinates*)malloc(sizeLeft * sizeof(Coordinates));
    Coordinates *R = (Coordinates*)malloc(sizeRight * sizeof(Coordinates));

    for(int i = 0; i < sizeLeft; i++) {
        L[i] = arr[l + i];
    }
    for(int i = 0; i < sizeRight; i++) {
        R[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while (i < sizeLeft && j < sizeRight) {
        if (compareTo(&L[i], &R[j]) == -1) { //will never eval to 0
            arr[k] = L[i];
            i++;
            k++;
        }
        else {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    while (i < sizeLeft) { //in case initial while loop got out bc j
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < sizeRight) { //in case initial while loop got out bc i
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

int binarySearch(Coordinates *list, int len, Coordinates key) { //not formally checked, but reviewed
    int left = 0, right = len - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (compareTo(&list[mid], &key) == 0) { //same coordinate
            return mid;
        }
        if (compareTo(&key, &list[mid]) == 1) { //check the right side of the array
            left = mid + 1;
        }
        else { //check the left side of the array
            right = mid - 1;
        }
    }
    return -1; //not in the list of stadiums so "x y: no stadium found at this location"
}