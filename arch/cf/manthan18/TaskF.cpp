#include "../l/lib.h"
 #include "../l/mod.h"

class TaskF {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N), S, L(N, -1), H(N, N); cin >> A;
        --K;
        for (int i = 0; i < N; ++i) {
            while (!S.empty() && A[S.back()] < A[i]) {
                H[S.back()] = i;
                S.pop_back();
            }
            if (!S.empty() && A[S.back()] >= A[i]) L[i] = S.back();
            S.push_back(i);
        }

        vector<int> Z(N+1);
        for (int i = 1; i <= N; i += K) {
            for (int j = 0; j < K && i + j <= N; ++j) Z[i+j] = i;
        }
        FieldMod ans = 0;
        for (int i = 0; i < N; ++i) {
            int l1 = i - L[i];
            int l2 = max(H[i]-i-1, K);
            int lo = Z[min(l1,l2)];
            int hi = Z[max(l1,l2)];
            int up = Z[min(N, H[i]-L[i])];
            ll cur = ll(lo + K + 1) * (lo-1)
                           + 2 * ll(min(H[i]-i,i-L[i])) * (hi-lo)
                           + ll(2*H[i] - 2*L[i] - hi - up - K) * (up-hi);
            ans += FieldMod{int(cur%1000000007)} * A[i];
        }
        cout << ans / 2 / K << endl;
    }
};
