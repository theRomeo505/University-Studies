// IhateMyLife.cpp: РѕРїСЂРµРґРµР»СЏРµС‚ С‚РѕС‡РєСѓ РІС…РѕРґР° РґР»СЏ РєРѕРЅСЃРѕР»СЊРЅРѕРіРѕ РїСЂРёР»РѕР¶РµРЅРёСЏ.
//

//#include "stdafx.h"
#include <iostream>  
using namespace std;
void WriteToFile1(int** arr, int rows, int cols) {
	FILE* f;
	char row;
	fopen_s(&f, "matr1", "wb");
	for (int i = 0; i < rows; i++) {
		int k = 0;
		for (int j = 0; j < cols; j++) {
			row = arr[i][j] + '0';
			fputc(row, f);
			row = ' ';
			fputc(row, f);
		}
		row = NULL;
		fputc(row, f);
	}
	fclose(f);
}
void ReadFromFile1(int** arr, int rows, int cols) {
	char row;
	FILE* f;
	fopen_s(&f, "matr1", "rb");
	int i = 0;
	int j = 0;
	while (!feof(f)) {
		row = fgetc(f);
		if (row == NULL) {
			i++; j = 0;
		}
		else if (row != ' ') {
			arr[i][j] = row - '0';
		}
	}
	fclose(f);
}
void WriteToFile2(int** arr, int rows, int cols) {
	FILE* f;
	char row[4];
	fopen_s(&f, "matr2", "wb");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (arr[i][j] != 0) {
				row[0] = i;
				row[1] = j;
				row[2] = arr[i][j];
				row[3] = NULL;
				fwrite(row, sizeof(row), 1, f);
			}
		}
	}
	fclose(f);
}

void ReadFromFile2(int** arr, int rows, int cols) {
	char row[4];
	FILE* f;
	fopen_s(&f, "matr2", "rb");
	int i = 0;
	int j = 0;
	while (!feof(f)) {
		fread(row, sizeof(row), 1, f);
		i = (int)row[0];
		j = (int)row[1];
		arr[i][j] = (int)row[2];
	}
	for (int b = 0; b < rows; b++) {
		for (int k = 0; k < cols; k++) {
		}
	}
	fclose(f);
}
void plusMatr(int** arr1, int** arr2, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			arr2[i][j] += arr1[i][j];
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << arr2[i][j];
		}
		cout << endl;
	}
}
void umnjMatr(int** arr1, int** arr2, int rows, int cols) {
	int** arr3 = new int* [rows];
	for (int i = 0; i < rows; i++) {
		arr3[i] = new int[cols];
		for (int j = 0; j < cols; j++)
		{
			arr3[i][j] = 0;
			for (int k = 0; k < cols; k++)
				arr3[i][j] += arr1[i][k] * arr2[k][j];
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) {
			cout << arr3[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < rows; i++) {
		delete[] arr3[cols];
	}
	delete[] arr3;
}
int main()
{
	const int rows = 3;
	const int cols = 3;
	int** arr = new int* [rows];
	int** arr2 = new int* [rows];
	for (int i = 0; i < rows; i++) {
		arr[i] = new int[cols];
		arr2[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> arr2[i][j];
		}
	}
	WriteToFile2(arr, rows, cols);
	//ReadFromFile2(arr, rows, cols);
	//umnjMatr(arr, arr2, rows, cols);
	  plusMatr(arr, arr2, rows, cols);
	for (int i = 0; i < cols; i++) {
		delete[] arr[cols];
		delete[] arr2[cols];
	}
	delete[] arr;
	delete[] arr2;
	return 0;
}