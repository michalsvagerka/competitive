#include "../l/lib.h"
// #include "../l/mod.h"

class trasa {
public:
    void test(istream &cin, ostream &cout) {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> E(N);
        vector<pii> F;
        vector2<bool> G(N, N, false);
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            E[a].push_back(b);
            E[b].push_back(a);
            G[a][b] = G[b][a] = true;
            if (a > b) swap(a, b);
            F.push_back({a, b});
        }

        for (int i = 0; i < N; ++i) {
            sort(E[i].begin(), E[i].end());
        }

        int triangles = 0;
        int triangleEdges = 0;
        ll squares = 0;
        vector2<vector<int>> C(N, N);
        vector<int> P(N, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                set_intersection(E[i].begin(), E[i].end(), E[j].begin(), E[j].end(), back_inserter(C[i][j]));
                if (G[i][j]) {
                    P[i] += E[j].size() - 1;
                    P[j] += E[i].size() - 1;
                }
                ll s = C[i][j].size();
                squares += s * (s - 1) / 2;

                for (int k = j + 1; k < N; ++k) {
                    if (G[i][j] && G[j][k] && G[i][k]) {
                        triangles++;
                        triangleEdges += E[i].size() + E[j].size() + E[k].size() - 6;
                    }
                }
            }
        }

        ll res = 0;
        for (const pii &f : F) {
            int a = f.x;
            int b = f.y;
            int c = P[f.x] - (E[f.y].size() - 1);
            int d = P[f.y] - (E[f.x].size() - 1);
            res += c * d;
        }

        cout << 2*(res - 3*triangles - 3*triangleEdges - 2*squares) << '\n';
    }

    void solve(istream &cin, ostream &cout) {
        int T; cin >> T;
        while(T--) test(cin, cout);
    };
};