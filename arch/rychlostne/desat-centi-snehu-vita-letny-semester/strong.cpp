#include "../../../l/lib.h"
// #include "../l/mod.h"

class strong {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;

        vector<int> B(5, 0);
        for (int i = 0; i < N; ++i) {
            char c;
            int p, t;
            cin >> p >> c >> t;

            for (int r = 4 - p; r >= 0; --r) {
                B[r+p] = max(B[r+p], B[r] + t);
            }
        }

        cout << *max_element(B.begin(),B.end()) << endl;

    }
};
