#include "../l/lib.h"
 #include "../l/fenwick.h"

class CCoins {
public:
    void solve(istream& cin, ostream& cout) {
        int X, Y, Z;
        cin >> X >> Y >> Z;
        int N = X + Y + Z;
        vector<int> A(N), B(N), C(N);
        for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> C[i];

        ll sumC = 0;
        for (int i = 0; i < N; ++i) {
            A[i] -= C[i];
            B[i] -= C[i];
            sumC += C[i];
            C[i] = 0;
        }

        vector<pii> AB(N);
        for (int i = 0; i < N; ++i) AB[i] = {A[i]-B[i], i};
        sort(AB.begin(),AB.end());
        reverse(AB.begin(),AB.end());
        
        multiset<int> SA, SB;
        ll s = 0;
        vector<ll> BestA(N+1, -1e18), BestB(N+1, -1e18);
        BestA[0] = 0;
        for (int i = 0; i < N; ++i) {
            s += A[AB[i].y];
            SA.insert(A[AB[i].y]);
            if (SA.size() > X) {
                s -= *SA.begin();
                SA.erase(SA.begin());
            }
            BestA[i+1] = s;
        }

        s = 0;
        for (int i = N-1; i >= 0; --i) {
            s += B[AB[i].y];
            SB.insert(B[AB[i].y]);
            if (SB.size() > Y) {
                s -= *SB.begin();
                SB.erase(SB.begin());
            }
            BestB[i] = s;
        }

        ll ans = 0;
        for (int i = X; i <= N-Y; ++i) {
            ans = max(ans, BestA[i] + BestB[i] + sumC);
        }
        cout << ans << '\n';
    }
};



