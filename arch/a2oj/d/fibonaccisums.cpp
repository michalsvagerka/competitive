#include "../../../l/lib.h"
// #include "../l/mod.h"

class fibonaccisums {
public:
    void solve(istream& cin, ostream& cout) {
        ll a=1,b=1;
        vector<ll> F;
        while (b < 1e18) {
            F.push_back(b);
            a=a+b;
            swap(a,b);
        }

        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ll N; cin >> N;
            vector<int> B;
            for (int i = F.size()-1; i >= 0; --i) if (N >= F[i]) { B.push_back(i); N -= F[i]; }
            reverse(B.begin(),B.end());
            int l = -1;
            ll one = 1, zero = 0;

            for (int i = 0; i < B.size(); ++i) {
                int b = B[i];
                ll newOne = one + zero;
                ll newZero = one * ((b-l-1)/2) + zero * ((b-l)/2);
                one = newOne;
                zero = newZero;
                l = b;
            }
            cout << one + zero << '\n';
        }
    }
};
