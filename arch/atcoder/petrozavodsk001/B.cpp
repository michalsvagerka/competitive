#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N);
        vector<int> B(N);
        cin >> A >> B;

        ll totA = 0, totB = 0;
        for (int a:A) totA += a;
        for (int b:B) totB += b;

        ll minA = 0, minB = 0;
        for (int i = 0; i < N; ++i) {
            if (A[i] < B[i]) {
                minA += (B[i]-A[i]+1)/2;
                minB += (B[i]-A[i])%2;
            } else {
                minB += A[i]-B[i];
            }
        }

//        cerr << minA << ' ' << minB << ' ' << totB << ' ' << totA << endl;
        if (max(minA, minB) > totB - totA) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
        }
    }
};
