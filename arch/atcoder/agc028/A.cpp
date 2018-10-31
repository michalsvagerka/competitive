#include "../l/lib.h"
// #include "../l/mod.h"

class A {
public:
void solve(istream& cin, ostream& cout) {
    ll N, M; string S, T;
    cin >> N >> M >> S >> T;
    ll G = gcd(N, M);
    map<int, char> Z;
    for (int i = 0; i < N; ++i) {
        Z[i * M / G] = S[i];
    }

    for (int j = 0; j < M; ++j) {
        auto it = Z.find(j * N / G);
        if (it != Z.end() && it->y != T[j]) {
            cout << "-1\n";
            return;
        }
    }

    cout << N * M / G << endl;
}
};
