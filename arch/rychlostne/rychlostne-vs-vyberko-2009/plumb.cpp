#include "../l/lib.h"
// #include "../l/mod.h"

class plumb {
public:
    void solve(istream& cin, ostream& cout) {
        int D,P; cin >> D >> P;
        vector<pii> A(P);
        for (int i = 0; i < P; ++i) {
            cin >> A[i].y >> A[i].x;
        }
        sort(A.begin(),A.end(),greater<pii>());
        vector<bool> R(D+1, false);
        R[0] = true;
        for (auto a:A) {
            for (int i = D-a.y; i >= 0; --i) R[i+a.y] = R[i+a.y] | R[i];
            if (R[D]) { cout << a.x << endl; return; }
        }
        cout << "0\n";
    }
};
