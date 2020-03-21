#include "../l/lib.h"

class BNumbersOnTree {
public:
    int N;
    vector<vector<int>> E;
    vector<int> C;
    int root;
    bool ok = true;
    
    vector<int> solve(int u) {
        vector<int> ans;
        for (int v: E[u]) {
            auto a = solve(v);
            for (int aa: a) ans.push_back(aa);
        }
        if (C[u] > ans.size()) {
            ok = false;
        } else {
            ans.insert(ans.begin()+C[u], u);
        }
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;

        E.resize(N);
        C.resize(N);
        for (int i = 0; i < N; ++i) {
            int p,c; cin >> p >> c;
            if (p == 0) root = i;
            else E[p-1].push_back(i);
            C[i] = c;
        }

        auto A = solve(root);
        if (!ok) {
            cout << "NO\n";
        } else {
            vector<int> Ans(N);
            for (int i = 0; i < N; ++i) {
                Ans[A[i]] = i+1;
            }
            cout << "YES\n" << Ans;
        }
    }
};
