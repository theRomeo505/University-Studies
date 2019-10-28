// 15.10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
	int x, y;
	cin >> x >> y;
	int** m = new int* [x];
	for(int i = 0; i < x; i++)
		m[i] = new int[y];
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			cin >> m[i][j];
	int mm = 0,nmb=0, ser=0, cser=0; bool g = false;
	for (int i = 0; i < y; i++) {
		g = false;
		for (int j = 0; j < x; j++)
		{  
			if (m[j][i] == 0)g = true;
		}
		if (g)
			mm++;
	}
	cout << mm << endl;
	for (int i = 0; i < x; i++) {
		cser = 0;
		for (int j = 0; j < y; j++) {
			if (j != y - 1 && m[i][j] == m[i][j + 1])
				cser++;
			else if (cser > ser) {
				ser = cser; nmb = i; cser = 0;
			}
			else cser = 0;
				
			
		}
	
	}
	cout << nmb;

 }
