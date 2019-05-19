#include "../l/lib.h"

class AHideAndSeek {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> X(K); cin >> X;
        vector<int> LO(N+1, K+1);
        vector<int> HI(N+1, -1);
        for (int i = 0; i < K; ++i) {
            LO[X[i]] = min(LO[X[i]], i);
            HI[X[i]] = max(HI[X[i]], i);
        }
        
        int ans = 0;
        for (int i = 1; i <= N; ++i) {
            if (HI[i] == -1) ans++;
            if (i != 1 && LO[i] > HI[i-1]) ans++;
            if (i != N && LO[i] > HI[i+1]) ans++;
        }
        cout << ans << endl;
    }
};
