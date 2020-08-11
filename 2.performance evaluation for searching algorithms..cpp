// ConsoleApplication2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//資訊工程四A 10503301A 鍾俊傑 演算法第二次作業

#include <iostream>
#include <stdlib.h>
#include<time.h>
#include<windows.h> 
#include <algorithm>
#include <vector>
#include <list>
#include <sstream>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;
int* Data = new int[10000000]; // problem size 用於存儲長度為6的字符串
int targeted;

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

class Hash
{
    int BUCKET;    // No. of buckets 

    // Pointer to an array containing buckets 
    list<int>* table;
public:
    Hash(int V);  // Constructor 

    // inserts a key into hash table 
    void insertItem(int x);

    // deletes a key from hash table 
    void deleteItem(int key);

    void SearchItem(int key);

    // hash function to map values to key 
    int hashFunction(int x) {
        return (x % BUCKET);
    }

    void displayHash();
};

Hash::Hash(int b)
{
    this->BUCKET = b;
    table = new list<int>[BUCKET];
}

void Hash::insertItem(int key)
{
    int index = hashFunction(key);
    table[index].push_back(key);
}

void Hash::deleteItem(int key)
{
    // get the hash index of key 
    int index = hashFunction(key);

    // find the key in (inex)th list 
    list <int> ::iterator i;
    for (i = table[index].begin();i != table[index].end(); i++) {
        if (*i == key)
            break;
    }
    // if key is found in hash table, remove it 
    if (i != table[index].end())
        table[index].erase(i);
}

void Hash::SearchItem(int key)
{
    // get the hash index of key 
    int index = hashFunction(key);

    // find the key in (inex)th list 
    list <int> ::iterator i;
    for (i = table[index].begin();i != table[index].end(); i++) {
        if (*i == key) {break;}
    }
    if (i != table[index].end()){
        targeted = key;
    }
}

void Hash::displayHash() {
    for (int i = 0; i < BUCKET; i++) {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x;
        cout << endl;
    }
}

struct node{
    int data;
    node* lc;
    node* rc;
    node()
        : data(0)
        , lc(NULL)
        , rc(NULL)
    {
    }
};

class bstree
{
public:
    enum
    {
        hmax_size = 10000000,
        hmin_size_0 = 0,
    };

public:
    bstree()
        : root(NULL)
        , size(0)
    {
    }
    virtual ~bstree() {}

    int get_size()
    {
        return size;
    }
    void insert_node(int data)
    {
        int cur_size = get_size();
        if (hmax_size == cur_size)
        {
            cout << "insert node error, the size of the tree is max" << endl;
            return;
        }
        root = insert(root, data);
    }

    /*
        查找某个结点
        int key - 查找结果

        返回值：
            NULL : 可能为root为空 或者 没有找到
            != NULL, 找到结点
    */
    node* query(int key)
    {
        if (NULL == root)
        {
            cout << "query error, root = null" << endl;
            return NULL;
        }

        return query_node(root, key);
    }

    void remove_all()
    {
        if (NULL == root)
        {
            cout << "remove all failed, root = null" << endl;
            return;
        }

        remove_all(root);

        int cur_size = get_size();
        if (0 == cur_size)
            root = NULL;
    }

    node* get_min_node(node* proot)
    {
        if (NULL == proot->lc)
            return proot;

        return get_min_node(proot->lc);
    }
    node* get_max_node(node* proot)
    {
        if (NULL == proot->rc)
            return proot;

        return get_max_node(proot->rc);
    }
    node* get_root_node()
    {
        return root;
    }
    node* get_parent_node(int key)
    {
        node* cur_node = NULL;
        node* parent_node = NULL;

        cur_node = root;
        bool is_find = false;
        while (cur_node)
        {
            if (key == cur_node->data)
            {
                is_find = true;
                break;
            }
            else if (key < cur_node->data)
            {
                parent_node = cur_node;
                cur_node = cur_node->lc;
            }
            else if (key > cur_node->data)
            {
                parent_node = cur_node;
                cur_node = cur_node->rc;
            }
        }
        return (true == is_find) ? parent_node : NULL;
    }
private:
    node* query_node(node* proot, int key)
    {
        if (NULL == proot)
        {
            return proot;
        }

        if (proot->data == key) {
            targeted = key;
            return proot;
        }
        else if (proot->data > key)
        {
            return query_node(proot->lc, key);
        }
        else if (proot->data < key)
        {
            return query_node(proot->rc, key);
        }

        return NULL;
    }

