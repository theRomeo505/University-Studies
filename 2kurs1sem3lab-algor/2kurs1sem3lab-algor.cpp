// 2kurs1sem3lab-algor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
0
123
456 789 101112
13
*/
#include <iostream>
#include <vector>
using namespace std;

class piramid {
public:
    int d;
    vector<int> m;
    piramid(int d) { this->d = d;   }
    int getParentIndex(int index) {
        
        int tmp = 0,i=0;
        while (tmp + pow(d, i) <= index) {
            tmp += pow(d, i);
            i++;
        }
        int floorIndex = index - tmp;
        int parentFloorIndex = floorIndex / d;
        //cout << tmp <<floorIndex<< parentFloorIndex;
        return tmp - pow(d, i - 1) + parentFloorIndex;
    }
    void up(int nodeIndex) {
        int parentIndex, tmp;

        if (nodeIndex != 0) {

            parentIndex = getParentIndex(nodeIndex);

            if (m[parentIndex] < m[nodeIndex]) {

                tmp = m[parentIndex];

                m[parentIndex] = m[nodeIndex];

                m[nodeIndex] = tmp;

                up(parentIndex);

            }

        }
    }
    void add(int n) {
        m.push_back(n);
        up(m.size()-1);

    }
    int maxChild(int index) {
        int tmp = 0, i = 0;
        while (tmp  <= index) {
            tmp += pow(d, i);
            i++;
        }
        int floorIndex = index - tmp + pow(d, i - 1);
        int childstartindex = tmp + floorIndex * d;
        int max = -1,maxindex=-1;
        if (childstartindex >= m.size())
            return -1;
        for (int j = childstartindex; j < childstartindex + d; j++) {
            if (j == m.size())
                return maxindex;
            if (m[j] >= max) { max = m[j]; maxindex = j; }
        }
        
        return maxindex;
    }
    void extractMax(int i) {
        if (i == 0)
            cout << m[i] << endl;
        int k = maxChild(i);
        if (k == -1)
        {
            m.erase(m.begin() + i);
            return;
        }
        m[i] = m[k];
        extractMax(k);
    }
    void increaseKey(int i, int k) {
        m[i] += k;
        up(i);
    }
    void show(int j,int floor) {
        int k = j;
        //cout << "msize" << m.size();
        for (int i = j; i < j + pow(3, floor); i++)
        {
            if (i == m.size())
                return;
            if (i % d == k % d)
                cout << ' ';
            cout << m[i] << ' ';
            
        }
        cout << endl;
        show(j + pow(3, floor), floor + 1);
    }
};
int main()
{
    piramid p(3);
    //cout << p.getParentIndex(8);
    for (int i = 0; i < 40; i++)
    {
        p.add(i);
      //  p.show(0, 0);
        //system("pause");
    }

    for (int i = 0; i < 40; i++)
        p.extractMax(0);

}

