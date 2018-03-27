#include "../../../l/lib.h"
#include "../../../l/mod.h"

constexpr int light = 400;

class C {
public:
    int N, M, K;
    vector<int> V, S;
    vector<vector<int>> E, F;

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M >> K;
        V.resize(N); cin >> V;
        S.resize(K); cin >> S;
        for (int&s:S) --s;
        E.resize(N); F.resize(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        for (int i = 0; i < N; ++i) {
            if (E[i].size() > light) {
                for (int v:E[i]) {
                    F[v].push_back(i);
                }
            }
        }



        FieldMod inv = FieldMod(1)/2;
        vector<FieldMod> Mult(N, 1);
        vector<FieldMod> Val(N, 0);
        vector<int> Count(N, 0);
        vector<int> Prev(N, 0);
        vector<bool> U(N, false);
        for (int s:S) {
            for (int u:F[s]) {
                Val[u] += Mult[u];
                U[u] = true;
            }
            if (E[s].size() <= light) {
                int tot = 0;
                for (int u:E[s]) {
                    tot += Count[u];
                }
                if (tot != Prev[s]) U[s] = true;
                Val[s] += Mult[s] * (tot - Prev[s]);
                Prev[s] = tot;
            }

            Count[s]++;
            Mult[s] *= inv;
        }

        FieldMod ans = 0;
        for (int i = 0; i < N; ++i) {
            if (E[i].size() <= light) {
                int tot = 0;
                for (int u:E[i]) {
                    tot += Count[u];
                }
                if (tot != Prev[i]) U[i] = true;
                Val[i] += Mult[i] * (tot - Prev[i]);
                Prev[i] = tot;
            }

            if (V[i] != 0) {
                if (Mult[i] == 1) {
                    cout << "-1\n";
                    return;
                }

                ans += V[i] * Val[i] / (1 - Mult[i]);
            }
        }

        cout << ans << endl;
    }
};
