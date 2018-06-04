#include "../../../l/lib.h"
// #include "../l/mod.h"

class insomnia {
public:
    void solve(istream& cin, ostream& cout) {
        int K,L,M,N,D;
        cin >> K >> L >> M >> N >> D;
        vector<bool> E(D+1, false);
        for (int i = 0; i <= D; i+=K) E[i] = true;
        for (int i = 0; i <= D; i+=L) E[i] = true;
        for (int i = 0; i <= D; i+=M) E[i] = true;
        for (int i = 0; i <= D; i+=N) E[i] = true;
        cout << D-count(E.begin(),E.end(),false) << endl;
    }
};
