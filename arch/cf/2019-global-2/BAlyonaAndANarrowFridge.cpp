#include "../l/lib.h"

class BAlyonaAndANarrowFridge {
public:
    void solve(istream& cin, ostream& cout) {
        int N; ll H; cin >> N >> H;
        vector<int> A(N); cin >> A;

        int c = N;
        for (int c = N; c > 0; --c) {
            vector<int> B(A.begin(),A.begin() + c);
            sort(B.begin(),B.end());
            reverse(B.begin(),B.end());
            ll tot = 0;
            for (int i = 0; i < c; i += 2) tot += B[i];
            if (tot <= H) {
                cout << c << endl;
                return;
            }
        }
        cout << 0 << endl;
    }
};
