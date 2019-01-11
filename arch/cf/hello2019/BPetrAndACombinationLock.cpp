#include "../l/lib.h"
// #include "../l/mod.h"

class BPetrAndACombinationLock {
public:
    int N;
    vector<int> A;

    bool solve(int i, int d) {
        if (i == N) {
            return d%360 == 0;
        }

        return solve(i+1, d+A[i]) || solve(i+1, d-A[i]);
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        A.resize(N);
        cin >> A;
        cout << (solve(0, 0) ? "YES" : "NO") << endl;
    }
};
