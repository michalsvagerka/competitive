#include "../l/lib.h"

class AValeriyAndDeque {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        deque<int> B;
        for (int i = 0; i < N; ++i) {
            int b; cin >> b;
            B.push_back(b);
        }

        vector<pii> Ans;
        for (int i = 0; i < 2*N; ++i) {
            int a = B.front(); B.pop_front();
            int b = B.front(); B.pop_front();
            B.push_back(min(a,b));
            B.push_front(max(a,b));
            Ans.push_back({a,b});
        }

        for (int q = 0; q < Q; ++q) {
            ll x; cin >> x; --x;
            if (x < 2*N) {
                cout << Ans[x] << '\n';
            } else {
                ll y = x/(N-1)-3;
                x -= y*(N-1);
                while (x >= 2*N) {
                    x -= N-1;
                }
                cout << Ans[x] << '\n';
            }
        }
    }
};
