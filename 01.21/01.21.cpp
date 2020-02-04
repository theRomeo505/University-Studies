// 01.21.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstdlib>
using namespace std;
//var 14
enum role { client = 0, adm = 1 };
char curlogin[20]="";
struct user {
	char login[20];
	//char password[20];
	int password;
	role role;//
	int id;
};
int leftrotate(unsigned int x, int c)
{
	return (x << c) | (x >> (32 - c));
}
int md5(char* p, int n) {
	int s[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22, 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };
	unsigned int k[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee , 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 , 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c , 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 , 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };
	unsigned int a0 = 0x67452301;   //A
	unsigned int b0 = 0xefcdab89;   //B
	unsigned int c0 = 0x98badcfe;   //C
	unsigned int d0 = 0x10325476;   //D
	string ss;
	unsigned int** u = new unsigned int* [ceil((double)n / 64) + 1];
	for (int i = 0; i < ceil((double)n / 64) + 1; i++)
		u[i] = new unsigned int[16];
	int j, jui = ceil((double)n / 64);
	for (int i = 0; i < ceil((double)n / 64) + 1; i++)
		for (int j = 0; j < 16; j++)
			u[i][j] = 0;
	for (j = 0; j < ceil((double)n / 64 - 1); j++) {

		for (int i = 64 * j + 3; i < 64 * j + 64; i += 4) {
			int y = 0;
			for (int g = i + 4; g > i; g--) {

				y *= 256;
				y += p[g];
			}
			u[j][(i - 64 * j) / 4] = y;
			//std::cout << u[j][(i - 64 * j) / 4] << ' ';
		}
		//std::cout << std::endl;
	}
	int tick = 0, ttick = 0;

	for (int i = 64 * j + 3; i < 64 * j + 64; i += 4) {
		int y = 0;
		tick = 0;
		for (int g = i; g > i - 4; g--) {

			y *= 256;
			if (g >= n) {
				tick = g - i + 3;
			}
			else y += p[g];
		}
		if (tick > 0) {

			y *= pow(256, 4 - tick);
			u[j][(i - 64 * j) / 4] = y + pow(256, 3 - tick);
			//std::cout << u[j][(i - 64 * j) / 4] << ' ';
			ttick++;
			break;
		}
		//ttick++;
		u[j][(i - 64 * j) / 4] = y;
		//std::cout << u[j][(i - 64 * j) / 4] << ' ';
	}
	//std::cout << std::endl;


	if (ttick < 14) {
		u[j][14] = n / pow(2, 32);
		u[j][15] = n % ((int)pow(2, 32));
	}
	else {
		jui++;
		u[j + 1][14] = n / pow(2, 32);
		u[j + 2][15] = n % ((long)pow(2, 32));
	}

	/*for (int i = 0; i < 16; i++)
	  std::cout << u[0][i] << ' ';
	std::cout << std::endl; system("pause");*/

	////
	int** uu = new int* [jui];
	int r;
	int A, B, C, D, f, g;
	for (int j = 0; j < jui; j++) {

		A = a0;
		B = b0;
		C = c0;
		D = d0;
		for (int i = 0; i < 64; i++) {
			if (i < 16) {
				f = (B & C) | (~B & D);
				g = i;
			}
			else if (i < 32) {
				f = (D & B) | ((~D) & C);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48) {
				f = (((~B & C) | (~C & B)) & ~D) | (~((~B & C) | (~C & B)) & D);
				g = (3 * i + 5) % 16;
			}
			else {
				f = (C & ~(B | ~D)) | (~C & (B | ~D));
				g = (7 * i) % 16;
			}
			f = f + A + k[i] + u[j][g];
			A = D;
			D = C;
			C = B;
			B = B + leftrotate(f, s[i]);
		}
		a0 = a0 + A;
		b0 = b0 + B;
		c0 = c0 + C;
		d0 = d0 + D;
	}
	//std::cout << std::endl << a0 << ' ' << b0 << ' ' << c0 << ' ' << d0 << std::endl;
	return a0 + b0 + c0 + d0;
}
struct auction {
	char name[20];
	char better[20];
	int startprice;
	int id;
	bool closed;
	
};
int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 2) % 2;
		if (key == 0) std::cout << "-> Login" << std::endl;
		else  std::cout << "   Login" << std::endl;
		if (key == 1) std::cout << "-> Register" << std::endl;
		else  std::cout << "   Register" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}
