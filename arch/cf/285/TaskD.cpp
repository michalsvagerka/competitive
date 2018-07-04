#include "../../../l/lib.h"
 #include "../../../l/bigint.h"

class TaskD {
public:
    void read(bitset<2000>&b, istream& cin, ostream& cout) {
        string s; cin >> s;
//        cout << s << '\n';
        Num N(s);

        for (int i = 0; i < N.size(); ++i) {
            auto Z = N[i];
            for (int j = 0; j < 8*sizeof(Num::word); ++j) {
                b[i*8*sizeof(Num::word)+j] = Z%2;
                Z >>= 1;
            }
        }
    }

void solve(istream& cin, ostream& cout) {
    int N; cin >> N;

    vector<pair<bitset<2000>,bitset<2000>>> Z(2000);
    for (int i = 0; i < N; ++i) {
        bitset<2000> X;
        read(X, cin, cout);
        bitset<2000> R;
        bool found = false;
        for (int j = 0; j < 2000; ++j) {
            if (X.test(j)) {
                if (Z[j].x.none()) {
                    cout << 0 << '\n';
                    R.set(i);
                    found = true;
                    swap(Z[j].x, X);
                    swap(Z[j].y, R);
                    break;
                } else {
                    X ^= Z[j].x;
                    R ^= Z[j].y;
                }
            }
        }

        if (!found) {
            cout << R.count();
            for (int i = 0; i < N; ++i) {
                if (R[i]) cout << " " << i;
            }
            cout << '\n';
        }

    }
}
};
