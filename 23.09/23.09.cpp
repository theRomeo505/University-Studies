// 23.09.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
void out(double x, double y, bool p) {
	if (p)
		cout << '|' << x << '\t' << (int) y << '|' << endl;
	else
	cout << '|' << x << '\t' << y << '|' << endl;
}
void fun(double a, double b, double c, double start, double end, double dx, bool p) {
if (a < 0 && c != 0)
	{
		for (double i = start; i <= end; i += dx)
			out(i, a * i * i + b * i + c, p);
	}
	else if (a > 0 && c == 0) {
		for (double i = start; i <= end; i += dx)
			if (i!=c) out(i, -1 * a / (i - c), p);			
	}
	else {
		for (double i = start; i <= end; i += dx)
		{
			out(i, a * (i + c), p);
		}
	}
}
int main()
{
	double a, b, c, start, end, dx;
	cin >> a >> b >> c >> start >> end >> dx;
	int A =(int) a, B=(int)b, C=(int)c;
	if (dx == 0)
	{
		cout << "stupido";
		return 0;
	}

	if (!(A & (B | C)))
		fun(a, b, c, start, end, dx, true);
	else
		fun(a, b, c, start, end, dx, false);
}

