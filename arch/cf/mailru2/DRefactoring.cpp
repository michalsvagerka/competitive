#include "../l/lib.h"
 #include "../l/string.h"

class DRefactoring {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<string> S(N), T(N); cin >> S >> T;

    set<string> A, B;
    vector<int> beg(N);
    vector<bool> U(N, false);
    for (int i = 0; i < N; ++i) {
        int j = 0, k = S[i].size()-1;
        while (j < S[i].size() && S[i][j] == T[i][j]) ++j;
        while (k >= 0 && S[i][k] == T[i][k]) --k;
        if (j != S[i].size()) {
            beg[i] = j;
            A.insert(S[i].substr(j, k-j+1));
            B.insert(T[i].substr(j, k-j+1));
            U[i] = true;
        }
    }

    if (A.size() > 1 || B.size() > 1) { cout << "NO\n"; return; }

    int len = A.begin()->size();
    while (true) {
        char c = 0;
        bool ok = true;
        for (int i = 0; i < N; ++i) {
            if (U[i]) {
                if (beg[i] == 0) ok = false;
                else {
                    if (c == 0) c = S[i][beg[i]-1];
                    ok &= S[i][beg[i]-1] == c && T[i][beg[i]-1] == c;
                }
            }
        }
        if (ok) {
            for (int i = 0; i < N; ++i) if (U[i]) beg[i]--;
            ++len;
        } else break;
    }

    while (true) {
        if (beg[0] + len == S[0].size()) break;
        char c = 0;
        bool ok = true;
        for (int i = 0; i < N; ++i) {
            if (U[i]) {
                if (beg[i] + len == S[i].size()) ok = false;
                else {
                    if (c == 0) c = S[i][beg[i] + len];
                    ok &= S[i][beg[i] + len] == c && T[i][beg[i] + len] == c;
                }
            }
        }
        if (ok) {
            ++len;
        } else break;
    }

    int i = 0; 
    while (!U[i]) ++i;
    string a = S[i].substr(beg[i], len);
    string b = T[i].substr(beg[i], len);

    KMP<string> K(a);
    for (int i = 0; i < N; ++i) {
        auto x = K.search(S[i]);
        if (!x.empty()) S[i].replace(x[0], a.size(), b);
        if (S[i] != T[i]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n" << a << '\n' << b << '\n';
}
};
