#include "../../../l/lib.h"
// #include "../l/mod.h"

class tennis {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> P(N+1, 0);
        for (int i = 0; i < N; ++i) {
            P[i+1] = P[i] + (A[i]==1);
        }

        vector<pii> Ans;
        for (int s = 1; s <= N; ++s) {
            int a = 0, b = 0, p = 0;
            while (p<N) {
                int t = bsl(p, min(p+2*s,N), [&](int k) { return P[k]-P[p] >= s || k-p-(P[k]-P[p]) >= s; });
                if (t == -1) break;
                if (P[t]-P[p]>=s) {
                    ++a;
                    if (t==N && a>b) Ans.push_back({a,s});
                } else {
                    ++b;
                    if (t==N && b>a) Ans.push_back({b,s});
                }
                p = t;
            }
        }
        sort(Ans.begin(),Ans.end());

        cout << Ans.size() << '\n';
        for (auto&ans:Ans) cout << ans << '\n';
    }
};
