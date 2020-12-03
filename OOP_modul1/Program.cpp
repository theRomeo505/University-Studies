#include "Program.h"
#include "Data.h"
#include "Server.h"
#include "Header.h"
#include <vector>
using namespace std;
bool ifvisited(vector<int> v, Server* s) {
    for (int i = 0; i < v.size(); i++)
        if (s->id == v[i]) {
            return true;
        }
    return false;
}
int fastest;
void tbs(Server* current, Server* goal, int time, vector<int> visited) {
    if (current->id == goal->id)
    {
        if (time < fastest)
            fastest = time;
        return;
    }
    visited.push_back(current->id);
    for (int i = 0; i < current->servers.size(); i++) {
        if (!ifvisited(visited, current->servers[i])) {
            tbs(current->servers[i], goal, time + current->time[i], visited);
        }
    }
}
int timebetweenserv(Server* s1, Server* s2) {
    fastest = 999999;
    int time = 0;
    vector<int> visited;
    tbs(s1, s2, 0, visited);
    return fastest;
}

void Program::send(Data *d) {
    int speed = timebetweenserv(d->fromS, d->toS);
    cout << d->fromS->id << "sent" << endl;
    datas.push_back(d->toS->id * 100 + speed*d->size);
    if (d->needanswer) {
        datas.push_back(d->fromS->id * 100 + 2*speed * d->size);
    }
}
void Program::send(Data *d,int periood) {
    int speed = timebetweenserv(d->fromS, d->toS);
    cout << d->fromS->id << "sent with period "<<periood  << endl;
    for (int i=0; speed * d->size+i*periood<100;i++)
    datas.push_back(d->toS->id * 100 + speed * d->size+periood*i);

    if (d->needanswer) {
        datas.push_back(d->fromS->id * 100 + 2 * speed * d->size);
    }
}
void Program::sendRandom(Data *d) {
    int speed = timebetweenserv(d->fromS, d->toS);
    cout << d->fromS->id << "sent" << endl;
    datas.push_back(d->toS->id * 100 + speed * d->size+rand()%10);

    if (d->needanswer) {
        datas.push_back(d->fromS->id * 100 + 2 * speed * d->size);
    }
}