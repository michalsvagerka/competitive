#include "../../../l/lib.h"
#include "../../../l/closest.h"

class trickyfunction {
public:
    vector<int> a;

    int g(int i, int j) {
        int sum = 0;
        for (int k = min(i, j); k < max(i, j); k = k + 1) sum = sum + a[k];
        return sum;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N+1, 0);
        vector<Point<ll>> S;
        for (int i = 0; i < N; ++i) {
            int a; cin >> a;
            P[i+1] = P[i] + a;
            S.push_back({i+1,P[i+1]});
        }

        Closest<ll> C;
        cout << C.minSquareDist(S) << endl;


//        if (S.size() == 2) {
//            cout << S[0].squaredDistance(S[1]) << endl;
//            return;
//        }
//
//        cerr << S;


//        ll ans = 1e16;
//        Delaunay<ll> D;
//        auto F = D.triangulate(S);
//        for (int i = 0; i < F.size(); i+=3) {
//            ans = min(ans, F[i].squaredDistance(F[i+1]));
//        }
//        cout << ans << endl;

    }
};
