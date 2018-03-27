#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    vector<vector<int>> E;
    int N,M;
    bool cycle;
    vector<int> P;
    vector2<bool> V;
    vector<bool> I;

    bool dfs(int u, bool vasya) {
        if (I[u]) cycle = true;
        if (V[u][vasya]) return false;
        V[u][vasya] = true;


        if (E[u].empty()) {
            if (vasya) { P.push_back(u+1); return true; }
            else return false;
        }

        I[u] = true;
        P.push_back(u+1);

        for (int v:E[u]) {
            if (dfs(v,!vasya)) return true;
        }

        I[u] = false;
        P.pop_back();
        return false;
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        E.resize(N);
        cycle = false;
        I = vector<bool>(N, false);
        V = vector2<bool>(N, 2, false);
        for (int i = 0; i < N; ++i) {
            int c; cin >> c;
            for (int j = 0; j < c; ++j) {
                int p; cin >> p;
                E[i].push_back(p-1);
            }
        }

        int S; cin >> S; --S;
        if (dfs(S, false)) {
            cout << "Win\n";
            cout << P;
        } else if (cycle) {
            cout << "Draw\n";
        } else {
            cout << "Lose\n";
        }
    }
};
