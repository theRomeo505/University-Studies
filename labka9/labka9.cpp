// labka9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
matr readM(int n, char filename[20]) {
	ifstream f(filename);
	int y;
	
	matr m;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			cin >> y;
			if (y != 0) {
				if (m.start == NULL) {
					matrE *e;
					e->next = NULL;
					e->x = i;
					e->y = j;
					e->s = y;
					e->next = NULL;
					m.start = e;
					m.end = e;
				}
				else {
					matrE *e;
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
void printM(matr m) {
	matrE *k= m.start;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (k->x == i && k->y == j) {
				cout << k->y << ' ';
				k = k->next;
			}
			else {
				cout << "0 ";
			}
		}
		cout << endl;
	}
}
matr addM(matr a, matr b) {
	matr c; c.start = NULL;
	matrE* x = a.start, * y = b.start,*e;
	while (&a != NULL && &b != NULL) {
		if (x->x < y->x) {
			if (c.start == NULL)
			{
				e = x;
				e->next = NULL;
				c.start = e;
				c.end = e;
				x = x->next;
			}
			else {
				e = x;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				x = x->next;
			}
		}
		else if (x->x>y->x) {
			if (c.start == NULL)
			{
				e = y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				y = y->next;
			}
			else {
				e = y;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				y = y->next;
			}
		}
		else if (x->y>y->y) {
			if (c.start == NULL)
			{
				e = y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				y = y->next;
			}
			else {
				e = y;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				y = y->next;
			}
		}
		else if (x->y<y->y){
			if (c.start == NULL)
			{
				e = x;
				e->next = NULL;
				c.start = e;
				c.end = e;
				x = x->next;
			}
			else {
				e = x;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				x = x->next;
			}
		}
		else {
			if (c.start == NULL)
			{
				e = x;
				e->s += y->s;
				e->next = NULL;
				c.start = e;
				c.end = e;
				x = x->next;
				y = y->next;
			}
			else {
				e = x;
				e->s += y->s;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				x = x->next;
				y = y->next;
			}
		}

	}
}
int main()
{
    std::cout << "Hello World!\n";
}

