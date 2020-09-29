// 2kurs1sem1lab-OOP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include"Date.h"
#include "Duration.h"
#include <iostream>
#include <ostream>

std::ostream& operator<<(std::ostream& out, Date& date) {
    out << date.day << "/" << date.month << "/" << date.year << " " << date.hour<<' '<<date.min<<' '<<date.sec<<std::endl;
    return out;
}
bool compare(Date a, Date b) {
    if (a.year < b.year)
        return 0;
    if (a.year > b.year)
        return 1;
    if (a.month < b.month)
        return 0;
    if (a.month > b.month)
        return 1;
    if (a.day < b.day)
        return 0;
    if (a.day > b.day)
        return 1;
    return 0;
}
template <class T>
bool compare(T a, T b)
{
    //if (T==Date)
    if (a < b)
        return 0;
    else
        return 1;
}

template <class T>
class Node{
public:
    T element;
    Node* next;
    //Node(T el) { this->element = el; }
};
template <class T>
class List {
    public:
        Node<T>* start=new Node<T>;
        List<T>(T el) { this->start->next = NULL; this->start->element = el; }
        void sort() {
            Node<T>* newList=new Node<T>;// = new Node<T>;
            newList->element = this->start->element;
            newList->next = NULL;
            Node<T>* i;
            Node<T>* j;
            i = this->start->next;
           // std::cout << this->start->next->element;
            while (i != NULL) {
                j = newList;
                system("PAUSE");
                if (compare(j->element,i->element))
                {
                    Node<T>* temp = new Node<T>;
                    temp->next = newList;
                    temp->element = i->element;
                    newList = temp;
                    
                }else{
                    while (j != NULL) {
                        std::cout << "hello";
                        //std::cout << compare(j->element, i->element) << ' ' << compare(i->element, j->next->element)<<std::endl;
                        if (!compare(j->element, i->element) && (j->next == NULL || !compare(i->element, j->next->element))) {
                            //std::cout << "ku";
                            Node<T>* temp = new Node<T>;
                            if (j->next != NULL)
                            {
                                temp->element = j->next->element;
                                temp->next = j->next->next;
                            }
                            else
                                temp = NULL;
                            j->next = new Node<T>; j->next->element = i->element;
                            j->next->next = temp;
                        }
                        j = j->next;
                    }
                }
                i = i ->next;
                //std::cout << i->element;
            }
            start=newList;
        }
        void add(T elem) {
            Node<T>* el=new Node<T>; el->element = elem; el->next = NULL;
            Node<T>* temp = this->start;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = el;
        }
        void delet(int i) {
            int j = 0;
            Node* temp = this->start;
            Node* prev;
            for (j; j < i; j++)
            {
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next;
        }
        void coutall() {
            Node<T>* temp = this->start;
           //\\ std::cout << "hello";
            while (temp != NULL) {
                std::cout << temp->element << std::endl;
                temp = temp->next;

            }
        }
};

//template <class T>
int main()
{
    /// <summary>
    /// 
    /// TEST WILL BE HERE IN FEW DAYS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    /// 
    /// 
    /// 
    /// </summary>
    /// <returns></returns>
    Date d(29, 9, 2020, 12, 0, 0);
    //Date d1(27, 8, 2001, 12, 0, 0);
    //d.add(Duration(d,d1));
    //Duration dur(d, d1);
    //Node<int>* m = new Node<int>(4);
    //Node<int>*  n = new Node<int>(8);
   // Node<int>*  b = new Node<int>(3);
  /*
    Date date(10, 10, 1800, 0, 0, 0);
    List<Date> list(date);
    for (int i = 0; i < 10; i++) {
        date.day = (i + 1) + 11;
        date.month = (i + 1) + 11;
        date.year = 1900 + (10 + (i * 10));
        list.add(date);
    }
    list.coutall();
    std::cout << std::endl;
    list.sort();
    list.coutall();*/
    /
}
