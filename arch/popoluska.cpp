#include "../l/lib.h"
// #include "../l/mod.h"

class popoluska {
public:
    void solve(istream& cin, ostream& cout) {
        int T;cin>>T;
        for (int t = 0; t < T; ++t) {
            string S; cin >> S;
            int a = 0, b = 0; ll c = 0, d = 0;
            for (int i = 0; i < S.size(); ++i) {
                if (S[i] == '.') {
                    d += i - b;
                    ++b;
                } else {
                    c += i - a;
                    ++a;
                }
            }
            if (c <= d) {
                for (int i = 0; i < a; ++i) cout << "o";
                for (int i = a; i < S.size(); ++i) cout << ".";
            } else {
                for (int i = 0; i < b; ++i) cout << ".";
                for (int i = b; i < S.size(); ++i) cout << "o";
            }
            cout << endl;
        }
    }
};
