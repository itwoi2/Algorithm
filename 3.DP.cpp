//資訊工程四A 10503301A 鍾俊傑 演算法第三次作業

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
#include <chrono>
#define INF 0xffffff
using namespace std;

void PRINT_OPTIMAL_PARENS(int** s, int i, int j) {
    if (i == j)
    {
        cout << "A" << i;
    }
    else
    {
        cout << "(";
        PRINT_OPTIMAL_PARENS(s, i, s[i][j]);
        PRINT_OPTIMAL_PARENS(s, s[i][j] + 1, j);
        cout << ")";
    }
}

double MatrixChainOrder(int* e, int n) {
    //時間計算宣告
    auto start = std::chrono::high_resolution_clock::now();
    //-----------------------------------------------//
    int** m;
    m = new int* [n + 1]; // 0~n, use 1~n
    for (int i = 0; i <= n; ++i) {
        m[i] = new int[n + 1];
    }

    int** s;
    s = new int* [n + 1];
    for (int i = 0; i <= n; ++i) {
        s[i] = new int[n + 1];
    }

    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    for (int d = 1; d <= n - 1; d++)
    {
        for (int i = 1; i <= n - d; i++)
        {
            int j = i + d;
            m[i][j] = 2147483647;
            for (int k = i; k <= j - 1; k++)
            {
                int tmp = m[i][k] + m[k + 1][j] + e[i - 1] * e[k] * e[j];
                if (tmp < m[i][j])
                {
                    m[i][j] = tmp;
                    s[i][j] = k;
                }
            }
        }
    }
    
    cout << endl << "m陣列 : " << endl;
    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= i - 1; j++)
        {
            cout << m[j][i] << " ";
        }
        cout << endl;
    }

    cout << endl << endl << "s陣列 : " << endl;
    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= i - 1; j++)
        {
            cout << s[j][i] << " ";
        }
        cout << endl;
    }
    PRINT_OPTIMAL_PARENS(s, 1, n);
    //-----------------------------------------------//
//計時結束
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    double time = duration.count();

    return time;
}

int Memorizedmatrixchain(int p[], int i, int j,int m[102][102])
{
    int k,q;
    if (m[i][j] < INF) return m[i][j];

    if (i == j) {
        m[i][j] = 0;
    }else {
            for (k = i; k <= j - 1; k++)
            {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        
    }
    
    return m[i][j];
}

int RMC(int p[], int n)
{

    int m[102][102];

    int i, j, k, L, q;

    for (i = 1; i < n; i++)
        m[i][i] = 0;

    for (L = 2; L < n; L++)
    {
        for (i = 1; i < n - L + 1; i++)
        {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                q = m[i][k] + m[k + 1][j] +
                    p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }
    cout << m[i][j];
    return m[1][n-1];
}

int main()
{
    int n; // n值
    cout << "//-----------------------------------------------//" << endl << "請輸入n值 : ";
    cin >> n;
    cout << endl;
    int* p = new int[n + 1]; // 建立n值+1數量的陣列
    for (int i = 0; i < n + 1; i++)
    {
        p[i] = (rand() % (97 + 1) + 2);
    }
    int m[102][102];
    double tm = MatrixChainOrder(p, n);

    //時間計算宣告
    auto start = std::chrono::high_resolution_clock::now();
    //-----------------------------------------------//
    n = n-1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            m[i][j] = INF;
        };
    };
    int temp1 = Memorizedmatrixchain(p, 1, n, m);
    //計時結束
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    double time = duration.count();

    //時間計算宣告
    auto start2 = std::chrono::high_resolution_clock::now();
    //-----------------------------------------------//
    n = n + 1;
    int temp2= RMC(p, n);
    //計時結束
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration2 = end2 - start2;
    double time2 = duration2.count();
    cout << endl << endl << "Recursive-matrix-chain 運行時間 : " << time2 << " S " << endl << "Memorized-matrix-chain 運行時間 : " << time << " S "<< endl << "Matrix-chain-order     運行時間 : " << tm << " S " << endl << "//-----------------------------------------------//";;
    //cout << temp1 << endl << temp2 << endl;
    system("pause");
    return 0;

}


