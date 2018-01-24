#include "../l/lib.h"
// #include "../l/mod.h"

class mikbanan {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        for (int i = 0; i < N; ++i) {
            string S; cin >> S;
            int H,W,z; cin >> H >> W >> z;
            int B=0,M=0;
            for (int j = 0; j < H*W; ++j) {
                int r,g,b; cin >> r >> g >> b;
                if (r > 200 && g > 180 && b < 100) ++B;
                if (r > 200 && g < 150 && b < 100) ++M;
            }

            if (B<M) cout << "mandarinka\n"; else cout << "banan\n";
        }
    }
};
