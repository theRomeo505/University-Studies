// labka3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
using namespace std;
void labka3task1() {
	string s;
	cin >> s;
	int i = 0,p;
	while (i < s.length()) {
		p = 0;
		while (isdigit(s.at(i))) {
			p *= 10;
			p += atoi(&s[i]);
			cout << p;
			i++;
		}
		i++;
	}
}
int main()
{
	labka3task1();
}
