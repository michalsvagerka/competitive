#include "../l/lib.h"

class covidfactor {
public:
    void solve(istream& cin, ostream& cout) {
        int K, N; cin >> N >> K;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        multiset<int> M;
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            if (i+K <= N) {
                M.insert(A[i+K-1] - A[i]);
            }

            ans = max(ans, *M.begin());

            if (i >= K-1) {
                M.erase(M.find(A[i] - A[i-K+1]));
            }
        }

        cout << ans << endl;
    }
};
