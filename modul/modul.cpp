// modul.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
double dop(int i) {
	double s = pow(-2, i);
	for (int j = 1; j <= i; j++)
		s /= j;
	return s;
}
void fun1(double  eps) {
	int i = 0; double s=0;
	while (abs(dop(i)) > eps) {
		s += dop(i);
		i++;
	}
	cout<<s;
}
void fun2(int n,int m) {
	int a,b,a1,b1,a2,b2,x,y,z;
	
	for (int i = 0; i < n; i++) {
		a = rand() % (m+1 ) * pow(-1, rand() % 2);
		a1 = rand() % (m + 1) * pow(-1, rand() % 2);
		a2 = rand() % (m + 1) * pow(-1, rand() % 2);
		b = rand() % (m + 1) * pow(-1, rand() % 2);
		b1 = rand() % (m + 1) * pow(-1, rand() % 2);
		b2 = rand() % (m + 1) * pow(-1, rand() % 2);
		x = sqrt((a1 - a) * (a1 - a) + (b1 - b) * (b1 - b));
		y = sqrt((a2 - a) * (a2 - a) + (b2 - b) * (b2 - b));
		z = sqrt((a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2));
		if ((x * x + y * y == z * z || x * x + z * z == y * y || y * y + z * z == x * x) && x!=0 && y!=0 && z!=0)
			cout << x<<' ' << y <<' '<< z<<endl ;
	}
}
void fun3(char* s, char* s1) {
	 
	int n,i=0;
	cin >> n;
	while (s[i] > 0 && s[i]!=s1[n]) {
		
		i++;
	}
	if (s[i] > 0) {
		cout << i;
	}
}
bool ifpal(char* s, int a, int b) {
	bool p = true;
	for (int i = 0; i <= (b-a)/2; i++) {
		//cout << s[a + i] << ' ' << s[b - i - 1] << endl;
		if (s[a + i] != s[b - i-1]) {
			p = false; break;
	}

	}
	//cout << endl;
	return p;
}
void fun4(char* s)
{
	 
	int h = 0;
	while (s[h] >= 0)
		h++;
	h--;
	int i;
	for ( i = 0; i < h ; i++) {
		if (ifpal(s, i, h)) {
			 break;
		}
	}
	int j = 0;
	while (s[j] > 0) {
		cout << s[j];
		j++;
	}
	for (int j = i-1; j >= 0; j--) {
		cout << s[j];
	}
}
//
int partition(int** a, int start, int end,int n)
{
	int pivot = a[n][end];

	int P_index = start;
	int i, t; 

	for (i = start; i < end; i++)
	{
		if (a[n][i] <= pivot)
		{
			for (int j = 0; j <= n; j++) {
				t = a[j][i];
				a[j][i] = a[j][P_index];
				a[j][P_index] = t;
				P_index++;
			}
		}
	}
	for (int j = 0; j <= n; j++) {
		t = a[j][end];
		a[j][end] = a[j][P_index];
		a[j][P_index] = t;
	}
	return P_index;
}
void Quicksort(int** a, int start, int end,int n)
{
	if (start < end)
	{
		int P_index = partition(a, start, end,n);
		Quicksort(a, start, P_index - 1,n);
		Quicksort(a, P_index + 1, end,n);
	}
}
//
void fun5() {
	int n, k, s;
	cin >> n >> k;
	int** m = new int* [n+1];
	for (int i = 0; i <= n; i++)
		m[i] = new int[k];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++)
			cin >> m[i][j];
	for (int j = 0; j < k; j++) {
		s = 0;
		for (int i = 0; i < n; i++)
		{
			if (m[i][j] < 0 && m[i][j] % 2 == -1)
				s -= m[i][j];
		}
		m[n][j] = s;
	}
	int y;
	Quicksort(m, 0, k-1, n);
	/*for (int i = 0; i < k; i++) {
		for (int j = i + 1; j < k; j++) {
			if (m[n][i] > m[n][j]) {
				for (int g = 0; g <= n; g++) {
					y = m[g][i];
					m[g][i] = m[g][j];
					m[g][j] = y;
				}
			}
		}
	}*/
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
	return;
}
int main()
{
	fun5();
}

