#include "../l/lib.h"

class EGraphCutting {
public:
    vector<set<int>> E;
    vector<vector<int>> Ans;

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        E.resize(N);
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            E[a].insert(b);
            E[b].insert(a);
        }

        for (int i = 0; i < N; ++i) {
            if (!E[i].empty()) {
                vector<int> m;
                if (!make_euler(i, m) || m.size()%2 == 1) {
                    cout << "No solution\n";
                    return;
                } else {
                    int g = m.size();
                    for (int j = 0; j + 2 < g; j += 2) {
                        Ans.push_back({m[j], m[j+1], m[j+2]});
                    }
                }

            }
        }

        for (auto ans: Ans) cout << ans;
    }
};
