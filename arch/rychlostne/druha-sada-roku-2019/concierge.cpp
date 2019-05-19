#include "../l/lib.h"

class concierge {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;
        vector<ll> B(N);
        for (int i = 0; i < N-1; ++i) {
            B[i] = (A[i+1] - A[i])/2;
        }
        B[N-1] = N;

        set<ll> S;
        for (int i = 0; i < N; ++i) {
            S.insert(i+1);
        }

        vector<ll> Ans(N);
        for (int i = 0; i < N; ++i) {
            auto it = S.upper_bound(B[i]);
            if (it == S.begin()) {
                cout << "IMPOSSIBLE\n";
                return;
            }
            else {
                it--;
                Ans[i] = *it;
                S.erase(it);
            }
        }

        cout << Ans;
    }
};
