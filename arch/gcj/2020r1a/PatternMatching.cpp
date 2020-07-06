#include "../l/lib.h"

class PatternMatching {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<string> P(N); cin >> P;
            vector<int> L(N), R(N);
            for (int i = 0; i < N; ++i) {
                L[i] = 0;
                while (P[i][L[i]] != '*') L[i]++;
                R[i] = 0;
                while (P[i][P[i].size()-1-R[i]] != '*') R[i]++;
            }
            string Prefix;
            for (int i = 0; i < N; ++i) {
                if (L[i] > Prefix.size()) {
                    Prefix = P[i].substr(0, L[i]);
                }
            }
            string Suffix;
            for (int i = 0; i < N; ++i) {
                if (R[i] > Suffix.size()) {
                    Suffix = P[i].substr(P[i].size()-R[i], R[i]);
                }
            }
            bool ok = true;
            for (int i = 0; i < N; ++i) {
                string pref = P[i].substr(0, L[i]);
                ok &= (pref == Prefix.substr(0, L[i]));
            }
            for (int i = 0; i < N; ++i) {
                string suf = P[i].substr(P[i].size()-R[i], R[i]);
                ok &= (suf == Suffix.substr(Suffix.size()-R[i],R[i]));
            }

            if (ok) {
                cout << "Case #" << t+1 << ": " << Prefix;
                for (int i = 0; i < N; ++i) {
                    for (int j = L[i]; j + R[i] < P[i].size(); ++j) {
                        if (P[i][j] != '*') cout << P[i][j];
                    }
                }
                cout << Suffix << '\n';
            } else {
                cout << "Case #" << t+1 << ": *\n";
            }
        }

    }
};
