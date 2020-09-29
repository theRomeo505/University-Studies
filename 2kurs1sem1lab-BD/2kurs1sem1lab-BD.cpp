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
	int projkey;
};
struct Project {
	int key;
	char name[20];
	int price;
	int nextkey;
	bool exists;
};

void createCust(vector<int> &index) {
	FILE *f=fopen("customers", "wb+"); /// ab+
	fclose(f);
	f = fopen("customers", "rb+");
	Customer c;
	cout << "enter name:\n";
	cin >> c.name;
	cout << "enter rating";
	cin >> c.rating;
	c.exists = true;
	c.projkey = -1;
	bool p = true;
	fseek(f, 0, 2);
	//cout << ftell(f)<<' '<<sizeof(Customer)<<endl;
	int fileindex = ftell(f) / sizeof(Project);
	for (int i = 0; i < index.size(); i++) {
		if (index[i] == -1)
		{
			p = false;
			c.key = i;
			index[i] = fileindex;
			break;
		}
	}
	if (p) {
		c.key = index.size();
		index.push_back(fileindex);
	}
	Customer cust; cust.exists = 1; int i = 0;
	fseek(f, 0, 0);

	while (cust.exists!=0 && fread(&cust,sizeof(Customer),1,f)!=NULL) {
		i++;
	}
	if (cust.exists == 0) {
		fseek(f, (i - 1) * sizeof(Customer), 0);
	}
	else {
		fclose(f);
		f = fopen("customers", "ab+");
	}
	fwrite(&c,sizeof(Customer),1,f);
	fclose(f);
}
void createProj(vector<int> &index) {
	FILE* f = fopen("projects", "ab+");
	fclose(f);
	f = fopen("projects", "rb+");/// ab+
	int custkey;
	Project c;
	cout << "enter name:\n";
	cin >> c.name;
	cout << "enter price";
	cin >> c.price;
	cout << "enter customer key";
	cin >> custkey;
	c.exists = true;
	FILE* f1 = fopen("customers", "rb+");
	//vector<Customer> vec;
	Customer cc;
	fseek(f1, sizeof(Customer) * custkey, 0);
	fread(&cc, sizeof(Customer), 1, f1);
	fclose(f1);
	


	fseek(f, 0, 2);
	//cout << ftell(f)<<' '<<sizeof(Customer)<<endl;
	int fileindex = ftell(f) / sizeof(Project);
	bool p = true;
	for (int i = 0; i < index.size(); i++) {
		if (index[i] == -1)
		{
			p = false;
			c.key = i;
			index[i] = fileindex;
			break;
		}
	}
	if (p) {
		c.key = index.size();
		index.push_back(fileindex);
	}
	f1 = fopen("customers", "rb+");
	if (cc.projkey == -1)
	{
		
		cc.projkey = fileindex;
		c.nextkey = -1;
		fseek(f1, sizeof(Customer) * custkey, 0);
		fwrite(&cc, sizeof(Customer), 1, f1);
		
	}
	else {
		fseek(f1, sizeof(Customer) * custkey, 0);
		int i = cc.projkey;
		cc.projkey = c.key;
		c.nextkey = i;
		fwrite(&cc, sizeof(Customer), 1, f1);
		
	}
	fclose(f1);
	fseek(f, 0, 0);
	Project proj; proj.exists = 1; int i = 0;
	while (proj.exists != 0 && fread(&proj, sizeof(Project), 1, f) != NULL) {
		i++;
	}
	if (proj.exists == 0) {
		//cout << i << "exist";
		fseek(f, (i - 1) * sizeof(Project), 0);
	}
	else {
		fclose(f);
		f = fopen("projects", "ab+");
	}
	fwrite(&c, sizeof(Customer), 1, f);
	fclose(f);

}


