#include "../l/lib.h"
// #include "../l/mod.h"

class A {
public:
void solve(istream& cin, ostream& cout) {
    int N, X; cin >> N >> X;
    vector<int> B(N); cin >> B;
    sort(B.begin(),B.end());
    ll sum = 0;
    for (int b:B) sum += b;
    if (sum == X) {
        cout << N << endl;
    } else if (sum < X) {
        cout << N-1 << endl;
    } else {
        for (int i = 0; i < N; ++i) {
            X -= B[i];
            if (X < 0) {
                cout << i << endl;
                return;
            }
        }
    }
}
};


//class B {
//public:
//    void solve(istream& cin, ostream& cout) {
//        ll N, P; cin >> N >> P;
//        vector<ll> X(N); cin >> X;
//        vector<ll> F(N+5, 0), G(N+5, 0);
//        for (int i = 0; i < N; ++i) {
//            F[i+1] = F[i] + X[i];
//            G[i+1] = G[i] + ll(i) * X[i];
//        }
//
//
//
//        vector<ll> D(N+5, 0);
//        Envelope::Lower<ll> E;
//        E.insert_line(0,0);
//        for (int i = 0; i < N; ++i) {
//            D[i+1] = E[i];
//            D[i+1] += X[i] + P + 3 * F[i] + 4 * X[i] - 2 * G[i] + 2 * F[i] * i;
//            D[i+1] += (G[i+2] * 2 - 3 * F[i+1] - 2 * ll(i+1) * X[i+1]);
//            E.insert_line(- 2 * F[i+1], D[i+1]);
//        }
//
////    cout << D;
//        cout << D[N] + ll(N)*P - (G[N+1] * 2 - 3 * F[N] - 2LL * N * X[N]) << endl;
//    }
//};