#include "../l/lib.h"
// #include "../l/mod.h"

class godfather {
public:
    vector<vector<ui>> E;
    vector<ui> S,Q;
    ui N;

    void calc(ui u, ui p) {
        ui s = 1;
        Q[u] = 0;
        for (ui v:E[u]) if (v!=p) {
                calc(v,u);
                s += S[v];
                Q[u] = max(Q[u], S[v]);
            }
        S[u] = s;
        Q[u] = max(Q[u], N - s);
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);S.resize(N);Q.resize(N);
        for (ui i = 0; i < N - 1; ++i) {
            ui a,b; cin >> a >> b;
            --a; --b;
            E[a].push_back(b);
            E[b].push_back(a);
        }
        calc(0,-1);
        int m = *min_element(Q.begin(),Q.end());
        vector<int> M;
        for (int i = 0; i < N; ++i) {
            if (Q[i] == m) M.push_back(i+1);
        }
        cout << M;
    }
};
