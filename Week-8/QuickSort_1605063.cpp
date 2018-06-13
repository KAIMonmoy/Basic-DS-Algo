#include <iostream>
#include <cstdlib>

#define PRINT_ARRAY(ARR,N) {for(int i=0; i<N; i++) cout<<ARR[i]<<" ";}

using namespace std;

///******************************** Quick Sort ******************************************

template<typename T>
int findMedianIndex(T* arr, int low, int high, int k)
{
    if(low >= high) return high;

    //Choosing random pivot
    int randIndex = low + rand() % (high-low+1);

    T temp = arr[randIndex];
    arr[randIndex] = arr[high];
    arr[high] = temp;

    //Partitioning
    T pivot = arr[high];

    int left = low;
    int right = high-1;

    while (left <= right) {
        //FIND item greater than pivot
        while (left <= right && arr[left]<=pivot) left++;
        //FIND item smaller than or equal to pivot
        while (right >= left && arr[right]>pivot) right--;
        if(left < right) {
            //SWAP(arr[left], arr[right]);
            T temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    }

    //SWAP(arr[left], arr[high]);
    temp = arr[left];
    arr[left] = arr[high];
    arr[high] = temp;

    if(left-low==k-1) return (left+1);
    if(k-1 < left-low) return findMedianIndex(arr, low, left-1, k);
    if(k-1 > left-low) return findMedianIndex(arr, left+1, high, k-left+low-1);
}

template <typename T>
void myQuickSort(T* arr, int low, int high)
{
    if(low >= high) return;

    int pivotIdx = findMedianIndex(arr,low,high,(high-low+1)/2);

    T temp = arr[pivotIdx];
    arr[pivotIdx] = arr[high];
    arr[high] = temp;

    T pivot = arr[high];

    int left = low;
    int right = high-1;

    while (left <= right) {
        //FIND item greater than pivot
        while (left <= right && arr[left]<=pivot) left++;
        //FIND item smaller than or equal to pivot
        while (right >= left && arr[right]>pivot) right--;
        if(left < right) {
            //SWAP(arr[left], arr[right]);
            T temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    }

    //SWAP(arr[left], arr[high]);
    temp = arr[left];
    arr[left] = arr[high];
    arr[high] = temp;

    myQuickSort(arr, low, left-1);
    myQuickSort(arr, left+1, high);
}

///********************************** Merge Sort ***********************************

void myMerge(int *leftArr, int leftLen, int *rightArr, int rightLen, int *arr)
{
    int leftIdx=0, rightIdx=0, arrIdx=0;
    while(leftIdx<leftLen && rightIdx<rightLen) {
        if(leftArr[leftIdx] <= rightArr[rightIdx]) {
            arr[arrIdx] = leftArr[leftIdx];
            arrIdx++;
            leftIdx++;
        } else {
            arr[arrIdx] = rightArr[rightIdx];
            arrIdx++;
            rightIdx++;
        }
    }

    while(leftIdx<leftLen) {
        arr[arrIdx] = leftArr[leftIdx];
        arrIdx++;
        leftIdx++;
    }

    while(rightIdx<rightLen) {
        arr[arrIdx] = rightArr[rightIdx];
        arrIdx++;
        rightIdx++;
    }


}

void myMergeSort(int *arr, int length)
{
    if(length<=1) return;

    int leftLen = (length+1)/2;
    int rightLen = length - leftLen;

    int *leftArr = new int[leftLen];
    int *rightArr = new int[rightLen];

    int i,j;
    for( i=0; i<leftLen; i++) leftArr[i] = arr[i];
    for( j=0; j<rightLen; j++,i++) rightArr[j] = arr[i];

    myMergeSort(leftArr,leftLen);
    myMergeSort(rightArr,rightLen);
    myMerge(leftArr, leftLen, rightArr, rightLen, arr);

    delete[] leftArr;
    delete[] rightArr;
}



int main()
{

    while(true) {
        cout << "\n\nChoose\n\t1. QuickSort\t2. Exit\n\nEnter your choice : ";
        char option;
        cin >> option;
        if(option=='1') {
            cout << "\nEnter size of array : ";
            int n;
            cin >> n;
            cout << "Enter items : ";
            int *arr = new int[n];
            for(int i=0; i<n; i++) {
                cin >> arr[i];
            }

            cout << "\nBefore sorting : " << endl;
            PRINT_ARRAY(arr,n);
            cout << endl;

            myQuickSort(arr, 0, (n-1));

            cout << "\nThe median : " << arr[findMedianIndex(arr,0,(n-1),(n/2))] <<endl;

            cout << "\nAfter sorting : " << endl;
            PRINT_ARRAY(arr,n);
            cout << endl;

            delete[] arr;
            arr = 0;

        } else if(option == '2') {
            break;
        }
    }

    return 0;
}
