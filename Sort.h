// Current code is from the textbook
// Modified by: Stanley Fung
// Comment file

//This program contains multiple sorting algorithms, including Insert Sort, Heap Sort, Shell Sort, Merge Sort, and Quick Sort with median of three pivot, middle pivot and the first pivot. There are also helper functions to help implement all the sorting functions within the program.
#ifndef SORT_H
#define SORT_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */

#include <vector>
#include <functional>
#include <iostream>
#include <cstdlib>
using namespace std;

//Function used to find the middle element of a vector
template <typename Comparable>
const Comparable & middle(vector<Comparable> &a, Comparable left, Comparable right)
{
    int middle = (left+right)/2;
    swap(a[middle], a[right-1]);
    return a[right-1];
}

//Function used to find the first element in the vector
template <typename Comparable>
const Comparable & first(vector<Comparable> &a, Comparable left, Comparable right)
{
    int first = left + 1;
    swap(a[first], a[right-1]);
    return a[right-1];
}
/**
 * Simple insertion sort.
 */
template <typename Comparable, typename Comparator>
void insertionSort( vector<Comparable> & a, Comparator less_than )
{
    for( int p = 1; p < a.size( ); ++p )
    {
        Comparable tmp = std::move( a[ p ] );

        int j;
        for( j = p; j > 0 && less_than(tmp, a[ j - 1 ]); --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}


/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void insertionSort( vector<Comparable> & a, Comparable left, Comparable right, Comparator less_than )
{
    for( int p = left + 1; p <= right; ++p )
    {
        Comparable tmp = std::move( a[ p ] );
        int j = p;

        while(j > 0 && less_than(tmp,a[j-1]))
        {
            a[ j ] = std::move( a[ j - 1 ] );
            j--;
        }
        a[ j ] = std::move( tmp );
    }
}



/**
 * Shellsort, using Shell's (poor) increments.
 */
template <typename Comparable, typename Comparator>
void shellsort( vector<Comparable> & a, Comparator less_than)
{
    for( int gap = a.size( ) / 2; gap > 0; gap /= 2 )
        for( int i = gap; i < a.size( ); ++i )
        {
            Comparable tmp = std::move( a[ i ] );
            int j = i;

            for( ; j >= gap && less_than(tmp, a[ j - gap ]); j -= gap )
                a[ j ] = std::move( a[ j - gap ] );
            a[ j ] = std::move( tmp );
        }
}

/**
 * Standard heapsort.
 */
template <typename Comparable>
void heapsort( vector<Comparable> & a)
{
    for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
        percDown( a, i, a.size( ));
    for( int j = a.size( ) - 1; j > 0; --j )
    {
        std::swap( a[ 0 ], a[ j ] );               /* deleteMax */
        percDown( a, 0, j);
    }
}

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i )
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <typename Comparable, typename Comparator>
void percDown( vector<Comparable> & a, Comparable i, Comparable n, Comparator less_than)
{
    int child;
    Comparable tmp;

    for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child )
    {
        child = leftChild( i );
        if( child != n - 1 && less_than(a[ child ],a[ child + 1 ]))
            ++child;
        if(less_than(tmp, a[ child ]) )
            a[ i ] = std::move( a[ child ] );
        else
            break;
    }
    a[ i ] = std::move( tmp );
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void merge( vector<Comparable> & a, vector<Comparable> &tmpArray, Comparable leftPos, Comparable rightPos, Comparable rightEnd, Comparator less_than)
{
    Comparable leftEnd = rightPos - 1;
    Comparable tmpPos = leftPos;
    Comparable numElements = rightEnd - leftPos + 1;

    // Main loop
    while( leftPos <= leftEnd && rightPos <= rightEnd )
        if( less_than(a[ leftPos ], a[ rightPos ]) || a[leftPos] == a[rightPos])
            tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );
        else
            tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    while( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );

    while( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    // Copy tmpArray back
    for( int i = 0; i < numElements; ++i, --rightEnd )
        a[ rightEnd ] = std::move( tmpArray[ rightEnd ] );
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void mergeSort( vector<Comparable> & a, vector<Comparable> & tmpArray, Comparable left, Comparable right, Comparator less_than)
{
    if( left < right )
    {
        Comparable center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center, less_than);
        mergeSort( a, tmpArray, center + 1, right, less_than);
        merge( a, tmpArray, left, center + 1, right, less_than);
    }
}

/**
 * Mergesort algorithm (driver).
 */
template <typename Comparable>
void mergeSort( vector<Comparable> & a )
{
    vector<Comparable> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}



/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable, typename Comparator>
const Comparable & median3( vector<Comparable> & a, Comparable left, Comparable right, Comparator less_than )
{
    int center = ( left + right ) / 2;
    
    if( less_than(a[ center ], a[ left ]) )
        std::swap( a[ left ], a[ center ] );
    if( less_than(a[ right ], a[ left ]) )
        std::swap( a[ left ], a[ right ] );
    if( less_than(a[ right ], a[ center ]) )
        std::swap( a[ center ], a[ right ] );

        // Place pivot at position right - 1
    std::swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksort( vector<Comparable> & a, Comparable left, Comparable right, Comparator less_than )
{
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right, less_than);

            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( less_than(a[ ++i ] ,pivot) ) { }
            while( less_than(pivot, a[ --j ]) ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

        quicksort( a, left, i - 1, less_than );     // Sort small elements
        quicksort( a, i + 1, right, less_than );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, less_than );
}

/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
void quicksort( vector<Comparable> & a )
{
    quicksort( a, 0, a.size( ) - 1 );
    
}

//Sorts the given vector using quick sort with the middle element as the pivot, meant to be used along with QuickSort2
template <typename Comparable, typename Comparator>
void quickSortMiddle(vector<Comparable> &a, Comparable left, Comparable right, Comparator less_than)
{
    if(left + 10 <= right)
    {
        const Comparable & pivot = middle(a, left, right);
        
        int i = left - 1, j = right - 1;
        for(;;)
        {
            while(less_than(a[i++], pivot)){}
            while(less_than(pivot, a[j--])){}
            if(i<j)
            {
                swap(a[i], a[j]);
            }
            else
                break;
        }
        swap(a[i], a[right-1]);
        quickSortMiddle(a, left, i-1, less_than);
        quickSortMiddle(a, i+1, right, less_than);
    }
    
    else{
        insertionSort(a, left, right, less_than);
    }
}

//Sorts the given vector using quick sort with the first element as the pivot, meant to be used along with QuickSort3
template <typename Comparable, typename Comparator>
void quickSortFirst(vector<Comparable> &a, Comparable left, Comparable right, Comparator less_than)
{
    if(left + 10 <= right)
    {
        const Comparable & pivot = first(a, left, right);
        int i = left-1, j = right - 1;
        
        for(;;)
        {
            while(less_than(a[i++], pivot)){}
            while(less_than(pivot, a[j--])){}
            
            if(i<j)
            {
                swap(a[i], a[j]);
            }
            else
                break;
        }
        swap(a[i], a[right-1]);
        quickSortFirst(a, left, i-1, less_than);
        quickSortFirst(a, i+1, right, less_than);
    }
    else
    {
        insertionSort(a, left, right, less_than);
    }
}

template <typename Comparable>
void SORT( vector<Comparable> & items )
{
    if( items.size( ) > 1 )
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;
        
        auto chosenItem = items[ items.size( ) / 2 ];
        
        for( auto & i : items )
        {
            if( i < chosenItem )
                smaller.push_back( std::move( i ) );
            else if( chosenItem < i )
                larger.push_back( std::move( i ) );
            else
                same.push_back( std::move( i ) );
        }
        
        SORT( smaller );     // Recursive call!
        SORT( larger );      // Recursive call!
        
        std::move( begin( smaller ), end( smaller ), begin( items ) );
        std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) );
        std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );

