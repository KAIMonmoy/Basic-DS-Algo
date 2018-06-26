#include <bits/stdc++.h>

using namespace std;

class MinHeapNode
{
public:

    char key;
    int frequency;
    MinHeapNode *left, *right;

    MinHeapNode() { key = '@'; frequency=0; left = right = NULL; }
    MinHeapNode(char _key, int _frequency) : key(_key), frequency(_frequency) { left = right = NULL; }

    bool isLeaf() { return ((left==NULL) && (right==NULL)); }
};

class MinHeap
{
public:

    int heapSize;
    int heapCapacity;
    MinHeapNode **heapArray;


    MinHeap(int _heapCapacity) : heapCapacity(_heapCapacity)
    {
        heapSize = 0;
        heapArray = new MinHeapNode*[_heapCapacity] ;
    }

    ~MinHeap()
    {
        delete[] heapArray;
        heapArray = NULL;
        heapSize = heapCapacity = 0;
    }


    void swapMinHeapNode(MinHeapNode **x, MinHeapNode **y);
    void minHeapify(int index);
    void insertMinHeap(MinHeapNode *newNode);
    MinHeapNode* extractMinNode();

    void fillMinHeapArray(char keys[], int freqs[], int n);
    MinHeapNode* buildHuffmanTree();
    void printHuffmanCodes(MinHeapNode *root, int code[], int idx);
};

void MinHeap::swapMinHeapNode(MinHeapNode **x, MinHeapNode **y) {
    MinHeapNode *temp = *x;
    *x = *y;
    *y = temp;
}

void MinHeap::minHeapify(int index) {
    int smallestIdx = index;
    int leftIdx = (index*2) + 1;
    int rightIdx = (index*2) + 2;

    if(leftIdx>=heapSize && rightIdx>=heapSize) return;

    if (leftIdx < heapSize && heapArray[leftIdx]->frequency < heapArray[smallestIdx]->frequency) smallestIdx = leftIdx;

    if (rightIdx < heapSize && heapArray[rightIdx]->frequency < heapArray[smallestIdx]->frequency) smallestIdx = rightIdx;

    if (smallestIdx != index) {
        swapMinHeapNode(&heapArray[smallestIdx], &heapArray[index]);
        minHeapify(smallestIdx);
    }
}

void MinHeap::insertMinHeap(MinHeapNode *newNode) {

    int index = heapSize;
    heapSize++;

    while (index>0 && newNode->frequency < heapArray[(index-1)/2]->frequency) {
        heapArray[index] = heapArray[(index-1)/2];
        index = (index-1)/2;
    }

    heapArray[index] = newNode;
}

MinHeapNode *MinHeap::extractMinNode() {
    MinHeapNode *minNode = heapArray[0];
    heapSize--;
    heapArray[0] = heapArray[heapSize];
    minHeapify(0);
    return minNode;
}

void MinHeap::fillMinHeapArray(char keys[], int freqs[], int n) {
    for (int i = 0; i < n; ++i) {
        insertMinHeap(new MinHeapNode(keys[i], freqs[i]));
    }
}

MinHeapNode *MinHeap::buildHuffmanTree() {
    MinHeapNode *left, *right, *parent;

    while (heapSize != 1) {
        left = extractMinNode();
        right = extractMinNode();

        parent = new MinHeapNode('@',(left->frequency+right->frequency));
        parent->left = left;
        parent->right = right;

        insertMinHeap(parent);
    }

    return heapArray[0];
}

void MinHeap::printHuffmanCodes(MinHeapNode *root, int code[], int idx) {

    if (root->left) {
        code[idx] = 0;
        printHuffmanCodes(root->left, code, idx + 1);
    }

    if (root->right) {
        code[idx] = 1;
        printHuffmanCodes(root->right, code, idx + 1);
    }

    if (root->isLeaf()) {
        cout << "\t\t" << root->key << " : ";
        for (int i = 0; i < idx; ++i) { cout<<code[i]; }
        cout<<endl;
    }
}

void HuffmanCode(char keys[], int freqs[], int n)
{
    MinHeap* HuffmanHeap = new MinHeap(n);
    HuffmanHeap->fillMinHeapArray(keys, freqs, n);
    int code[n] = {};
    cout << "\n\n**************Huffman Codes***************\n\n";
    HuffmanHeap->printHuffmanCodes(HuffmanHeap->buildHuffmanTree(),code,0);
}


int main(void)
{
    int n;
    cout << "Enter number of different characters : ";
    cin >> n;

    char keys[n];
    int freqs[n];
    cout << "Enter the characters and their frequencies : \n\t";

    for(int i=0; i<n; i++) {
        cin >> keys[i] >> freqs[i];
    }

    HuffmanCode(keys, freqs, n);

    return 0;
}

