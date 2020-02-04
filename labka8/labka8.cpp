// labka8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

struct elem {
	double koef;
	double power;
	elem* next;
};
struct polinom {
	elem* first;//null
	elem* last;
};
bool isempty(polinom m) {
	return (m.first == NULL);
}
void addElem(polinom &pol, double koef, double power) {
	elem* e = new elem(); bool p = false;
	e->koef = koef;
	e->power = power;
	e->next = NULL;
	if (isempty(pol)) {
		pol.first = e;
		pol.last = e;
	}
	else
	{
		elem* e1 = pol.first;
		//cout << e1->power << endl;
		if (e1->power > e->power) {
			e->next = pol.first;
			pol.first = e;
		}
		else {
			if (e1->power < e->power && (e1->next != NULL && e1->next->power > e->power)) {
				e->next = e1->next;
				e1->next = e;

			}
			else {
				while (e1->next != NULL) {
					e1 = e1->next;
					if (e1->power < e->power && (e1->next != NULL && e1->next->power > e->power)) {
						e->next = e1->next;
						e1->next = e;
						p = true; break;
					}
				}
				if (!p) {
					pol.last->next = e;
					pol.last = e;
				}
			}
		}
	}
}
void showList(polinom m) {
	elem* e=m.first;
	cout << e->koef<<' '<<(*e).power << endl;
	while (e->next != NULL) {
		e = e->next;
		cout <<e->koef<<' '<< e->power << endl;
	}
	cout << endl;
}
bool addKoef(polinom a, double koef, double power) {
	elem* e = a.first;
	//cout << "l";
	while (e != NULL) {
		if (e->power==power)
		{
			e->koef += koef; return 1;
		}
		e = e->next;
	}
	return 0;
}
polinom multP(polinom a, polinom b) {
	polinom c;
	c.first = NULL;
	c.last = NULL;
	elem* e = a.first, * r = b.first;
	while (e != NULL) {
		r = b.first;
		while (r != NULL) {
			
			if (!addKoef(c, e->koef * r->koef, e->power + r->power)) {
				//cout << "k";
				addElem(c, e->koef * r->koef, e->power + r->power);
			}
		//	showList(c);
			r = r->next;
		}
		e=e->next;
	}
	return c;
}

int main()
{
	polinom pol, po, p; pol.first = NULL; pol.last = NULL; po.first = NULL; po.last = NULL; p.first = NULL; p.last = NULL;
	addElem(pol, 1, 2);	//showList(pol);
	addElem(pol, 2, 1); //showList(pol);
	addElem(pol, 1, 0); showList(pol);
	addElem(po, 1, 2); //showList(po);
	addElem(po, 2, 1); //showList(po);
	addElem(po, 1, 0); showList(po);


	p=multP(pol, po);
	showList(p);
}

