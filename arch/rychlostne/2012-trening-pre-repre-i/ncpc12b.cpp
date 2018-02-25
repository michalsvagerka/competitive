#include "../../../l/lib.h"
#include "../../../l/fenwick.h"

class ncpc12b {
public:
    int N;
    ll inversions(const vector<int> &A) {
        Fenwick<int> F(N, 0);
        ll ans = 0;
        for (int a:A) {
            ans += F.range(a, N-1);
            F.add(a-1, 1);
        }
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        vector<int> A(N), B(N);
        cin >> A >> B;
        if ((inversions(A) - inversions(B)) % 2 == 0) {
            cout << "Possible\n";
        } else {
            cout << "Impossible\n";
        }
    }
};
