// OOP_modul1_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;
struct colornum {
    string color;
    int n;
};
colornum function2(int n) {

    colornum p;
    if (n > 0) {
        cout << "natural ";
        p.color = "red";
        p.n = ((int)(pow(2, n) + pow(n, 2))) % 119;
    }
    else {
        cout << "negative ";
        p.color = "green";
        p.n = ((int)(n - 1 + pow(n, 5))) % 219;
    }
    return p;
}
colornum function2(double n) {
    colornum p;
    cout << "double ";
    p.color = "blue";
    p.n = ((int)ceil(1 / (sin(log(n))))) % 319;
    return p;
}
colornum function2(string n) {
    cout << "string ";
    colornum p;
    int s = 0, length = 0;
    bool temp = false;
    for (int i = 0; i < n.size(); i++) {
        if (n[i] == ' ') {
            if (!temp && length >= 4 && length <= 7)
                s++;
            temp = false;
            length = 0;
        }
        else
            if (!isalpha(n[i])) {
                temp = true;
            }
            else
                length++;
    }
    p.color = "green";
    if (!temp && length >= 4 && length <= 7)
        s++;
    p.n = s;
    return p;
}
template< typename T, typename T1>
colornum function2(T a, T1 b) {
    cout << "pair ";
    colornum p, p1, p2;
    p1 = function2(a);
    p2 = function2(b);
    if (p1.color == p2.color)
    {
        p.color = p1.color;
    }
    else
    {
        if (p1.color == "green")
        {
            if (p2.color == "red")
                p.color = "blue";
            else
                p.color = "red";
        }
        else if (p1.color == "red") {
            if (p2.color == "green")
                p.color = "blue";
            else
                p.color = "green";
        }
        else {
            if (p2.color == "green")
                p.color = "red";
            else
                p.color = "green";
        }
    }
    p.n = ((int)pow(p1.n, p2.n)) % 519;
    return p;
}
template< typename T >
colornum function2(T* n, int size) {
    cout << "mas ";
    colornum p;
    int i = 0, red = 0, blue = 0, green = 0;
    colornum* m = new colornum[size];
    for (int i = 0; i < size; i++) {
        m[i] = function2(n[i]);
    }
    p.n = 0;
    for (int i = 0; i < size; i++) {
        p.n += m[i].n * m[size - i - 1].n;
        if (m[i].color == "blue")
        {
            blue++;
        }
        else if (m[i].color == "red")
        {
            red++;
        }
        else
            green++;
    }
    if (red >= green && red >= blue)
        p.color = "red";
    else if (blue >= red && blue >= green)
        p.color = "blue";
    else p.color = "green";
    return p;
}
template< typename T >
colornum function2(T n) {
    cout << "else ";
    colornum p;
    p.color = "red";
    p.n = 8359;
    return p;
}
void testfunction2() {
    colornum p;

    int x = 6;
    p = function2(x);
    cout << p.color << ' ' << p.n << endl;

    x = -6;
    p = function2(x);
    cout << p.color << ' ' << p.n << endl;

    double xx = 5.6;
    p = function2(xx);
    cout << p.color << ' ' << p.n << endl;

    string xxx = "no daddy dont touch me";
    p = function2(xxx);
    cout << p.color << ' ' << p.n << endl;

    x = 56;
    string s = "no daddy dont touch me";
    p = function2(x, s);
    cout << p.color << ' ' << p.n << endl;

    int* m = new int[5]{ 5,-5,2,-2,8 };
    p = function2(m, 5);
    cout << p.color << ' ' << p.n << endl;

    vector<int> k;
    p = function2(k);
    cout << p.color << ' ' << p.n << endl;
}
int main()
{
    testfunction2();
}
