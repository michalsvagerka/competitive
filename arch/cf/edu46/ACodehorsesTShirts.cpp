#include "../../../l/lib.h"

class ACodehorsesTShirts {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> S(N), T(N);
        cin >> S >> T;
        map<string, int> A;
        for (string s: S) A[s]++;
        for (string s: T) A[s]--;
        int ans = 0;
        for (auto a: A) ans += abs(a.y);
        cout << ans/2 << '\n';

    }
};
