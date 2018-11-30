#include "../l/lib.h"
// #include "../l/mod.h"

class AAirportBus {
public:
    void solve(istream& cin, ostream& cout) {
        int N, C, K; cin >> N >> C >> K;
        vector<int> T(N); cin >> T;
        sort(T.begin(),T.end());
        int a = 1, j = 0;
        for (int i = 0; i < N; ++i) {
            if (T[i] > T[j] + K || i-j >= C) {
                a++;
                j = i;
            }
        }
        cout << a << endl;
    }
};
