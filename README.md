[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9312360&assignment_repo_type=AssignmentRepo)
#Assignment 4

**Functions**

**-test_sorting_algorithms**

-vector<int> GenerateRandomVector -Creates a vector of random integers with the argument as the size of the vector.

-vector<int> GenerateSortedVector -Creates a vector of sorted integers from lowest to highest with the given size, if the given condition is true, otherwise, a vector of sorted integers from highest to lowest will be generated instead

-bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) -Checks if the given vector is sorted according to the given Comparator and returns true if it is and false otherwise.

-testSortingWrapper(int arc, char **argv) -Wrapper used to test the different sorting algorithms that were implemented in the Sort.h file.

**-Sort.h**

-const Comparable & middle(vector<Comparable> &a, Comparable left, Comparable right) -Used to find the middle element of a vector and a helper function for the quickSortMiddle.

-const Comparable & first(vector<Comparable> &a, Comparable left, Comparable right) -Used to find the first element in the vector and a helper function for quickSortFirst.

-void insertionSort( vector<Comparable> & a ) -Takes in a vector and performs insertion sort on the vector.

-void insertionSort( vector<Comparable> & a, Comparable left, Comparable right, Comparator less_than ) - Four parameter insertion sort for subarrays and a helper function for quick sort, quickSortMiddle, and quickSortFirst.

-void shellsort( vector<Comparable> & a )- Performs shell sort, using shell increments, on the given vector.

-void heapsort( vector<Comparable> & a )- Performs heap sort on the given vector.

-inline int leftChild( int i )- Gives the index of the left child, helper function of heap sort.

-void percDown( vector<Comparable> & a, Comparable i, Comparable n, Comparator less_than) -Method that percolates downward and is used as a helper function for heap sort.

-void mergeSort( vector<Comparable> & a, vector<Comparable> & tmpArray, Comparable left, Comparable right, Comparator less_than) - Five parameter merge sort that uses recursive calls.

-void mergeSort( vector<Comparable> & a ) - One parameter merge sort.

-void merge( vector<Comparable> & a, vector<Comparable> &tmpArray, Comparable leftPos, Comparable rightPos, Comparable rightEnd, Comparator less_than) - Used to merge two halves of a sorted array and is a helper function for mergeSort.

-const Comparable & median3( vector<Comparable> & a, Comparable left, Comparable right, Comparator less_than ) - Gets the median of the first, middle, and last element of given array, used as a helper function for quicksort function.

-void quicksort( vector<Comparable> & a, Comparable left, Comparable right, Comparator less_than )- Four parameter quick sort that is performed using the median of 3 as the method to find the pivot.

-void quicksort( vector<Comparable> & a ) - One parameter quick sort.

-void quickSortMiddle(vector<Comparable> &a, Comparable left, Comparable right, Comparator less_than)- Four parameter quick sort that is performed using the middle element in the vector as the pivot.

-void quickSortFirst(vector<Comparable> &a, Comparable left, Comparable right, Comparator less_than) - Four parameter quick sort that is performed using the first element in the vector as the pivot.

-void insertionSort( const RandomIterator & begin, const RandomIterator & end, Comparator lessThan ) - Public version of insertion sort, uses iterators in this function.

-void insertionSort( const RandomIterator & begin, const RandomIterator & end )- Two parameter version of above function. ↑

-void HeapSort(vector<Comparable> &a, Comparator less_than) - Driver for heap sort, Uses two parameters of two different template types.

-void MergeSort(vector<Comparable> &a, Comparator less_than) - Driver for merge sort, also uses two parameter of two different template types.

-void QuickSort(vector<Comparable> &a, Comparator less_than) - Quick sort that uses median of 3 to find the pivot and uses two parameters of two different template types.

-void QuickSort2(vector<Comparable> &a, Comparator less_than) - Quick sort that uses the middle element as the pivot and uses two parameters of two different template types.

-void QuickSort3(vector<Comparable> &a, Comparator less_than) - Quick sort that uses the first element as the pivot and uses two parameters of two different template types. 

**Bugs:**

-QuickSort2 and QuickSort3 did not properly sort with the comparator.

-All other sorts were list index out of range.



**How to run:**

-Using makefile

-all: make $(PROGRAM_0)

-Example: run ./test_sorting_algorithms random 20000 less