/*
        items.clear( );
        items.insert( end( items ), begin( smaller ), end( smaller ) );
        items.insert( end( items ), begin( same ), end( same ) );
        items.insert( end( items ), begin( larger ), end( larger ) );
*/
    }
}

/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 */
template <typename RandomIterator, typename Comparator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end,
                    Comparator lessThan )
{
    if( begin == end )
        return;
        
    RandomIterator j;

    for( RandomIterator p = begin+1; p != end; ++p )
    {
        auto tmp = std::move( *p );
        for( j = p; j != begin && lessThan( tmp, *( j-1 ) ); --j )
            *j = std::move( *(j-1) );
        *j = std::move( tmp );
    }
}

/*
 * The two-parameter version calls the three parameter version, using C++11 decltype
 */
template <typename RandomIterator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end )
{
    insertionSort( begin, end, less<decltype(*begin )>{ } );
}

//   Provide code for the following functions.
//   See PDF for full details.
//   Note that you will have to modify some of the functions above, or/and add new helper functions.

// Driver for HeapSort.
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void HeapSort(vector<Comparable> &a, Comparator less_than) {
  // Add code. You can use any of functions above (after you modified them), or any other helper
  // function you write.
    for(int i = a.size()/2 - 1; i >= 0; i--)
    {
        int max = a.size();
        percDown(a, i, max, less_than);
    }
    for(int j = a.size()-1; j > 0; j--)
    {
        swap(a[0], a[j]);
        percDown(a, 0, j, less_than);
    }
}
 
// Driver for MergeSort.
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void MergeSort(vector<Comparable> &a, Comparator less_than) {
  // Add code. You can use any of functions above (after you modified them), or any other helper
  // function you write.
    vector<Comparable> temp(a.size());
    Comparable left_pos = a.size() - 1;
    mergeSort(a, temp, 0, left_pos, less_than);
}

// Driver for QuickSort (median of 3 partitioning).
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void QuickSort(vector<Comparable> &a, Comparator less_than) {
  // Add code. You can use any of functions above (after you modified them), or any other helper
  // function you write.
    Comparable left = 0;
    Comparable right = a.size() - 1;
    quicksort(a, left, right, less_than);
}

// Driver for QuickSort (middle pivot).
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable> &a, Comparator less_than) {
  // quicksort implementation
  // to be filled
    Comparable left = 0;
    Comparable right = a.size() - 1;
    quickSortMiddle(a, left, right, less_than);
}

// Driver for quicksort using the first element as pivot
template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable> &a, Comparator less_than) {
  // quicksort implementation
  // to be filled
    Comparable left = 0;
    Comparable right = a.size() - 1;
    quickSortFirst(a, left, right, less_than);
}


#endif  // SORT_H
