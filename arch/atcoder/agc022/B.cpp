#include <numeric>
#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 3) {
            cout << "2 5 63\n";
        } else {
            vector<int> X{2,3,4,9};
            N -= 4;
            for (int j = 12; j+9 <= 30000 && N >= 2; j+=12) {
                X.push_back(j+3);
                X.push_back(j+9);
                N -= 2;
            }

            for (int j = 6; j < 30000 && N >= 2; j += 6) {
                X.push_back(j+2);
                X.push_back(j+4);
                N -= 2;
            }


            for (int j = 6; j <= 30000 && N >= 1; j += 6) {
                X.push_back(j);
                N -= 1;
            }

            cout << X;
        }
    }
};
