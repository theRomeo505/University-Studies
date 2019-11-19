// labka5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
using namespace std;
void labka5task1(){
	ifstream f("laba.txt");
	char* s = new char[1000]; int i = 0;
		while (!f.eof()) {
			f.read(s, 256);
			i = 0;
			while (s[i] == ' ') {
				i++;
			}cout << '\t';
			while (s[i] > 0) {
				if (!(s[i] == ' ' && s[i - 1] == ' ')) {
					cout << s[i];
				}
				if (s[i] == '\n') {
					cout <<'\t';
				}
				s++;
			}
		}
}
void labka5task2() {
	ofstream f("laba");
	int n, x, y; double s;
	cin >> n;
	int* m = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> m[i]; f << m[i];
	}
	f.close();
	ifstream f1("laba");
	f1 >> x; int i = 1;
	while (!f1.eof) {
		f1 >> y;
		s *= (double)i / (i + 1);
		s += x * y / (i + 1);
		x = y;
	}
}
int main()
{
	labka5task1();
}

