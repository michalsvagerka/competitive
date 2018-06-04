#include "../../../l/lib.h"
// #include "../l/mod.h"

class mrkitayuta {
public:
    void solve(istream& cin, ostream& cout) {
        int N, D; cin >> N >> D;
        vector<int> C(30001, 0);
        for (int i = 0; i < N; ++i) {
            int a; cin >> a; C[a]++;
        }

        int s = max(0, D-250);
        cerr << s << endl;

        int t = 0;
        vector2<int> Q(30001, 500, -1);
        int ans = C[D];
        Q[D][D-s] = C[D];
        for (int i = D; i < 30000; ++i) {
            for (int j = 0; j < 500; ++j) {
                if (Q[i][j] != -1) {
                    for (int k = max(1, j + s - 1); k <= j + s + 1; ++k) {
                        if (i + k <= 30000) {
                            Q[i + k][k - s] = max(Q[i + k][k - s], 0); Q[i][j] + C[i + k]);
                            ans = max(ans, Q[i + k][k - s]);
                        }
                    }
                }
            }
            t += Q[i].size();
        }
        cout << ans << endl;
    }
};
