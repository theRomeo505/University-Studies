// OOP_modul1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cstring>
#include "Data.h"
#include "Program.h"
#include "Server.h"
#include"Header.h"
using namespace std;



//////////// function3

int main()
{
    Server* s1=new Server(),*s2=new Server();
    s1->id = 1;
    s2->id = 2;
    s1->servers.push_back(s2);
    s2->servers.push_back(s1);
    s1->time.push_back(5);
    s2->time.push_back(3);
    Program* p1=new Program();
    Program* p2=new Program();
    s1->p.push_back(p1);
    s2->p.push_back(p2);
    Data* d=new Data();
    d->fromP = p1;
    d->toP = p2;
    d->fromS = s1;
    d->toS = s2;
    d->needanswer = false;
    d->size = 1;
    d->type = "no";
    p1->send(d);
    d->needanswer = true;
    p2->sendRandom(d);
    d->needanswer = false;
    p2->send(d, 5);
    for (curtime ; curtime < 100; curtime++) {
        for (int j = 0; j < datas.size(); j++) {
            if (datas[j] % 100 == curtime) {
                cout << j << "got" << endl;
                break;
            }
        }
        cout << curtime << " sec";
        
    }
}
