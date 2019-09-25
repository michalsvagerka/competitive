#include "../l/lib.h"
#include "../l/fenwick.h"

class DRestorePermutation {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> S(N); cin >> S;
        vector<ll> Orig(N+1, 0);
        for (int i = 1; i <= N; ++i) Orig[i] = i;
        Fenwick<ll> F(Orig, 0);
        vector<int> Ans(N);
        for (int i = N-1; i >= 0; --i) {
            int j = F.max_lower(S[i]+1);
            Ans[i] = j;
            F.add(j, -j);
        }
        cout << Ans;
    }
};
