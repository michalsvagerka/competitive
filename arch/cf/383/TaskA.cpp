#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N);
    vector<bool> C(N, false);
    cin >> A;
    for (int &a:A) --a;
    for (int a:A) C[a] = true;
    if (count(C.begin(),C.end(),false)) {
        cout << "-1\n";
        return;
    }

    ll ans = 1;
    for (int i = 0; i < N; ++i) {
        int j = A[i], k = 1;
        while (j != i) {
            k++;
            j = A[j];
        }

        if (k%2 == 0) k /= 2;
        ans = ans * k / gcd(ans, (ll)k);
    }

    cout << ans << endl;

}
};
