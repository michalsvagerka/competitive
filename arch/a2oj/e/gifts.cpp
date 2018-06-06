#include "../../../l/lib.h"
// #include "../l/mod.h"

class gifts {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<vector<int>> E(M);
        for (int i = 0; i < M; ++i) {
            int k; cin >> k;
            E[i].resize(k); cin >> E[i];
        }

        vector<int> WW;
        for (auto&e:E) for (int ee:e) WW.push_back(ee);
        sort(WW.begin(),WW.end());

        int prc = WW[WW.size()-N];
        vector2<double> C(1001, 1001, 0);
        for (int i = 0; i <= 1000; ++i) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; ++j) C[i][j] = C[i-1][j-1] + C[i-1][j];
        }

        vector2<double> DP(M+1, 1001, 0);
        DP[0][0] = 1;
        int R = 0, totEq = 0, totGt = 0;
        for (int i = 0; i < M; ++i) {
            int gt = 0, eq = 0;
            for (int s:E[i]) {
                gt += s>prc;
                eq += s==prc;
            }

            totEq += eq;
            totGt += gt;

            int tot = E[i].size();
            for (int j = 0; j <= R; ++j) {
                DP[i+1][j+gt] += DP[i][j] / C[tot][gt];
                if (eq) DP[i+1][j+gt+1] += DP[i][j] / C[tot][gt+1];
            }
            R += tot;
        }

        cout << fixed << setprecision(10) << DP[M][N]/C[totEq][N - totGt] << endl;

    }
};
