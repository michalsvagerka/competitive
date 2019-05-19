#include "../l/lib.h"

class randmod {
public:
    void solve(istream& cin, ostream& cout) {
        int N;
        cin >> N;

        double pref = 1;
        vector<double> F(N+1, 0);
        F[1] = 1;
        for (int i = 2; i <= N; ++i) {
            F[i] = (pref/i) + 1;
            pref += F[i];
        }
        cout << fixed << setprecision(10) << F[N] << endl;
    }
};
