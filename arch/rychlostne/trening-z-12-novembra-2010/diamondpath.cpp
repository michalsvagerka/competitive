#include "../l/lib.h"
#include "../l/mod.h"

class diamondpath {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        Field<1000000009> F(2);
        F = F.pow(N);
        do F *= N; while (--N);
        cout << F * F << endl;
    }
};
