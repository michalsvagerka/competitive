#include "../l/lib.h"
// #include "../l/mod.h"

class FTreeTacToe {
public:
    int N;
    vector<vector<int>> E;
    string S;

    vector<int> D;
    void dist(int u, int p, int d) {
        D[u] = d;
        for (int w: E[u]) if (w != p) dist(w, u, d+1);
    }

    bool subgraph1(int u) {
        vector<int> Z;
        for (int v : E[u]) Z.push_back(E[v].size());
        sort(Z.begin(),Z.end());
        return Z[1] >= 2;
    }

    bool path4(int u) {
        vector<int> Z;
        for (int v : E[u]) Z.push_back(E[v].size());
        sort(Z.begin(),Z.end());
        return Z.size() >= 2 && Z[1] >= 2;
    }

    bool won() {
        vector<int> Wh;
        for (int i = 0; i < N; ++i) if (S[i] == 'W') Wh.push_back(i);
        if (Wh.size() >= 3) return true;
        vector<int> D3;
        for (int i = 0; i < N; ++i) {
            if (E[i].size() >= 4) return true;
            if (E[i].size() == 3 && subgraph1(i)) return true;
            if (E[i].size() == 3) D3.push_back(i);
        }

        if (Wh.size() == 2) {
            if (!D3.empty()) return true;
            if (E[Wh[0]].size() != 1 || E[Wh[1]].size() != 1) return true;
            D.resize(N);
            dist(Wh[0], -1, 0);
            if (D[Wh[1]] % 2 == 0) return true;
        }

        for (int wh: Wh) {
            if (path4(wh)) return true;
            if (E[wh].size() >= 3) return true;
            D.resize(N);
            dist(wh, -1, 0);
            for (int i = 0; i < N; ++i) if (E[i].size() == 3 && D[i] % 2 == 1) return true;
        }
        
        if (D3.size() >= 3) return true;
        if (D3.size() == 2) {
            D.resize(N);
            dist(D3[0], -1, 0);
            if (D[D3[1]] % 2 == 0) return true;
        }

        return false;
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> N;
            E.clear(); E.resize(N);
            for (int i = 0; i < N - 1; ++i) {
                int u, v; cin >> u >> v;
                --u; --v;
                E[u].push_back(v);
                E[v].push_back(u);
            }

            cin >> S;

            if (won()) {
                cout << "White\n";
            } else {
                cout << "Draw\n";
            }
        }
    }
};
