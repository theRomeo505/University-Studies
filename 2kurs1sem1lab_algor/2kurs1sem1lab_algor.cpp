// 2kurs1sem1lab_algor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
using namespace std;
void quickSort(vector<int>& array, int low, int high)
{
	int i = low;
	int j = high;
	int pivot = array[(i + j) / 2];
	int temp;

	while (i <= j)
	{
		while (array[i] < pivot)
			i++;
		while (array[j] > pivot)
			j--;
		if (i <= j)
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	if (j > low)
		quickSort(array, low, j);
	if (i < high)
		quickSort(array, i, high);
}

int main()
{
	srand(time(NULL));
	int n, max, files;
	cin >> n >> max >> files;
	int peaces = (n) / (max)+((n%max==0)?0:1);
	if ((peaces-1)%(files-2)!=0)
	{
		peaces += files - 1 - peaces % (files - 2);
	}
	// 0 1 equal 
	int* m = new int[n];
	for (int i = 0; i < n; i++)
		m[i] = rand() % 200;
	// in data
	int inpeace = n / peaces;
	ofstream f;
	f.open("file0");
	f.close();
	f.open("file1");
	vector <int> mm;
	int i = 0;
	for (i = 0; i < inpeace;i++) {
		mm.push_back(m[i]);
	}
	quickSort(mm, 0, inpeace - 1);
	for (i = 0; i < inpeace; i++) {
		f << mm[i];
	}
	
	f.close();
	int g = 3;
	f.open("file2");
	for (i = 1; i < peaces; i++) {
		mm.clear();
		for (int j = 0; j < inpeace; j++) {
			mm.push_back(m[inpeace * i + j]);
		}
		if (i == peaces - 1)
		{
			int k = inpeace * peaces;
			while (k < n) {
				mm.push_back(m[k]);
				k++;
			}
		}
		quickSort(mm, 0, mm.size() - 1);
		for (int j = 0; j < mm.size(); j++) {
			f << mm[j];
			cout << mm[j]<<' ';
		}
		cout << endl;
		if (i % ((peaces - 1) / (files - 2)) == 0) {
			cout << endl;
			f.close();
			f.open("file" + (g+'0'));
			g++;
		}
	}
	f.close();
	///////////////////
	vector<fstream> file;
	ofstream f;

	for (i = 0; i < files; i++)
	{
		f.open("file"+(i+'0'));
	
		file.push_back(f);
		f.close;
	}
	while (!file[2].eof()) {
		int f;
		file[2] >> f;
		cout << f << ' ';
	}
	for (i = 0; i < (peaces - 1) % (files - 2); i++) {

	}
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
