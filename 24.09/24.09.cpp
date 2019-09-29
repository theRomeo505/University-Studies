// 24.09.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
void rect(int n, int m)
{
	for (int i = 0; i < n; i++)
		cout << "*";
	cout << endl;
	for (int i = 0; i < m - 2; i++)
	{
		cout << "*";
		for (int j = 0; j < n - 2; j++)
			cout << ' ';
		cout << "*" << endl;

	}
	for (int i = 0; i < n; i++)
		cout << "*";
	cout << endl;
}
void tria(int a, int b)
{

	cout << "*" << endl;

	for (int i = 0; i < a - 2; i++) {
		cout << "*";
		for (int j = 0; j < (i+1) * (b-1) / a; j++)
			cout << ' ';
		cout << '*';
		cout << endl;
	}
	for (int i = 0; i < b; i++)
		cout << "*";
	cout << endl;
}
void eqtria(int h, int l)
{
	if (l % 2 == 0)
	{
		cout << "no";
		return;
	}
	int k = 0;
	if ((l - 1) % (h-1) == 0)
	{
		 k = (l - 1) / (h-1)-1;
	}
	else
	{
		cout << "No"; return;
	}

	for (int j = 0; j < l / 2 ; j++)
		cout << ' ';
	cout << "*" << endl;
	for (int i = 0; i < h-2; i++) {
		for (int j = 0; j < l/2-k*(i+1);j++)
			cout << ' ';
		cout << "*";
		for (int j = 0; j < l- 2*(l / 2 - k * (i+1)) -2; j++)
			cout << ' ';
		cout << '*'<<endl;

	}
	for (int i = 0; i < l; i++)
		cout << '*';
	cout << endl;
}
void rombus(int h1,int l) {
	if (l % 2 == 0)
	{
		cout << "no";
		return;
	}
	int h = h1 / 2 ;
	int k = 0;
	if ((l - 1) % (h - 1) == 0)
	{
		k = (l - 1) / (h - 1)-1;
	}
	else
	{
		cout << "No"; return;
	}

	for (int j = 0; j < l / 2; j++)
		cout << ' ';
	cout << "*" << endl;
	for (int i = 0; i < h - 2; i++) {
		for (int j = 0; j < l / 2 - k * (i)-1; j++)
			cout << ' ';
		cout << "*";
		for (int j = 0; j < l - 2 * (l / 2 - k * (i)-1) - 2; j++)
			cout << ' ';
		cout << '*' << endl;

	}
	cout << "*";
	for (int i = 0; i < l - 2; i++)
		cout << ' ';
	cout << "*" << endl;

	for (int i = h-3; i >=0; i--) {
		for (int j = 0; j < l / 2 - k * (i)-1; j++)
			cout << ' ';
		cout << "*";
		for (int j = 0; j < l - 2 * (l / 2 - k * (i)-1) - 2; j++)
			cout << ' ';
		cout << '*' << endl;

	}
	for (int j = 0; j < l / 2; j++)
		cout << ' ';
	cout << "*" << endl;
}
int main()
{
	int x, y;
	cin >> x >> y;
	rect(x, y);
	cin >> x >> y;
	tria(x, y);
	cin >> x >> y;
	eqtria(x, y);
	cin >> x >> y;
	rombus(x, y);
}
