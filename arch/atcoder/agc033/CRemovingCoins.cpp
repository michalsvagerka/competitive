#include "../l/lib.h"

class CRemovingCoins {
public:
    vector<vector<int>> E;
    
    pii dfs(int u, int p) {
        int mxOne = 0;
        int mxTwo = 0;
        for (int v : E[u]) {
            if (v != p) {
                pii q = dfs(v, u);
                mxTwo = max(mxTwo, q.x + 1 + mxOne);
                mxTwo = max(mxTwo, q.y);
                mxOne = max(mxOne, q.x + 1);
            }
        }
        
        return {mxOne, mxTwo};
    }
    
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            E[a].push_back(b);
            E[b].push_back(a); 
        }
        
        auto ans = dfs(0, -1);
        if (ans.y % 3 == 1) {
            cout << "Second\n";
        } else {
            cout << "First\n";
        }
    }
};
