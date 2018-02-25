#include "../../../l/lib.h"
// #include "../l/mod.h"

class wordclass {
public:
    void solve(istream& cin, ostream& cout) {
        int N;
        cin >> N;
        cout << 0 << ' ' << (1LL<<N);
        for (int i = 0; i < N; ++i) {
            cout << " 0";
        }
        cout << endl;
    }
};
