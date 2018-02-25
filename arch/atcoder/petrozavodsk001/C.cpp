#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int lo = 0, hi = N-1;
        string Lo, Hi, Mi;

        cout << lo << endl;
        cin >> Lo;
        if (Lo == "Vacant") return;

        cout << hi << endl;
        cin >> Hi;
        if (Hi == "Vacant") return;

        while (true) {
            int m = (lo+hi)/2;
            cout << m << endl;
            cin >> Mi;
            if (Mi == "Vacant") break;

            if ((Mi == Lo) != ((m-lo)%2 == 0)) {
                hi = m;
                Hi = Mi;
            } else {
                lo = m;
                Lo = Mi;
            }
        }
    }
};
