#include "../../../l/lib.h"

class BSonyaAndExhibition {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S;
        for (int i = 0; i < N/2; ++i) {
            S += "01";
        }
        if (N%2 == 1) S += "0";
        cout << S << '\n';
    }
};
