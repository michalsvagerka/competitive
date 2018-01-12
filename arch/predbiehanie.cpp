#include "../l/lib.h"
// #include "../l/mod.h"

class predbiehanie {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        vector<ui> Z(N); cin >> Z;
        ll a = Z.back();
        ui m = Z.back();
        for (int i = N-2; i >= 0; --i) {
            m = min(m,Z[i]);
            a += m;
        }
        cout << a << endl;
    }
};
