#include "../l/lib.h"

class rover {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A;
        ll X = 1, Y = 1, tot = 0;
        for (int i = 0; i < N; ++i) {
            char c;
            int lo, hi;
            cin >> c >> lo >> hi;
            switch (c) {
                case '?':
                    A.push_back(hi);
                    tot += hi;
                    break;
                case 'N':
                case 'S':
                    X += hi - lo;
                    break;
                case 'W':
                case 'E':
                    Y += hi - lo;
                    break;
            }
        }

        vector<int> G{0};
        int M = A.size();
        for (int j = 0; j < M; ++j) {
            vector<int> H;
            for (int g: G) H.push_back(g + A[j]);
            vector<int> S(H.size() + G.size());
            merge(G.begin(),G.end(),H.begin(),H.end(),S.begin());
            swap(G, S);
        }

        ll ans = 0;
        for (int i = 1; i < (1<<M); ++i) {
            ans += G[i-1] * ll(G[i] - G[i-1]);
        }
        ans *= 4;
        ans += X * Y + 2 * tot * (X + Y);
        cout << ans << endl;
    }
};
