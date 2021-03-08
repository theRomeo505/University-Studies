#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
using namespace std;
struct group {
    string name;
    string students;
};
struct params {
    int a;
    int b;
    int p;
    int m;
};
class perfect_h {
public:

    params param;
    vector<pair<params, vector<group>>> data;
    perfect_h(int a, int b, int p, int m) {
        param.a = a; param.b = b; param.p = p; param.m = m;
        data.resize(param.m);
    }
    int first_hashing(vector<group> grs) {
        vector<vector<group>> pre;
        pre.resize(param.m);
        int hashed = 0;
        int hashed_two = 0;
        for (auto& gr : grs) {
            pre[string_hash(gr.students, param)].push_back(gr);
        }
        for (int i = 0; i < grs.size(); i++) {
            if (pre[i].size() != 0)
                data[i].second.resize(pre[i].size() * pre[i].size());
        }
        for (int i = 0; i < pre.size(); i++) {

            //cout << pre[i].size() << " ";
            if (pre[i].size() > 1) second_hashing(pre, i);
        }
        //cout << endl << endl;

        for (auto& gr : grs) {
            hashed = string_hash(gr.students, param);

            if (data[hashed].second.size() == 1) {
                data[string_hash(gr.students, param)].second[0] = gr;
            }
        }

        cout << endl << endl;
        return 0;
    }
    void second_hashing(vector<vector<group>> pre, int col) {

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, 100);
        params temp{ dist(mt),dist(mt),param.p,(int)data[col].second.size() };

        
        int i = 0;
        while (true) {


            int sec = string_hash(pre[col][i].students, temp);
            if (data[col].second[sec].students.empty()) {
                data[col].second[sec] = pre[col][i];
                i++;
            }
            else {
                for (auto& z : data[col].second) {
                    z.students = "";
                    z.name = "";
                }
                temp.a = dist(mt);
                temp.b = dist(mt);
                i = 0;

            }
            if (i == pre[col].size()) { data[col].first = temp; return; }
        }
        // }
     //}
    }

    static int string_hash(const string& input, params currentParams) {
        int hash = 0;
        int power = 1;
        for (char i : input) {
            hash = (hash * currentParams.a + currentParams.b + (int)i * power) % currentParams.m;
            power = (power * currentParams.p) % currentParams.m;
        }
        return hash;
    }
    void search(const string& input) {
        const string err = "no elem\n";
        int hashed = string_hash(input, param);
        if (hashed<0 || hashed>data.size() || data[hashed].second.size() == 0) { cout << err; return; }
        if (data[hashed].second.size() == 1) {
            if (input == data[hashed].second[0].students)
                cout << hashed  << "0" << data[hashed].second[0].students << " " << data[hashed].second[0].name << endl;
            else cout << err;
        }
        else if (data[hashed].second.size() > 1) {
            int second = string_hash(input, data[hashed].first);
            if (input == data[hashed].second[second].students) {
                cout << hashed << " ";
                cout << second << " " << data[hashed].second[second].students << " "
                    << data[hashed].second[second].name << endl;
            }
        }
    }
};


int main() {
    vector<group> keys{ {"K29", "R,i,o,ou"},
                           {"K28","o,p,u,ty,k"},
                           {"K27", "op,pom,lk"},
                           {"K26", "bhj,bhj,lkn"},
                           {"K25", "ivanov,ppupkin"},
                           {"K24", "sid"},
                           {"K23", "varus,novus"},
    };
    srand(time(NULL));
    perfect_h map(rand() % 100 + 1, rand() % 101 + 1, 101, keys.size());

    map.first_hashing(keys);
    for (int i = 0; i < map.data.size(); i++) {
        for (int j = 0; j < map.data[i].second.size(); j++) {
            cout <<   i << " " << j << " " << map.data[i].second[j].students << endl;
        }
        cout << endl;
    }
    string find;
    while (find != "-") {
        cin >> find;
        map.search(find);
    }

    return 0;
}
