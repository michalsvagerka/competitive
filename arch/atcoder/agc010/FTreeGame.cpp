#include "../l/lib.h"
// #include "../l/mod.h"

class FTreeGame {
public:
    int N;
    vector<int> A;
    vector<vector<int>> E;

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        A.resize(N);
        cin >> A;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        vector<pii> G;
        for (int i = 0; i < N; ++i) {
            G.push_back({A[i],i});
        }
        sort(G.begin(),G.end());
        vector<bool> W(N, false);
        for (pii g : G) {
            for (int v : E[g.y]) {
                if (A[g.y] > A[v] && !W[v]) W[g.y] = true;
            }
        }

        vector<int> Ans;
        for (int i = 0; i < N; ++i) if (W[i]) Ans.push_back(i+1);
        cout << Ans;
    }
};
