// 2kurs1sem4lab-algor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<vector>
using namespace std;
struct elem {
    int key;
    int id;
};
void timeMemory(vector<elem>& m) {
    int start = 0, end = m.size()-1;
    while (start <= end ) {
        while (m[start].key != 1 && start<m.size())
            start++;
        while (m[end].key != 0 && end>=0)
            end--;
        if (start < end)
        {
            elem temp=m[start];
            m[start] = m[end];
            m[end] = temp;

        }
    }
} //// do sort struct !
void timeStable(vector<elem>& m) {
    vector<elem> ones;
    vector<elem> zeros;
    for (int i = 0; i < m.size(); i++) {
        if (m[i].key == 0)
            zeros.push_back(m[i]);
        else
            ones.push_back(m[i]);
    }
   
    for (int i = 0; i < m.size(); i++) {
        if (zeros.empty())
        {
            m[i] = ones[0];
            ones.erase(ones.begin());
        }
        else {
            m[i] = zeros[0];
            zeros.erase(zeros.begin());
        }
    }
}

void stableMemmory(vector<elem>& m) {
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.size()-1; j++)
        {
            if (m[j + 1].key < m[j].key)
            {
                elem temp = m[j];
                m[j] = m[j + 1];
                m[j + 1] = temp;
            }
        }
    }
}
int main()
{
    vector<elem> m;
    elem e;
    for (int i = 0; i < 10; i++) {
        e.id = i;
        e.key = i % 2;
        m.push_back(e);
    
    }
    
    timeMemory(m);
    for (int i = 0; i < 10; i++)
        cout << m[i].id <<' '<< m[i].key << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
