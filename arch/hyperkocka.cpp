#include "../l/lib.h"
// #include "../l/mod.h"

class hyperkocka {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<vector<int>> E(N);
        int M; cin >> M;
        for (int i = 0; i < M; ++i) {
            int u,v; cin >> u >> v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        int D = E[0].size();
        for (int i = 0; i < N; ++i) {
            sort(E[i].begin(),E[i].end());
        }

        vector<int> F(N, -1);
        vector<int> B(N, -1);
        F[0] = 0;
        B[0] = 0;
        for (int i = 0; i < D; ++i) {
            F[1<<i] = E[0][i];
            B[E[0][i]] = 1<<i;
        }

        for (int z = 0; z < N; ++z) {
            if (__builtin_popcount(z) < 2) continue;
            int a=0;
            while (!(z&(1<<a))) ++a;
            int b=a+1;
            while (!(z&(1<<b))) ++b;
            int u = F[z^(1<<a)], v = F[z^(1<<b)];
            int i = 0, j = 0;
            while (true) {
                if (E[u][i] < E[v][j]) ++i;
                else if (E[u][i] > E[v][j]) ++j;
                else if (B[E[u][i]] != -1) {
                    ++i; ++j;
                } else {
                    F[z] = E[u][i];
                    B[E[u][i]] = z;
                    break;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < D; ++j) {
                cout << ((B[i] >> j)&1);
            }
            cout << '\n';
        }

        
    }
};
