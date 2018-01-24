#include "../l/lib.h"
// #include "../l/mod.h"

constexpr ui maxN = 1<<19;

class billboard {
public:
    void solve(istream& cin, ostream& cout) {
        ui H,W,N; cin >> H >> W >> N;
        vector<ui> T(2*maxN, W);
        for (ui i = 0; i < N; ++i) {
            ui w; cin >> w;
            if (w > W) { cout << "-1\n"; continue; }
            ui j = 1;
            while (j < maxN) j = 2 * j + (T[2 * j] < w);
            if (j >= maxN + H)  { cout << "-1\n"; continue; }
            cout << j - maxN + 1 << '\n';
            T[j] -= w;
            while (j != 1) {
                T[j >> 1] = max(T[j], T[j ^ 1]);
                j >>= 1;
            }
        }
    }
};
