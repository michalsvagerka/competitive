#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        int o = 0;
        while (E[o].empty()) ++o;
        deque<int> D;
        set<int> S;
        D.push_back(o);
        S.insert(o);
        while (true) {
            int q = -1;
            for (int v: E[D.back()]) {
                if (S.count(v) == 0) { q = v; break; }
            }
            if (q == -1) break;
            D.push_back(q);
            S.insert(q);
        }


        while (true) {
            int q = -1;
            for (int v: E[D.front()]) {
                if (S.count(v) == 0) { q = v; break; }
            }
            if (q == -1) break;
            D.push_front(q);
            S.insert(q);
        }

        vector<int> Ans(D.begin(),D.end());
        for (int&a:Ans) ++a;
        cout << Ans.size() << endl << Ans;
    }
};
