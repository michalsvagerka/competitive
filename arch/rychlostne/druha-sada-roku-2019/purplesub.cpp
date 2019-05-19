#include "../l/lib.h"

class purplesub {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        for (int &a: A) --a;
        int L; cin >> L;
        vector<map<vector<int>, pair<ll, int>>> D(N+1);
        D[0][{}] = {1LL, 0};
        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j <= i; ++j) {
                for (auto& d: D[j]) {
                    if (d.y.y & (1<<A[i])) continue;
                    d.y.y |= 1<<A[i];
                    int k = 0;

                    vector<int> Z = d.x;
                    if (Z.empty() || Z[0] != -1) {
                        while (k < Z.size() && A[i] > Z[k]) ++k;
                        if (k < Z.size()) {
                            Z[k] = A[i];
                        } else if (k == L-1) {
                            Z = {-1};
                        } else {
                            Z.push_back(A[i]);
                        }
                    }
                    if (Z[0] == -1) ans += d.y.x;
                    D[i+1][Z].y = 0;
                    D[i+1][Z].x += d.y.x;
                }
            }
        }
        
        cout << ans << '\n';
    }
};
