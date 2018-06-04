#include "../../../l/lib.h"
 #include "../../../l/mod.h"

constexpr int S = 5000;

class antimatter {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N);
        vector<FieldMod> D(2*S+1, 0); cin >> A;
        D[S] = 1;
        FieldMod ans = 0;
        for (int &a:A) {
            vector<FieldMod> E(2*S+1, 0);
            for (int i = 0; i <= 2*S; ++i) {
                if (i-a >= 0) E[i-a] += D[i];
                if (i+a <= 2*S) E[i+a] += D[i];
            }
            swap(E,D);
            ans += D[S];
            D[S]++;
        }
        cout << ans << endl;

    }
};
