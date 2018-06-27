#include "../../../l/lib.h"
 #include "../../../l/runtimemod.h"
#include "../../../l/util.h"

class clues {
public:
    void solve(istream& cin, ostream& cout) {
        ui N, M, K; cin >> N >> M >> K;
        UnionFind UF(N);
        for (int i = 0; i < M; ++i) {
            int a,b; cin >> a >> b;
            --a; --b;
            UF.unite(a,b);
        }

        RField RF{1, K};
        int c = 0;
        for (int j = 0; j < N; ++j) {
            if (UF.P[j] < 0) {
                RF *= {ui(-UF.P[j]),K};
                if (++c > 2) RF *= {N, K};
            }
        }
        cout << (c==1 ? 1%K : RF)  << endl;
    }
};
