#include "../l/lib.h"

class EDimaAndKicks {
public:

    map<pii,vector<pii>> E;
    set<pii> Visited;

    void dfs(pii v) {
        if (Visited.find(v) != Visited.end()) return;
        Visited.insert(v);
        for (pii w: E[v]) dfs(w);
    }


    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<int> A(N, M); cin >> A;
        vector<pii> V;
        vector<vector<int>> R(N), C(M);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (A[i][j]) {
                    int v = 0, h = 0;
                    v += i!=0 && A[i-1][j];
                    v += i!=N-1 && A[i+1][j];
                    h += j!=0 && A[i][j-1];
                    h += j!=M-1 && A[i][j+1];
                    if ((v && h) || (v + h == 1)) {
                        V.emplace_back(i,j);
                        R[i].push_back(j);
                        C[j].push_back(i);
                    }

                    if (v + h == 0) {
                        cout << "-1\n";
                        return;
                    }
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            sort(R[i].begin(),R[i].end());
            for (int j = 1; j < R[i].size(); ++j) {
                bool ok = true;
                for (int k = R[i][j-1] + 1; k < R[i][j]; ++k) ok &= A[i][k];
                if (ok) {
                    E[{i,R[i][j-1]}].emplace_back(i,R[i][j]);
                    E[{i,R[i][j]}].emplace_back(i,R[i][j-1]);
                }
            }
        }


        for (int j = 0; j < M; ++j) {
            sort(C[j].begin(),C[j].end());
            for (int i = 1; i < C[j].size(); ++i) {
                bool ok = true;
                for (int k = C[j][i-1] + 1; k < C[j][i]; ++k) ok &= A[k][j];
                if (ok) {
                    E[{C[j][i-1],j}].emplace_back(C[j][i], j);
                    E[{C[j][i],j}].emplace_back(C[j][i-1], j);
                }
            }
        }

        int odd = 0;
        for (auto &m: E) {
            odd += m.y.size() % 2;
        }

        if (odd > 2) {
            cout << "-1\n";
            return;
        }

        dfs(V[0]);
        if (Visited.size() != V.size()) {
            cout << "-1\n";
            return;
        }

        int g = 0;
        for (auto &m: E) {
            for (pii w: m.y) {
                g = gcd(g, abs(w.x-m.x.x) + abs(w.y-m.x.y));
            }
        }

        if (g == 1) {
            cout << "-1\n";
            return;
        }

        vector<int> Ans;
        for (int a = 2; a <= g; ++a) if (g % a == 0) Ans.push_back(a);
        cout << Ans;
    }
};
