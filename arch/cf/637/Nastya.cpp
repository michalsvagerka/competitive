#include "../l/lib.h"

class Nastya {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            vector<int> I(N);
            for (int i = 0; i < N; ++i) I[A[i]-1] = i;
            set<int> Av;
            for (int i = 0; i < N; ++i) Av.insert(i);
            set<pii> X;
            for (int i = 0; i < N; ++i) X.insert({1,i});
            bool ok = true;
            auto dist = [&](int j) {
                auto it = Av.find(j);
                if (it == Av.begin()) return j+1;
                else return j-*prev(it);
            };
            for (int i = 0; i < N; ++i) {
                int mx = X.rbegin()->x;
                int pos = I[i];
                int val = dist(pos);
                ok &= mx == val;
                auto it = next(Av.find(pos));
                if (it != Av.end()) {
                    int next = *it;
                    X.erase({dist(next),next});
                    X.erase({dist(pos), pos});
                    Av.erase(pos);
                    X.insert({dist(next),next});
                } else {
                    X.erase({dist(pos), pos});
                    Av.erase(pos);
                }
            }
            cout << (ok ? "Yes" : "No") << '\n';
        }
    }
};
