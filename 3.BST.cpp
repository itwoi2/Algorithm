//資訊工程四A 10503301A 鍾俊傑 演算法第三次作業BST

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
using namespace std;

#define N 50//N值
#define MAX 999999.99999//限制MAX值
void optimal_binary_search_tree(float* p, float* q, int n, float e[N + 2][N + 1], int root[N + 1][N + 1]);

void optimal_binary_search_tree(float* p, float* q, int n, float e[N + 2][N + 1],float w[N + 2][N + 1], int root[N + 1][N + 1])
{
	int i, j, k, r;
	float t;
	for (i = 1; i <= N + 1; ++i) //初始化
	{
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (k = 1; k <= n; ++k)  
		for (i = 1; i <= n - k + 1; i++)
		{
			j = i + k - 1;
			e[i][j] = MAX;
			w[i][j] = w[i][j - 1] + p[j] + q[j];

			for (r = i; r <= j; r++) 
			{
				t = e[i][r - 1] + e[r + 1][j] + w[i][j];

				if (t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
}

int main()
{
	//時間計算宣告
	auto start = std::chrono::high_resolution_clock::now();
	//-----------------------------------------------//
	//建立n值
    srand(time(NULL));
	int n = N;
	//-----------------------------------------------//
	//建立陣列p
    float* p = new float[n + 1];
	//P0是空白
    p[0] = NULL;
    for (int i = 1; i <= n + 1; i++) {
        p[i] = float(rand() % (98 + 1) + 1) / 100;
		//cout << p[i] << "	";//顯示p陣列
    };//cout <<endl;//分隔p陣列與q陣列
	//-----------------------------------------------//
	//建立陣列q
    float* q = new float[n + 1];
    for (int i = 0; i <= n + 1; i++) {
        q[i] = float(rand() % (98 + 1) + 1) / 100;
		//cout << q[i] << "	";//顯示q陣列
    };
	//-----------------------------------------------//
	//建立BST所需變數
	float e[N + 2][N + 1];
	float w[N + 2][N + 1];
	int root[N + 1][N + 1];
	int i, j;
	optimal_binary_search_tree(p, q, N, e,w, root);//執行BST副程式
	//-----------------------------------------------//
	//計時結束
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;
	//-----------------------------------------------//
	//顯示程式結果

	cout << "二元樹 Root : " << e[1][N] << endl;

	cout << endl << "二元樹 e ：" << endl;
	for (i = 1; i <= N + 1; i++)
	{
		for (j = i - 1; j <= N; j++)
			cout << e[i][j] << " ";
		cout << "|| ";
	}

	cout << endl;

	cout << endl << "二元樹 w ：" << endl;
	for (i = 1; i <= N + 1; i++)
	{
		for (j = i - 1; j <= N; j++)
			cout << w[i][j] << " ";
		cout << "|| ";
	}
	double time= duration.count();
	cout << endl <<"n值 : " << n << "	" <<"BST程式運行時間 : "<< time << " S ";

}


