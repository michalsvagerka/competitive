#include "../../../l/lib.h"

class EBusNumber {
public:
    vector<int> C, D;
    vector<ll> F;

    ll gen(int i) {
        if (i == 10) {
            int tot = accumulate(D.begin(),D.end(), 0);
            ll ans = F[tot];
            for (int j = 0; j < 10; ++j) ans /= F[D[j]];

            if (D[0] >= 1) {
                ll sum = F[tot-1];
                for (int j = 0; j < 10; ++j) sum /= F[D[j]-(j==0)];
                ans -= sum;
            }

            return ans;
        } else {
            ll ans = 0;
            if (C[i] == 0) ans += gen(i+1);
            else
                for (int j = 1; j <= C[i]; ++j) {
                    D[i] = j;
                    ans += gen(i+1);
                }
            return ans;
        }
    }


    void solve(istream& cin, ostream& cout) {
        ll N; cin >> N;
        C.assign(10, 0);
        D.assign(10 ,0);
        while (N) {
            C[N%10]++;
            N /= 10;
        }
        F.assign(20, 1);
        for (int i = 1; i < 20; ++i) F[i] = F[i-1] * i;
        cout << gen(0) << '\n';
    }
};
