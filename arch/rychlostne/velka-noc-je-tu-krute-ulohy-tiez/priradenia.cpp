#include "../../../l/lib.h"
// #include "../l/mod.h"

class priradenia {
public:
    vector<vector<string>> current;
    unordered_map<string, vector<int>> assign;

    void read(istream &cin, ostream&cout, int level) {
        string s;
        while (cin >> s) {
            if (s == "}") {
                for (auto&r:current.back()) assign[r].pop_back();
                current.pop_back();
                return;
            } else if (s == "{") {
                current.emplace_back();
                read(cin, cout, level+1);
            } else {
                int z = 0;
                string v;
                while (s[z] != '=') v += s[z++];
                z++;
                int val = 0;

                string w;
                while (z < s.size()) w += s[z++];
                if (w[0] == '-' || (w[0] >= '0' && w[0] <= '9')) {
                    stringstream ss(w);
                    ss >> val;
                } else {
                    if (!assign[w].empty()) val = assign[w].back();
                    cout << val << '\n';
                }

                assign[v].push_back(val);
                current.back().push_back(v);
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        current.resize(1);
        read(cin, cout, 0);
    }
};