    void remove_all(node* proot)
    {
        if (NULL != proot)
        {
            remove_all(proot->lc);
            remove_all(proot->rc);
            delete proot;

            dec_size();
        }
    }

    node* insert(node* proot, int data)
    {
        if (NULL == proot)
        {
            node* new_node = new(std::nothrow) node;
            if (NULL != new_node)
            {
                new_node->data = data;
                proot = new_node;
                add_size();
            }

            return proot;
        }
        if (proot->data > data)
        {
            proot->lc = insert(proot->lc, data);
        }
        else if (proot->data < data)
        {
            proot->rc = insert(proot->rc, data);
        }
        return proot;
    }

    void add_size()
    {
        if (hmax_size == size)
            return;
        size++;
    }

    void dec_size()
    {
        if (hmin_size_0 == size)
        {
            return;
        }

        size--;
    }
private:
    node* root;
    int size;
};


//主程式
int main()
{   
    int size = 10000000;// problem size 更改Data陣列的size時需要跟著改
    int SCsize = 10000000;
    int tmp, min, i, j, protime, target, left, right, mid, Run, protime1,protime2,bt;//宣告變數名稱
    //時間計算宣告
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    //隨機種子
    srand(time(NULL));

    /*---------------------------------------*/
    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    Run = 0;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    merge_sort(Data, size); //疊代合併排序演算法

    QueryPerformanceCounter(&nEndTime);//停止計時
    protime1 = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    cout << "字典建立完成" << endl;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    
    while (Run < SCsize) {
        target = (1.0 * rand() / RAND_MAX * 500000 + 100000);// 隨機產生一個演算法搜尋目標
        targeted = 0;
        left = 0, right = (size - 1),mid = ((left + right) / 2);//遞迴二元搜尋法
        bt = 0;
        while (left <= right) {
            if (Data[mid] == target) {
                targeted = Data[mid];
                break;
            }
            if (bt < (size/2)) {
                if (Data[mid] > target) {
                    bt = bt + 2;
                    mid = mid - 1;
                }
                else {
                    bt = bt - 1;
                    mid = mid + 1;
                }
            }
            else {
                break;
            }
        }
        Run++;
    }
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    protime2 = (protime1 + (protime));
    cout << "遞迴二元搜尋法 : " << endl << "  數據量：" << size << "筆  " << endl << "運行時間：" << protime2 << "秒" << endl << endl;
    /*---------------------------------------*/
    /*---------------------------------------*/
    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    Run = 0;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    merge_sort(Data, size); //迭代合併排序演算法

    QueryPerformanceCounter(&nEndTime);//停止計時
    protime1 = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    cout << "字典建立完成" << endl;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    while (Run < SCsize) {
        target = (1.0 * rand() / RAND_MAX * 500000 + 100000);// 隨機產生一個演算法搜尋目標
        targeted = 0;
        left = 0, right = (size - 1), mid;//迭代二元搜尋法
        while (left <= right) {
            mid = ((left + right) / 2);
            if (Data[mid] == target) {
                targeted = Data[mid];
                break;
            }
            if (Data[mid] > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        Run++;
    }

    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    protime2 = (protime1 + (protime));
    cout << "迭代二元搜尋法 : " << endl << "  數據量：" << size << "筆  " << endl << "運行時間：" << protime2 << "秒" << endl << endl;

    /*---------------------------------------*/
    /*---------------------------------------*/
    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    Run = 0;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    // array that contains keys to be mapped 
    int n = sizeof(Data) / sizeof(Data[0]);

    // insert the keys into the hash table 
    Hash h(size);
    for (int i = 0; i < n; i++) {
        h.insertItem(Data[i]);
    }
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime1 = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    cout << "字典建立完成" << endl;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    while (Run < SCsize) {
        target = (1.0 * rand() / RAND_MAX * 500000 + 100000);// 隨機產生一個演算法搜尋目標
        targeted = 0;
        h.SearchItem(target);
        Run++;
    }

    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    protime2 = (protime1 + (protime));
    cout << "鏈哈希表搜尋 : " << endl << "  數據量：" << size << "筆  " << endl << "運行時間：" << protime2 << "秒" << endl << endl;

    /*---------------------------------------*/
    /*---------------------------------------*/
    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    Run = 0;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時

    bstree tree;

    for (int i = 0; i < size; i++) {
        tree.insert_node(Data[i]);
    }
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime1 = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    cout << "字典建立完成" << endl;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時

    while (Run < SCsize) {
        target = (1.0 * rand() / RAND_MAX * 500000 + 100000);// 隨機產生一個演算法搜尋目標
        targeted = 0;
        tree.query(target);
        Run++;
    }

    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    protime2 = (protime1 + (protime));
    cout << "二進制搜索樹 : " << endl << "  數據量：" << size << "筆  " << endl << "運行時間：" << protime2 << "秒" << endl << endl;
    tree.remove_all();
    /*---------------------------------------*/
    /*---------------------------------------*/
    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    Run = 0;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    merge_sort(Data, size); //疊代合併排序演算法
    map<int, int> mapStudent;
    map<int, int>::iterator iter;
    map<int, int>::reverse_iterator iter_r;


    for (int i = 0; i < size; i++) {
        mapStudent.insert(pair<int, int>(Data[i], i));//將排序後的資料插入Map
    }
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime1 = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    cout << "字典建立完成" << endl;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    while (Run < SCsize) {
        target = (1.0 * rand() / RAND_MAX * 500000 + 100000);// 隨機產生一個演算法搜尋目標
        targeted = 0;
        if ((iter = mapStudent.find(target)) != mapStudent.end()) {
            targeted = target;
        }
        Run++;
    }
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    protime2 = (protime1 + (protime));
    cout << "C++ Map : " << endl << "  數據量：" << size << "筆  " << endl << "運行時間：" << protime2 << "秒" << endl << endl;
    mapStudent.erase(mapStudent.begin(), mapStudent.end());
    /*---------------------------------------*/
    /*---------------------------------------*/
    for (i = 0; i < size; i++) { Data[i] = (1.0 * rand() / RAND_MAX * 500000 + 100000); };//為Data陣列填入隨機六位數數字
    Run = 0;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    merge_sort(Data, size); //疊代合併排序演算法
    unordered_map<string, int>  umap;

    for (int i = 0; i < size; i++) {
        string s = to_string(Data[i]);
        umap.insert(unordered_map<string, int>::value_type(s,i));
    }

    QueryPerformanceCounter(&nEndTime);//停止計時
    protime1 = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    cout << "字典建立完成" << endl;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//開始計時
    while (Run < SCsize) {
        target = (1.0 * rand() / RAND_MAX * 500000 + 100000);// 隨機產生一個演算法搜尋目標
        string target1 = to_string(target);
        targeted = 0;

        unordered_map<string, int>::iterator it;
        if ((it = umap.find(target1)) != umap.end()) {
            targeted = target;
        }

        Run++;
    }
    QueryPerformanceCounter(&nEndTime);//停止計時
    protime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//計算程式執行時間
    protime2 = (protime1+(protime));
    cout << "C++ unordered_map : " << endl << "  數據量：" << size << "筆  " << endl << "運行時間：" << protime2 << "秒" << endl << endl;
    /*---------------------------------------*/
    system("PAUSE");
    return 0;
}