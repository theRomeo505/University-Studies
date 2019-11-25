// 19.11(2).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
struct scan_info {
	char model[25];
	int price;
	double x_size;
	double y_size;
	int optr;
	int grey;
};
using namespace std;

void infile(scan_info *m,string name,int count) {
	ofstream in(name);
	in << (long)count;
	for (int i = 0; i < count; ++i) {
		in.write((char*)& m[i], sizeof(scan_info));
	}
	in.close();

}
scan_info* sortt(scan_info* m, int count) {
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			if (strcmp(m[i].model, m[j].model) > 0)
			{
				scan_info p = m[i];
				m[i] = m[j];
				m[j] = p;
			}
		}
	}
	return m;
}
int main()
{
	int count;
	cin >> count;
	scan_info* m = new scan_info[count];

	ifstream out("scan.dat");
	for (int i = 0; i < count; ++i) {
		out.read((char*)& m[i], sizeof(scan_info));
	}
	out.close();
	/////
	
	
	
	/////
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
