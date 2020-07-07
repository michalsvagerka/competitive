#include "../../../l/lib.h"
#include "../../../l/mod.h"

class AIvanTheFoolAndTheProbabilityTheory {
public:
    void solve(istream& cin, ostream& cout) {
        vector<FieldMod> Fib{1,1};
        for (int i = 0; i < 100000; ++i) {
            Fib.push_back(Fib[i] + Fib[i+1]);
        }

        int N, M; cin >> N >> M;
        cout << 2*(Fib[N] + Fib[M] -1) << endl;
    }
};
