#include "../../../l/lib.h"
// #include "../l/mod.h"

class edoandmagnets {
public:
    vector<pii> MX,MY;
    vector<int> R;
    ll ans;
    int N, K;
    vector<int> P;

    void solve(int left, int q) {
        if (q == 4) {
            ans = min(ans, ll(max(1,(P[1]-P[0]+1)/2))*ll(max(1,(P[3]-P[2]+1)/2)));
            return;
        }

        auto &S = q < 2 ? MX : MY;
        auto A = (q&1) ? -1 : 1;
        auto B = (q&1) ? N-1 : 0;
        int i = B;
        while (R[S[i].y]) R[S[i].y]++, i+=A;

        P[q] = S[i].x;
        solve(left, q+1);
        while (left > 0) {
            R[S[i].y]++; i+=A; left--;
            while (R[S[i].y]) R[S[i].y]++, i+=A;

            P[q] = S[i].x;
            solve(left, q+1);
        }

        for (int j = B; j != i; j+=A) R[S[j].y]--;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> K;
        P.resize(4);
        ans = 1e18+1e12;

        for (int i = 0; i < N; ++i) {
            int X1,Y1,X2,Y2;
            cin >> X1 >> Y1 >> X2 >> Y2;
            MX.emplace_back(X1+X2,i);
            MY.emplace_back(Y1+Y2,i);
        }

        sort(MX.begin(),MX.end());
        sort(MY.begin(),MY.end());
        R = vector<int>(N, 0);

        solve(K, 0);
        cout << ans << endl;

    }
};
