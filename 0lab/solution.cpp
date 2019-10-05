#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm> //for std::sort
#include <locale> //for isalnum

using namespace std;

class Word {
    public:
        Word(string word, int fr) {
            str = word;
            freq = fr;
        }
        const string get_str() {
            return str;
        }
        const int get_freq() const {
            return freq;
        }
    private:
        string str;
        int freq;
};

bool operator<(Word const &a, Word const &b) {
    return a.get_freq() > b.get_freq();
}

int read_in(map<string, int>& mp, const string fname) {
    ifstream fin(fname.c_str(), ifstream::in);
    if (!fin.is_open()) {
        throw "Unable to open input file: " + fname;
    }

    string line;
    int n = 0;

    while (getline(fin, line)) {
        string word;
        for (int i = 0; i < line.size(); i++) {
            if (isalnum(line[i])) {
                word.push_back(line[i]);
                continue;
            }
            if (word.empty()) {
                continue;
            }
            mp[word]++;
            n++;
            word.clear();
        }
        mp[word]++;
        n++;
    }

    fin.close();
    return n;
}

 void write_out(const int n, const vector<Word>& v, const string fname) {
    ofstream fout(fname.c_str());
    if (!fout.is_open()) {
        throw "Unable to open or create output file: " + fname;
    }

    for(auto it : v) {
        fout << it.get_str() << "," << it.get_freq() <<"," << float(it.get_freq()) / n * 100 << "%" << endl;
    }

    fout.close();
}

int main(int argc, char **argv) {
    try {
        map<string, int> mp;

        int n = read_in(mp, argv[1]);

        vector <Word> v;
        for (auto it : mp) {
            Word word(it.first, it.second);
            v.push_back(word);
        }
        sort(v.begin(), v.end());

        write_out(n, v, argv[2]);

        mp.clear();
    } catch(string error) {
        cerr << "Exception: " << error << endl;
    }
}
