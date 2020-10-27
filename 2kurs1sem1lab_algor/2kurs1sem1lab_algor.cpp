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
bool allnewpeace(bool* m,int n,int j) {
	for (int i = 0; i < n; i++)
		if (m[i] == false && i!=j)
			return false;
	return true;
}
int minim(int* m, int n,bool* p,int j)
{
	int min = 999999,minindex=999999;
	for (int i = 0; i < n; i++)
	{
		if (m[i] < min && !p[i] && i!=j)
		{
			min = m[i];
			minindex = i;
		}
	}
	return minindex;
}
int sum(int* m, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += m[i];
	return sum;
}
int main()
{
	srand(time(NULL));
	int n, max, files;
	cin >> n >> max >> files;
	int *dop=new int[files];
	dop[0] = 1;
	for (int i = 1; i < files; i++)
		dop[i] = 0;
	int j = 0,coun=0;
	while (sum(dop, files) < n / max) {
		for (int i = 0; i < files; i++) {
			if (i != j)
				dop[i] += dop[j];
		}
		dop[j] = 0;
		j++;
		coun++;
		j = j % files;
		//for (int i = 0; i < files; i++)
			//cout << dop[i] << ' ';
		//cout << endl;
	}
	int peaces = sum(dop, files);
	j --; // pointer on start point kekw
	// 0 1 equal 
	int* m = new int[n];
	for (int i = 0; i < n; i++)
		m[i] = rand() % 1000;
	// in data
	int inpeace = n / peaces;



	char fli[5];
	vector<FILE*> fs(files);
	vector<int> perm;
	int ptr = 0;
	for (int i = 0; i < files; i++) {
		fs[i] = fopen(_itoa(i,fli,10), "wb");
		for (int g = 0; g < dop[i]; g++) {
			for (int k = 0; k < inpeace; k++)
			{
				perm.push_back(m[ptr + k]);
				//cout << ptr + k << ' ' << m[ptr + k] << endl;
				//ptr++;
			}
			quickSort(perm,0,perm.size()-1);
			for (int k = 0; k < inpeace; k++)
			{

				fwrite(&perm[k], sizeof(int), 1, fs[i]);
			}
			ptr += inpeace;
			perm.clear();
		}
		fclose(fs[i]);
	}
	cout << "separated"<<endl;
	
	//system("PAUSE");
	/*for (int i = 0; i < files; i++) {
		fs[i] = fopen(_itoa(i,fli,10), "rb");

		int x,y=0;
		while (fread(&x, sizeof(int), 1, fs[i]) != NULL)
		{if (x < y)
				cout << endl;
			cout << x << ' ';
			
			y = x;
		}
		cout << endl<<endl;
		fclose(fs[i]);
	}*/
	//system("pause");
	/// algor 
	 char r[5];
	 for (int g = 0; g < files; g++)
	 {
		 if (g != j)
			 fs[g] = fopen(_itoa(g, r, 10), "rb");
		 else
			 fs[g] = fopen(_itoa(g, r, 10), "wb");
	 }
	int *numbers=new int[files];
	bool *newpeace=new bool[files];

	for (int i = 0; i < files; i++)
	{
		numbers[i] = 0;
		newpeace[i] = false;
	}
	
	int num;
	for (int g = 0; g < files; g++) {
		if (g != j) {
			fread(&num, sizeof(int), 1, fs[g]);
			numbers[g] = num;
		}
	}
	//vector<int> my;
	for (int g = 0; g < coun; g++)
		{
			 
			
			int prev = j - 1;
			if (prev == -1)
				prev += files;
			for (int d = 0; d < dop[prev]; d++)
			{
				while (!allnewpeace(newpeace, files,j)) {
					//for (int y = 0; y < files; y++) {
						//cout << numbers[y] << ' ';
					//}cout << endl;
					//system("pause");
					int poi=minim(numbers, files, newpeace,j);
					fwrite(&numbers[poi], sizeof(int),1, fs[j]);
					//my.push_back(numbers[poi]);
					int next; bool b = false;
					if (fread(&next, sizeof(int), 1, fs[poi]) == NULL)
						b = true;
					if (next < numbers[poi] || b)
						newpeace[poi] = true;
					numbers[poi] = next;
				}
				//for (int m = 0; m < my.size(); m++)
					//cout << my[m] << ' ';
				//system("pause"); 
				for (int h = 0; h < files; h++)
					newpeace[h] = false;
			}
			for (int dd = 0; dd < files; dd++) {
				if (dd != prev)
					dop[dd] -= dop[prev];
			}
			dop[prev] = 0;
			//my.clear();
			cout << g+1 <<"of"<<coun<< "done" << endl;
			fclose(fs[j]);
			fclose(fs[prev]);
			fs[j] = fopen(_itoa(j, r, 10), "rb");
			fs[prev] = fopen(_itoa(prev, r, 10), "wb");
			fread(&numbers[j], sizeof(int), 1, fs[j]);
			j--;
			if (j == -1)
				j += files;
		}
	//fs[0] = fopen("0", "rb");
	int y;
	//while (fread(&y, sizeof(int), 1, fs[0]) != NULL) {
	//	cout << y << ' ';
	//}
	cout << "done";
}
