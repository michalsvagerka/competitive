#include "../l/lib.h"

class sentence {
public:
    vector<vector<pair<int, bool>>> E;
    vector<bool> V;
    vector<bool> T;

    bool dfs(int u, bool part, int &p1, int &p2) {
        if (V[u]) return T[u] == part;

        V[u] = true;
        T[u] = part;
        if (part) p1++; else p2++;
        bool ret = true;
        for (auto e:E[u]) {
            ret &= dfs(e.x, e.y ^ part, p1, p2);
        }
        return ret;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        while (N) {
            E.clear();
            E.resize(N);
            V.resize(N);
            fill(V.begin(),V.end(),false);
            T.resize(N);
            for (int i = 0; i < N; ++i) {
                string a,b,c; int id;
                cin >> a >> id >> b >> c;
                bool d = c == "false.";
                E[i].push_back({--id,d});
                E[id].push_back({i,d});
            }
            bool ok = true;
            int ans = 0;
            for (int i = 0; i < N && ok; ++i) {
                if (!V[i]) {
                    int p1 = 0, p2 = 0;
                    ok &= dfs(i, true, p1, p2);
                    ans += max(p1, p2);
                }
            }
            if (ok) cout << ans << '\n';
            else cout << "Inconsistent\n";
            cin >> N;
        }
    }
};
