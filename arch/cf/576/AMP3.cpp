#include "../l/lib.h"

class AMP3 {
public:
    void solve(istream& cin, ostream& cout) {
        int N, I; cin >> N >> I;
        vector<int> A(N); cin >> A;
        int k = min(30, 8 * I / N);
        int K = 1<<k;
        map<int,int> C;
        for (int a: A) C[a]++;
        vector<int> G;
        for (pii c: C) G.push_back(c.y);
        if (G.size() <= K) { cout << 0 << endl; }
        else {
            int ans = N;
            int cur = 0;
            for (int i = 0; i < K; ++i) cur += G[i];
            ans = min(ans, N - cur);
            for (int i = K; i < G.size(); ++i) {
                cur += G[i];
                cur -= G[i-K];
                ans = min(ans, N - cur);
            }
            cout << ans << endl;
        }
    }
};
