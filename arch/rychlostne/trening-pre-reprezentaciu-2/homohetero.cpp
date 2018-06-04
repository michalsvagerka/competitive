#include "../l/lib.h"
// #include "../l/mod.h"

class homohetero {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        set<int> homo;
        map<int, int> hetero;
        for (int i = 0; i < N; ++i) {
            string S; int v;
            cin >> S >> v;
            if (S == "insert") {
                if (homo.find(v) != homo.end()) {
                    homo.erase(v);
                    hetero[v] = 2;
                } else if (hetero.find(v) != hetero.end()) {
                    hetero[v]++;
                } else {
                    homo.insert(v);
                }
            } else {
                if (homo.find(v) != homo.end()) {
                    homo.erase(v);
                } else if (hetero.find(v) != hetero.end()) {
                    hetero[v]--;
                    if (hetero[v] == 1) {
                        hetero.erase(v);
                        homo.insert(v);
                    }
                }
            }

            if (hetero.size() + homo.size() > 1) {
                cout << (hetero.empty() ? "hetero\n" : "both\n");
            } else {
                cout << (hetero.empty() ? "neither\n" : "homo\n");
            }
        }
    }
};
