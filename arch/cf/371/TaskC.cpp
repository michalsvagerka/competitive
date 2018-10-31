#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    vector<pii> B(N);
    for (int i = 0; i < N; ++i) {
        A[i] -= i;
        B[i] = {A[i],i};
    }
    sort(B.begin(),B.end());
    
    vector2<ll> C(N, N, 0);
    for (int i = 0; i < N; ++i) {
        C[0][i] = abs(A[i]-A[0]);
    }

    for (int j = 1; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            C[j][i] = C[j-1][i] + abs(A[i]-A[j]);
        }
        
        ll best = 1e18;
        for (pii b: B) {
            if (b.y < j) {
                best = min(best, C[j-1][b.y]);
            } else {
                C[j][b.y] = min(C[j][b.y], best + abs(A[b.y] - A[j]));
            }
        } 
    }
    
    cout << *min_element(C[N-1].begin(),C[N-1].end()) << endl;
}
};
