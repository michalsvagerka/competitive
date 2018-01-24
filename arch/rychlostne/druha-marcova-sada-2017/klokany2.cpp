#include "../l/lib.h"
// #include "../l/mod.h"

class klokany2 {
public:
    ui N, M;
    vector<vector<ui>> E;
    vector<set<ui>> T;
    vector<ui> D;
    vector<puu> Z, S;

    void dfs(ui u, ui d, map<ui,ui> &sk) {
        D[u] = d;
        for (ui t:T[u]) {
            auto it = sk.find(t+d);
            if (it != sk.end()) T[it->y].erase(it->x-D[it->y]);
            sk[t+d] = u;
        }

        for (ui v: E[u]) dfs(v, d+1, sk);
        for (ui t:T[u]) sk.erase(t+d);
    }

    void dfs2(ui u, ui d, map<ui,ui>&sk) {
        for (ui t:T[u]) sk[t+d] = u;

        auto it = sk.find(d);
        if (it != sk.end()) Z[u] = *it;
        else Z[u] = {-1,-1};

        for (ui v: E[u]) dfs2(v, d+1, sk);
        for (ui t:T[u]) sk.erase(t+d);
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        Z.resize(N);
        E.resize(N);
        T.resize(N);
        D.resize(N);
        for (ui i = 1; i < N; ++i) {
            int p; cin >> p; --p;
            E[p].push_back(i);
        }

        cin >> M;
        S.resize(M);
        for (ui i = 0; i < M; ++i) {
            cin >> S[i].x >> S[i].y;
            S[i].x--;
            T[S[i].x].insert(S[i].y);
        }

        map<ui,ui> sk;
        dfs(0, 0, sk);
        M = 0;
        for (ui i = 0; i < N; ++i) M += T[i].size();
        sk.clear();
        dfs2(0, 0, sk);

        map<puu, ui> C;
        C[{-1,-1}] = 1;
        ui e = 0;
        ui bl = N, bb = 0;
        for (ui b = 0; b < N; ++b) {
            while (e < N && M) {
                if (!C[Z[e]]++) --M;
                ++e;
            }

            if (!M && e-b < bl) { bl = e-b; bb = b; }
            if (!--C[Z[b]]) ++M;
        }

        cout << bb+1 << ' ' << bb+bl << endl;
    }
};
