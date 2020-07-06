#include "../l/lib.h"
#include "../l/geo.h"

class covidstand {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<Point<ll>> A(N);
        for (int i = 0; i < N; ++i) cin >> A[i].x;
        for (int i = 0; i < N; ++i) cin >> A[i].y;

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                for (int k = j+1; k < N; ++k) {
                    if (i == k) continue;
                    if (!rightAngle(A[i], A[j], A[k])) continue;
                    for (int a = 0; a < N; ++a) {
                        if (a == i || a == j || a == k) continue;
                        for (int b = a+1; b < N; ++b) {
                            if (b == i || b == j || b == k) continue;
                            for (int c = 0; c < N; ++c) {
                                if (c == i || c == j || c == k || c == a || c == b) continue;
                                if (!rightAngle(A[b], A[a], A[c])) continue;
                                if (A[b].squaredDistance(A[a]) >= A[b].squaredDistance(A[c])) continue;

                                for (int d = 0; d < N; ++d) {
                                    if (d == i || d == j || d == k || d == a || d == b || d == c) continue;
                                    if (!rightAngle(A[c], A[b], A[d]) || !rightAngle(A[d], A[a], A[c]) || !rightAngle(A[a], A[d], A[b])) continue;
                                    ans++;
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << ans*8 << '\n';
    }
};
