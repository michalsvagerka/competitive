#include "../../../l/lib.h"
// #include "../l/mod.h"

class pes3ma3x {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 0) {
            cout << "ANO\n0\n";
        } else {
            for (int i = 1; i < 2000; ++i) {
                if (N == i*(i+1)/2) {
                    cout << "ANO\n";
                    for (int j = 0; j < i; ++j) {
                        for (int k = 0; k < i; ++k) {
                            cout << (k<=j);
                        }
                        cout << '\n';
                    }
                    return;
                }
            }
            cout << "NIE\n";
        }

    }
};
