#include "../l/lib.h"
 #include "../l/mod.h"
#include "../l/matrix.h"
#include <numeric>

class D {
public:
    int N, G;
    vector<map<vector<vector<int>>, pair<pii,bool>>> I;


    bool isomorphic(const vector<vector<int>> &E, const vector<vector<int>> &F) {
        vector<int> P(N);
        iota(P.begin(),P.end(),0);
        do {
            bool cool = true;
            for (int i = 0; i < N; ++i) {
                vector<int> X, Y;
                if (F[P[i]].size() != E[i].size()) { cool = false; break; }
                for (int j : F[P[i]]) X.push_back(j);
                for (int j : E[i]) Y.push_back(P[j]);
                sort(X.begin(),X.end());
                sort(Y.begin(),Y.end());
                if (X!=Y) { cool = false; break; };
            }
            if (cool) return true;
        } while (next_permutation(P.begin(),P.end()));
        return false;
    }

    void dfs(const vector<vector<int>> &E, int u, int &v) {
        if (v&(1<<u)) return;
        v |= 1<<u;
        for (int w:E[u]) dfs(E, w, v);
    }

    bool connected(const vector<vector<int>> &E) {
        int v = 0;
        dfs(E, 0, v);
        return __builtin_popcount(v) == N;
    }

    void gen(int b, pair<pii,bool> P, const vector<vector<int>> &E, Matrix<FieldMod> &Trans) {

        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                vector<vector<int>> F(N);
                bool isRem = false;
                for (int k = 0; k < N; ++k) {
                    for (int l:E[k]) {
                        if ((i == k && l == j) || (i == l && k == j)) {
                            isRem = true;
                        } else {
                            F[k].push_back(l);
                        }
                    }
                }
                if (!isRem) { F[i].push_back(j); F[j].push_back(i); }
                int nb = isRem ? b-1 : b+1;
                for (auto&i:I[nb]) {
                    if (isomorphic(i.x, F)) {
                        Trans[i.y.x.y][P.x.y] += FieldMod{1} / G;
                        break;
                    }
                }
            }
        }

    }



void solve(istream& cin, ostream& cout) {
    cin >> N;

    G = N * (N - 1) / 2;
    I.resize(G + 1);

    int tot = 0, conn = 0;
    for (int m = 0; m < (1 << G); ++m) {
        vector<vector<int>> E(N);

        int p = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (m & (1 << p)) {
                    E[i].push_back(j);
                    E[j].push_back(i);
                }
                ++p;
            }
        }

        int b = __builtin_popcount(m);
        bool found = false;
        for (auto &i:I[b]) {
            if (isomorphic(i.x, E)) {
                i.y.x.x++;
                found = true;
                break;
            }
        }

        if (!found) {
            bool isConn = connected(E);
            conn += isConn;
            I[b][E] = {{1, tot++}, isConn};
        }
    }


    Matrix<FieldMod> Trans(tot, tot);
    vector<int> Conn(tot), Unconn(tot, -1);
    int z = 0;
    for (int b = 0; b <= G; ++b) {
        for (auto &i:I[b]) {
            gen(b, i.y, i.x, Trans);
            Conn[i.y.x.y] = z++;
            if (!i.y.y) Unconn[i.y.x.y] = z++;
        }
    }

    Matrix<FieldMod> TT(z, z, 0);
    for (int i = 0; i < tot; ++i) {
        for (int j = 0; j < tot; ++j) {
            TT[Conn[i]][Conn[j]] = Trans[i][j];
            if (Unconn[j] != -1) {
                if (Unconn[i] != -1) {
                    TT[Unconn[i]][Unconn[j]] = Trans[i][j];
                } else {
                    TT[Conn[i]][Unconn[j]] = Trans[i][j];
                }
            }
        }
    }

    vector<Matrix<FieldMod>> V{TT};
    for (int i = 0; i < 60; ++i) {
        V.push_back(V[i] * V[i]);
    }

    int M;
    cin >> M;
    vector<vector<int>> R(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        R[u].push_back(v);
        R[v].push_back(u);
    }

    int id = -1;
    for (auto &i:I[M]) {
        if (isomorphic(R, i.x)) {
            id = i.y.x.y;
        }
    }

    int realId = Conn[id];
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        ll L, R;
        cin >> L >> R;
        vector<FieldMod> ST(z, 0);
        ST[realId] = 1;
        if (L > 0) {
            ll g = L;
            for (int i = 60; i >= 0; --i) {
                if (g & (1LL << i)) {
//                    cerr << V[i].rows() << ' ' << V[i].columns() << ' ' << ST.size() << endl;
                    ST = V[i] * ST;
                }
            }
        }

        for (int i = 0; i < tot; ++i) {
            if (Unconn[i] != -1) {
                ST[Unconn[i]] += ST[Conn[i]];
                ST[Conn[i]] = 0;
            }
        }

        ll g = R - L;
        for (int i = 60; i >= 0; --i) {
            if (g & (1LL << i)) {
                ST = V[i] * ST;
            }
        }

        FieldMod ans = 0;
        for (int i = 0; i < tot; ++i) {
            ans += ST[Conn[i]];
        }
        cout << ans << '\n';
    }
}
};
