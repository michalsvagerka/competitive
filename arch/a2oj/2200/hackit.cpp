#include "../../../l/lib.h"

constexpr ll MX = 1e16+5e15;

class hackit {
public:
    vector<ll> W, P;

    ll pref(ll x) {
        x += 1;
        vector<int> Z;
        while (x) {
            Z.push_back(x%10);
            x /= 10;
        }
        int N = Z.size();
        ll z = 0, pre = 0;
        for (int j = N-1; j >= 0; --j) {
            int d = Z[j];
            z += d*W[j] + pre*d*P[j] + d*(d-1)/2*P[j];
            pre += d;
        }
        return z;
    }

    int get(ll x) {
        int ans = 0;
        while (x) {
            ans += x%10;
            x /= 10;
        }
        return ans;
    }


    void solve(istream& cin, ostream& cout) {
        P.push_back(1);
        for (int i = 1; i <= 16; ++i) P.push_back(P[i-1]*10);
        W.push_back(0);
        W.push_back(45);
        for (int i = 2; i <= 17; ++i) W.push_back(W[i-1]*10);
        for (int i = 2; i <= 17; ++i) W[i] *= i;

        ll A; cin >> A;

        ll l = 1;
        ll r = bsl(1LL, MX, [&](ll s) { return pref(s) >= A; });
        ll cur = pref(r);
        while (cur != A) {
            if (cur > A) {
                cur -= get(l++);
            } else {
                cur += get(++r);
            }
        }
        cout << l << ' ' << r << endl;
    }
};
