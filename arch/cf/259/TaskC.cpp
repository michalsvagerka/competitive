#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    int N, M;
    vector<vector<int>> E;
    vector<int> X, P;
    vector<bool> V;

    bool hasOdd(int u) {
        if (V[u]) return false;
        V[u] = true;
        bool ans = false;
        if (X[u]) ans = true;

        for (int v:E[u]) {
            if (hasOdd(v)) ans = true;
        }
        return ans;
    }

    void dfs(int u, int p) {
        V[u] = true;
        P.push_back(u);
        X[u] = !X[u];
        for (int v:E[u]) {
            if (!V[v]) {
                dfs(v, u);
                P.push_back(u);
                X[u] = !X[u];
            }
        }

        if (X[u] && p != -1) {
            P.push_back(p);
            P.push_back(u);
            X[u] = !X[u];
            X[p] = !X[p];
        }
    }

void solve(istream& cin, ostream& cout) {
    cin >> N >> M;
    E.resize(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }

    V = vector<bool>(N, false);
    X.resize(N); cin >> X;

    vector<int> Odd;
    for (int i = 0; i < N; ++i) {
        if (hasOdd(i)) {
            Odd.push_back(i);
        }
    }

    if (Odd.size() >= 2) {
        cout << "-1\n";
        return;
    } else if (Odd.empty()) {
        cout << "0\n";
        return;
    } else {
        fill(V.begin(),V.end(),false);
        dfs(Odd[0], -1);
        if (X[Odd[0]]) {
            P.push_back(E[Odd[0]][0]);
            P.push_back(Odd[0]);
            P.push_back(E[Odd[0]][0]);
            X[Odd[0]] = !X[Odd[0]];
        }
        cout << P.size() << '\n';
        for (int &p:P) ++p;
        cout << P;
    }
}
};
