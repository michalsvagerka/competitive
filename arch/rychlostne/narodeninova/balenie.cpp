#include "../l/lib.h"
// #include "../l/mod.h"

class balenie {
public:
    void solve(istream& cin, ostream& cout) {
        int A,B; cin >> A >> B;
        vector<string> C(A), D(B);
        vector<set<int>> E(B);
        cin >> C >> D;
        for (int o = 1; o <= 20; ++o) {
            for (int z = 1; z <= 20; ++z) {
                for (int h = 1; h <= 20; ++h) {
                    int c = 0;
                    bool ok = true;
                    for (int i = 0; i < A; ++i) {
                        int b = 0; while (b < C[i].size() && C[i][b] == '.') ++b;
                        if (b != c) { ok = false; break; }
                        for (;b < C[i].size(); ++b) {
                            switch (C[i][b]) {
                                case '(': c += o; break;
                                case ')': c -= o; break;
                                case '[': c += h; break;
                                case ']': c -= h; break;
                                case '{': c += z; break;
                                case '}': c -= z; break;
                            }
                        }
                    }

                    if (ok) {
                        for (int i = 0; i < B; ++i) {
                            E[i].insert(c);
                            for (char b : D[i]) {
                                switch (b) {
                                    case '(': c += o; break;
                                    case ')': c -= o; break;
                                    case '[': c += h; break;
                                    case ']': c -= h; break;
                                    case '{': c += z; break;
                                    case '}': c -= z; break;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < B; ++i) {
            if (E[i].size() == 1) {
                cout << *E[i].begin() << '\n';
            } else {
                cout << "-1\n";
            }
        }
    }
};
