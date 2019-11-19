// labka6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;
int main()
{
	char* m = new char[256];
	cin.getline(m,256);
	vector <int> equation;
	int y = 0,l=0;
	while (m[l] > 0)
	{
		l++;
	}

	for (int i = 0; i < l; i++) {
		if (m[i] == ' ' && m[i-1]>=0)
		{
			equation.push_back(y);
			y = 0;
		}
		
		
		if (m[i] == '+') {
			equation.push_back(-1); 
		}if (m[i] == '-') {
			equation.push_back(-2); 
		}if (m[i] == '*') {
			equation.push_back(-3); 
		}if (m[i] == '/') {
			equation.push_back(-4); 
		}if (m[i] == '^') {
			equation.push_back(-5); 
		}
		else {
			y *= 10;
			y += m[i] - 48;
		}
	}
	for (int i = 0; i < equation.size(); i++) {
			cout << m[i];
	}
	for (int i = l - 1; i--; i >= 0) {

	}
}

