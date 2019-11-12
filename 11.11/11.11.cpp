// 11.11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;
struct student {
	string s;
	int numba;
	int marks[5];
};
student* inp(int n) {
	student* m = new student[n];
	ofstream ff("new");
	student h;
	for (int i = 0; i < n; i++) {
		cin >> h.s >> h.numba >> h.marks[0] >> h.marks[1] >> h.marks[2] >> h.marks[3] >> h.marks[4];
		ff.write((char*)& h, sizeof(student));

	}
	ff.close();
	ifstream f("new");
	for (int i = 0; i < n; i++) {

		f.read((char*)& m[i],sizeof(student));
		//cout << m[i].s;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (m[i].numba > m[j].numba) {
				h = m[i];
				m[i] = m[j];
				m[j] = h;
			}
		}
	}

	return m;
}
void cool(int n, student* m) {
	double s = 0; bool p = false;
	for (int i = 0; i < n; i++) {
		s = 0;
		for (int j = 0; j < 5; j++) {
			s += m[i].marks[j];
		}
		if (s / 5 >= 4)
		{
			p = true;
			cout << m[i].s << ' ' << m[i].numba << endl;
		}
	}
	if (!p)
		cout << "stupido";
}
int main()
{
	//ofstream f("new.txt");
	int n;
	cin >> n;
	student* p = inp(n);
	cool(n, p);
}

