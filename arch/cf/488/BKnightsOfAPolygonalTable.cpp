#include "../../../l/lib.h"

class BKnightsOfAPolygonalTable {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> P(N), C(N); cin >> P >> C;
        vector<pii> G(N);
        for (int i = 0; i < N; ++i) {
            G[i] = {P[i],i};
        }
        sort(G.begin(),G.end());
        vector<int> Reward;
        vector<ll> Ans(N);
        for (int i = 0; i < N; ++i) {
            Ans[G[i].y] = C[G[i].y] + accumulate(Reward.begin(),Reward.end(),0LL);
            Reward.push_back(C[G[i].y]);
            if (Reward.size() == K+1) {
                for (int j = 0; j < K; ++j) if (Reward[j] < Reward[K]) swap(Reward[j], Reward[K]);
                Reward.pop_back();
            }
        }
        cout << Ans;
    }
};
