#include "../l/lib.h"

class DNumberDiscovery {
public:
    ll K, N;

    // the missing value in super block x is the sum of block x
    ll findSumOfBlock(ll blockId) {
        if (blockId == 0) {
            return K*(K+1)/2;
        } else {
            ll missingHere = findSumOfBlock(blockId / K);
            ll firstNumInBlock = blockId * K + blockId / K + 1;
            return (2 * firstNumInBlock + K - 1) * K / 2 + max(0LL, min(K, firstNumInBlock + K - missingHere));
        }
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> N >> K;
            ll superBlockId = (N - 1) / (K * K + 1);
            auto m = findSumOfBlock(superBlockId);
            ll result;
            if (m == N) {
                result = (superBlockId+1)*(K+1);
            } else {
                N -= (N > m) + superBlockId;
                result = N + (N-1) / K;
            }
            cout << result << '\n';
        }
    }
};
