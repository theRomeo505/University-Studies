// labka3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
double stepp(vector <double> n, vector <int> m, double z) {
	
	for (int i = 0; i < n.size() - 1; i++) {
		if (n[i] == 0)
			n[i] = z;
	}
	for (int j = 0; j < m.size(); j++) {
			if (m[0] == 4) {
				m.erase(m.begin());
				n[0] = pow(n[0], n[1]);
				n.erase(n.begin() + 1);
			}
		}for (int j = 0; j < m.size(); j++) {
			if (m[0] == 3) {
				m.erase(m.begin());
				n[0] = n[0] * n[1];
				n.erase(n.begin() + 1);
			}if (m[0] == 2) {
				m.erase(m.begin());
				n[0] = n[0] / n[1];
				n.erase(n.begin() + 1);
			}
		}for (int j = 0; j < m.size(); j++) {
			if (m[0] == 1) {
				m.erase(m.begin());
				n[0] = n[0] - n[1];
				n.erase(n.begin() + 1);
			}if (m[0] == 0) {
				m.erase(m.begin());
				n[0] = n[0] + n[1];
				n.erase(n.begin() + 1);
			}

		}
		return n.at(0);
}
void labka3task1() {
	string s;
	cin >> s;
	int i = 0, p; double a, b, step;
	cin >> a >> b>>step;
	vector <double> n;
	vector <int> m;
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i])) {
			n.push_back(s[i] - 48);
			i++;
			do {
				n.at(n.size() - 1) *= 10;
				n.at(n.size() - 1) += s[i] - 48;
			} while (isdigit(s[i]));

		}
		if (s[i] == 'x') {
			n.push_back(0);
		}

		if (s[i] == '+') {
			m.push_back(0);
		}
		if (s[i] == '-') {
			m.push_back(1);
		}
		if (s[i] == '/') {
			m.push_back(2);
		}
		if (s[i] == '*') {
			m.push_back(3);
		}
		if (s[i] == '^') {
			m.push_back(4);
		}
	}
	double ingr = 0;
	for (double i = a; i < b; i+=step) {
		ingr+=(stepp(n, m, i)+stepp(n,m,i+step))/2*step;
	}
	cout << ingr;
}
double poh(vector <double> n, vector <int> m, int a,int k,double h) {
	// x_h-x_0/h x_2h-x_h/h = x0 2xh - x2h
	vector <double> p;
	for (double i = a; i <= a + h * k; i += h) {
		p.push_back(stepp(n, m, i));
	}
	for (int i = k-1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			p[j] = p[j + 1] - p[j];
		}
	}
	
	return p[0]/pow(h,k);
}
void labka3task2() {
	string s;
	cin >> s;
	int i = 0, p; double a, b, step;
	vector <double> n;
	vector <int> m;
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i])) {
			n.push_back(s[i] - 48);
			i++;
			do {
				n.at(n.size() - 1) *= 10;
				n.at(n.size() - 1) += s[i] - 48;
			} while (isdigit(s[i]));

		}
		if (s[i] == 'x') {
			n.push_back(0);
		}

		if (s[i] == '+') {
			m.push_back(0);
		}
		if (s[i] == '-') {
			m.push_back(1);
		}
		if (s[i] == '/') {
			m.push_back(2);
		}
		if (s[i] == '*') {
			m.push_back(3);
		}
		if (s[i] == '^') {
			m.push_back(4);
		}
	}
	double x, nn,h, sum = 0, ss;
	cin >> x >> a >> nn>>h;
	for (int i = 0; i < nn; i++) {
		ss = poh(n, m, a,nn, h) * pow(x - a, i);
		for (int j = 1; j <= i; j++)
			ss /= j;
		sum += ss;
	}
	cout << sum;
}
int main()
{
	labka3task1();
}
