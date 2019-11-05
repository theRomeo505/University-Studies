// 04.11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
using namespace std;
char** fun1() {
	char** m = new char* [100];
	for (int i = 0; i < 100; i++)
		m[i] = new char[100];
	char* s = new char[1000];
	cin.getline(s,1000);
	int i = 0,j=0,g=0;
	while (s[i] > 0) {
		if (s[i] == ' ') {
			g++; j = 0;
		}
		else {
			m[g][j] = s[i];
			j++;
		}
		i++;
	}
	i = 0,j=0;
	

	i = 0; j = 0; char* r = new char[100];
	while (m[i][0] > 0) {
		j = i + 1;
		while (m[j][0] > 0) {
			// compare 
			g = 0;
			while (m[i][g] == m[j][g] && m[i][g]>0 && m[j][g]>0) {
				g++;
			}
			if (m[i][g] > m[j][g])
			{
				g = 0;
				while (m[i][g] > 0) {
					r[g] = m[i][g];
					g++;
				}
				while (r[g + 1] > 0)
				{
					r[g + 1] = '\0'; g++;
				}
				g = 0;
				while (m[j][g] > 0 ) {
					m[i][g] = m[j][g];
					g++;
				}
				while (m[i][g + 1] > 0)
				{
					m[i][g + 1] = '\0'; g++;
				}
				g = 0;
				while (r[g] > 0) {
					m[j][g] = r[g];
				}
				while (m[j][g + 1] > 0) {
					m[j][g + 1] = '\0';
					g++;
				}


			}
			j++;
		}
		i++;
	}
	while (m[i][0] > 0) {
		j = 0;
		while (m[i][j] > 0)
		{
			cout << m[i][j]; j++;
		}
		cout << endl;
		i++;
	}
	return m;
}
int main()
{
	char** m = new char* [100];
	for (int i = 0; i < 100; i++)
		m[i] = new char[100];
	m = fun1();
	int i = 0, j = 0;
	i = rand();
}

