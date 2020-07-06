#include "../l/lib.h"

class CardboardBoxes {
public:
    long long count2(long long ab, long long ac) {
//        return min(ac-1, ab / 2);
        ll x = ab;
        ll other = ac;
        ll lo = max({1LL, (2*x-other+1)/2, x-other+1});
        ll hi = x-1;
        ll ans = 0;
        ans += max(0LL, hi-lo+1);
        return ans;
    }

    long long count2(long long S) {
        if (S % 2 != 0) return 0LL;
        S /= 2;
        ll ans = 0;
        for (ll i = 1; i*i <= S; ++i) {
            if (S%i != 0) continue;
            ans += count2(i, S/i);
            if (i*i != S) ans += count2(S/i, i);
        }
        return ans;
    }


    long long count(long long ab, long long ac) {
        return min(ac-1, ab / 2);
    }
    long long count(long long S) {
        if (S % 2 != 0) return 0LL;
        S /= 2;
        ll ans = 0;
        for (ll i = 1; i*i <= S; ++i) {
            if (S%i != 0) continue;
            ans += count(i, S/i);
            if (i*i != S) ans += count(S/i, i);
        }
        return ans;
    }
    void solve(istream& cin, ostream& cout) {
        for (int i = 100; i < 1000000; ++i) {
            ll a = count(i);
            ll b = count2(i);
            if (a != b) {
                cout << i << ' ' << a << ' ' << b << endl;
            }
        }
//        cout << count(197) << endl;
//        cout << count(47) << endl;
//        cout << count(470) << endl;
//        cout << count(4700) << endl;
//        cout << count(8) << endl;
//        cout << count(1e13) << endl;
    }
};
