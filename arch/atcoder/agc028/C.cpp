#include "../l/lib.h"
// #include "../l/mod.h"

class C {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N), B(N);
    ll sumA = 0, sumB = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
        sumA += A[i];
        sumB += B[i];
    }

    ll ans = min(sumA, sumB);

    vector<pii> C(2*N);
    for (int i = 0; i < N; ++i) {
        C[2*i] = {A[i], i};
        C[2*i+1] = {B[i], i};
    }
    sort(C.begin(), C.end());
    vector<bool> Used(N, false);
    int both = 0, unused = N;
    ll cur = 0;
    for (int j = 0; j < N-1; ++j) {
        pii c = C[j];
        cur += c.x; 
        if (Used[c.y]) { 
            both++;
        } else {
            unused--;
            Used[c.y] = true;    
        }
    }
    
    if (unused == 1) {
        if (Used[C[N-1].y]) ans = min(ans, cur + C[N-1].x);
        if (Used[C[N].y]) ans = min(ans, cur + C[N].x);
        if (Used[C[N+1].y]) ans = min(ans, cur + C[N+1].x);
        if (!Used[C[N-1].y]) ans = min(ans, cur + A[C[N-1].y] + B[C[N-1].y] - C[N-2].x);
    } else {
        ans = min(ans, cur + C[N-1].x);
    }

    cout << ans << endl;

}
};
