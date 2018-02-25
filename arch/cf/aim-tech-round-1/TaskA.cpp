#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<bool> E(N,N,false);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u][v] = E[v][u] = true;
        }

        string S(N, ' ');
        for (int i = 0; i < N; ++i) {
            if (count(E[i].begin(),E[i].end(),true) == N-1) {
                S[i] = 'b';
            }
        }


        int k = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] == 'b') continue;
            if (S[i] == ' ') {
                if (k == 2) {
                    cout << "No\n";
                    return;
                }
                S[i] = "ac"[k];
                for (int j = 0; j < N; ++j) {
                    if (!E[i][j]) continue;
                    if (S[j] == 'b') continue;
                    if (S[j] == ' ' || S[j] == S[i]) {
                        S[j] = S[i];
                    } else {
                        cout << "No\n";
                        return;
                    }
                }
                k++;
            }
        }



        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                if (S[i] == S[j] || S[i] + 1 == S[j] || S[i] - 1 == S[j]) {
                    if (!E[i][j]) {
                        cout << "No\n";
                        return;
                    }
                } else {
                    if (E[i][j]) {
                        cout << "No\n";
                        return;
                    }
                }
            }
        }

        cout << "Yes\n" << S << endl;
    }
};
