#include "../l/lib.h"

class EPrefixSuffixAddition {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N+2, 0);
        for (int i = 0; i < N; ++i) cin >> A[i+1];
        int x = 0, y = 0;
        vector<pair<int,pii>> X{{0,{0,0}}};
        for (int i = 1; i <= N+1; ++i) {
            x += A[i-1] > A[i];
            y += A[i-1] < A[i];
            auto cost = [&](int cur) {
                int ans = 2*N;
                for (auto &x: X) {
                    ans = min(ans, x.x + (x.y.x > cur) + (A[i-1]-x.y.x < A[i]-cur));
                }
                return ans;
            };
            int hi = cost(0);
            int lo = cost(A[i]);
            vector<pair<int,pii>> Y;
            int b = 0;
            for (int a = hi; a >= lo; --a) {
                int c = bsh(b, A[i], [&](int x) { return cost(x) >= a; });
                if (c != -1) {
                    Y.push_back({a, {b,c}});
                    b = c+1;
                }
            }
            swap(Y,X);
        }
        cout << X[0].x << '\n';
    }
};
