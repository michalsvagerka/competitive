#include "../l/lib.h"
// #include "../l/mod.h"

class DKThK {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> X(N); cin >> X;
    vector<pii> Y;
    for (int i = 0; i < N; ++i) Y.push_back({X[i]-1,i+1});
    sort(Y.begin(),Y.end());
    vector<int> A(N*N, 0);
    int j = 0;
    for (pii y: Y) {
        for (int k = 0; k < y.y-1; ++k) {
            while (j < N*N && A[j] != 0) ++j;
            A[j++] = y.y;
        }
        if (A[y.x] != 0) {
            cout << "No\n";
            return;
        }
        A[y.x] = y.y;
    }
    
    for (pii y: Y) {
        for (int k = y.y; k < N; ++k) {
            while (j < N*N && A[j] != 0) ++j;
            A[j++] = y.y;
        }
    }
    
    vector<int> Cnt(N, 0), Got(N, -1);
    for (int i = 0; i < N*N; ++i) {
        if (++Cnt[A[i]-1] == A[i]) Got[A[i]-1] = i+1;
    }
    
    if (Got == X) {
        cout << "Yes\n";
        cout << A;
    } else {
        cout << "No\n";
    }
}
};
