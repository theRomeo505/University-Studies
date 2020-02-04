// classwork1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <direct.h>
#include <cstdlib>
using namespace std;
struct angl {
	char angl[20];
	char ukr[20];
};
void fun() {
	ifstream f("words.bin", ios::binary);
	angl a;
	_chdir("aaa");
	//_mkdir("words");
	
	while (f.read((char*)& a, sizeof(angl))) {
		ofstream f1(a.angl,ios::binary);
		f1 << a.ukr;
		f1.close();cout << "created";
	}
}
int main()
{
	//ofstream f("words.bin",ios::app,ios::binary);
	angl a;
	//
	//strcpy(a.angl, "ojhku");
	//strcpy(a.ukr, "projh");
	//f.write((char*)& a, sizeof(angl));
	//f.close();
	fun();
  //  std::cout << "Hello World!\n";
	
}
