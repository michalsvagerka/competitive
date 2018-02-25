#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    vector<int> R;

    int f(int x) {
        int r = 1;
        while (x) {
            int d = x%10;
            if (d) r *= d;
            x /= 10;
        }
        return r;
    }

    int g(int x) {
        while (x >= 10) x = f(x);
        return x;
    }

    void solve(istream& cin, ostream& cout) {
        R = vector<int>(1000001, -1);
        for (int i = 1; i <= 1000000; ++i) R[i] = g(i);
        vector2<int> Z(10, 1000001, 0);
        for (int i = 0; i < 10; ++i) {
            for (int j = 1; j <= 1000000; ++j) {
                Z[i][j] = Z[i][j-1] + (R[j] == i);
            }
        }


        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int l,r,k; cin >> l >> r >> k;
            cout << Z[k][r] - Z[k][l-1] << '\n';
        }

    }
};
