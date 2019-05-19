#include "../l/lib.h"

class cwtree {
public:
    void solve(istream& cin, ostream& cout) {
        ll A, B;
        char c;
        cin >> A >> c >> B;

        ll level = -1;
        while (A > 0) {
            while (A > 0 && A <= B) {
                ll X = B / A;
                B %= A;
                swap(A, B);
                level += X;
            }
            swap(A, B);
        }
        cout << level << endl;
    }
};
