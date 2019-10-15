#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//) Задаються n пар чисел, які задають багатокутник.Написати програму
//перевірки його опуклості
void vabka2task2(vector <double> a, vector <double> b, vector <double> c, double x, double y, double z) {
	double k,m,l; double n;
	for (int i = 0; i < 8; i++)
	{
		k = b.at(i) * cos(x) + c.at(i) * sin(x);
		m = c.at(i) * cos(x) - b.at(i) * sin(x);
		c.at(i) = m;b.at(i) = k;
	}
	for (int i = 0; i < 8; i++)
	{
		k = a.at(i) * cos(y) - c.at(i) * sin(y);
		m = a.at(i) * sin(y) + c.at(i) * cos(y);
		c.at(i) = m;a.at(i) = k;
	}
	for (int i = 0; i < 8; i++)
	{
		k = a.at(i) * cos(z) - b.at(i) * sin(z);
		m = a.at(i) * sin(z) + b.at(i) * cos(z);
		b.at(i) = m;a.at(i) = k;
	}
	for (int i = 0; i < 8; i++) {
		cout << a.at(i) << ' ' << b.at(i) << ' ' << c.at(i) << endl;
	}
}
void vabka2task1(vector <double> a, vector <double> b) {
	double x, y,x1,y1,x2,y2,x3,y3,A,B,C; 
	x = a.at(0);
	y = b.at(0); 
	x1 = a.at(1);
	y1 = b.at(1);
	x2 = a.at(2); 
	y2 = b.at(2); 
	x3 = a.at(3); 
	y3 = b.at(3); 
	
	for (int i = 0; i < a.size(); i++) {
		/*cout << x << ' '<<y << endl;
		cout << x1 << ' '<<y1 << endl;
		cout << x2 << ' '<<y2 << endl;
		cout << x3 << ' '<<y3 << endl;
		cout << endl;*/
		A = y1 - y2;
		B = x2 - x1;
		C = y1 * (x1 - x2) - x1 * (y1 - y2);
		if ((x * A + y * B + C) * (x3 * A + y * B + C) < 0) {
			cout << "Not a convex";
			return ;
		}
		
		x = x1; y = y1; x1 = x2; y2 = y3; y1 = y2; x2 = x3;
		x3 = a.at((i+4)%a.size()); 
		y3 = b.at((i + 4) % a.size());
	}
	cout << "Convex";
}
int main()
{
	double n,x,y;
	cin >> n;
	vector <double> a, b;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		a.push_back(x);
		b.push_back(y);
	}
	vabka2task1(a, b);
	a.clear(); b.clear();
	vector <double> c;
	for (int i = 0; i < 8; i++)
	{
		cin >> n >> x >> y;
		a.push_back(n);
		b.push_back(x);
		c.push_back(y);
	}		cin >> n >> x >> y;
	vabka2task2(a, b, c, n, x, y);
	
	return 0;
}