int login() {
	system("cls");
	user newu, test; char pass[20];
	std::cout << "Enter ur login:" << std::endl;
	std::cin >> newu.login;
	std::cout << "Enter ur password:" << std::endl;
	std::cin >> pass;
	ifstream f("base");
	while (!f.eof()) {
		f.read((char*)& test, sizeof(user));
	//	cout << "cur" << test.password << endl;
		
		if (strcmp(test.login,newu.login)==0) {
			
			
			if (test.password=md5(pass,strlen(pass)))
			{
				//std::cout << "Success"; 
				strcpy_s(curlogin,newu.login);
				if (test.role == client) return 1;
				else
					return 2;
			}
			else
				return 0;
		}
	}
	
	return 0;
}
void registration() {
	
	user newu,t; char c; bool ch = true; int id = 1;
	ifstream f1("base");
	while (ch) {
		system("cls");
		std::cout << "Enter ur login:" << std::endl;
		std::cin >> newu.login;
		f1.seekg(0, f1.beg);
		while (f1.read((char*)& t, sizeof(user))){
			if (strcmp(newu.login, t.login) == 0 ) {
				break;
			}
			ch = false;
			id++;
		}
	}
	f1.close();
	char pass[20];
	std::cout << "Enter ur password:" << std::endl;
	std::cin >> pass;
	newu.password = md5(pass, strlen(pass));
//	cout << "cur" << newu.password<<endl;
	std::cout << "Enter ur role:" << std::endl;
	std::cin >> c;
	if (c == 'a')
		newu.role = adm;
	else
		newu.role=client;
	ofstream f("base",ios::app);
	///crypt passw 
	newu.id = id;
	f.write(((char*)& newu),sizeof(newu));
	system("pause");
}
int admint() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 4) % 4;
		if (key == 0) std::cout << "-> Users" << std::endl;
		else  std::cout << "   Users" << std::endl;
		if (key == 1) std::cout << "-> Auctions" << std::endl;
		else  std::cout << "   Auctions" << std::endl;
		if (key == 2) std::cout << "-> Add auction" << std::endl;
		else  std::cout << "   Add auction" << std::endl;
		if (key == 3) std::cout << "-> Exit" << std::endl;
		else  std::cout << "   Exit" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}
