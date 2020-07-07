#include "../../../l/lib.h"
#include "../../../l/mod.h"

class CNastyaAndAWardrobe {
public:
    void solve(istream& cin, ostream& cout) {
        ll X, K; cin >> X >> K;
        if (X == 0) {
            cout << 0 << endl;
            return;
        }
        
        K %= 1000000006;

        int XX = X%1000000007;
        cout << XX * FieldMod{2}.pow(K+1) - FieldMod{2}.pow(K) + 1 << endl;
    }
};
