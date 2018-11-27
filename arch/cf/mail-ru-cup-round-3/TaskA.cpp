#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    map<int, int> C;
    for (int i = 0; i < N; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int l; cin >> l;
            C[l]++;
        }
    }

    vector<int> S;
    for (pii c: C) if (c.y == N) S.push_back(c.x);
    cout << S;
}
};
