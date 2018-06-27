#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    vector<vector<int>> Z;
    int t;

    bool isCube() {
        map<ll,int> C;
        for (int i = 0; i < 8; ++i) {
            for (int j = i+1; j < 8; ++j) {
                ll d = 0;
                for (int k = 0; k < 3; ++k) {
                    ll x = Z[i][k] - Z[j][k];
                    d += x*x;
                }
                C[d]++;
            }
        }
        ll lo = C.begin()->x;
        return C[lo] == 12 && C[2*lo] == 12 && C[3*lo] == 4;
    }

    bool check(int i) {
        if (i == 8) {
            return isCube();
        } else {
            do {
                if (check(i+1)) return true;
            } while (next_permutation(Z[i].begin(),Z[i].end()));
        }
        return false;
    }

void solve(istream& cin, ostream& cout) {
    Z = vector2<int>(8, 3, 0); cin >> Z;
    for (auto&z:Z) sort(z.begin(),z.end());
    bool ans = check(1);
    if (ans) {
        cout << "YES\n";
        for (auto&z:Z) cout << z;
    } else {
        cout << "NO\n";
    }
}
};
