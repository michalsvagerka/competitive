#include "../../../l/lib.h"
// #include "../l/mod.h"

class vosky {
public:
    int read(istream&cin) {
        double Z;
        cin >> Z;
        return int(round(Z*1000000));
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;

        vector<int> T(N);
        for (int i = 0; i < N; ++i) T[i] = read(cin);
        sort(T.begin(),T.end());

        int M; cin >> M;
        vector<pii> W(M);
        for (int j = 0; j < M; ++j) {
            W[j].y = read(cin);
            W[j].x = read(cin);
        }
        sort(W.begin(),W.end());
        reverse(W.begin(),W.end());
        vector<int> S{30000000};
        for (pii &v:W) {
            int s = bsl(0, int(S.size())-1, [&](int k) { return S[k] <= v.x; });
            if (s == -1) break;

            if (s == S.size()-1) {
                S.push_back(v.y);
            } else {
                S[s+1] = min(S[s+1], v.y);
            }
        }

        if (T[0] < S.back()) {
            cout << -1 << endl;
        } else {
            ll ans = 0;
            int s = S.size()-1;
            for (int t:T) {
                while (s > 0 && S[s-1] <= t) --s;
                ans += s;
            }
            cout << ans << endl;
        }

    }
};
