#include "../l/lib.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    int g = A[0];
    for (int &a:A) g = gcd(g, a);
    for (int &a:A) a /= g;

    constexpr int M = 15000001;
    vector<int> S(M, 0);
    vector<int> P;
    for (int i = 2; i < M; ++i) {
        if (S[i] == 0) {
            S[i] = i;
            P.push_back(i);
        }
        for (int j=0; j<P.size() && P[j]<=S[i] && i*P[j]<M; ++j) {
            S[i * P[j]] = P[j];
        }
    }
    1342823773
    unordered_map<int, int> R;
    for (int a:A) {
        while (a != 1) {
            int p = S[a];
            while (a%p == 0) {
                a /= p;
            }
            R[p] += 1;
        }
    }

    int ans = N+1;
    for (pii r:R) {
        ans = min(ans, N-r.y);
    }
    cout << (ans==N+1?-1:ans) << endl;
}
};
