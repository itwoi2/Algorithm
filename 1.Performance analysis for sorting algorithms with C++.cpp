// ConsoleApplication2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//資訊工程四A 10503301A 鍾俊傑 演算法作業

#include <iostream>
#include <stdlib.h>
#include<time.h>
#include<windows.h> 
#include <algorithm>
#include <vector>

using namespace std;

int d[100] = { 0 };//給mergesort用的陣列 更改Data陣列的size時需要跟著改
int* Data = new int[100]; // problem size 用於存儲長度為6的字符串

//swap交換小程式
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
//遞迴合併演算法（Top-down）
void merge(int left, int right) {
    int mid = (left + right) / 2;
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        if (Data[i] < Data[j])
        {
            d[k++] = Data[i++];
        }
        else
        {
            d[k++] = Data[j++];
        }
    }

    while (i <= mid)d[k++] = Data[i++];
    while (j <= right)d[k++] = Data[j++];
    for (i = left, k = 0; i <= right; i++, k++)Data[i] = d[k];
}
void mergesort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergesort(left, mid);
        mergesort(mid + 1, right);
        merge(left, right);
    }
}
//疊代合併演算法（Bottom-up）
template<typename T> // 整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
void merge_sort(T arr[], int len) {
    T* a = arr;
    T* b = new T[len];
    for (int seg = 1; seg < len; seg += seg) {
        for (int start = 0; start < len; start += seg + seg) {
            int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        T* temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        for (int i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    delete[] b;
}
//遞迴快速演算法
void QuickSort_vector_index(int* nums, int start, int end) {
    if (start >= end) return;
    int temp = nums[start];
    int L = start;
    int R = end;

    while (L < R) {
        while (L < R && nums[R] >= temp)
            R--;
        if (L < R)
            nums[L++] = nums[R];
        while (L < R && nums[L] <= temp)
            L++;
        if (L < R)
            nums[R--] = nums[L];
    }

    nums[L] = temp;
    QuickSort_vector_index(nums, start, L - 1);
    QuickSort_vector_index(nums, L + 1, end);
}
//疊代快速演算法
int Partition(int* arr, int front, int end) {
    int pivot = arr[end];
    int i = front - 1;
    for (int j = front; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}
void QuickSort(int* arr, int front, int end) {
    if (front < end) {
        int pivot = Partition(arr, front, end);
        QuickSort(arr, front, pivot - 1);
        QuickSort(arr, pivot + 1, end);
    }
};
//堆積排序法(Heap Sort)
void downPercolate(int *nums, int index, int end) {
    int index_temp = index;
    while (1) {
        int hole = 2 * index_temp + 1;
        if (hole > end) break;
        if (hole + 1 <= end && nums[hole] > nums[hole + 1])
            ++hole;
        if (nums[index_temp] < nums[hole]) break;
        swap(nums[index_temp], nums[hole]);
        index_temp = hole;
    }
}
void HeapSort(int *nums, int size) {
    for (int i = size / 2; i >= 0; --i) {
        downPercolate(nums, i, size - 1);
    }
    for (int i = 0; i < size; ++i) {
        swap(nums[0], nums[size - 1 - i]);
        downPercolate(nums, 0, size - 2 - i);
    }
}

//主程式
int main()
{
    int size = 100;// problem size 更改Data陣列的size時需要跟著改
    int tmp, min, i, j, protime;//宣告變數名稱
    //時間計算宣告
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    //隨機種子
    srand(time(NULL));

    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    for (i = 1; i < size; i++) {//insertion sort
        tmp = Data[i];
        for (j = i; j > 0 && tmp < Data[j - 1]; j--)
            Data[j] = Data[j - 1];
        Data[j] = tmp;
    }
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    cout << "\n" << "Data數目有" << size << "個的時候," << "Insertion sort" << "程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間


    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    for (i = 0; i < size; i = i + 1)
    {
        for (j = i + 1; j < size; j = j + 1)
        {
            if (Data[i] > Data[j])
            {
                //變數交換
                tmp = Data[i];
                Data[i] = Data[j];
                Data[j] = tmp;
            }
        }
    }
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    cout << "\n" << "Data數目有" << size << "個的時候," << "Selection sort" << "程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間


    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < (size - 1 - i); j++) {
            if (Data[j] > Data[j + 1]) {
                tmp = Data[j];
                Data[j] = Data[j + 1];
                Data[j + 1] = tmp;
            };
        };
    };
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    cout << "\n" << "Data數目有" << size << "個的時候," << "Bubble sort" << "程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間

    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    mergesort(0, size - 1);
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    cout << "\n" << "Data數目有" << size << "個的時候," << "Recursive merge sort" << "程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間

    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    merge_sort(Data, size);
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    cout << "\n" << "Data數目有" << size << "個的時候," << "Iterative merge sort" << "程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間

    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    QuickSort_vector_index(Data, 0, size - 1);
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    cout << "\n" << "Data數目有" << size << "個的時候," << "Recursive quick sort" << "程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間

    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    QuickSort(Data, 0, size - 1);//recursive quicksort
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    cout << "\n" << "Data數目有" << size << "個的時候," << "Iterative quick sort" << "程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間

    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    HeapSort(Data, size);//HeapSort
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    cout << "\n" << "Data數目有" << size << "個的時候," << "HeapSort" << "程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間

    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    sort(Data, Data + size);//C++ built in sorting function
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間單位為s
    cout << "\n" << "Data數目有" << size << "個的時候," << "C++ built in sorting function" << "程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間

    //for (i = 0; i < size; i++) { cout << Data[i] << "\t"; };//輸出經演算法排序後的陣列
    //int target = (1.0 * rand() / RAND_MAX * 500000 + 100000);// 隨機一個演算法搜尋目標
    //cout << "\n" << "搜尋目標：" << target << "\n";
    //cout << "\n" << "Data數目有"<< size << "個的時候," << "" <<"程式執行時間：" << protime * 1000 << "ms" << endl;//輸出演算法執行時間
    return 0;
}