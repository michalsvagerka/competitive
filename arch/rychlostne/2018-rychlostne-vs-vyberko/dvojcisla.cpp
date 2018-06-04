#include "../../../l/lib.h"
#include "../../../l/mod.h"

class dvojcisla {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        FieldMod mult = N;
        for (int a:A) {
            int p = 1;
            while (p <= a) p *= 10;
            mult += p;
        }

        FieldMod ans = 0;
        for (int a:A) {
            int p = 1;
            while (p <= a) p *= 10;
            ans += FieldMod{a} * (mult - p - 1);
        }
        cout << ans << endl;
    }
};
