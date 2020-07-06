#include "../l/lib.h"

class BBeautifulSequence {
public:
    void solve(istream& cin, ostream& cout) {
        int A, B, C, D; cin >> A >> B >> C >> D;
        if (B < A-1 || C < D-1) {
            cout << "NO\n";
            return;
        }
        vector<string> S;
        if (A != 0) {
            string T;
            for (int i = 0; i < A-1; ++i) T += "01";
            T += '0';
            S.push_back(T);
            B -= A-1;
            A = 0;
        }
        if (D != 0) {
            string T;
            for (int i = 0; i < D-1; ++i) T += "32";
            T += '3';
            S.push_back(T);
            C -= D-1;
            D = 0;
        }
        if (B > 1 && C > 1) {
            string T;
            int m = min(B,C);
            for (int i = 0; i < m-2; ++i) T += "12";
            B -= m-2;
            C -= m-2;
            if (!T.empty())
                S.push_back(T);
        }
        for (int i = 0; i < B; ++i) S.push_back("1");
        for (int i = 0; i < C; ++i) S.push_back("2");

        if (S.size() > 10) {
            cout << "NO\n";
            return;
        }

        int Q = S.size();
        vector<int> P(Q);
        for (int i = 0; i < Q; ++i) {
            P[i] = i;
        }

        do {
            bool ok = true;
            for (int i = 0; i < Q-1; ++i) {
                ok &= abs(S[P[i]].back() - S[P[i+1]][0]) == 1;
            }
            if (ok) {
                vector<int> V;
                for (int i = 0; i < Q; ++i) {
                    for (char c: S[P[i]]) V.push_back(c-'0');
                }
                cout << "YES\n" << V;
                return;
            }
        } while (next_permutation(P.begin(),P.end()));
        cout << "NO\n";
    }
};
