#include "../../../l/lib.h"
#include "../../../l/string.h"
#include "../../../l/mod.h"

typedef Field<1000000009> F;

class reqsubstr {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> S(N); cin >> S;
        int C,L; cin >> C >> L;
        vector<KMP<string>> K;
        for (string s: S) K.emplace_back(s);
        map<vector<int>, F> M;
        M[vector<int>(N,0)] = 1;

        for (int l = 0; l < L; ++l) {
            map<vector<int>, F> Q;
            for (const auto&m: M) {
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    vector<int> T(N, 0);
                    for (int i = 0; i < N; ++i) {
                        T[i] = m.x[i] == S[i].size() ? S[i].size() : K[i].advance(m.x[i], ch);
                        if (S[i].size() - T[i] > L-l-1) T[i] = 0;
                    }
                    Q[T] += m.y;
                }
            }

            swap(Q,M);
        }

        F ans = 0;
        for (const auto&m : M) {
            int c = 0;
            for (int i = 0; i < N; ++i) c += m.x[i] == S[i].size();
            if (c == C) ans += m.y;
        }
        cout << ans << '\n';
    }
};
