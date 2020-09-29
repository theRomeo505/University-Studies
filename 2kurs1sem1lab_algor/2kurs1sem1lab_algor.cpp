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
bool allnewpeace(bool* m,int n) {
	for (int i = 0; i < n; i++)
		if (m[i] == false)
			return false;
	return true;
}
int minim(int* m, int n,bool* p)
{
	int min = 999999,minindex=999999;
	for (int i = 0; i < n; i++)
	{
		if (m[i] < min && !p[i])
		{
			min = m[i];
			minindex = i;
		}
	}
	return minindex;
}
int main()
{
	srand(time(NULL));
	int n, max, files;
	cin >> n >> max >> files;
	int peaces = (n) / (max)+((n % max == 0) ? 0 : 1);
	if ((peaces - 1) % (files - 2) != 0)
	{
		peaces += files - 1 - peaces % (files - 2);
	}
	// 0 1 equal 
	int* m = new int[n];
	for (int i = 0; i < n; i++)
		m[i] = rand() % 1000;
	// in data
	int inpeace = n / peaces;




	//f.close();
	//f.open("file2");
	vector<FILE*> fs(files);
	fs[0] = fopen("0", "wb");
	fclose(fs[0]);
	fs[1] = fopen("1", "wb");
	vector <int> mm;
	int i = 0;
	cout << "start" << endl;

	for (i = 0; i < inpeace; i++) {
		mm.push_back(m[i]);
	}
	quickSort(mm, 0, inpeace - 1);

	for (i = 0; i < inpeace; i++) {
		fwrite(&mm[i], sizeof(int), 1, fs[1]);
		//cout << mm[i] << ' ';
	}
	fclose(fs[1]);
	//cout << endl;
	int g = 2;
	//string fil = "file";
	//cout <<(char)(2 + '0');
	fs[2] = fopen("2", "wb");
	for (i = 1; i < peaces; i++) {
		//cout << endl << i << ' ' << (peaces - 1) / (files - 2) << endl;
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
			fwrite(&mm[j],sizeof(int),1,fs[g]);
			//cout << mm[j]<<' ';
		}
		if (i % ((peaces - 1) / (files - 2)) == 0) {
			//cout << endl;
			fclose(fs[g]);
			//f.open("file" + (g+'0'));
			g++;
			char fli[5];
						_itoa(g, fli, 10);
//cout << "fli" << _itoa(g, fli, 10) << endl;
			if (g<fs.size())
			fs[g] = fopen(fli, "wb");
		}
		//cout << endl;
		
	}
	cout << "separated"<<endl;
	fclose(fs[files - 1]);
	//system("PAUSE");
	char fli[5];
	for (int i = 0; i < files; i++) {
		fs[i] = fopen(_itoa(i,fli,10), "rb");

		int x;
		while (fread(&x, sizeof(int), 1, fs[i]) != NULL)
		{
		}//cout << x<<' ';
		//cout << endl<<endl;
		fclose(fs[i]);
	}
	/// algor 
	 char r[5];
	for (int j = 2; j < files; j++)
		fs[j] = fopen(_itoa(j, r, 10), "rb");
	int *numbers=new int[files];
	bool *newpeace=new bool[files];
	int num;
	for (int j = 0; j < files; j++)
		{
			 
			if (j > 1) {
				fread(&num, sizeof(int), 1, fs[j]);
				numbers[j] = num;
			}
		}
	for (int i = 0; i < ((peaces - 1) / (files - 2)); i++) {
		if (i%25==0)
		cout << i << "iteration of "<< ((peaces - 1) / (files - 2)) << endl;
		for(int j = 0; j < files; j++)
		{
			newpeace[j] = false;
		}
		if (i != 0) {
			fclose(fs[0]);
			fclose(fs[1]);
		}
		if (i % 2 == 0) {
			fs[0] = fopen("0", "wb");
			fs[1] = fopen("1", "rb");
			newpeace[0] = true;
			fread(&numbers[1], sizeof(int), 1, fs[1]);
		}
		else {
			fs[0] = fopen("0", "rb");
			fs[1] = fopen("1", "wb");
			newpeace[1] = true;
			fread(&numbers[0], sizeof(int), 1, fs[0]);
		}
		int minindex,nextnum;
		//fread(&num, sizeof(int), 1, fs[2]);
		//cout << num << "nextnum";
		while (allnewpeace(newpeace,files) != true) {
			//for (int k = 0; k < files; k++) {
				//cout << newpeace[k] << ' ' << (newpeace[k] ? -1 : numbers[k]) << endl;
			//}
			//cout << endl;
			
			minindex=minim(numbers,files,newpeace);
			fwrite(&numbers[minindex], sizeof(int), 1, fs[i % 2]);
			
			if (fread(&nextnum, sizeof(int), 1, fs[minindex]) != NULL) {
				//cout << nextnum << "nextnum" << ' ' << minindex << endl;;
				//cout << nextnum << ' ';
				if (nextnum < numbers[minindex])
					newpeace[minindex] = true;
				numbers[minindex] = nextnum;
			}
			else
				newpeace[minindex] = true;
		}
	}
	cout << "end";
	fclose(fs[0]);
	fclose(fs[1]);
	//fs[(((peaces - 1) / (files - 2))-1)%2] = fopen(_itoa((((peaces - 1) / (files - 2)) - 1) % 2,fli,10), "rb");
	//int h;
	//while (fread(&h, sizeof(int), 1, fs[(((peaces - 1) / (files - 2)) - 1) % 2]) != NULL)
		//cout << h << ' ';
}
