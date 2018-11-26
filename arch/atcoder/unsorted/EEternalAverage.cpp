#include "../l/lib.h"
#include "../l/mod.h"

class EEternalAverage {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, K;
        cin >> N >> M >> K;

        /* Find trees in canonical form:
         *  - have <= N zeros and <= M ones, and at least one of each.
         *  - on each level, there is at most one node that propagates to the next level
         *  - the number of missing zeros (up to N), resp. missing ones (up to M) is divisible by K-1
         *  - on the last level, there are some zeros and some ones
         *
         *  Basically, doing this means that on each level, we sort the values from left to right,
         *  i.e. first come the zeros, then possibly the node to lower level, and then all ones.
         *  There are no nodes which have all zeros or all ones (since we can exchange such node with a
         *  leaf containing either 0 or 1, saving K-1 zeros (or ones).
         *
         *  Once we have such tree, we can put the rest of the zeros under any zero,
         *  and the rest of the ones under any one, and we're done. */

        if (M > N) swap(N, M);

        vector2<FieldMod> D((N+M-1)/(K-1)+1, M+2, 0); // remaining values (in multiples of K-1) x remaining ones
        vector<FieldMod> W(M+2, 0);
        for (int j = 0; j < M; j += K-1) W[j+1] = 1;
        for (int j = 0; j <= M; ++j) W[j+1] += W[j];

        for (int vals = 1; vals <= (N+M-1)/(K-1); vals++) {
            for (int ones = max(0, vals*(K-1) - N + 1); ones <= M; ++ones) {
                int lo = max(0, ones - (K - 1));
                int hi = min(1 + (vals-1)*(K-1), ones);

                D[vals][ones+1] +=
                        // we continue to next layer
                        (D[vals-1][hi+1] - D[vals-1][lo])
                        // we fill the layer
                        + (W[hi] - W[lo]);
            }

            for (int i = 0; i <= M; ++i) D[vals][i+1] += D[vals][i];
        }

        cout << D[(N+M-1)/(K-1)][M+1] - D[(N+M-1)/(K-1)][M] << '\n';
    }
};
