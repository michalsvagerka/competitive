#include "../l/lib.h"

class CTreeDiameter {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            int ans = 0;
            for (int b = 1; ; b*=2) {
                vector<int> A, B;
                for (int i = 0; i < N; ++i) {
                    if (i&b) A.push_back(i+1);
                    else B.push_back(i+1);
                }
                if (A.empty() || B.empty()) break;

                cout << A.size() << ' ' << B.size();
                for (int a: A) cout << ' ' << a;
                for (int b: B) cout << ' ' << b;
                cout << endl;

                int r; cin >> r;
                if (r == -1) return;
                ans = max(ans, r);
            }

            cout << "-1 " << ans << endl;
        }
    }
};
