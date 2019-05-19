#include "../l/lib.h"

class potatopl {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> R(N);
        cin >> R;

        multiset<int> M;
        for (int a: R) M.insert(a);
        vector<int> Y, Z;
        while (!M.empty()) {
            int mx = *M.rbegin();
            M.erase(M.find(mx));
            Y.push_back(mx);
            if (!M.empty()) {
                Y.push_back(*M.begin());
                M.erase(M.begin());
                swap(Y,Z);
            }
        }

        reverse(Y.begin(),Y.end());
        for (int y: Y) Z.push_back(y);

        ll ans = Z[0] + Z[N-1];
        for (int i = 0; i < N-1; ++i) {
            ans += min(Z[i] + Z[i+1], K);
        }
        cout << ans << endl;
    }
};
