#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    ll increasing(const vector<int> &Q) {
        vector<ll> Z(101, 0);
        Z[0] = 1;
        for (int i = 0; i < Q.size(); ++i) {
            for (int j = 0; j < Q[i]; ++j) Z[Q[i]] += Z[j];
        }
        ll ans = 0;
        for (ll z:Z) ans += z;
        return ans - 1;
    }

    vector<int> buildSuffix(ll X) {
        vector<int> Ans;
//        for (int i = 1; i < 100; ++i) {
//            Ans.push_back(i);
//        }
        Ans.push_back(100);
        if (X != 1 && (X&1)) Ans.push_back(99);
        ll Y = X>>1;
        int i = 0;
        while (Y) {
            Ans.push_back(2*i+1);
            ++i;
            Y >>= 1;
        }

        for (int b = i-1; b >= 1; --b) {
            if (X&(1LL<<b)) Ans.push_back(2*b);
        }

//        cerr << i << endl;
        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
//        for (ll i = 1e12-1e3; i < 1e12; ++i) {
//            auto a = buildSuffix(i);
//            ll x = increasing(a);
//            if (x!=i)cout << x << ' ' << i << endl;
//        }

        ll N; cin >> N;
        vector<int> Ans = buildSuffix(N);
        cout << Ans.size() + 100 << '\n';
        for (int i = 1; i <= 100; ++i) {
            cout << i << ' ';
        }
        cout << Ans;

//        cout << increasing({1,1,1,1}) << endl;
//        cout << increasing({100,1,2,3}) << endl;
//        cout << increasing({100,1,2,3,4,5}) << endl;
//        cout << increasing({100,1,2,3,4,6,7}) << endl;
//        cout << increasing({100,1,3,5,7,9,8,6}) << endl;
//        cout << buildSuffix(32) << endl;
//        cout << buildSuffix(56) << endl;
    }
};
