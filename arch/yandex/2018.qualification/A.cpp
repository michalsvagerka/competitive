#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        vector<bool> D(33, false);
        for (int i = 0; i < 10; ++i) {
            int a; cin >> a;
            D[a] = true;
        }
        int N; cin >> N;
        for (int i = 0; i < N; ++i) {
            int c = 0;
            for (int j = 0; j < 6; ++j) {
                int g; cin >> g;
                c += D[g];
            }
            cout << (c >= 3 ? "Lucky" : "Unlucky") << '\n';
        }
    }
};
