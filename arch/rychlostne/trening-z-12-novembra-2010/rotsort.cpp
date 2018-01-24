#include "../l/lib.h"
// #include "../l/mod.h"

class rotsort {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        for (int i = 0; i < N; ++i) {
            pii m = {A[i],i};
            for (int j = i+1; j < N; ++j) m = min(m, {A[j],j});
            if (m.y != i) cout << "R " << i+1 << ' ' << m.y+1 << '\n';
            for (int j = m.y; j > i; --j) swap(A[j],A[j-1]);
        }
    }
};
