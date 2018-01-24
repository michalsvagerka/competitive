#include "../l/lib.h"
#include "../l/fenwick.h"

class virusy {
public:
    vector<vector<int>> E;
    vector<int> I,O;
    int N,T,R;
    Fenwick<int> F;
    ll ans;

    void dfs(int u) {
        I[u] = T++;
        for (int v:E[u]) dfs(v);
        O[u] = T-1;
    }

    void dfs2(int u) {
        F.add(I[u], 1);
        ans -= F.range(I[u], O[u]);
        for (int v:E[u]) dfs2(v);
        ans += F.range(I[u], O[u]);
    }

    void convert(const vector<int> &P) {
        E.clear(); E.resize(N);
        for (int i = 0; i < N; ++i) {
            if (P[i] == 0) R = i;
            else E[P[i]-1].push_back(i);
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        vector<int> C(N), D(N);
        cin >> C >> D;

        I.resize(N); O.resize(N);
        T = 0;
        convert(C);
        dfs(R);

        F = Fenwick<int>(N, 0);
        ans = 0;
        convert(D);
        dfs2(R);

        cout << ans << endl;
    }
};
