#include "../l/lib.h"

class AMessy {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, K; cin >> N >> K;
            string S; cin >> S;
            set<int> O, C;
            for (int i = 0; i < N; ++i) {
                (S[i]=='('?O:C).insert(i);
            }
            vector<pii> Ans;
            auto putO = [&](int p) {
                if (*O.begin() != p) {
                    Ans.push_back({p, *O.begin()});
                    C.erase(p);
                    C.insert(*O.begin());
                }
                O.erase(*O.begin());
            };
            auto putC = [&](int p) {
                if (*C.begin() != p) {
                    Ans.push_back({p, *C.begin()});
                    O.erase(p);
                    O.insert(*C.begin());
                }
                C.erase(*C.begin());
            };
            
            for (int j = 0; j < K-1; ++j) {
                putO(2*j);
                putC(2*j+1);
            }
            
            for (int j = 0; j < (N/2)-(K-1); ++j) {
                putO(2*(K-1) + j);
            }
            cout << Ans.size() << '\n';
            for (pii a: Ans) {
                cout << a.x+1 << ' ' << a.y+1 << '\n';
            }
        }
    }
};
