﻿// labka9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
using namespace std;
struct matrE {
	int x;
	int y;
	double s;
	matrE* next;
};
struct matr {
	matrE* start;
	matrE* end;
};
// posl-zvyaz
struct matrE1 {
	double s;
	int count;
	matrE1* next;
};
struct matr1 {
	matrE1* start;
	matrE1* end;
};
/// posl
matr readM(string filename) { // def
	ifstream f(filename, ios::beg);
	int y;

	matr m; m.start = NULL;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			f >> y;  //cout << y << ' ';
			
			if (y != 0) {
				if (m.start == NULL) {
					matrE* e = new matrE;
					e->next = NULL;//
					e->x = i;
					e->y = j;
					e->s = y;
					//cout << e->s; system("pause");
					e->next = NULL;
					m.start = e;
					m.end = e;
				}
				else {
					matrE* e = new matrE;
					e->next = NULL;
					e->x = i;
					e->y = j;
					e->s = y;
					e->next = NULL;
					m.end->next = e;
					m.end = e;
				}
			}
		}
	}
	return m;
}
matr1 readM1(string filename) {
	ifstream f(filename);
	int b, p = 0, k = 0; matr1 m; m.start = NULL; m.end = NULL;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			f >> b; //cout << b;
			if (b == p) {
				k++;
			}
			else {
			//	cout << p << ' ' << k;
				//system("pause");
				if (m.start == NULL) {
					matrE1* e = new matrE1;
					e->count = k;
					e->next = NULL;
					e->s = p;
					m.start = e;
					m.end = e;
				}
				else {
					matrE1* e = new matrE1;
					e->count = k;
					e->next = NULL;
					e->s = p;
					m.end->next=e;
					m.end = e;
				}
				k = 1;
				p = b;
			}
		}
	}
	return m;
}
void printM(matr m) {
	matrE* k = m.start;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (k != NULL && k->x == i && k->y == j) {
				cout << k->s << ' ';
				k = k->next;
			}
			else {
				//cout << "0 ";
			}
		}
		cout << endl;
	}
}
void printM1(matr1 m) {
	matrE1* k = m.start;
	//int i = 0;
	while (k != NULL) {
		for (int i = 0; i < k->count; i++)
		{
			cout << k->s << ' ';
			i++;
			if (i == 100) {
				i = 0; cout << endl;
			}
		}
		k = k->next;
	}
}
matr addM(matr a, matr b) {
	matr c; c.start = NULL; c.end = NULL;
	//matrE *x = a.start,  *y = b.start, *e=new matrE;
	/*
	while (x != NULL || y != NULL) {
		//cout << 'l';
		if (y==NULL || x->x < y->x ) {
			if (c.start == NULL)
			{
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				x = x->next;
				cout << '1';
			}
			else {
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				x = x->next;
				cout << '1';

			}
		}
		else if (x==NULL || x->x > y->x  ) {
			if (c.start == NULL)
			{
				e->s = y->s;
				e->x = y->x;
				e->y = y->y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				y = y->next;
				cout << '2';

			}
			else {

				e->s = y->s;
				e->x = y->x;
				e->y = y->y;				e->next = NULL;
				c.end->next = e;
				c.end = e;
				y = y->next;
				cout << '2';

			}
		}
		else if (x->y > y->y) {
			if (c.start == NULL)
			{
				e = y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				y = y->next;
				cout << '3';

			}
			else {
				e = y;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				y = y->next;
				cout << '3';

			}
		}
		else if (x->y < y->y) {
			if (c.start == NULL)
			{
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				x = x->next;
				cout << '4';

			}
			else {
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				x = x->next;
				cout << '4';
			}
		}
		else {
			//cout << 'l';
			if (c.start == NULL)
			{
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->s += y->s;
				//cout << e->s; system("pause");
				e->next = NULL;
				
				c.start = e;
				c.end = e;
				cout << endl;
				printM(c);
				x = x->next;
				y = y->next;
				//cout << '5';

			}
			else {
				//cout << 'k';
				e->s= x->s; 
				e->x = x->x;
				e->y = x->y;
				e->s += y->s;
				e->next = NULL;

				c.end->next = e;
				c.end = e;/// shoto ne tak
				printM(c);
				system("pause");
				x = x->next;
				y = y->next;
				//cout << '6';
				//cout << c.end->s; system("pause");
			}
		}
		*/
	//printM(c); 
double m[100][100], /*mm[100][100]*/m1[100][100];

for (int i = 0; i < 100; i++) {
	for (int j = 0; j < 100; j++)
	{
		m[i][j] = 0;
		//mm[i][j] = 0;
		m1[i][j] = 0;
	}
}
matrE* e = b.start;
while (e != NULL) {
	m[e->x][e->y] = e->s;
	e = e->next;
}
e = a.start;
while (e != NULL) {
	m1[e->x][e->y] = e->s;
	e = e->next;
}
// = new matrE;
for (int i = 0; i < 100; i++) {
	for (int j = 0; j < 100; j++)
	{
		if (m[i][j] != 0 || m1[i][j] != 0) {
			matrE *k=new matrE;
			k->x = i;
			k->y = j;
			k->s = m[i][j] + m1[i][j];
			k->next = NULL;
			if (c.start == NULL) {
				c.start = k;
				c.end = k;
				//cout << "k";

			}
			else {
				c.end->next = k;
				c.end = k;
			}
			//printM(c); system("pause");

		}
	}
}
	return c;
}
matr multM(matr a, matr b) {
	double m[100][100], mm[100][100], m1[100][100];
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++)
		{
			m[i][j] = 0;
			mm[i][j] = 0;
			m1[i][j] = 0;
		}
	}
	cout << 'k';

	matrE* e = b.start;
	while (e != NULL) {
		m[e->x][e->y] = e->s;
		e = e->next;
	}
	e = a.start;
	while (e != NULL) {
		m1[e->x][e->y] = e->s; e = e->next;
	}
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			for (int g = 0; g < 100; g++) {
				mm[i][j] += m[i][g] * m1[g][j];
			}
		}
	}
	matr mn; mn.start = NULL,mn.end=NULL;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			for (int g = 0; g < 100; g++) {
				//cin >> y;
				if (m[i][g] != 0 && m1[g][j] != 0)
				{
					mm[i][j] += m[i][g] * m1[g][j];
				}
			}
		}
	}
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (mm[i][j]!=0) cout << mm[i][j]/2 << ' ';
		}cout << endl;
	}
	return mn;
}
int main()
{
	//matr m = readM("matrixLight");
	//cout << "k";
	//printM(m);
	ofstream f("popl");    
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (j % 100 == 50) f << 5 << ' ';
			else f << 0 << ' ';
		}
	}
	//f.close();
	matr m = readM("popl"),mm=readM("popl");
	printM(m);
	system("pause");
	printM(mm);
	system("pause");
	matr r = addM(m, mm);

	//system("pause");
	//cout << "k";
	printM(r);
	system("pause");
	r=multM(m, mm);
	printM(r);
}

