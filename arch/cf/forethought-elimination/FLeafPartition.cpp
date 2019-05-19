#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class FLeafPartition {
public:
    vector<vector<int>> E;

    pair<FF, FF> solve(int u) {
        if (E[u].empty()) return {1,1};
        
        vector<FF> ans{1,0,0};
        for (int v: E[u]) {
            auto s = solve(v);
            vector<FF> res{0,0,0};
            res[0] = ans[0] * s.x;
            res[1] = ans[0] * s.y + ans[1] * s.x;
            res[2] = ans[1] * s.y + ans[2] * s.x + ans[2] * s.y;
            ans = res;
        }
        return {ans[0]+ans[2], ans[1]+ans[2]};
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N-1); cin >> P;
        E.resize(N);
        for (int i = 0; i < N-1; ++i) E[P[i]-1].push_back(i+1);
        auto s = solve(0);
        cout << s.x << endl;
    }
};