void users() {
	system("cls");
	user newu;
	ifstream f("base");
		while(f.read((char*)& newu, sizeof(user))){
		std::cout << newu.login <<' '<<newu.id<<' '<<newu.role<< std::endl;
	} 
	system("pause");
}
void auctions() {
	int key = 0;
	int code;
	ifstream f("aucs");
	auction a; int numb = 0,j=0,fulln=0;
	while (f.read((char*)& a, sizeof(auction))) {
		if (!a.closed)
		numb++;
		fulln++;
	}
	
	do {
		system("cls");
		f.close();
		f.open("aucs");
		key = (key + fulln+1) % (fulln+1);
		j = 0;
		while(
			f.read((char*)& a, sizeof(auction))){
			
			//if (!a.closed) {
				if (key == j) std::cout << "-> " << a.name << ' ' << a.startprice<<' '<<a.better<<' '<<a.closed << std::endl;
				else  std::cout << "   " << a.name << ' ' << a.startprice <<  ' '<<a.better  <<' '<<a.closed<< std::endl;
				j++;
			//}
			
		}
		if (key == fulln) std::cout << "-> Exit" << std::endl;
		else  std::cout << "   " << "Exit" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	if (key != fulln)
	{
		f.close();
		f.open("aucs");
		j = 0; int jj =0;
		auction* aucs = new auction[fulln];
		while (
			f.read((char*)& a, sizeof(auction))) {
			if (j == key)
			{
				a.closed = true; j++;
			}
			aucs[jj] = a;
			if (!a.closed) j++;
			jj++;
		}
		f.close();
		ofstream ff("aucs");
		for (int i = 0; i < fulln; i++) {
			ff.write((char*)& aucs[i], sizeof(auction));
		}
		ff.close();
	}
	//system("cls");
}
void addauc() {
	auction a,a1; bool isfake=true;
	ifstream f("aucs"); int id = 0;
	while (isfake) {
		system("cls");
		std::cout << "Enter name" << std::endl;
		std::cin >> a.name;
		while (f.read((char*)& a1, sizeof(auction))) {
			if (strcmp(a.name, a1.name) == 0)
				break;
			id++;
		}
		isfake = false;
	}
	f.close();
	std::cout << "Enter start price" << std::endl;
	std::cin >> a.startprice;
	ofstream ff("aucs",ios::app);
	a.id = id;
	a.closed = false;
	strcpy_s(a.better,"default"); 
	
	ff.write((char*)& a, sizeof(auction));
	system("pause");
}
int userint() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 2) % 2;
		if (key == 0) std::cout << "-> Auctions" << std::endl;
		else  std::cout << "   Auctions" << std::endl;
		if (key == 1) std::cout << "-> Exit" << std::endl;
		else  std::cout << "   Exit" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}
void u_aucs() {
	int key = 0;
	int code;
	ifstream f("aucs");
	auction a; int numb = 0, j = 0, fulln = 0;
	while (f.read((char*)& a, sizeof(auction))) {
		if (!a.closed)
			numb++;
		fulln++;
	}

	do {
		system("cls");
		f.close();
		f.open("aucs");
		key = (key + numb + 1) % (numb + 1);
		j = 0;
		while (
			f.read((char*)& a, sizeof(auction))) {

			if (!a.closed) {
			if (key == j) std::cout << "-> " << a.name << ' ' << a.startprice  << std::endl;
			else  std::cout << "   " << a.name << ' ' << a.startprice  << std::endl;
			j++;
			}

		}
		if (key == numb) std::cout << "-> Exit" << std::endl;
		else  std::cout << "   " << "Exit" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	int bet;
	if (key != numb) {
		std::cout << "Your bet ?" << std::endl;
		std::cin >> bet;
		f.close();
		f.open("aucs");
		j = 0; int jj = 0;
		auction* aucs = new auction[fulln];
		while (
			f.read((char*)& a, sizeof(auction))) {
			if (j == key)
			{
				if (a.startprice >= bet) {
					std::cout << "too small bet" << std::endl;
					system("PAUSE");
						return;
				}
				else {
					a.startprice = bet;
					strcpy_s(a.better, curlogin);
				}
			}
			aucs[jj] = a;
			if (!a.closed) j++;
			jj++;
		}
		f.close();
		ofstream ff("aucs");
		for (int i = 0; i < fulln; i++) {
			ff.write((char*)& aucs[i], sizeof(auction));
		}
		ff.close();
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");

	int answer ,ans1=0;
	while (ans1 == 0) {
			answer = menu();
			switch (answer)
			{
			case 0:  ans1 = login();  break;
			case 1:  registration(); ans1 = login();   break;

			}
	}
	switch (ans1) {
	case 1:
		ans1 = 0;
		while (ans1 != 1) {
			ans1=userint();
			switch (ans1) {
			case 0:
				u_aucs();
				break;
			case 1:
				std::cout << "txs" << std::endl;
				return 0;
			}
		}
		break;
	case 2:
		ans1 = 0;
		while (ans1 != 3) {
			ans1 = admint();
			switch (ans1) {
			case 0:
				
				users();
				break;
			case 1:
				auctions();
				
				break;
			case 2:
				addauc();
				
				break;
			case 3:
				std::cout << "txs" << std::endl;
				return 0;
			}
		}
		break;
	}
	system("pause");
	return 0;
}




// 500 reached