#include "../l/lib.h"
// #include "../l/mod.h"

class TaskF {
public:
void solve(istream& cin, ostream& cout) {
    vector<int> S(3e5+1, 0);
    for (int j = 2; j <= 3e5; ++j) {
        if (S[j] == 0) for (int i = j; i <= 3e5; i += j) S[i] = j;
    }

    int N; cin >> N;
    vector<int> A(N); cin >> A;
    sort(A.begin(),A.end());
    A.erase(unique(A.begin(), A.end()),A.end());
    if (A[0] == 1) { cout << 1 << endl; return; }
    N = A.size();

    int g = A[0];
    for (int i = 1; i < N; ++i) g = gcd(g, A[i]);
    if (g != 1) { cout << -1 << endl; return; }

    int ans = 10;

    vector<int> Div(3e5+1, 0), R(128), Q(128);
    for (int i = 0; i < N; ++i) {
        int g = A[i];
        vector<int> P;
        while (g != 1) {
            int d = S[g];
            P.push_back(d);
            while (g % d == 0) g /= d;
        }
        
        vector<int> Z{1};
        for (int p: P) {
            vector<int> ZZ;
            for (int z: Z) {
                ZZ.push_back(z);
                ZZ.push_back(z * p);
            }
            swap(ZZ, Z);
        }

        int M = Z.size();
        fill(R.begin(),R.begin()+M,0);
        fill(Q.begin(),Q.begin()+M-1,20);
        Q[M-1] = 1;

        for (int i = 0; i < M; ++i) {
            Div[Z[i]]++;
            for (int j = 0; j < M; ++j) {
                if ((i & j) == j) {
                    R[j] += __builtin_popcount(i ^ j) % 2 == 1 ? -Div[Z[i]] : Div[Z[i]];
                }
            }
        }

        if (R[0]) { ans = 2; break; }

        for (int i = 0; i < M; ++i) {
            if (R[i]) {
                for (int j = 0; j < M; ++j) {
                    int g = i & j;
                    Q[g] = min(Q[g], Q[j] + 1);
                }
            }
        }

        ans = min(ans, Q[0]);
    }
    
    cout << ans << endl;
}
};
