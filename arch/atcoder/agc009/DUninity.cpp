#include "../../../l/lib.h"

constexpr int MAX = 20;

class DUninity {
public:
    int N;
    vector<vector<int>> E;

    int dfs(int u, int p) {
        int any = 0, two = 0;
        for (int v: E[u]) if (v != p) {
            int s = dfs(v, u);
            two |= any & s;
            any |= s;
        }
        int ss = two?logceil(two):0;
        return (any >> ss) + 1 >> ss;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            E[a].push_back(b);
            E[b].push_back(a);
        }

        cout << logceil(dfs(0, -1)) - 1 << '\n';
    }
};
