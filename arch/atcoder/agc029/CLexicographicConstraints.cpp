#include "../l/lib.h"
// #include "../l/mod.h"

class CLexicographicConstraints {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        bool ok = true;
        for (int i = 1; i < N; ++i) ok &= A[i] > A[i-1];
        if (ok) {
            cout << 1 << endl;
            return;
        }
        
        A.push_back(0);
        cout << bsl(2, N, [&](int x) {
            vector<pii> Q;
            Q.push_back({0,0});
            for (int a: A) {
                if (Q.back().x == a) {
                    Q.back().y++;
                } else if (Q.back().x > a) {
                    while (Q.back().x > a) {
                        int z = Q.back().x;
                        int y = Q.back().y;
                        Q.pop_back();
                        int to = a;
                        if (Q.back().x >= a) to = Q.back().x;
                        while (y && z != to) {
                            y /= x;
                            z--;
                        }
                        if (to == a) Q.push_back({a, y+1}); else Q.back().y += y;
                    }
                } else {
                    Q.push_back({a, 0});
                }
            }

            return Q.back().y == 1;
        }) << endl;
    }
};
