#include "../l/lib.h"

class rutina1 {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        map<int, vector<int>> B;
        for (int i = 0; i < N; ++i) {
            B[A[i]].push_back(i);
        }
        vector<ll> Ans(N);
        for (int i = 0; i < N; ++i) {
            Ans[i] = (N-i)*ll(i+1);
        }

        vector<ll> C(N+1, 0);
        for (auto b: B) {
            int s = b.y.size();
            for (int i = 0; i < s-1; ++i) {
                int dist = b.y[i+1]-b.y[i];
                C[dist]++;
                C[b.y[i+1]+1]--;
                C[N-1-b.y[i]+1]--;
            }
        }

        for (int i = 1; i <= N; ++i) C[i] += C[i-1];
        for (int i = 1; i <= N; ++i) C[i] += C[i-1];
        for (int i = 0; i < N; ++i) Ans[i] -= C[i];
        cout << Ans;

//        vector<int> Ans2(N);
//        for (int i = 0; i < N; ++i) {
//            map<int, int> M;
//            int cnt = 0;
//            for (int j = 0; j < i; ++j) { cnt += !M[A[j]]++; }
//            for (int j = i; j < N; ++j) {
//                cnt += !M[A[j]]++;
//                Ans2[i] += cnt;
//                cnt -= !--M[A[j-i]];
//            }
//        }
//        cout << Ans2;
    }
};
