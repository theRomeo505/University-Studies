// 28.10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;
void task1() {
	char *s=new char[1000];

	cin.getline(s,1000);
	int k = 1, i = 0;
	while (s[i]>=0){
	if (s[i] == ' ') {
			k++;
		}
	i++;
	}
	cout << k << "words";
}
void task2() {
	char* s = new char[1000];

	cin.getline(s, 1000);
	int k = 0,k1=0,i=0;
	while (s[i] >= 0) {
		if (isdigit(s[i]))
			k++;
		if (isalpha(s[i]))
			k1++;
		i++;
	}
	cout << "digits" << k << endl;
	cout << "letters" << k1;
}
void task3() {
	char* s = new char[1000];char* s0 =new char[0];

	cin.getline(s, 1000);
	char** m = new char* [1000];
	for (int i = 0; i < 1000;i++)
		m[i] = new char[1000];
	int j = 0,g=0;
	while (s[j] >= 0) {
		//cout << s[j] << "sj" << endl;
		if (s[j] != ' ') {
			s0 += s[j];
			//cout << s0 << endl;
		}
		else {
			//cout << s0<< ' ' ;
			int i = 0;
			for (int i=0;i<g;i++)
			if (strcmp(s0,m[i])==0)
				{
					cout << "yes"; return ;
				}
		while (s0[i] >= 0) {
			m[g][i] = s0[i]; i++;
		}
		g++;
		s0 = new char[0];
		}
		
		
		
		j++;
	}
	/////
	//for (int i=0;i<g;i++)
	for (int i = 0; i < g; i++)
		if (strcmp(s0, m[i]) == 0)
		{
			cout << "yes"; return;
		}
	cout << "no";
}
int main()
{
	
	task3();
}
