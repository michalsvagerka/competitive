#include "../l/lib.h"
// #include "../l/mod.h"

class BMinimumDiameterTree {
public:
    int N, S;
    vector<vector<int>> E;

    void solve(istream& cin, ostream& cout) {
        cin >> N >> S;

        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        int leaves = 0;
        for (int i = 0; i < N; ++i) {
            leaves += E[i].size() == 1;
        }

        cout << fixed << setprecision(18) << double(2*S)/leaves << endl;


    }
};
