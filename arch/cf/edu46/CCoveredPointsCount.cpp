#include "../../../l/lib.h"

class CCoveredPointsCount {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pair<ll,ll>> A(N); cin >> A;
        vector<pair<ll,int>> X;
        for (int i = 0; i < N; ++i) {
            X.push_back({A[i].x, 1});
            X.push_back({A[i].y+1, -1});
        }
        sort(X.begin(), X.end());
        vector<ll> T(N+1, 0);
        ll prev = 0; int cnt = 0;
        for (auto x: X) {
            T[cnt] += x.x - prev;
            cnt += x.y;
            prev = x.x;
        }
        T.erase(T.begin());
        cout << T;
    }
};
