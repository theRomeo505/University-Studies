// labka4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
void lab4task1() {
	char* m = new char[1000];
	char* n = new char[1000];
	cin.getline(m, 1000);
	cin.getline(n, 1000);
	int i = 0, g = 0; bool t = true;
	while (m[i] > 0 && n[g] > 0) {
		if (m[i + 1] < 0) {
			if (m[i] == '*')
				break;
			else {
				if (n[g + 1] > 0)
					t = false;
				else if (m[i] != '?' && m[i] == n[g])
					break; else if (m[i] != '?') {
					t = false;  break;
				}
				break;
			}
		}
		if (m[i] != '?' && m[i] != '*') {
			if (n[g] != m[i]) {
				t = false; break;
			}
			g++;
		}
		if (m[i] == '?')
			g++;
		if (m[i] == '*' && m[i + 1] > 0) {
			while (n[g] != m[i + 1] && n[g] > 0)
				g++;
			//g++;
		}

		i++;
	}
	cout << t;
}
int maxlength = 0, *maxm = new int[1000];
void rec(int *m,int g,int length,int n, int *mm) {
	int k = g-1;
	//for (int i = 0; i < length; i++)
		//cout << mm[i] << ' ';
	//cout << endl;
	while (g<n) {
		if (m[g]>m[k])
		{
			mm[length] = m[g];
			rec(m, g + 1, length + 1, n, mm);
		}
		g++;
	}
	if (g  >= n) {
		//cout << length<<endl;
		if (length > maxlength) {
			maxlength = length;
			for (int i = 0; i < length; i++)
				maxm[i] = mm[i];
			//maxm = mm;
		}
			return;
	}
	
	
}
void lab4task2() {
	int n;
	cin >> n;
	int* m = new int[n];
	int* mm = new int[n];
	for (int i = 0; i < n; i++)
		cin >> m[i];
	for (int i = 0; i < n; i++) {
		mm[0] = m[i];
		rec(m, i+1, 1, n, mm);
	}
	for (int i = 0; i < maxlength; i++) {
		cout << maxm[i] << ' ';
	}
}

int main()
{
	
	lab4task1();
	lab4task2();
	
}


