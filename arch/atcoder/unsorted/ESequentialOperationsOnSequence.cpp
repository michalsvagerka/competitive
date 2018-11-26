#include "../l/lib.h"
// #include "../l/mod.h"

class ESequentialOperationsOnSequence {
public:


    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<ll> P(N, 0), A(Q), S{N};
        cin >> A;
        for (ll a:A) {
            while (!S.empty() && S.back() >= a) S.pop_back();
            S.push_back(a);
        }

        Q = S.size();
        vector<ll> T(Q, 0);
        T[Q-1] = 1;
        for (int i = Q-1; i >= 0; --i) {
            ll k = S[i];
            while (true) {
                auto it = lower_bound(S.begin(), S.end(), k);
                if (it == S.begin()) break;
                int j = it - S.begin() - 1;
                T[j] += T[i] * (k / S[j]);
                k %= S[j];
            }
            if (k) P[k-1] += T[i];
        }

        for (int i = N-1; i > 0; --i) P[i-1] += P[i];
        for (int i = 0; i < N; ++i) cout << P[i] << '\n';
    }
};
