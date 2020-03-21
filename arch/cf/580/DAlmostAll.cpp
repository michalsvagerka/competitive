#include "../l/lib.h"

class DAlmostAll {
public:
    int N;
    vector<vector<int>> E;
    vector<int> S;
    vector<pair<pii, int>> Ans;

    int size(int u, int p) {
        S[u] = 1;
        for (int v : E[u]) if (v != p) S[u] += size(v, u);
        return S[u];
    }

    void fill(int u, int p, int&cnt, int par, ll mul) {
        int mine = cnt;
        ll val = (cnt - par) * mul;
        val = min(1000000LL, val);
        Ans.push_back({{u+1, p+1}, val});
        cnt++;
        for (int v: E[u]) if (v != p) {
            fill(v, u, cnt, mine, mul);
        }
    }

    int centroid(int u, int p) {
        int m = N - S[u];
        for (int v : E[u]) if (v != p) m = max(m, S[v]);
        if (2 * m <= N) return u;

        for (int v : E[u]) if (v != p && 2 * S[v] > N) return centroid(v, u);
        return -1;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        S.assign(N, 0);
        size(0, -1);
        int ctr = centroid(0, -1);
        ll mul = 1;

        int M = E[ctr].size();
        size(ctr, -1);
        vector2<bool> B(M+1, N+1, false);
        B[0][0] = true;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j <= N; ++j) {
                if (B[i][j]) {
                    B[i+1][j] = true;
                    B[i+1][j+S[E[ctr][i]]] = true;
                }
            }
        }
//
//        for (int i = 0; i < M; ++i) {
//            cout << S[E[ctr][i]] << '\n';
//        }
//

        for (int i = 0; i <= N; ++i) {
            if (B[M][i] && (i+1)*(N-i-1)+i >= 2*N*N/9) {
                vector<bool> Left(M, false);
                int x = i;
                for (int j = M-1; j >= 0; --j) {
                    if (!B[j][x]) {
                        Left[j] = true;
                        x -= S[E[ctr][j]];
                    }
                }

//                cout << i << ' ' << Left << endl;
//                return;

                int c1 = 1, c2 = 1;
                for (int j = 0; j < M; ++j) {
                    if (Left[j]) {
                        fill(E[ctr][j], ctr, c1, 0, 1);
                    } else {
                        fill(E[ctr][j], ctr, c2, 0, i+1);
                    }
                }

                for (auto a: Ans) {
                    cout << a << '\n';
                }

                break;
            }
        }


    }
};
