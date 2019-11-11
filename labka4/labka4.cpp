// labka4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
	char* m = new char[1000];
	char* n = new char[1000];
	cin.getline(m, 1000);
	cin.getline(n, 1000);
	int i = 0,g=0; bool t = true;
	while (m[i] > 0 && n[g]>0) {
		if (m[i + 1] < 0) {
			if (m[i] == '*')
				break;
			else {
				if (n[g + 1] > 0)
					t = false;
				else if (m[i] != '?' && m[i] == n[g])
					break; else if (m[i] != '?') {
					t = false; break;
				}
				break;
			}
		}
		if (m[i] != '?' && m[i] != '*') {
			if (n[g] != m[i]) {
				t = false; break;
			}
			g++;
		}
		if (m[i] == '?')
			g++;
		if (m[i] == '*' && m[i+1]>0) {
			while (n[g] != m[i + 1] && n[g]>0)
				g++;
			g++;
		}
		
		i++;
	}
	cout << t;
}


