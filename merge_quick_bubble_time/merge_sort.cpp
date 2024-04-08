#include <iostream>
#include <cstdlib>
#include <ctime>
// #include <algorithm>

const int size = 10000;
    int arr[size];

using namespace std;

// Function to merge two subarrays of arr[].
// First subarray is arr[l..m].
// Second subarray is arr[m+1..r].
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quick sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Heapify a subtree rooted with node i which is an index in arr[].
void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Bubble sort function
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to find minimum and maximum using divide and conquer
void findMinMax(int arr[], int low, int high, int& min, int& max) {
    if (low == high) {
        min = max = arr[low];
        return;
    } else if (high - low == 1) {
        if (arr[low] < arr[high]) {
            min = arr[low];
            max = arr[high];
        } else {
            min = arr[high];
            max = arr[low];
        }
        return;
    }

    int mid = (low + high) / 2;
    int min1, max1, min2, max2;

    findMinMax(arr, low, mid, min1, max1);
    findMinMax(arr, mid + 1, high, min2, max2);

    min = min1 < min2 ? min1 : min2;
    max = max1 > max2 ? max1 : max2;
}

int main() {
    // srand(time(0)); // Seed for random number generation

    

    // Fill the array with random numbers from 1 to 10000
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000 + 1;
    }

    clock_t start, end;
    
    start = clock();

    // Sorting using merge sort
    int mergeSorted[size];
    copy(arr, arr + size, mergeSorted);
    mergeSort(mergeSorted, 0, size - 1);

    end = clock();
    cout << "Merge Sort: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;


    start = clock();
    // Sorting using quick sort
    int quickSorted[size];
    copy(arr, arr + size, quickSorted);
    quickSort(quickSorted, 0, size - 1);

    end = clock();
    cout << "Quick Sort: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;


    start = clock();
    // Sorting using heap sort
    int heapSorted[size];
    copy(arr, arr + size, heapSorted);
    heapSort(heapSorted, size);

    end = clock();
    cout << "Heap Sort: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;


    start = clock();
    // Sorting using bubble sort
    int bubbleSorted[size];
    copy(arr, arr + size, bubbleSorted);
    bubbleSort(bubbleSorted, size);

    end = clock();
    cout << "Bubble Sort: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;


    start = clock();
    // Finding min and max using divide and conquer
    int min, max;
    findMinMax(arr, 0, size - 1, min, max);

    end = clock();
    cout << "Min Max: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n\n" << endl;


    cout << "Merge Sort Results:" << endl;
    cout << "First 10 elements: ";
    for (int i = 0; i < 10; i++) {
        cout << mergeSorted[i] << ", ";
    }
    cout << endl;
    cout << "Last 10 elements: ";
    for (int i = size - 10; i < size; i++) {
        cout << mergeSorted[i] << ", ";
    }
    cout << endl;

    cout << "\nQuick Sort Results:" << endl;
    cout << "First 10 elements: ";
    for (int i = 0; i < 10; i++) {
        cout << quickSorted[i] << ", ";
    }
    cout << endl;
    cout << "Last 10 elements: ";
    for (int i = size - 10; i < size; i++) {
        cout << quickSorted[i] << ", ";
    }
    cout << endl;

    cout << "\nHeap Sort Results:" << endl;
    cout << "First 10 elements: ";
    for (int i = 0; i < 10; i++) {
        cout << heapSorted[i] << ", ";
    }
    cout << endl;
    cout << "Last 10 elements: ";
    for (int i = size - 10; i < size; i++) {
        cout << heapSorted[i] << ", ";
    }
    cout << endl;

    cout << "\nBubble Sort Results:" << endl;
    cout << "First 10 elements: ";
    for (int i = 0; i < 10; i++) {
        cout << bubbleSorted[i] << ", ";
    }
    cout << endl;
    cout << "Last 10 elements: ";
    for (int i = size - 10; i < size; i++) {
        cout << bubbleSorted[i] << ", ";
    }
    cout << endl;

    cout << "\nMinimum: " << min << endl;
    cout << "Maximum: " << max << endl;

    return 0;
}