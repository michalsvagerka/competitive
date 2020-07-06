#include "../l/lib.h"

class A1AddOnATree {
public:
    int N;
    vector<vector<int>> E;
    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u,v; cin >> u >> v; --u; --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        for (int i = 0; i < N; ++i) {
            if (E[i].size() == 2) {
                cout << "NO\n";
                return;
            }
        }

        cout << "YES\n";

    }
};
