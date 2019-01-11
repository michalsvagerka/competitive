#include "../l/lib.h"
// #include "../l/mod.h"

class BTreeBurning {
public:
    void solve(istream& cin, ostream& cout) {
        int L, N;
        cin >> L >> N;
        vector<int> X(N);
        cin >> X;
        vector<ll> P(N+1, 0);
        for (int i = 0; i < N; ++i) P[i+1] = P[i] + X[i];

        ll ans = max(X[N-1], L-X[0]);
//        for (int i = 1; i < N; ++i) {
//            ll cur = 0;
//            int left = (N-i)/2;
//            int right = (N-i)-left;
//            cur += 2 * (P[i+left] - P[i-1]);
//            if (i == 2) cerr << cur << endl;
//            cur += 2 * ((ll(right) * L) - (P[N] - P[N-right]));
//
//            if (i == 2) cerr << cur << endl;
//            if (right > left) cur -= L-X[i+left];
//
//            else cur -= X[i+left];
//
//            if (i == 2) cerr << cur << endl;
//            ans = max(ans, cur);
//
//            /*cur = 0;
//            right = (N-i)/2;
//            left = (N-i)-right;
//            if (right > 0) {
//                cur += 2 * (P[i + left] - P[i]);
//                cur += 2 * ((ll(right) * L) - (P[N] - P[N - right]));
//                cur -= X[i + left - 1];
//
//                ans = max(ans, cur);
//            }*/
//        }

        for (int i = 1; i < N; ++i) {
            ll cur = 0;
            int right = (N-i)/2;
            int left = (N-i)-right;
            cur += 2 * P[left];
            cur += 2 * ((ll(right+1) * L) - (P[N-i+1] - P[N-i-right]));
            if (left > right) cur -= X[left-1];
            else cur -= L-X[left];
            ans = max(ans, cur);
        }

        reverse(X.begin(),X.end());
        for (int&x:X) x = L-x;
        for (int i = 0; i < N; ++i) P[i+1] = P[i] + X[i];

        for (int i = 1; i < N; ++i) {
            ll cur = 0;
            int right = (N-i)/2;
            int left = (N-i)-right;
            cur += 2 * P[left];
            cur += 2 * ((ll(right+1) * L) - (P[N-i+1] - P[N-i-right]));
            if (left > right) cur -= X[left-1];
            else cur -= L-X[left];
            ans = max(ans, cur);
        }
        
        cout << ans << endl;
    }
};
