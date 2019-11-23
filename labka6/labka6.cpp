// labka6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
int main()
{
	char* m = new char[256];
	cin.getline(m,256);
	vector <double> equation;
	double y = 0; int  l = 0; bool flazok=0;
	while (m[l] > 0)
	{
		l++;
	}
	//cout << l;
	for (int i = 0; i < l; i++) {
		if (m[i] == ' ' )
		{
			if (isdigit(m[i - 1]))
			{
				if (flazok)
				equation.push_back(-1*y);
				else
				equation.push_back(y);
				y = 0;
				flazok = 0;
			}
		}else		
		if (m[i] == '+') {
			if (!isdigit(m[i+1]))
			equation.push_back(-0.1); 
		}else if (m[i] == '-') {
			if (isdigit(m[i + 1]))
				flazok = 1;
			else
			equation.push_back(-0.2); 
		}else if (m[i] == '*') {
			equation.push_back(-0.3); 
		}else if (m[i] == '/') {
			equation.push_back(-0.4); 
		}else if (m[i] == '^') {
			equation.push_back(-0.5); 
		}
		else {
			y *= 10;
			y += (double)(m[i] - 48);
		}
	}//last
	//cout << equation.size();
//	while (equation.size() > 1) {
	for (int i = 0; i < equation.size(); i++) {
		cout << equation[i] << ' ';

	}cout << endl;
		for (int i = equation.size(); i--; i >= 2) {
			//cout << equation.size() << endl;
			//cout << "i" << i << endl;
			if ((equation[i]>-1 && equation[i] < 0) && (equation[i - 1] >= 0 || equation[i-1]<=-1) && (equation[i - 2] >= 0 || equation[i - 2] <= -1) ){
				
				
				if (equation[i] == -0.1) {
					equation[i - 2] += equation[i - 1];
					equation.erase(equation.begin() + i - 1); equation.erase(equation.begin() + i - 1);
					
				}else if (equation[i] == -0.2) {
					equation[i - 2] -= equation[i - 1];
					equation.erase(equation.begin() + i - 1); equation.erase(equation.begin() + i - 1);
				}else if (equation[i] == -0.3) {
					equation[i - 2] *= equation[i - 1];
					equation.erase(equation.begin() + i - 1); equation.erase(equation.begin() + i - 1);
				} else 	if (equation[i] == -0.4) {
					equation[i - 2] = (int)equation[i-2]/equation[i - 1];
					equation.erase(equation.begin() + i - 1); equation.erase(equation.begin() + i - 1);
				} else 	if (equation[i] == -0.5) {
					equation[i - 2] = pow(equation[i - 2], equation[i - 1]);
					equation.erase(equation.begin() + i - 1); equation.erase(equation.begin() + i - 1);
				}
				
				
				i = equation.size();

			}
			
		}
		if (equation.size() == 1)
		{
			cout << equation[0];
			return 0;
		}
	//}
}