void deleteCust(int id, vector<int>& index, vector<int>& indexpro) {
	
	FILE* f=fopen("customers","rb+");
	Customer p;
	fseek(f, sizeof(Customer)*id, 0);
	fread(&p, sizeof(Customer), 1, f);

		
	
	p.exists = 0;
	fseek(f, sizeof(Customer) * id, 0);
	fwrite(&p, sizeof(Customer), 1, f);
	fclose(f);

	f = fopen("projects", "rb+");
	Project pp;
	int next = p.projkey;
	while (next != -1) {
		fseek(f, sizeof(Project )* indexpro[next], 0);
		fread(&pp, sizeof(Project),1, f);
		cout << "k" << pp.key << ' ' << pp.nextkey << " " << endl;
		
		pp.exists = 0;
		fseek(f, sizeof(Project) * indexpro[next], 0);
		fwrite(&pp, sizeof(Project), 1, f);
		indexpro[pp.key] = -1;
		next = pp.nextkey;
		//cout <<"k"<< pp.key <<' '<<next<<" "<< indexpro[next]<< endl<<endl;
		
		system("PAUSE");
	}
	
	fclose(f);
	
	index[id] = -1;
}
void deleteProj(int id, vector<int>& index) {
	
	FILE* f = fopen("projects", "rb+");
	Project pr;
	while (fread(&pr, sizeof(Project), 1, f) != NULL ) {
		if (pr.nextkey == id && pr.exists)
			break;
	}
	//cout << "key of previus" << pr.key << endl;
	if (pr.nextkey == id) {
		//pr previous
		Project pro;
		fseek(f, sizeof(Project) * id, 0);
		fread(&pro, sizeof(Project), 1, f);
		//pro - cur key=id
		//cout << "our key" << pro.key <<index[pro.key]<< endl;
		pro.exists = 0;
		fseek(f, sizeof(Project) * index[pro.key], 0);
		fwrite(&pro, sizeof(Project), 1, f);
		if (pro.nextkey != -1) {
			fseek(f, sizeof(Project) * index[pro.nextkey], 0);
			fread(&pro, sizeof(Project), 1, f);
			//cout << "nextkey" << pro.key << endl;
			//pro next after id 
			pr.nextkey = pro.key;
		}
		else {
			pr.nextkey = -1;
		}
		fseek(f, sizeof(Project) * index[pr.key], 0);
		fwrite(&pr, sizeof(Project), 1, f);
	}
	fclose(f);
	index[id] = -1;
}

void changeCust(int id, vector<int>& index) {
	FILE* f = fopen("customers", "rb+");
	Customer cust;
	fseek(f, sizeof(Customer) * index[id], 0);
	fread(&cust, sizeof(Customer), 1, f);
			char g[20];
			cout << "enter name (or 0 to keep)";
			cin >> g;
			if (g != "0")
				strcpy(cust.name ,g);
			cout << "enter rating(or 0 tio keep)";
			int gg;
			cin >> gg;
			if (g != "0")
				cust.rating = gg;
			fseek(f, sizeof(Customer) * index[id], 0);
		fwrite(&cust, sizeof(Customer), 1, f);
	
	fclose(f);
}
void changeProj(int id, vector<int>& index) {
	FILE* f = fopen("projects", "rb+");
	Project proj;
	//f = fopen("projects", "wb");
	fseek(f, sizeof(Project) * index[id], 0);
	fread(&proj, sizeof(Project), 1, f);
			char g[20];
			cout << "enter name (or 0 to keep)"<<endl;
			cin >> g;
			if (g != "0")
				strcpy(proj.name ,g);
			cout << "enter price(or 0 to keep)" << endl;
			int gg;
			cin >> gg;
			if (g != "0")
				proj.price = gg;
			
			fseek(f, sizeof(Project) * index[id], 0);
		fwrite(&proj, sizeof(Project), 1, f);
	
	fclose(f);
}

void infoCust(int id, vector<int>& index, vector<int>& indexpro) {
	FILE* f = fopen("customers", "rb+");
	fseek(f, sizeof(Customer)*index[id], 0);
	
	Customer cust;
	fread(&cust, sizeof(Customer), 1, f);
	cout << cust.name<< ' '<<cust.rating<<endl;
	cout << "projects:" << endl;
	fclose(f);

	f = fopen("projects", "rb+");
	Project pr; int count = 0,next=cust.projkey;
	while (next != -1)
	{
		fseek(f, sizeof(Project) * indexpro[next], 0);
		fread(&pr, sizeof(Project), 1, f);
		next = pr.nextkey;
		if (pr.exists)
		cout << pr.name << ' ' << pr.price << endl; count++;
	}
			
		
	
	cout << count << " projects"<<endl;
	//cout << "ku";

	fclose(f);
	//cout << "ku";
}
void infoProj(int id, vector<int>& index) {
	FILE* f=fopen("projects","rb");
	Project pr;
	fseek(f, sizeof(Project) * index[id], 1);
	fread(&pr, sizeof(Project), 1, f);
	cout << pr.name << ' ' << pr.price << endl;
	fclose(f);
}

