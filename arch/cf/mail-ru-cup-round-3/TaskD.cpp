#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
    vector<vector<int>> E;
    vector<int> L;

    int leafs(int u) {
        L[u] = E[u].empty();
        for (int v : E[u]) L[u] += leafs(v);
        return L[u];
    }


    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        E.resize(N);
        L.assign(N, 0);

        for (int i = 1; i < N; ++i) {
            int p; cin >> p; --p;
            E[p].push_back(i);
        }

        leafs(0);
        sort(L.begin(),L.end());
        cout << L;
    }
};
