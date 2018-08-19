#include "../l/lib.h"
// #include "../l/mod.h"

class Ethan {
public:
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        cout << "Case #" << t+1 << ": ";

        string A; cin >> A;
        int j = 1;
        while (j < A.size() && A[0] != A[j]) ++j;
        if (j != A.size()) {
            int k = 0;
            while (j + k < A.size() && A[k] == A[j+k]) ++k;
            if (j + k != A.size()) {
                cout << A.substr(0, j) << A;
            } else {
                cout << "Impossible";
            }
        } else {
            cout << "Impossible";
        }


        cout << '\n';
    }

}
};
