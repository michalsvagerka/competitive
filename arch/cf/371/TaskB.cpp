#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<vector<int>> R(2);
    for (int i = 0; i < 2; ++i) {
        vector<int> C{1, 1, N, N};
        for (int c = 0; c < 4; ++c) {
            for (int s = 15; s >= 0; s--) {
                if (c >= 2) {
                    C[c] -= 1<<s;
                    if (C[c] < C[c-2]) {
                        C[c] += 1<<s;
                        continue;
                    }
                } else {
                    C[c] += 1 << s;
                    if (C[c] > N) {
                        C[c] -= 1<<s;
                        continue;
                    }
                }

                cout << "? " << C[0] << ' ' << C[1] << ' ' << C[2] << ' ' << C[3] << endl;
                int ans; cin >> ans;
                for (int j = 0; j < i; ++j) {
                    ans -= (R[j][0] >= C[0] && R[j][1] >= C[1] && R[j][2] <= C[2] && R[j][3] <= C[3]);
                }
                if (ans == 0) {
                    if (c >= 2) {
                        C[c] += 1<<s;
                    } else {
                        C[c] -= 1<<s;
                    }
                }
            }
        }

        R[i] = {C[0], C[1], C[2], C[3]};
    }

    cout << "!";
    for (auto&r:R[1]) cout << ' ' << r;
    for (auto&r:R[0]) cout << ' ' << r;
    cout << endl;
}
};
