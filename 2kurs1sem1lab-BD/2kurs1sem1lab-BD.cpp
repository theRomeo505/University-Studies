// 2kurs1sem1lab-BD.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

struct Customer {
	int key;
	char name[20];
	int rating;
	bool exists;
};
struct Project {
	int key;
	char name[20];
	int price;
	int custkey;
	bool exists;
};

void createCust() {
	FILE *f=fopen("customers", "ab+"); /// ab+
	Customer c;
	cout << "enter name:\n";
	cin >> c.name;
	cout << "enter rating";
	cin >> c.rating;
	c.exists = true;
	fseek(f, 0, 2);
	//cout << ftell(f)<<' '<<sizeof(Customer)<<endl;
	c.key = ftell(f) / sizeof(Customer);
	fseek(f, SEEK_END, 1);
	fwrite(&c,sizeof(Customer),1,f);
	fclose(f);
}
void createProj() {
	FILE* f = fopen("projects", "ab+"); /// ab+
	Project c;
	cout << "enter name:\n";
	cin >> c.name;
	cout << "enter price";
	cin >> c.price;
	cout << "enter customer key";
	cin >> c.custkey;
	c.exists = true;
	fseek(f, 0, 2);
	//cout << ftell(f)<<' '<<sizeof(Customer)<<endl;
	c.key = ftell(f) / sizeof(Project);
	fseek(f, SEEK_END,1);
	fwrite(&c, sizeof(Project), 1, f);
	fclose(f);
}


void deleteCust(int id) {
	FILE* f=fopen("customers","rb");
	vector<Customer> m;
	Customer p;
	while (fread(&p, sizeof(Customer), 1, f) != NULL) {
		m.push_back(p);
	}
	m[id].exists = 0;
	fclose(f);

	f = fopen("customers", "wb");
	for (int i = 0; i < m.size(); i++)
		fwrite(&m[i], sizeof(Customer), 1, f);
	fclose(f);
	m.clear();
	/////
	f = fopen("projects", "rb");
	vector<Project> proj;
	Project pr;
	while (fread(&pr, sizeof(Project), 1, f) != NULL) {
		if (pr.custkey == id)
			pr.exists = 0;
		proj.push_back(pr);
	}
	fclose(f);
	f = fopen("projects", "wb");
	for (int i = 0; i < proj.size(); i++)
		fwrite(&proj[i], sizeof(Project), 1, f);
	fclose(f);
	proj.clear();
	
}
void deleteProj(int id) {
	FILE* f = fopen("projects", "rb");
	vector<Project> proj;
	Project pr;
	while (fread(&pr, sizeof(Project), 1, f)) {
		proj.push_back(pr);
	}
	fclose(f);
	f = fopen("projects", "wb");
	for (int i = 0; i < proj.size(); i++) {
		if (i == id)
			proj[i].exists = false;
		fwrite(&proj[i], sizeof(Project), 1, f);
	}
	proj.clear();
	fclose(f);
}

void changeCust(int id) {
	FILE* f = fopen("customers", "rb");
	vector<Customer> custs;
	Customer cust;
	while (fread(&cust, sizeof(Customer), 1, f))
		custs.push_back(cust);
	fclose(f);
	f = fopen("customers", "wb");
	for (int i = 0; i < custs.size(); i++) {
		if (i == id) {
			char g[20];
			cout << "enter name (or 0 to keep)";
			cin >> g;
			if (g != "0")
				strcpy(custs[i].name ,g);
			cout << "enter rating(or 0 tio keep)";
			int gg;
			cin >> gg;
			if (g != "0")
				custs[i].rating = gg;
		}
		fwrite(&custs[i], sizeof(Customer), 1, f);
	}
	fclose(f);
}
void changeProj(int id) {
	FILE* f = fopen("projects", "rb");
	vector<Project> projs;
	Project proj;
	while (fread(&proj, sizeof(Project), 1, f))
		projs.push_back(proj);
	fclose(f);
	f = fopen("projects", "wb");
	for (int i = 0; i < projs.size(); i++) {
		if (i == id) {
			char g[20];
			cout << "enter name (or 0 to keep)"<<endl;
			cin >> g;
			if (g != "0")
				strcpy(projs[i].name ,g);
			cout << "enter price(or 0 to keep)" << endl;
			int gg;
			cin >> gg;
			if (g != "0")
				projs[i].price = gg;
			cout << "enter customer (or -1 to keep)" << endl;
			cin >> gg;
			if (gg != -1)
				projs[i].custkey = gg;
		}
		fwrite(&projs[i], sizeof(Project), 1, f);
	}
	fclose(f);
}

