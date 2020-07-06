#include "../l/lib.h"

class CReorderTheArray {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        map<int, int> C;
        for (int a: A) C[a]++;
        int mx = 0;
        for (pii c: C) mx = max(mx, c.y);
        cout << N-mx << '\n';
    }
};
