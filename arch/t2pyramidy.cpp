#include "../l/lib.h"
// #include "../l/mod.h"

class t2pyramidy {
public:
    void solve(istream& cin, ostream& cout) {
        vector<ll> Z{0};
        for (ll i = 1; Z.back() < 1e15; ++i) {
            Z.push_back(Z[i-1] + i*i);
        }
        ui N; cin >> N;
        vector<long> A(N);
        for (ui i = 0; i < N; i++) {
            ll s; cin >> s;
            A[i] = distance(Z.begin()+1,upper_bound(Z.begin(),Z.end(),s));
        }
        cout << A;
    }
};
