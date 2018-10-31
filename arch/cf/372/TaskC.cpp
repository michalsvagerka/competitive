#include "../l/lib.h"
 #include "../l/mod.h"

class TaskC {
public:
    int N, M;
    vector<vector<pii>> E;
    vector<int> S, P;
    vector<bool> V, U;
    vector<int> A, AA;

    int size(int u, int p) {
        V[u] = true;
        int s = 1;
        for (pii v:E[u]) if (v.x!=p && U[v.x]) s += size(v.x,u);
        return S[u] = s;
    }

    int centroid(int u, int p, int n) {
        int s = n - S[u];
        for (pii v:E[u]) if (v.x!=p && U[v.x]) s = max(s, S[v.x]);
        if (2*s <= n) {
            return u;
        } else {
            for (pii v:E[u]) if (v.x!=p && U[v.x]) if (S[v.x] > n/2) return centroid(v.x,u,n);
        }
    }

    void run(int u, int p, vector<pair<int,int>> &forward, vector<int> &backward, int curForw, int curBack, int depth) {
        forward.push_back({curForw, depth});
        backward.push_back(curBack);

        for (pii v:E[u]) {
            if (v.x != p && U[v.x]) {
                run(v.x, u, forward, backward, (curForw * 10ll + v.y)%M, (curBack + v.y * ll(A[depth]))%M, depth+1);
            }
        }
    }

    ll cnt(vector<pii>&F, vector<int>&B) {
        unordered_map<int,int> C;
        for (pii f: F) C[(ll(M-f.x) * AA[f.y]) % M]++;
        ll ans = 0;
        for (int b:B) ans += C[b];
        return ans;
    }

    ll perf(int ctr) {
        vector<pii> F; vector<int> B;

        ll ans = 0;
        for (pii v:E[ctr]) {
            if (U[v.x]) {
                vector<pii> forw;
                vector<int> back;
                run(v.x, -1, forw, back, v.y%M, v.y%M, 1);
                ans -= cnt(forw, back);
                copy(forw.begin(), forw.end(), back_inserter(F));
                copy(back.begin(), back.end(), back_inserter(B));
            }
        }

        for (pii f: F) ans += (f.x == 0);
        for (int b: B) ans += (b == 0);

        return ans + cnt(F,B);
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        A.resize(N+1); AA.resize(N+1);
        A[0] = AA[0] = 1;

        for (int i = 1; i <= N; ++i) {
            A[i] = (10ll*A[i-1])%M;
            AA[i] = Ring::div<ll>(1ll, A[i], M);
        }

        E.resize(N); S.resize(N), P.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u, v, w; cin >> u >> v >> w;
            E[u].push_back({v,w});
            E[v].push_back({u,w});
        }

        U = vector<bool>(N, true);
        ll ans = 0;
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
                        ans += perf(ctr);
                    }
                }
            }
        } while (calc);

        cout << ans << endl;
    }
};
