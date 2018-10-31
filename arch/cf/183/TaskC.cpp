#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    vector<int> A(N); cin >> A;
    sort(A.begin(),A.end());

    vector<int> D(1e6+1, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            D[A[j]-A[i]]++;
        }
    }

    vector<int> E(1e6+1, 0);
    for (int i = 1; i <= 1e6; ++i) {
        for (int j = i; j <= 1e6; j += i) {
            E[i] += D[j];
        }
    }

    for (int i = N-K; i <= 1e6; ++i) {
        if (E[i] <= K*(K+1)/2) {
            unordered_set<int> S;
            int c = 0;
            for (int a:A) {
                int b = a%i;
                if (!S.insert(b).y && ++c > K) break;
            }
            if (c <= K) {
                cout << i << endl;
                return;
            }
        }
    }
    
    cout << int(1e6+1) << '\n';
}
};
