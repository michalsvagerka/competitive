#include "../l/lib.h"

class DTreeFactory {
public:
    int N;
    vector<vector<int>> E;
    vector<int> D, A, R;
    int C;

    int depth(int u) {
        int d = 0;
        for (int v: E[u]) d = max(d, 1 + depth(v));
        return D[u] = d;
    }
    
    int dfs(int u, int up) {
        A[C++] = u;
        for (int i = 0; i < up; ++i) R.push_back(u);
        
        up = 0;
        for (int v : E[u]) {
            up = dfs(v, up);
        }
        return up + 1;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        vector<int> P(N-1); cin >> P;
        E.clear(); E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            E[P[i]].push_back(i+1);
        }

        D.assign(N, 0);
        depth(0);
        for (int i = 0; i < N; ++i) {
            sort(E[i].begin(),E[i].end(), [&](int u, int v) {
                return D[u] < D[v];
            });
        }

        A.assign(N, -1);
        C = 0;
        dfs(0, 0);
        
        cout << A << R.size() << '\n' << R;
    }
};
