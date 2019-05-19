#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class DPalindromeXOR {
public:
    vector<vector<pii>> E;
    vector<bool> V, P, U, F;
    void bipartite(int u, bool p, bool&ok) {
        if (V[u]) {
            ok &= P[u] == p;
            return;
        }

        V[u] = true;
        P[u] = p;

        for (pii v: E[u]) {
            if (v.y == 1) {
                bipartite(v.x, !p, ok);
            } else {
                bipartite(v.x, p, ok);
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int M = S.size();

        FF tot = 0;
        for (int i = 1; i < M; ++i) {

            E.clear(); E.resize(M + i);
            V.assign(M+i, false);
            P.assign(M+i, false);
            U.assign(M+i, false);
            F.assign(M+i, false);

            bool ok = true;
            for (int j = 0; j < i; ++j) {
                if (S[M-j-1] == '0') {
                    E[j].push_back({M + j, 0});
                    E[M + j].push_back({j, 0});
                } else if (S[M-j-1] == '1') {
                    E[j].push_back({M+j, 1});
                    E[M + j].push_back({j, 1});
                }
            }

            for (int j = 0; j < M/2; ++j) {
                E[j].push_back({M-1-j, 0});
                E[M-1-j].push_back({j, 0});
            }


            for (int j = 0; j < i/2; ++j) {
                E[M+j].push_back({M+i-1-j, 0});
                E[M+i-1-j].push_back({M+j, 0});
            }

            for (int j = i; j < M; ++j) {
                if (S[M-j-1] == '0') {
                    U[j] = true;
                    F[j] = false;
                } else if (S[M-j-1] == '1') {
                    U[j] = true;
                    F[j] = true;
                }
            }

            U[0] = true;
            F[0] = true;
            U[M] = true;
            F[M] = true;

            for (int j = 0; j < M+i; ++j) {
                if (U[j]) {
                    bipartite(j, F[j], ok);
                }
            }

            FF ans = 1;
            for (int j = 0; j < M+i; ++j) {
                if (!V[j]) {
                    bipartite(j, true, ok);
                    ans *= 2;
                }
            }

            if (ok) {
                tot += ans;
            }
        }

        cout << tot << endl;
    }
};
