#include "../l/lib.h"
// #include "../l/mod.h"

class t2deadliny {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i].y >> A[i].x;
        }
        sort(A.begin(),A.end());
        ll c = 0;
        for (int i = 0; i < N; ++i) {
            c += A[i].y;
            if (c > A[i].x) {
                cout << "NIE\n";
                return;
            }
        }
        cout << "ANO\n" << c << endl;
    }
};
