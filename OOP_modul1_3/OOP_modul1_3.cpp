// OOP_modul1_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;
int s = 0;
class Base {
public:

    Base() {
        n = number;
        Base::number++;
    }
    virtual int getNum() {
        return n;
    }
    static int number;
    Base* b1;
    Base* b2;
    virtual ~Base() = 0;
    virtual int pseudodestr(int s) = 0;
private:
    int n;
};
int Base::number = 1;
Base::~Base() {
    cout << "base destr, ";
    s = 3 * s + this->getNum() - 19;
}
class Alpha : public Base {
public:

    ~Alpha() {
        cout << "alp destr, ";
        s = s / 3 - this->getNum();
    }
    int pseudodestr(int ss) override {
        cout << "pseudoalp, ";
        ss = ss - 2 * this->getNum() - 19;
        return ss;
    }
};
class Beta : public Base {
public:
    ~Beta() {
        cout << "bet destr, ";
        s += this->getNum() + 5;
    }
    int pseudodestr(int ss) override {
        cout << "pseudob, ";
        ss = 3 * ss + 4 * this->getNum() - 4;
        return ss;
    }
};
class Red : public Alpha {
public:
    ~Red() {
        cout << "red destr, ";
        s -= this->getNum() / 2;
    }
    int pseudodestr(int ss) override {
        cout << "pseudored,  ";
        ss = ss - 2.5 * this->getNum() - 19;
        return ss;
    }
};
class Green : public Alpha {
public:
    ~Green() {
        cout << "green destr, ";
        s -= this->getNum() / 2 + 4;
    }
    int pseudodestr(int ss) override {
        cout << "pseudog,  ";
        ss = ss - 2.5 * this->getNum() - 22;
        return ss;
    }
};
int simulate(vector<Base*> m) {
    int sim = s;
    for (int i = 0; i < m.size(); i++) {
        sim = m[i]->pseudodestr(sim); cout << sim << endl;
    }

    return sim;
}
/////////////

void testfunction3() {
    cout << "start s=" << s << endl;
    Alpha* a1 = new Alpha(); Beta* a2 = new Beta(); Red* a3 = new Red();    Green* a4 = new Green();
    vector<Base*> m; m.push_back(a1); m.push_back(a2); m.push_back(a3); m.push_back(a4);
    simulate(m);
    cout << "number=" << a1->getNum() << "  ";
    delete(a1);
    cout << "after delete alpha s=" << s << endl;


    cout << "number=" << a2->getNum() << "  ";
    delete(a2);
    cout << "after delete beta s=" << s << endl;


    cout << "number=" << a3->getNum() << "  ";
    delete(a3);
    cout << "after delete red s=" << s << endl;

    cout << "number=" << a4->getNum() << "  ";
    delete(a4);
    cout << "after delete green s=" << s << endl;
}
int main()
{
    testfunction3();
}

