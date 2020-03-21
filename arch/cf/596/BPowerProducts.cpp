#include "../l/lib.h"

constexpr int MX = 100000;

class BPowerProducts {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N); cin >> A;

        vector<int> P(MX+1, 0);
        for (int i = 2; i <= MX; ++i) {
            if (P[i] == 0) {
                for (int j = i; j <= MX; j+=i) P[j] = i;
            }
        }

        map<vector<pii>, int> C;
        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            int a = A[i];
            vector<pii> X;
            while (a != 1) {
                int b = P[a];
                int c = 0;
                while (P[a] == b) {
                    a /= b;
                    c++;
                }
                if (c%K != 0) X.push_back({b,c%K});
            }
            vector<pii> Y;
            for (pii x: X) Y.push_back({x.x, K-x.y});
            ans += C[Y];
            C[X]++;
        }
        cout << ans << endl;
    }
};
