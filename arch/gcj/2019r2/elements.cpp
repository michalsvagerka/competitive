#include "../l/lib.h"

class elements {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<pii> A(N); cin >> A;

            set<pii> Q;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (A[i].x > A[j].x && A[i].y < A[j].y) {
                        int dx = A[i].x - A[j].x;
                        int dy = A[j].y - A[i].y;
                        int g = gcd(dx, dy);
                        dx /= g;
                        dy /= g;
                        Q.insert({dx,dy});
                    }
                }
            }
            cout << "Case #" << t+1 << ": ";
            cout << Q.size() + 1;
            cout << endl;
        }
    }
};
