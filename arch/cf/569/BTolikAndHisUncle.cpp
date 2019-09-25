#include "../l/lib.h"
#include <numeric>

class BTolikAndHisUncle {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        for (int i = 0; i < N*M/2; ++i) {
            int a = i;
            cout << 1+a/M << ' ' << 1+a%M << '\n';
            a = N*M - i - 1;
            cout << 1+a/M << ' ' << 1+a%M << '\n';
        }
        if (N*M%2==1) {
            int a = N*M/2;
            cout << 1+a/M << ' ' << 1+a%M << '\n';
        }
    }
};
