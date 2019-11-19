// 18.11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <fstream>
#include <iostream>
using namespace std;


struct notebook {
	struct res {
		int x;
		int y;
	};
	res l;

	int f;
	float d;
	float hdd;
	char model[21];
	int price;
	double weight;
	double length, width, height;
	int cf; // cpu 
	int ram;
	int gpu;
};
int main()
{
	ifstream f("note.txt");
	int n=0,l,k;
	char* r = new char[1000];
	while (!f.eof()) {
		f.getline(r,1000);
		n++;
	}
	f.seekg(0, ios::beg);
	
	notebook* m = new notebook[n];
	char t,t1[1];
	for (int i = 0; i < n; i++)
	{
		//l = f.tellg(); cout << "k" << l << "k";
		f.get(m[i].model, 21);
		
		//f.seekg(21+76*i, ios::beg);
		//f >> t;
		//cout << t;
		// 8 40 - 10 10
		
		f >> m[i].price>>m[i].weight>>m[i].height>>t>>m[i].length>>t>>m[i].width>>m[i].cf>> m[i].ram>>m[i].d>>m[i].gpu>>m[i].l.x>>t>> m[i].l.y>>m[i].f>>m[i].hdd ;
		//cout << m[i].model<<m[i].hdd<<endl;
		f.getline(t1, 1);
	}
	notebook p;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (m[j].price < m[i].price) {
				p = m[i];
				m[i] = m[j];
				m[j] = p;
			}
		}
	}
	ofstream popa("of");
	for (int i = 0; i < n; i++) {
		if (m[i].price <= 3000)
			break;
		popa << (char*)& m[i];
	}
	popa.close();
	ifstream ff("of");
	ff >> (char*)& p;
	cout << (char*)& p;

}
