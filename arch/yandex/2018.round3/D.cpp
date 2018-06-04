#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:

    vector<vector<int>> E;
    vector<int> A, S;
    vector<bool> K, V, U;

    int size(int u, int p) {
        V[u] = true;
        int s = 1;
        for (int v:E[u]) if (v!=p && U[v]) s += size(v,u);
        return S[u] = s;
    }

    int centroid(int u, int p, int n) {
        int s = n - S[u];
        for (int v:E[u]) if (v!=p && U[v]) s = max(s, S[v]);
        if (2*s <= n) {
            return u;
        } else {
            for (int v:E[u]) if (v!=p && U[v]) if (S[v] > n/2) return centroid(v,u,n);
        }
    }

    bool perf(int u, int p, int depth, double m, double &l, double &r) {
        bool hasV = false;
        if (K[u]) {
            hasV = true;
            l = max(l, A[u] - depth*m);
            r = min(r, A[u] + depth*m);
        }

        for (int v:E[u]) {
            if (v != p && U[v]) {
                hasV |= perf(v, u, depth+1, m, l, r);
            }
        }

        return hasV;
    }

    bool isPossible(int centr, double m) {
        double lo = -1e9, hi = 1e9;
        bool hasV = false;
        for (int v:E[centr]) {
            if (U[v]) {
                double l = -1e9, r = 1e9;
                if (perf(v, -1, 1, m, l, r)) {
                    hasV = true;
                    lo = max(lo, l);
                    hi = min(hi, r);
                }
            }
        }

        if (K[centr]) {
            hasV = true;
            lo = max(lo, double(A[centr]));
            hi = min(hi, double(A[centr]));
        }

        return !hasV || (lo <= hi + 1e-9);
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        A.resize(N);
        K.resize(N);
        E.resize(N);
        S.resize(N);
        for (int i = 0; i < N; ++i) {
            K[i] = (bool)(cin >> A[i]);
            if (!K[i]) {
                cin.clear();
                char c; cin >> c;
            }
        }

        if (count(K.begin(),K.end(),true) <= 1) {
            cout << 0.00000000 << endl;
            return;
        }

        double ans = 0.0;
        for (int i = 0; i < N-1; ++i) {
            int u,v; cin >> u >> v;
            --u; --v;
            if (K[u] && K[v]) {
                ans = max(ans, double(abs(A[u] - A[v])));
            } else {
                E[u].push_back(v);
                E[v].push_back(u);
            }
        }

        U = vector<bool>(N, true);

        bool calc;
        do {
            calc = false;

            V = vector<bool>(N, false);
            for (int i = 0; i < N; ++i) {
                if (!V[i] && U[i]) {
                    if (size(i, -1) > 1) {
                        int ctr = centroid(i, -1, S[i]);
                        U[ctr] = false;
                        calc = true;
                        double cur = bsld(0.0, 1e6, [&](double x) {
                            return isPossible(ctr, x);
                        }, 1e-9);
                        ans = max(cur, ans);
                    }
                }
            }
        } while (calc);

        cout << fixed << setprecision(10) << ans << endl;
    }
};
