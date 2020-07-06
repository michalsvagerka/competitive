#include "../l/lib.h"
#include "../l/frac.h"

class Recalculating {
public:
    vector<ll> inter(vector<ll> A, vector<ll> B) {

        ll loX = max(A[0], B[0]);
        ll hiX = min(A[1], B[1]);
        ll loY = max(A[2], B[2]);
        ll hiY = min(A[3], B[3]);
        hiX = max(hiX, loX);
        hiY = max(hiY, loY);
        return {loX, hiX, loY, hiY};
    }

    ll area(vector<ll> A) {
        return (A[1]-A[0])*(A[3]-A[2]);
    }

    vector<ll> translate(vector<ll> A, ll X, ll Y) {
        A[0] += X;
        A[1] += X;
        A[2] += Y;
        A[3] += Y;
        return A;
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; ll D; cin >> N >> D;
            vector<pair<ll,ll>> P(N); cin >> P;

            vector<vector<ll>> R(N);
            for (int i = 0; i < N; ++i) {
                R[i] = {P[i].x + P[i].y - D, P[i].x + P[i].y + D, P[i].x - P[i].y - D, P[i].x - P[i].y + D};
            }

            assert(N == 2);
            ll tot = 8*D*D;
            vector<vector<ll>> PIE{inter(R[0], R[1])};
            tot -= area(PIE[0]);
            int dx = P[0].x + P[0].y - (P[1].x + P[1].y);
            int dy = (P[0].x - P[0].y) - (P[1].x - P[1].y);
            PIE.push_back(translate(PIE[0], dx, dy));
            PIE.push_back(translate(PIE[0], -dx, -dy));

            ll good = area(PIE[0])+area(PIE[1])+area(PIE[2])
                    - area(inter(PIE[0],PIE[1]))
                    - area(inter(PIE[0],PIE[2]))
                    - area(inter(PIE[1],PIE[2]))
                    + area(inter(inter(PIE[0],PIE[1]),PIE[2]));
            ll g = gcd(good, tot);

//            cout << good << ' ' << tot << endl;
            cout << "Case #" << t+1 << ": " << good/g << ' ' << tot/g << endl;
        }
    }
};
