#include "../l/lib.h"
 #include "../l/random.h"

class CJohnnySolving {
public:
    int N, M, K;
    vector<vector<int>> Cycles, E;
    vector<int> Path;
    vector<int> D, P, S;
    vector<bool> V;

    void dfs(int u, int p, int d) {
        if (Cycles.size() == K || !Path.empty()) return;

        P[u] = p;
        S[d] = u;
        D[u] = d;
        V[u] = true;

        if ((d+1)*K >= N) {
            for (int i = 0; i <= d; ++i) Path.push_back(S[i]);
            return;
        }

        bool hasNext = false;
        for (int v : E[u]) {
            if (!V[v]) {
                dfs(v, u, d+1);
                hasNext = true;
            }
        }

        if (!hasNext && Cycles.size() < K) {
            int w = -1;
            for (int v : E[u]) {
                if (D[v] != D[u] - 1) {
                    if ((D[u] - D[v] + 1)%3 != 0) {
                        vector<int> C;
                        for (int j = D[v]; j <= D[u]; ++j) C.push_back(S[j]);
                        reverse(C.begin(),C.end());
                        Cycles.push_back(C);
                        return;
                    } else if (w == -1) {
                        w = v;
                    } else {
                        vector<int> C;
                        if (D[w] > D[v]) swap(w,v);
                        for (int j = D[w]; j <= D[v]; ++j) C.push_back(S[j]);
                        C.push_back(u);
                        reverse(C.begin(),C.end());
                        Cycles.push_back(C);
                        return;
                    }
                }
            }
        }
    }


//    bool findRepr(vector<int> &C) {
//        for (int i = 0; i < C.size(); ++i) {
//            if (!Repr[C[i]]) {
//                Repr[C[i]] = true;
//                rotate(C.begin(),C.begin()+i,C.end());
//                return true;
//            }
//        }
//        return false;
//    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M >> K;
        E.resize(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        V.assign(N, false);
        D.assign(N, 0);
        P.assign(N, 0);
        S.resize(N);

        dfs(0, -1, 0);

        if (!Path.empty()) {
            cout << "PATH\n";
            cout << Path.size() << '\n';
            for (int i = 0; i < Path.size(); ++i) cout << Path[i]+1 << " \n"[i==Path.size()-1];
        } else {
            cout << "CYCLES\n";
            for (auto &cc: Cycles) {
                cout << cc.size() << '\n';
                for (int i = 0; i < cc.size(); ++i) cout << cc[i]+1 << " \n"[i==cc.size()-1];
            }
        }
    }
};
