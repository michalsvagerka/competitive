#include "../l/lib.h"
// #include "../l/mod.h"

class cajovyobrad {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        char c;
        if (N == 1) cout << "rovnako\n";
        else {
            int b = 0;
            for (int i = 0; i < N - 1; ++i) {
                cin >> c;
                b += (c == 'C') - (c == 'M');
            }
            if (b > 0 || (b==0 && c == 'M')) cout << "caj\n";
            else cout << "mlieko\n";
        }
    }
};
