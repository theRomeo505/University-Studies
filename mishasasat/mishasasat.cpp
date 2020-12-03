/ #include "stdafx.h"
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
	cout << endl << "make_inp done";
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
	cout << endl << "make_pieces done";
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
	cout << endl << "merge_files done";
}
int sum_end(bool* pieces, int files) {
	int sum = 0;
	for (int i = 0; i < files; i++) {
		if (pieces[i] == 1) sum++;
	}
	return sum;
}
int merging_final(int* pieces, int files) {
	bool* if_null = new bool[files] {0};
	char name[100];
	bool* end_of_piece = new bool[files] {0};
	int* nums = new int[files];
	FILE** file_arr = new FILE * [files];
	int input_file = 0;
	cout << endl;
	int read_num = 0;
	for (int i = 0; i < files; i++) {
		cout << if_null[i] << " ";
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
		}
	}
	cout << endl;
	while (sum_end(end_of_piece, files) != files) {
		int minimal = minim(nums, files, end_of_piece);
		//cout << endl;
		fwrite(&nums[minimal], sizeof(int), 1, file_arr[input_file]);
		if (fread(&read_num, sizeof(int), 1, file_arr[minimal]) != NULL) {
			if (read_num < nums[minimal]) {
				nums[minimal] = read_num;
				end_of_piece[minimal] = 1;
			}
			else nums[minimal] = read_num;
		}
		else {
			//		if_null[minimal] = 1;
			end_of_piece[minimal] = 1;
		}
		int new_input = input_file;
		/*		cout << endl;
				for (int i = 0; i < files; i++) {
					cout << pieces[i] << " ";
				}*/

		if (sum_end(end_of_piece, files) == files) {
			for (int i = 0; i < files; i++) {
				if (pieces[i] == 0) { // ?????????????????????????????? if null != 1 anywhere but end_of_piece = 1 and then what? && if_null[i] == 1
					new_input = i;
				}
			}
			for (int i = 0; i < files; i++) {
				cout << pieces[i] << " ";
				if (i == input_file) pieces[i]++;
				//if (i != input_file && if_null[i]!=1) pieces[i]--;
				else if (i != input_file && if_null[i] != 1)pieces[i]--;
				end_of_piece[i] = 0;
				if (if_null[i] == 1 || i == input_file) end_of_piece[i] = 1;
				//			if (i == input_file) end_of_piece[i] = 1;
			}
			if (new_input != input_file) {
				fclose(file_arr[new_input]);
				fclose(file_arr[input_file]);
				_itoa(input_file, name, 10);
				file_arr[input_file] = fopen(name, "rb");
				if_null[input_file] = 0;
				fread(&nums[input_file], sizeof(int), 1, file_arr[input_file]);
				end_of_piece[input_file] = 0;
				if_null[input_file] = 0;
				//			if_null[new_input] = 1;
				//			end_of_piece[new_input] = 1;
				_itoa(new_input, name, 10);
				file_arr[new_input] = fopen(name, "wb");
				//			cout << "NEW: " << new_input << endl << "OLD: " << input_file << endl;
				input_file = new_input;
			}
			cout << endl;
			for (int i = 0; i < files; i++) cout << if_null[i] << " ";
			cout << endl;
			int counter = 0;
			/*			for (int i = 0; i < files; i++) {
							if (if_null[i] == 1) counter++;
							if (counter == files - 1) {
								for (int i = 0; i < files; i++) {
									if (if_null[i] == 0) if_null[i] = 1;
								}
							}
						}*/
						/*			for (int i = 0; i < files; i++) {
										if (pieces[i] == 0 ) { // ?????????????????????????????? if null != 1 anywhere but end_of_piece = 1 and then what? && if_null[i] == 1
											new_input = i;
										}
									}
									if (new_input != input_file) {
										fclose(file_arr[new_input]);
										fclose(file_arr[input_file]);
										_itoa(input_file, name, 10);
										file_arr[input_file] = fopen(name, "rb");
										if_null[input_file] = 0;
										fread(&nums[input_file], sizeof(int), 1, file_arr[input_file]);
										end_of_piece[input_file] = 0;
										end_of_piece[new_input] = 1;
										_itoa(new_input, name, 10);
										file_arr[new_input] = fopen(name, "wb");
										new_input = input_file;
									}*/
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
	//	unsigned int start_time = clock(); // начальное время
										   // здесь должен быть фрагмент кода, время выполнения которого нужно измерить
		 // конечное время

	int nums, max, files;
	cin >> nums >> max >> files;
	int* pieces = new int[files] {0};
	make_inp(nums);
	make_pieces(pieces, files, nums / max);
	int inpeace = nums / sum_of(pieces, files);
	//	cout << endl << inpeace* sum_of(pieces, files);
	merge_files(pieces, files, inpeace);
	//	int file = merging_final(pieces, files);


	int file = mrg_f(pieces, files);
	//	cout << endl << file;
	//	char name[20];
	//	_itoa(file, name, 10);
	//	FILE *read = fopen(name, "rb");
	//	cout << endl << endl;
	//	int s = 0;
	//	while (fread(&file, sizeof(int), 1, read) != NULL) {
	cout << file << " ";
	//		s++;
	//		if (s % 20 == 0) cout << endl;
	//	}



	cout << endl;
	int asd;
	cin >> asd;
	//	FILE *reader = fopen("4", "rb");
	//	int k=0;
	//	while (fread(&k, sizeof(int), 1, reader) != NULL) k++;
	//	cout << endl<<endl << file << endl << endl<<k;
	//	unsigned int end_time = clock();
	//	cout << (end_time - start_time)/1000 << endl; // искомое время
	return 0;

}