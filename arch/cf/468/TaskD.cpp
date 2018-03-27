#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<vector<pii>> Q(2);
        for (int i = 0; i < N; ++i) {
            int x,y; cin >> x >> y;
            int d = ((x+y)&1);
            Q[d].push_back({(x+y-d)/2,(x-y-d)/2});
        }

        ll ans = 0;
        for (auto&q:Q) {
            sort(q.begin(),q.end());
            if (q.empty()) continue;
            int l = q[0].x;
            for (pii&qq:q) qq.x -= l;
            int h = q.back().x;
            vector<int> lo(h+1, 1000000), hi(h+1, -1000000);
            for (pii&qq:q) {
                lo[qq.x] = min(lo[qq.x], qq.y);
                hi[qq.x] = max(hi[qq.x], qq.y);
            }
            vector<int> LL = lo, LH = hi, RL = lo, RH = hi;
            for (int i = 0; i < h; ++i) {
                LL[i+1] = min(LL[i+1], LL[i]);
                LH[i+1] = max(LH[i+1], LH[i]);
                RL[h-i-1] = min(RL[h-i-1], RL[h-i]);
                RH[h-i-1] = max(RH[h-i-1], RH[h-i]);
            }
            for (int i = 0; i < h; ++i) {
                int lo = max(LL[i], RL[i+1]);
                int hi = min(LH[i], RH[i+1]);
                if (lo < hi) {
                    ans += hi - lo;
                }
            }
        }
        cout << ans << endl;
    }
};
