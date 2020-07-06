#include "../l/lib.h"

class DPaveTheParallelepiped {
public:
    int brute(int A, int B, int C) {
        int M = max(A,max(B,C));
        set<vector<int>> S;
        for (int i = 1; i <= A; ++i) {
            if (A%i) continue;
            for (int j = 1; j <= B; ++j) {
                if (B%j) continue;
                for (int k = 1; k <= C; ++k) {
                    if (C%k) continue;
                    vector<int> R{i,j,k};
                    sort(R.begin(),R.end());
                    S.insert(R);
                }
            }
        }
        return S.size();
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;

        vector<int> P(100001, 0);
        for (int i = 2; i <= 100000; ++i) {
            if (P[i] == 0) {
                for (int j = i; j <= 100000; j += i) P[j] = i;
            }
        }

        auto divs = [&](int a) {
            int x = 1;
            while (a != 1) {
                int b = P[a];
                int c = 1;
                while (P[a] == b) {
                    a /= b;
                    c++;
                }
                x *= c;
            }
            return x;
        };
        vector<int> D(100001, 0);
        for (int i = 1; i <= 100000; ++i) {
            D[i] = divs(i);
        }

        set<vector<int>> Sol;
        for (int i = 1; i < 8; ++i) {
            for (int j = i; j < 8; ++j) {
                for (int k = j; k < 8; ++k) {
                    if ((i|j|k)==7 && __builtin_popcount(i|j)>=2 && __builtin_popcount(j|k)>=2 && __builtin_popcount(i|k)>=2) {
                        vector<int> A{i,j,k};
                        Sol.insert(A);
                    }
                }
            }
        }
        vector<vector<int>> U(Sol.begin(),Sol.end());

        auto solve = [&](int A, int B, int C) {
            int G3 = D[gcd(A, gcd(B, C))];
            int GA = D[gcd(B,C)], GB = D[gcd(A,C)], GC = D[gcd(A,B)];
            vector<int> S(8, 0);
            S[7] = G3;
            S[3] = GC-G3;
            S[5] = GB-G3;
            S[6] = GA-G3;
            S[1] = D[A]-GC-GB+G3;
            S[2] = D[B]-GC-GA+G3;
            S[4] = D[C]-GA-GB+G3;
            ll ans = 0;
            for (auto &uu: U) {
                ll cur = 1;
                int p = 0, c = 0;
                for (int u: uu) {
                    if (u != p) { p = u; c = 0; }
                    else c++;
                    if (c == 0) cur *= S[u];
                    else if (c == 1) { cur *= (S[u]+1); cur /= 2; }
                    else if (c == 2) { cur *= (S[u]*S[u]+3*S[u]+2); cur /= 3; cur /= S[u]+1; }
                }
                ans += cur;
            }
            return ans;
        };
        for (int t = 0; t < T; ++t) {
            int A, B, C; cin >> A >> B >> C;
            cout << solve(A,B,C) << '\n';
        }
    }
};
