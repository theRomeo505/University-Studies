#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <chrono>

using namespace std;/*
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
	//files++;
	int *dop=new int[files];
	dop[0] = 1;
	for (int i = 1; i < files; i++)
		dop[i] = 0;
	int j = 0, coun = 0; // max++;
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
	int peaces = sum(dop, files)+1;
	j --; // pointer on start point kekw
	// 0 1 equal 
	int* m = new int[n];
	for (int i = 0; i < n; i++)
	{
		m[i] = rand() % 1000;
		//cout << m[i] << ' ';
	}cout << endl;
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
	}
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
			if (prev < 0 )
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
					int next=0; bool b = false;
					//cout << poi << endl;
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
	fs[0] = fopen("0", "rb");
	int y,rr=0;
	while (fread(&y, sizeof(int), 1, fs[0]) != NULL) {
		rr++;
	}
	cout << rr;/*
	cout << "done"<<endl;
	fs[0] = fopen("1", "rb");
	
	while (fread(&y, sizeof(int), 1, fs[0]) != NULL) {
		cout << y << ' ';
	}
	cout << "done";
}*/


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
bool allnewpeace(bool* m, int n) {
	for (int i = 0; i < n; i++)
		if (m[i] == false)
			return false;
	return true;
}
int minim(int* m, int n, bool* p)
{
	int min = 999999, minindex = 999999;
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
void make_inp(int nums) {
	srand(time(0));
	cout << endl;
	FILE* input = fopen("inp.bin", "wb");
	while (nums != 0) {
		int num = rand() % 1000;
		fwrite(&num, sizeof(int), 1, input);
		nums--;
	}
	fclose(input);
	//	cout << endl << "make_inp done";
}
int sum_of(int* pieces, int files) {
	int sum = 0;
	for (int i = 0; i < files; i++) {
		sum += pieces[i];
	}
	return sum;
}
void make_pieces(int* pieces, int files, int piece) {
	pieces[files - 1] = 1;
	/*	0 0 0 0 1
		1 1 1 1 0
		2 2 2 0 1
		4 4 0 2 3*/
	int real_pieces = 0;
	while (real_pieces < piece) {
		int max = pieces[0];
		int max_count = 0;
		for (int i = 0; i < files; i++) {
			if (max <= pieces[i]) {
				max = pieces[i];
				max_count = i;
			}
		}
		for (int i = 0; i < files; i++) {
			if (i != max_count)pieces[i] += max;
			else pieces[i] -= max;
		}
		real_pieces = sum_of(pieces, files);
	}
	//	cout << endl << "make_pieces done";
}
void merge_files(int* pieces, int files, int inpiece) {
	vector<int> arr;
	FILE* input = fopen("inp.bin", "rb");
	char name[100];
	int* pieces2 = new int[files];
	for (int i = 0; i < files; i++) pieces2[i] = pieces[i];
	int j = 0;
	int inp = 0;
	while (sum_of(pieces2, files) != 0) {
		_itoa(j, name, 10);
		FILE* opened = fopen(name, "wb");
		while (pieces2[j] != 0) {
			while (arr.size() != inpiece) {
				fread(&inp, sizeof(int), 1, input);
				arr.push_back(inp);
			}
			pieces2[j]--;
			if (pieces2[j] == 0 && j == files - 1) {
				while (fread(&inp, sizeof(int), 1, input) != NULL) {
					arr.push_back(inp);
				}
			}
			quickSort(arr, 0, arr.size() - 1);
			for (int i = 0; i < arr.size(); i++) {
				fwrite(&arr[i], sizeof(int), 1, opened);
			}
			arr.clear();
		}
		fclose(opened);
		j++;
	}
	fclose(input);
	delete[] pieces2;
	//	cout << endl << "merge_files done"<<endl;
}
int sum_end(bool* pieces, int files) {
	int sum = 0;
	for (int i = 0; i < files; i++) {
		if (pieces[i] == 1) sum++;
	}
	return sum;
}
int mrg_f(int* pieces, int files) {
	bool* if_null = new bool[files] {0};
	char name[100];
	bool* end_of_piece = new bool[files] {0};
	int* nums = new int[files];
	FILE** file_arr = new FILE * [files];
	int input_file = 0;
	int read_num = 0;
	for (int i = 0; i < files; i++) {
		_itoa(i, name, 10);
		if (pieces[i] != 0) {
			file_arr[i] = fopen(name, "rb");
			fread(&read_num, sizeof(int), 1, file_arr[i]);
			nums[i] = read_num;
		}
		else {
			input_file = i;
			file_arr[i] = fopen(name, "wb");
			end_of_piece[i] = 1;
			if_null[i] = 1;
		}
	}
	while (sum_of(pieces, files) != 1) {
		int minimal = minim(nums, files, end_of_piece);
		fwrite(&nums[minimal], sizeof(int), 1, file_arr[input_file]);
		if (fread(&read_num, sizeof(int), 1, file_arr[minimal]) != NULL) {
			if (read_num < nums[minimal]) {
				end_of_piece[minimal] = 1;
			}
			nums[minimal] = read_num;
		}
		else
		{
			//		cout << "FILE " << minimal << " NULL" << endl;
			nums[minimal] = -1;
			if_null[minimal] = 1;
			end_of_piece[minimal] = 1;
		}

		if (sum_end(end_of_piece, files) == files) {
			//		cout << endl;
			int new_input = input_file;
			for (int i = 0; i < files; i++) {

				end_of_piece[i] = 0;

				if (if_null[i] == 1) { pieces[i] = 0; end_of_piece[i] = 1; }
				if (i == input_file) {
					pieces[i]++;
					end_of_piece[i] = 1;
				}
				else if (if_null[i] != 1) pieces[i]--;
				//			cout << pieces[i] << " ";
			}
			//		cout << endl;
			if (sum_of(pieces, files) != 1) {
				for (int i = 0; i < files; i++) {

					if (pieces[i] == 0 && if_null[i] == 1) new_input = i;
				}
			}
			if (new_input != input_file) {
				fclose(file_arr[input_file]);
				fclose(file_arr[new_input]);
				_itoa(new_input, name, 10);
				file_arr[new_input] = fopen(name, "wb");
				_itoa(input_file, name, 10);
				file_arr[input_file] = fopen(name, "rb");
				end_of_piece[input_file] = 0;
				if_null[input_file] = 0;
				if_null[new_input] = 1;
				end_of_piece[new_input] = 1;
				fread(&nums[input_file], sizeof(int), 1, file_arr[input_file]);
				input_file = new_input;
				//			cout << endl << "NEW INP FILE " << input_file << endl;

			}
		}
	}
	for (int i = 0; i < files; i++) {
		fclose(file_arr[i]);
	}
	delete[] if_null;
	delete[] end_of_piece;
	delete[] file_arr;
	return input_file;
}
int main()
{
	

	int nums, max, files;
	cin >> nums >> max >> files;auto t_start = std::chrono::high_resolution_clock::now();
	//nums = 1000000;
	//max = 1000;
	//files = 5;
	int* pieces = new int[files] {0};
	make_inp(nums);
	make_pieces(pieces, files, nums / max);
	int inpeace = nums / sum_of(pieces, files);
	//	cout << endl << inpeace* sum_of(pieces, files);
	merge_files(pieces, files, inpeace);
	//	int file = merging_final(pieces, files);


	int file = mrg_f(pieces, files);
	
	cout << file << " "<<endl;
	
	auto t_end = std::chrono::high_resolution_clock::now();

	cout << "time"<< std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << endl; // искомое время
	//system("pause");
	return 0;

}
