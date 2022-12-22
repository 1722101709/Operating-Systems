#include <iostream>
#include <pthread.h>
#include <time.h>
#define MAX 20
#define THREAD_MAX 4
using namespace std;

int a[MAX];

int part = 0;
 
void merge(int low, int mid, int high)
{

    int* left = new int[mid - low + 1];

    int* right = new int[high - mid];
 
   int n1 = mid - low + 1, n2 = high - mid, i, j;

    for (i = 0; i < n1; i++)

        left[i] = a[i + low];
 
    for (i = 0; i < n2; i++)

        right[i] = a[i + mid + 1];
 

    int k = low;

    i = j = 0;
 
    while (i < n1 && j < n2) {

        if (left[i] <= right[j])

            a[k++] = left[i++];

        else

            a[k++] = right[j++];

    }
 
    while (i < n1) {

        a[k++] = left[i++];

    }
 
    while (j < n2) {

        a[k++] = right[j++];

    }
}
void merge_sort(int low, int high)
{

    int mid = low + (high - low) / 2;

    if (low < high) {

        merge_sort(low, mid);

        merge_sort(mid + 1, high);

        merge(low, mid, high);

    }
}

void* merge_sort(void* arg)
{

    int thread_part = part++;

    int low = thread_part * (MAX / 4);

    int high = (thread_part + 1) * (MAX / 4) - 1;

    int mid = low + (high - low) / 2;

    if (low < high) {

        merge_sort(low, mid);

        merge_sort(mid + 1, high);

        merge(low, mid, high);

    }
}
 
int usingthreads()
{
 clock_t t1,t2;
 t1=clock();
    for (int i = 0; i < MAX; i++)
        a[i] = rand() % 100;
    cout<<"\ngiven array is\n";    
 for (int i = 0; i < MAX; i++)
   cout<<a[i]<<" ";
   cout<<endl<<endl;
    pthread_t threads[THREAD_MAX];

    for (int i = 0; i < THREAD_MAX; i++)

        pthread_create(&threads[i], NULL, merge_sort, (void*)NULL);

    for (int i = 0; i < 4; i++)

        pthread_join(threads[i], NULL);

    merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);

    merge(MAX / 2, MAX/2 + (MAX-1-MAX/2)/2, MAX - 1);

    merge(0, (MAX - 1)/2, MAX - 1);
 
    t2 = clock();

    cout << "Sorted array:\n ";

    for (int i = 0; i < MAX; i++)

        cout << a[i] << " ";

    cout << "\n\nTime taken using threads: " << (t2 - t1) / 

              (double)CLOCKS_PER_SEC << endl;
 
    return 0;
}

void merge(int array[], int const left, int const mid, int const right)
{

    auto const subArrayOne = mid - left + 1;

    auto const subArrayTwo = right - mid;

    auto *leftArray = new int[subArrayOne],

         *rightArray = new int[subArrayTwo];
 
    for (auto i = 0; i < subArrayOne; i++)

        leftArray[i] = array[left + i];

    for (auto j = 0; j < subArrayTwo; j++)

        rightArray[j] = array[mid + 1 + j];
 

    auto indexOfSubArrayOne = 0, 
        indexOfSubArrayTwo = 0; 
    int indexOfMergedArray = left;
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {

        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {

            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];

            indexOfSubArrayOne++;

        }

        else {

            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];

            indexOfSubArrayTwo++;

        }

        indexOfMergedArray++;

    }

    while (indexOfSubArrayOne < subArrayOne) {

        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];

        indexOfSubArrayOne++;

        indexOfMergedArray++;

    }

    while (indexOfSubArrayTwo < subArrayTwo) {

        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];

        indexOfSubArrayTwo++;

        indexOfMergedArray++;

    }
}
 
void mergeSort(int array[], int const begin, int const end)
{

    if (begin >= end)

        return;
 
    auto mid = begin + (end - begin) / 2;

    mergeSort(array, begin, mid);

    mergeSort(array, mid + 1, end);

    merge(array, begin, mid, end);
}
 
void printArray(int A[], int size)
{

    for (auto i = 0; i < size; i++)

        cout << A[i] << " ";
}
 
int usingprocess()
{
  clock_t t1, t2;

    t1 = clock();
    
  int arr[MAX];
  
  for (int i = 0; i < MAX; i++)

        arr[i] = rand() % 100;

    auto arr_size = sizeof(arr) / sizeof(arr[0]);
 

    cout << "Given array is \n";

    printArray(arr, arr_size);
 
cout<<endl;
    mergeSort(arr, 0, arr_size - 1);
 

    cout << "\nSorted array is \n";

    printArray(arr, arr_size);
cout<<endl;
t2=clock();
  cout << "\nTime taken using process: " << (t2 - t1) / 

              (double)CLOCKS_PER_SEC <<endl<< endl;
 
    return 0;
}

int main()
{
	usingprocess();
	usingthreads();
	return 0;
}