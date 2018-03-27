#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<bool> Q(1001);
        for (int i = 0; i < K; ++i) {
            int c; cin >> c;
            Q[c] = true;
        }

        vector<int> Z;
        for (int i = 0; i <= 1000; ++i) {
            if (Q[i]) Z.push_back(i);
        }

        bitset<2001> R; R[0] = true;
        for (int i = 1; i <= 3000; ++i) {
            bitset<2001> T;
            for (int z:Z) {
                T |= R << z;
            }
            T >>= N;

            swap(R,T);
            if (R[0]) {
                cout << i << endl;
                return;
            }
        }
        cout << -1 << endl;
    }
};
