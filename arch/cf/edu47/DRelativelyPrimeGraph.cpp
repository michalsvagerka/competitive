#include "../l/lib.h"

class DRelativelyPrimeGraph {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        if (M < N-1) {
            cout << "Impossible\n";
            return;
        }

        vector<pii> X;
        for (int i = 2; i <= N; ++i) {
            X.push_back({1,i});
        }

        if (X.size() == M) {
            cout << "Possible\n";
            for (pii x: X) cout << x << '\n';
            return;
        }
        for (int i = 2; i <= N; ++i) {
            for (int j = i+1; j <= N; ++j) {

                if (gcd(i,j) == 1) {
                    X.push_back({i,j});
                    if (X.size() == M) {
                        cout << "Possible\n";
                        for (pii x: X) cout << x << '\n';
                        return;
                    }
                }

            }
        }

        cout << "Impossible\n";

    }
};
