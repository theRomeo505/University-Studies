// 01.21.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;
//var 14
enum role { client = 0, adm = 1 };
char curlogin[20]="";
struct user {
	char login[20];
	char password[20];
	role role;//
	int id;
};
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
		if (key == 0) cout << "-> Login" << endl;
		else  cout << "   Login" << endl;
		if (key == 1) cout << "-> Register" << endl;
		else  cout << "   Register" << endl;
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
	user newu, test;
	cout << "Enter ur login:" << endl;
	cin >> newu.login;
	cout << "Enter ur password:" << endl;
	cin >> newu.password;
	ifstream f("base");
	while (!f.eof()) {
		f.read((char*)& test, sizeof(user));
		
		if (strcmp(test.login,newu.login)==0) {
			if (strcmp(test.password,newu.password)==0)
			{
				//cout << "Success"; 
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
		cout << "Enter ur login:" << endl;
		cin >> newu.login;
		f1.seekg(0, f1.beg);
		while (f1.read((char*)& t, sizeof(user))){
			if (strcmp(newu.login, t.login) == 0) {
				break;
			}
			ch = false;
			id++;
		}
	}
	f1.close();
	cout << "Enter ur password:" << endl;
	cin >> newu.password;
	cout << "Enter ur role:" << endl;
	cin >> c;
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
		if (key == 0) cout << "-> Users" << endl;
		else  cout << "   Users" << endl;
		if (key == 1) cout << "-> Auctions" << endl;
		else  cout << "   Auctions" << endl;
		if (key == 2) cout << "-> Add auction" << endl;
		else  cout << "   Add auction" << endl;
		if (key == 3) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
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
		cout << newu.login <<' '<<newu.id<<' '<<newu.role<< endl;
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
				if (key == j) cout << "-> " << a.name << ' ' << a.startprice<<' '<<a.better<<' '<<a.closed << endl;
				else  cout << "   " << a.name << ' ' << a.startprice <<  ' '<<a.better  <<' '<<a.closed<< endl;
				j++;
			//}
			
		}
		if (key == fulln) cout << "-> Exit" << endl;
		else  cout << "   " << "Exit" << endl;
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
		cout << "Enter name" << endl;
		cin >> a.name;
		while (f.read((char*)& a1, sizeof(auction))) {
			if (strcmp(a.name, a1.name) == 0)
				break;
			id++;
		}
		isfake = false;
	}
	f.close();
	cout << "Enter start price" << endl;
	cin >> a.startprice;
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
		if (key == 0) cout << "-> Auctions" << endl;
		else  cout << "   Auctions" << endl;
		if (key == 1) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
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
			if (key == j) cout << "-> " << a.name << ' ' << a.startprice  << endl;
			else  cout << "   " << a.name << ' ' << a.startprice  << endl;
			j++;
			}

		}
		if (key == numb) cout << "-> Exit" << endl;
		else  cout << "   " << "Exit" << endl;
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
		cout << "Your bet ?" << endl;
		cin >> bet;
		f.close();
		f.open("aucs");
		j = 0; int jj = 0;
		auction* aucs = new auction[fulln];
		while (
			f.read((char*)& a, sizeof(auction))) {
			if (j == key)
			{
				if (a.startprice >= bet) {
					cout << "too small bet" << endl;
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
				cout << "txs" << endl;
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
				cout << "txs" << endl;
				return 0;
			}
		}
		break;
	}
	system("pause");
	return 0;
}
