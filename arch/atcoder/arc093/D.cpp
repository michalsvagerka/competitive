#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int A,B; cin >> A >> B;
        vector<string> R(100,string(100,'.'));
        for (int i = 50; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                R[i][j] = '#';
            }
        }

        --A; --B;
        for (int a = 0; a < A; ++a) {
            R[51+(a/50)*2][2*(a%50)] = '.';
        }


        for (int b = 0; b < B; ++b) {
            R[1+(b/50)*2][2*(b%50)] = '#';
        }


        cout << "100 100\n";
        for (auto&r:R) {
            cout << r << '\n';
        }
    }
};
