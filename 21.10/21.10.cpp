// 21.10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int n, k;
	cin >> n;
	int** m = new int* [n];
	for (int i = 0; i < n; i++)
	{
		m[i] = new int[2];
		cin >> m[i][0] >> m[i][1];
	}
	cin >> k;
	int** b = new int* [k];
	for (int i = 0; i < k; i++)
	{
		b[i] = new int[2];
		cin >> b[i][0] >> b[i][1];
	}
	double cx, cy, a1, b1, c1, r, p,min=9999999;
	bool pp;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int g = j + 1; g < n; g++) {
				if ((m[i][0] - m[j][0]) * (m[g][1] - m[i][1]) - (m[i][1] - m[j][1]) * (m[g][0] - m[i][0]) == 0)
				{
					break;
				}
				cx = -1 * ((m[i][1] - m[j][1]) * (m[g][0] * m[g][0] + m[g][1] * m[g][1]) + (m[j][1] - m[g][1]) * (m[i][0] * m[i][0] + m[i][1] * m[i][1]) + (m[g][1] - m[i][1]) * (m[j][0] * m[j][0] + m[j][1] * m[j][1])) / (2 * ((m[i][0] - m[j][0]) * (m[g][1] - m[i][1]) - (m[i][1] - m[j][1]) * (m[g][0] - m[i][0])));
				cy = -1 * ((m[i][0] - m[j][0]) * (m[g][0] * m[g][0] + m[g][1] * m[g][1]) + (m[j][0] - m[g][0]) * (m[i][0] * m[i][0] + m[i][1] * m[i][1]) + (m[g][0] - m[i][0]) * (m[j][0] * m[j][0] + m[j][1] * m[j][1])) / (2 * ((m[i][0] - m[j][0]) * (m[g][1] - m[i][1]) - (m[i][1] - m[j][1]) * (m[g][0] - m[i][0])));
				a1 = sqrt(pow(m[i][0] - m[j][0], 2) + pow(m[i][1] - m[j][1], 2));
				b1 = sqrt(pow(m[g][0] - m[j][0], 2) + pow(m[g][1] - m[j][1], 2));
				c1 = sqrt(pow(m[i][0] - m[g][0], 2) + pow(m[i][1] - m[g][1], 2));
				p = a1 + b1 + c1; p /= 2;
				r = (a1 * b1 * c1) / (4 * sqrt(p * (p - a1) * (p - b1) * (p - c1)));
				pp = false;
				for (int h = 0; h < k; h++) {
					if (pow(b[h][0] - cx, 2) + pow(b[h][1] - cy, 2) > pow(r, 2)) {
						pp = true;
					}
				}
				if (!pp)
				{
					if (r < min) {
						min = r;
					}
				}
			}
		}

		
	}
	if (min != 9999999)
			cout << min;
		else
			cout << "no";
}