void infoCust(int id) {
	FILE* f = fopen("customers", "rb");
	fseek(f, sizeof(Customer)*id, 0);
	
	Customer cust;
	fread(&cust, sizeof(Customer), 1, f);
	cout << cust.name<< ' '<<cust.rating<<endl;
	cout << "projects:" << endl;
	fclose(f);

	f = fopen("projects", "rb");
	Project pr; int count = 0;
	while (fread(&pr, sizeof(Project), 1, f) != NULL) {
		if (pr.custkey == id && pr.exists)
		{
			cout << pr.name << ' ' << pr.price << endl; count++;
		}
	}
	cout << count << " projects"<<endl;
	//cout << "ku";

	fclose(f);
	//cout << "ku";
}
void infoProj(int id) {
	FILE* f=fopen("projects","rb");
	Project pr;
	fseek(f, sizeof(Project) * id, 1);
	fread(&pr, sizeof(Project), 1, f);
	cout << pr.name << ' ' << pr.price << endl;
	fclose(f);
	f = fopen("customers", "rb");
	fseek(f, sizeof(Customer) * pr.custkey, 1);
	Customer cust;
	fread(&cust, sizeof(Customer), 1, f);
	cout << cust.name << ' ' << cust.rating << endl;
	fclose(f);
}

void coutAll() {
	FILE* f = fopen("customers", "rb");
	Customer r;
	while (fread(&r, sizeof(Customer), 1, f) != NULL) {
		cout << r.name << ' ' << r.key << ' ' << r.exists << endl;
		
	}
	cout << endl;
	fclose(f);
	f = fopen("projects", "rb");
	Project p;
	while (fread(&p, sizeof(Project), 1, f) != NULL) {
		cout << p.name << ' ' << p.key<< ' '<< p.custkey << ' ' << p.exists << endl;

	}

	fclose(f);
}

void count()
{
	FILE* f = fopen("projects", "rb");
	fseek(f, 0, 2);
	int count = ftell(f) / sizeof(Project);
	fclose(f);
	f = fopen("customers", "rb");
	fseek(f, 0, 2);
	cout << count << "projects" << endl;
	count = ftell(f) / sizeof(Customer);
	cout << count << "customers";
	fclose(f);
	
}
int main()
{
	cout << "1-create cust" << endl;
	cout << "2-create proj" << endl;
	cout << "3-delete cust" << endl;
	cout << "4-delete proj" << endl;
	cout << "5-change cust" << endl;
	cout << "6-change proj" << endl;
	cout << "7-info cust" << endl;
	cout << "8-info proj" << endl;
	cout << "9-show all" << endl;
	int a;int id;
	while (true) {
		cin >> a;
		switch (a) {
		case 1:
			createCust();
			break;
		case 2:
			createProj(); break;
		case 3:
			
			cout << "enter id" << endl;
			cin >> id;
			deleteCust(id); break;
		case 4:
			cout << "enter id" << endl;
			cin >> id;
			deleteProj(id); break;
		case 5:
			cout << "enter id" << endl;
			cin >> id;
			changeCust(id); break;
		case 6:
			cout << "enter id" << endl;
			cin >> id;
			changeProj(id); break;
		case 7:
			cout << "enter id" << endl;
			cin >> id;
			infoCust(id); break;
		case 8:
			cout << "enter id" << endl;
			cin >> id;
			infoProj(id); break;
		case 9:
			coutAll(); break;
		}
	}
	return 0;
}


