#include <bits/stdc++.h>

using namespace std;

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

void CoinChangeGreedy(int *arr, int n, int target)
{
    int requiredCoins[n*2]={}, idx=0, totalCoins=0;

    myMergeSort(arr, n);

    for (int i = (n-1); i >= 0; --i) {
        if(arr[i]<=target) {
            requiredCoins[idx] = arr[i];
            idx++;
            requiredCoins[idx] = 0;
            while(arr[i]<=target) {
                target -= arr[i];
                requiredCoins[idx]++;
                totalCoins++;
            }
            idx++;
        }
    }

    cout << "\n\n" << totalCoins << endl;
    for (int j = 0; j < idx; j+=2) {
        cout << requiredCoins[j] << " " << requiredCoins[j+1] << endl;
    }
}

int main(void)
{
    int n, target;
    cout << "Enter number of coins : ";
    cin >> n;

    int *coins  = new int[n];
    cout << "Enter the value of coins : \n\t";
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    cout << "Enter target amount : ";
    cin >> target;

    CoinChangeGreedy(coins, n, target);

    return 0;
}