void coutAll() {
	FILE* f = fopen("customers", "rb");
	Customer r;
	while (fread(&r, sizeof(Customer), 1, f) != NULL) {
		cout << r.name << " k" << r.key << 'e' << r.exists <<"p"<<r.projkey <<endl;
		
	}
	cout << endl;
	fclose(f);
	f = fopen("projects", "rb");
	Project p;
	while (fread(&p, sizeof(Project), 1, f) != NULL) {
		cout << p.name << " k" << p.key << 'e' << p.exists<<"n"<<p.nextkey << endl;

	}

	fclose(f);
}

void count(vector<int> indexcus, vector<int> indexpro)
{
	int cus = 0, pro = 0;
	for (int i = 0; i < indexcus.size(); i++) {
		if (indexcus[i] != -1)
			cus++;

	}
	for (int i = 0; i < indexpro.size(); i++) {
		if (indexpro[i] != -1)
			pro++;

	}
}
int main()
{	

	////////
	FILE* f = fopen("incust", "ab+");
	vector<int> indexcus;int t;
	int max = 0;
	while (fread(&t, sizeof(int), 1, f) != NULL) {
		int y = t;
		fread(&t, sizeof(int), 1, f);
		if (t > max)
			max = t;
		indexcus[y] = t;
	}
	for (int i = 0; i < indexcus.size(); i++) {
		if (indexcus[i] > max || indexcus[i] < 0)
			indexcus[i] = -1;
	}
	fclose(f);
	f = fopen("inproj", "ab+");
	vector<int> indexpro; max = 0;
	while (fread(&t, sizeof(int), 1, f) != NULL) {
		int y = t;
		fread(&t, sizeof(int), 1, f);
		if (t > max)
			max = t;
		indexpro[y] = t;
	}
	fclose(f);
	for (int i = 0; i < indexpro.size(); i++) {
		if (indexpro[i] > max || indexpro[i] < 0)
			indexpro[i] = -1;
	}
	////////
	cout << "1-create cust" << endl;
	cout << "2-create proj" << endl;
	cout << "3-delete cust" << endl;
	cout << "4-delete proj" << endl;
	cout << "5-change cust" << endl;
	cout << "6-change proj" << endl;
	cout << "7-info cust" << endl;
	cout << "8-info proj" << endl;
	cout << "9-show all" << endl;
	cout << "10-exit" << endl;
	int a;int id;
	while (true) {
		cin >> a;
		switch (a) {
		case 1:
			createCust(indexcus);
			break;
		case 2:
			createProj(indexpro); break;
		case 3:
			
			cout << "enter id" << endl;
			cin >> id;
			deleteCust(id,indexcus,indexpro); break;
		case 4:
			cout << "enter id" << endl;
			cin >> id;
			deleteProj(id,indexpro); break;
		case 5:
			cout << "enter id" << endl;
			cin >> id;
			changeCust(id,indexcus); break;
		case 6:
			cout << "enter id" << endl;
			cin >> id;
			changeProj(id,indexpro); break;
		case 7:
			cout << "enter id" << endl;
			cin >> id;
			infoCust(id,indexcus,indexpro); break;
		case 8:
			cout << "enter id" << endl;
			cin >> id;
			infoProj(id,indexpro); break;
		case 9:
			coutAll(); break;
		case 10:
			f = fopen("incust", "wb");
			for (int i = 0; i < indexcus.size(); i++) {
				if (indexcus[i] != -1) {
					fwrite(&i, sizeof(int), 1, f);
					fwrite(&indexcus[i], sizeof(int), 1, f);
				}
			}
			fclose(f);
			f = fopen("inproj", "wb");
			for (int i = 0; i < indexpro.size(); i++) {
				if (indexpro[i] != -1) {
					fwrite(&i, sizeof(int), 1, f);
					fwrite(&indexpro[i], sizeof(int), 1, f);
				}
			}
			fclose(f);
			return 0;
		}
	}
	return 0;
}


