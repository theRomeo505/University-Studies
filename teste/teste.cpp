// teste.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int twos(int a) {
    int temp = 0;
    while (a % 2 == 0) {
        temp++;
        a /= 2;
    }
    return temp;
}
int fifs(int a) {
    int temp = 0;
    while (a % 5 == 0) {
        temp++;
        a /= 5;
    }
    return temp;
}
int main()
{
    int n;
    cin >> n;
    int two = 0, five = 0;
   /* for (int i = 2; i <= n; i++) {
        two += twos(i);
        five += fifs(i);
    }*/
    int temp=2;
    while (n > temp){
        two += n / temp;
        temp *= 2;
    }
     temp = 5;
    while (n > temp) {
        five += n / temp;
        temp *= 5;
    }
    
    //cout << two << five;
    cout << ((two < five) ? two : five);
}

