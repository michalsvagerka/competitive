#include "../l/lib.h"
#include "../l/mod.h"
class BApplemanAndTree {
public:
    vector<vector<int>> E;
    vector<int> C;

    pair<FieldMod, FieldMod> dfs(int u) {
        FieldMod b = 0, w = 0;
        if (C[u]) b++; else w++;
        for (int v : E[u]) {
            auto ans = dfs(v);
            b = b*ans.x + w*ans.y;
            w = w*ans.x;
        }

        return {w+b, b};
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        E.resize(N);
        C.resize(N);
        for (int i = 1; i < N; ++i) {
            int p; cin >> p;
            E[p].push_back(i);
        }
        cin >> C;
        auto ans = dfs(0);
        cout << ans.y << endl;
    }
};
