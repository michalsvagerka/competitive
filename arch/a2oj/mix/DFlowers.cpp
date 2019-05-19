#include "../l/lib.h"
 #include "../l/mod.h"

class DFlowers {
public:
void solve(istream& cin, ostream& cout) {
    vector<FieldMod> W(1e5+1, 0);
    W[0] = 1;

    int T, K; cin >> T >> K;
    for (int i = 0; i < 1e5; ++i) {
        W[i+1] += W[i];
        if (i+K <= 1e5) W[i+K] += W[i];
    }

    for (int i = 0; i < 1e5; ++i) {
        W[i+1] += W[i];
    }
    
    for (int t = 0; t < T; ++t) {
        int a, b; cin >> a >> b;
        cout << W[b] - W[a-1] << '\n';
    }

}
};
