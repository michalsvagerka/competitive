#include "../../../l/lib.h"

class BSequenceSorting {
public:
    void solve(istream& cin, ostream& cout) {
        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            for (int &a: A) --a;
            vector<int> L(N, N), H(N, -1);
            for (int i = 0; i < N; ++i) {
                L[A[i]] = min(L[A[i]], i);
                H[A[i]] = max(H[A[i]], i);
            }
            vector<pii> R;
            for (int i = 0; i < N; ++i) {
                if (L[i] != N) {
                    R.push_back({L[i],H[i]});
                }
            }

            int ans = R.size() - 1;
            int j = 0;
            for (int i = 1; i < R.size(); ++i) {
                if (R[i].x < R[i-1].y) {
                    j = i;
                }
                ans = min(ans, (int)R.size() - (i-j + 1));
            }
            cout << ans << '\n';
        }
    }
};
