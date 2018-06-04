#include "../l/lib.h"
// #include "../l/mod.h"

class circles {
public:
    void solve(istream& cin, ostream& cout) {
        int W, H, N; cin >> W >> H >> N;
        vector<int> X(N), Y(N), R(N);
        for (int i = 0; i < N; ++i) { cin >> X[i] >> Y[i] >> R[i]; }

        int ans = 0;
        for (int x = 0; x < W; ++x) {
            map<int, int> E;
            for (int i = 0; i < N; ++i) {
                if (abs(X[i]-x) > R[i]) continue;
                int len = bsh(0, 100000, [&](int y) { return ll(X[i]-x)*(X[i]-x)+ll(y)*y <= ll(R[i])*R[i]; });
                int y1 = Y[i] - len;
                int y2 = Y[i] + len;
                E[y1]++;
                E[y2+1]--;
            }
            int cnt = 0, last = -100000;
            for (auto&e:E) {
                if (cnt != 0 && last < H && e.x >= 0) {
                    ans += min(e.x, H) - max(last, 0);
                }

                last = e.x;
                cnt += e.y;
            }

        }
        cout << W*H-ans << endl;

    }
};
