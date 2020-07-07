#include "../../../l/lib.h"

class AIfAtFirstYouDontSucceed {
public:
    void solve(istream& cin, ostream& cout) {
        int A,B,C,N; cin >> A >> B >> C >> N;
        int ans = N - A - B + C;
        if (ans <= 0 || C > A || C > B || A >= N || B >= N || C >= N) cout << "-1\n";
        else cout << ans << '\n';
    }
};
