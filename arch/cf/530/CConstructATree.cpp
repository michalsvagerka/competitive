#include "../l/lib.h"
// #include "../l/mod.h"

class CConstructATree {
public:
    int N;
    ll S;

    vector<int> findDepthSeq(int branchingFactor) {
        ll left = S - 1;
        vector<int> D{1};
        ll prev = 1;
        ll cur = 0;
        int add = N-1;
        for (int d = 2; add > 0; ) {
            if (cur == prev * branchingFactor || ll(d+d+add-1)*add/2 < left) {
                if (cur == 0) return {};
                prev = cur;
                cur = 0;
                d++;
            }

            D.push_back(d);
            cur++;
            left -= d;
            --add;
            if (left < 0) return {};
        }

        return D;
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N >> S;
        if (ll(N)*ll(N+1)/2 < S || 2*N-1 > S) {
            cout << "No\n";
        } else {
            int s = bsl(1, N, [&](int x) {
                return !findDepthSeq(x).empty();
            });


            auto D = findDepthSeq(s);
            int prevLo = 0, curStart = 1;
            vector<int> P;
            for (int i = 1; i < N; ++i) {
                P.push_back(1 + prevLo + (i-curStart)/s);
                if (i != N-1 && D[i+1] != D[i]) {
                    prevLo = curStart;
                    curStart = i+1;
                }
            }

            cout << "Yes\n" << P;
        }
    }
};
