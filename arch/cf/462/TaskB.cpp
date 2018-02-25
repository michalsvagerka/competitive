#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    void solve(istream& cin, ostream& cout) {
        ll P; int K; cin >> P >> K;
        vector<int> A;
        while (P) {
            int x = P%K;
            if (x<0) x+=K;
            A.push_back(x);
            P-=x;
            P/=(-K);
        }
        cout << A.size() << endl << A;
    }
};
