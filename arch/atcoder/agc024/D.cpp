#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    int N;
    vector<vector<int>> E;

    vector<int> bfs(int u) {
        vector<int> D(N, -1);
        vector<int> Q{u};
        D[u] = 0;
        for (int i = 0; i < N; ++i) {
            int q = Q[i];
            for (int v:E[q]) {
                if (D[v] == -1) {
                    D[v] = D[q] + 1;
                    Q.push_back(v);
                }
            }
        }
        return D;
    }

    void dfs(int u, int p, int d, vector<int> &M) {
        M[d] = max(M[d], (int)E[u].size() - (p!=-1));
        for (int v:E[u]) if (v != p) dfs(v, u, d+1, M);
    }

    ll getAns(const vector<int>&U) {
        ll ans = 1;
        for (int u:U) ans *= u;
        return ans;
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }


        vector<int> D = bfs(0);
        pii l{0,0};
        for (int i = 0; i < N; ++i) l = max(l, {D[i],i});

        int source = l.y;
        D = bfs(l.y);
        l = {0,0};
        for (int i = 0; i < N; ++i) l = max(l, {D[i],i});

        int target = l.y;
        auto D2 = bfs(l.y);
//        cout << source+1 << ' ' << target+1 << ' ' << l.x << endl;

        vector<int> C;
        for (int i = 0; i < N; ++i) {
            if (D[i] + D2[i] == l.x && D[i] >= l.x/2 && D2[i] >= l.x/2) {
                C.push_back(i);
            }
        }

        ll ans = 0;
        vector<int> U(l.x/2+1, 1);
        if (C.size() == 1) {
            dfs(C[0], -1, 0, U);
            ans = getAns(U);

            for (int v:E[C[0]]) {
                U = vector<int>(l.x/2+1, 1);
                dfs(C[0], v, 0, U);
                dfs(v, C[0], 0, U);
                ans = min(2*getAns(U), ans);
            }
        } else {
            dfs(C[0], C[1], 0, U);
            dfs(C[1], C[0], 0, U);
            ans = 2*getAns(U);
        }
        cout << l.x/2 + 1 << ' ' << ans << endl;
    }
};
