#include "../l/lib.h"
 #include "../l/mod.h"

class B {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;

    auto F = FieldMod::fact(N);
    FieldMod ans = 0;

    vector<FieldMod> PS(N+1,0);
    for (int i = 1; i <= N; ++i) {
        PS[i] = PS[i-1] + (FieldMod{1} / FieldMod{i});
    }
    for (int i = 0; i < N; ++i) {
        FieldMod cur = 1;
        cur += PS[i+1]-1;
        cur += PS[N-i]-1;
        ans += cur * A[i];
    }
    cout << ans * F[N] << endl;
}
};
