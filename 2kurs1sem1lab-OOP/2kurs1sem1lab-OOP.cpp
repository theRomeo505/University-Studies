// 2kurs1sem1lab-OOP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include"Date.h"
#include "Duration.h"
#include <iostream>
using namespace std;
template <class T>
bool compare(T a, T b)
{
    if (a < b)
        return 0;
    else
        return 1;
}
/*bool compare(Date *a, Date *b) {
    if (a->year < b->year)
        return 0;
    if (a->year > b->year)
        return 1;
    if (a->month < b->month)
        return 0;
    if (a->month > b->month)
        return 1;
    if (a->day < b->day)
        return 0;
    if (a->day > b->day)
        return 1;
    return 0;
}*/
template <class T>
class Node {
    public:
        T element;
        Node* next;
        static Node* sort(Node* head) {
            Node* newlist;
            newList->element = head->element;
            newList->next = NULL;
            Node* i, j;
            i = head->next;
            while (i != NULL) {
                j = newlist;
                while (j != NULL) {
                    if (compare(j->element, i->element) && (j->next==NULL || compare(i->element,j->next->element))) {
                        Node* temp=j->next;
                        j->next=i;
                        i->next=temp;
                    }
                    j=j->next;
                }
                i = i ->next;
            }
            return newList;
        }
};


int main()
{
    Date d(27, 7, 2001, 12, 0, 0);
    Date d1(27, 8, 2001, 12, 0, 0);
    d.add(Duration(d,d1));
    Duration dur(d, d1);
    d.show();
    cout << d.isRight();
}
