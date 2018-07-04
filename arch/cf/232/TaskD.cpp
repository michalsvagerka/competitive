#include "../l/lib.h"
#include <numeric>
 #include "../l/mod.h"
#include "../l/fenwick.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    for (int&a:A) --a;

    auto F = FieldMod::fact(N+1);

    FieldMod ans = 0;

    Fenwick<int> H(N, 0);
    for (int i = 0; i < N; ++i) H.add(i,1);

    vector<bool> Z(N, true);
    FieldMod pref = 0;
    for (int i = 0; i < N; ++i) {
        int cnt = H.range(0, A[i]-1);
        ans += F[N-i-1] * (2 * (cnt-1) + 4 * pref + FieldMod{N-i-1} * (N-i-2)) * cnt / 4;
        pref += cnt;
        H.add(A[i], -1);
        Z[A[i]] = false;
    }

    cout << ans + pref << endl;

//    vector<int> B(N);
//    iota(B.begin(),B.end(),1);
//    FieldMod ans = 0;
//    do {
//        for (int i = 0; i < N; ++i)
//            for (int j = i+1; j < N; ++j)
//                ans += B[j] < B[i];
//
//        if (A == B) break;
//    } while (next_permutation(B.begin(),B.end()));

}
};
